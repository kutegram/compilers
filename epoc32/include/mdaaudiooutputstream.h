// MdaAudioOutputStream.h
//
// Copyright(c) Symbian Software Ltd 2002-2007. All rights reserved.
//

#ifndef __MDAAUDIOOUTPUTSTREAM_H
#define __MDAAUDIOOUTPUTSTREAM_H


#include <e32std.h>
#include <mmf/common/mmfbase.h>
#include <mmf/common/mmfstandardcustomcommands.h>
#include <mda/common/base.h>      
#include <mda/client/utility.h>
#include <mmf/common/mmfaudio.h>
#include <mmfclntutility.h>


/**
@publishedAll


An interface class that notifies the client of the progress of audio output streaming.

It must be implemented by users of the CMdaAudioOutputStream class.

An object that implements this interface is passed to CMdaAudioOutputStream::NewL().
*/
class MMdaAudioOutputStreamCallback 
	{
public:

	/**
	A callback function that is called when CMdaAudioOutputStream::Open() has completed, indicating that the
	audio output stream is ready for use.

	@param  aError
	        An error value which indicates if open was completed successfully. KErrNone if succeeded.
	*/
	virtual void MaoscOpenComplete(TInt aError) = 0;

	/**
	A callback function that is called when a descriptor has been copied to the lower layers of MMF. 

	It is also called when an error has occurred or when the client has stopped the stream playing before the descriptor 
	has been fully copied (by calling CMdaAudioOutputStream::Stop()).

	This function indicates to the client that it is safe to destroy the buffer passed to CMdaAudioOutputStream::WriteL(). 
	It can also be used to make the next call to WriteL().

	@param  aError
	        KErrNone if the copy succeeded, otherwise one of the system error codes. KErrAbort indicates that 
	        the client has stopped the stream playing before the descriptor has been copied.
	@param  aBuffer
	        A reference to the buffer that has been copied.
	*/
	virtual void MaoscBufferCopied(TInt aError, const TDesC8& aBuffer) = 0;

	/**
	A callback function that is called when playback terminates as a result of a CMdaAudioOutputStream::Stop().

	If the end of the sound data has been reached, the function returns KErrUnderFlow. If playback terminates for any 
	other reason, the function returns an appropriate error value.

	@param  aError
	        An error value which indicates play success or not. KErrNone if the close succeeded, otherwise one of the
	        system error codes.
	*/
	virtual void MaoscPlayComplete(TInt aError) = 0;
	};


class CMMFMdaAudioOutputStream;

/**
@publishedAll


The interface to an audio stream player passing raw audio data from specified buffers to the audio hardware.

This class enables MMF clients to:

Stream raw audio data to the audio hardware from specified buffers

Specify the priority of the audio stream in relation to other clients that may request to use the same audio hardware

Set the sample rate and the number of channels after successfully opening the stream. It is not possible to change these 
values once  streaming has started.

Change the volume and balance before or while the stream is open for writing. Volume and balance settings take effect immediately.

The API supports callbacks from the server to notify the client:

MaoscOpenComplete() will be called when the audio streaming object is open and ready to stream data back to the
audio hardware as a result of a previous call to Open().

MaoscBufferCopied()
Each time audio data has been successfully copied to the lower layers of the MMF as a result of a previous ReadL().

MaoscRecordComplete:
When the audio data stream has been closed as a result of a previous Stop().
*/
class CMdaAudioOutputStream : public CBase,
							  public MMMFClientUtility
	{
public:

	/**
	Allocates and constructs an audio stream player object.

	@param  aCallBack
	        A callback to notify the client when the sound device is open and ready to receive data, when 
	        each descriptor has been copied and when the stream is closed. The caller must create a 
	        callback class which implements this interface.
	@param  aServer
	        A pointer to a CMdaServer. CMdaServer is deprecated and as such this parameter is only provided 
	        for backward compatibility.

	@return A pointer to new audio stream player.
	*/
	IMPORT_C static CMdaAudioOutputStream* NewL(MMdaAudioOutputStreamCallback& aCallBack,
												CMdaServer* aServer = NULL);

	/**
	Constructs and initialises a new instance of an audio streaming object.

	The function leaves if the audio streaming object cannot be created.

	@param  aCallBack
	        A callback to notify the client when the sound device is open and ready to receive data, when each
	        descriptor has been copied and when the stream is closed. The caller must create a callback class
	        which implements this interface.
	@param  aPriority
	        This client's relative priority. This is a value between EMdaPriorityMin and EMdaPriorityMax and represents
	        a relative priority. A higher value indicates a more important request.
	@param  aPref
	        The required behaviour if a higher priority client takes over the sound output device.

	@return A pointer to CMdaAudioOutputStream.

	@capability MultimediaDD
	            A process requesting or using this method that has MultimediaDD capability will
				always have precedence over a process that does not have MultimediaDD.
	*/
	IMPORT_C static CMdaAudioOutputStream* NewL(MMdaAudioOutputStreamCallback& aCallBack,
												TInt aPriority,
												TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);


	/**
    Destructor.

	Frees all resources owned by the object prior to its destruction.
	*/
	~CMdaAudioOutputStream();

	/**
	Sets the sample rate and number of audio channels.

	@param  aSampleRate
	        The new sample rate. For possible values, see the TAudioCaps enum in class TMdaAudioDataSettings.
	@param  aChannels
	        The new number of channels. For possible values, see the TAudioCaps enum in class TMdaAudioDataSettings.
	
	*/
	virtual void SetAudioPropertiesL(TInt aSampleRate, TInt aChannels);

	/**
	Opens an output audio stream package.

	The MMdaAudioOutputStreamCallback::MaosOpenComplete() callback function is called when the stream has been 
	opened and is ready to receive audio data. If the open was unsuccessful, this is indicated by the aError 
	parameter of the callback.


	@param  aSettings
	        A pointer to a TMdaPackage object.
	
	*/
	virtual void Open(TMdaPackage* aSettings);

	/**
	Returns the maximum volume level.

	@return The maximum volume level supported by the sound device, as an integer.
	*/
	virtual TInt MaxVolume();

	/**
	Returns the current volume.

	@return The current volume as an integer.
	*/
	virtual TInt Volume();

	/**
	Sets the audio volume.

	Set the volume to zero for "sound off" or any other value between 1 and MaxVolume().

	@param  aNewVolume
	        A specified audio volume.

	*/
	virtual void SetVolume(const TInt aNewVolume);

	/**
	Sets the audio priority values.

	This function cannot be used while the stream object is open. It is intended for use before an Open() 
	is issued, or between a previous Stop() and a new Open().

	@param  aPriority
	        The priority level to apply, EMdaPriorityMin allows the client can be interrupted by any other client,
	        EMdaPriorityNormal allows the client is only interrupted by clients with a higher priority or
			EMdaPriorityMax allows the client cannot be interrupted by other clients.
	@param  aPref
	        A set of priority values that define the behaviour to be adopted by a client using a sound device if a 
	        higher priority client takes over that device.


	@capability MultimediaDD
	            A process requesting or using this method that has MultimediaDD capability will
				always have precedence over a process that does not have MultimediaDD.
	*/
	virtual void SetPriority(TInt aPriority, TMdaPriorityPreference aPref);
	
	/**
	Writes (plays) streaming raw audio data.

	This function is asynchronous. When aData has been received, the client is notified by a call to 
	MMdaAudioOutputStreamCallback::MaoscBufferCopied(). The client can call WriteL() again before this notification 
	takes place because the buffers are maintained in a client-side queue until they have been sent. An active object 
	performs the notification, and copies the next item in the queue to the server.
	MMdaAudioOutputStreamCallback::MaoscPlayComplete() is called when all descriptors have been sent.

	@param  aData
	        A reference to the stream data.

	*/
	virtual void WriteL(const TDesC8& aData);

	/**
	Stops writing data to a stream.

	*/
	virtual void Stop();

	/**
	Returns the current position within the data stream.

	@return The current position within the stream in microseconds.
	*/
	virtual const TTimeIntervalMicroSeconds& Position();

	/**
	Sets the audio balance.

	@param  aBalance
	        A specified balance volume. Default is KMMFBalanceCenter.

	*/
	IMPORT_C void SetBalanceL(TInt aBalance = KMMFBalanceCenter);
	
	/**
	Returns the current balance as an integer.

	@return The current balance value as integer.
	*/
	IMPORT_C TInt GetBalanceL() const;

	/**
	Returns the current number of bytes rendered by audio hardware.

	@return The current current number of bytes rendered by audio hardware as an integer.
	*/
	IMPORT_C TInt GetBytes();

	/**
    Sets the data type.  If the data type is not explicitly set it will assumed to be pcm16.
    If it is set then the hardware must support the data type being set otherwise the 
    function leaves with KErrNotSupported.
    
    @param	aAudioType The fourCC code used to specify the data type of the streamed audio

	@leave KErrNotSupported
	       Leaves with this for any unsuported data type.
	*/
    IMPORT_C void SetDataTypeL(TFourCC aAudioType);

	/**
	Returns the current data type.

	@return The ID of the data type.
	*/
	IMPORT_C TFourCC DataType() const;
	
	/**
	Registers the Event for Notification when resource is avaliable.
	@param	aCallback
	      	The audio outputstream observer interface..
	@param 	aNotificationEventUid
	 	The Event for which the client is registered.
	@param 	aNotificationRegistrationData
		Notification registration specific data.
	@return An error code indicating if the registration was successful. KErrNone on success, 
		otherwise another of the system-wide error codes.
	*/
	IMPORT_C TInt RegisterAudioResourceNotification(MMMFAudioResourceNotificationCallback& aCallback,TUid aNotificationEventUid,const TDesC8& aNotificationRegistrationData = KNullDesC8);
	
	/**
	Cancels the registered notification event.
	@param  aNotificationEventUid
		The Event to notify the client.
		
	@return An error code indicating if the registration was successful. KErrNone on success, 
		otherwise another of the system-wide error codes.
	*/
	IMPORT_C TInt CancelRegisterAudioResourceNotification(TUid aNotificationEventId);
    
    	/**
	Waits for the client to resume the play even after the default timer expires.
	@return An error code indicating if the registration was successful. KErrNone on success, 
		otherwise another of the system-wide error codes.
	*/
	IMPORT_C TInt WillResumePlay();
	
	/**
	Retrieves a custom interface to the underlying device.

	@param  aInterfaceId
	        The interface UID, defined with the custom interface.
	
	@return A pointer to the interface implementation, or NULL if the device does not
	        implement the interface requested. The return value must be cast to the
	        correct type by the user.
	*/
	IMPORT_C TAny* CustomInterface(TUid aInterfaceId);

private:
	CMdaAudioOutputStream();
private:
	/**
	This member is internal and not intended for use.
	*/
	CMMFMdaAudioOutputStream* iProperties;
	};

#endif
