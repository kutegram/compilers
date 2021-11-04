// MdaAudioTonePlayer.h
//
// Copyright (c) Symbian Software Ltd 2002 - 2007.  All rights reserved.
//

#ifndef __MDAAUDIOTONEPLAYER_H__
#define __MDAAUDIOTONEPLAYER_H__


#include <e32std.h>
#include <mmf/common/mmfbase.h>
#include <mmf/common/mmfstandardcustomcommands.h>
#include <mmfclntutility.h>

class CMdaServer;


/**
@publishedAll


The state of the audio tone utility.
*/
enum TMdaAudioToneUtilityState
	{
	/** The audio tone utility has not been prepared to play a tone.
	*/
	EMdaAudioToneUtilityNotReady=0,
	/** The audio tone utility has been prepared to play a tone and is ready.
	*/
	EMdaAudioToneUtilityPrepared,
	/** The audio tone utility is currently playing a tone.
	*/
	EMdaAudioToneUtilityPlaying
	};

const TInt KMdaInfiniteDurationDTMFToneOnLength = -1; 
const TInt KMdaAudioToneRepeatForever = -2;

/**
@publishedAll


An interface to a set of audio tone player callback functions.

The class is a mixin and is intended to be inherited by the client
class which is observing the audio tone playing operation. The
functions encapsulated by this class are called when specific events
occur in the process of preparing to play a tone and during the
playing of a tone. A reference to this object is passed as a
parameter when constructing an audio tone player utility, using the
CMdaAudioToneUtility interface.


*/
class MMdaAudioToneObserver
	{
public:

	/**
	Defines required client behaviour when an attempt to configure the
	audio tone player utility has completed, successfully or otherwise.

	@param     aError
	           KErrNone if successful. One of the system
	           wide error codes if the attempt failed. The possible
	           values depend on the EPOC platform.
	*/
	virtual void MatoPrepareComplete(TInt aError) = 0;

	/**
	Defines required client behaviour when the tone playing operation has
	completed, successfully or otherwise.

	@param     aError
	           KErrNone if successful. One of the system
	           wide error codes if the attempt failed. The possible
	           values depend on the EPOC platform.
	*/
	virtual void MatoPlayComplete(TInt aError) = 0;
	};


class CMMFMdaAudioToneUtility;

/**
@publishedAll


Generates tones on an audio capable EPOC device.

The class offers an interface for generating tones on all audio
capable EPOC devices.

To use the tone utility:

1. Create an instance by calling NewL().

2. Call the appropriate PrepareToPlay variant for the required tone type
and wait for the callback indicating success.

3. Call Play and either wait for the callback to indicate completion,
or call CancelPlay to end playback early.

4. Delete the instance.

It is possible to call Play before calling any PrepareToPlay variant. This
will result in a default fixed sequence tone being played.


*/
class CMdaAudioToneUtility : public CBase,
							 public MMMFClientUtility
	{
public:

	IMPORT_C static CMdaAudioToneUtility* NewL(MMdaAudioToneObserver& aObserver, CMdaServer* aServer = NULL);

	IMPORT_C static CMdaAudioToneUtility* NewL(MMdaAudioToneObserver& aObserver, CMdaServer* aServer,
											   TInt aPriority, 
											   TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);

	~CMdaAudioToneUtility();

	virtual TMdaAudioToneUtilityState State();

	virtual TInt MaxVolume();

	virtual TInt Volume();

	virtual void SetVolume(TInt aVolume);

	virtual void SetPriority(TInt aPriority, TMdaPriorityPreference aPref);

	virtual void SetDTMFLengths(TTimeIntervalMicroSeconds32 aToneLength,
								TTimeIntervalMicroSeconds32 aToneOffLength,
								TTimeIntervalMicroSeconds32 aPauseLength);

	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence);

	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration);

	virtual TInt FixedSequenceCount();

	virtual const TDesC& FixedSequenceName(TInt aSequenceNumber);

	virtual void PrepareToPlayTone(TInt aFrequency, const TTimeIntervalMicroSeconds& aDuration);

	virtual void PrepareToPlayDTMFString(const TDesC& aDTMF);

	virtual void PrepareToPlayDesSequence(const TDesC8& aSequence);

	virtual void PrepareToPlayFileSequence(const TDesC& aFileName);

	virtual void PrepareToPlayFixedSequence(TInt aSequenceNumber);

	virtual void CancelPrepare();

	virtual void Play();

	virtual void CancelPlay();

	IMPORT_C void SetBalanceL(TInt aBalance=KMMFBalanceCenter);

	IMPORT_C TInt GetBalanceL();

	IMPORT_C void PrepareToPlayDualTone(TInt aFrequencyOne, TInt aFrequencyTwo, const TTimeIntervalMicroSeconds& aDuration);
	
	IMPORT_C void PrepareToPlayFileSequence(RFile& aFile);
	
	IMPORT_C TAny* CustomInterface(TUid aInterfaceId);

protected:
	/**
	This member is internal and not intended for use.
	*/
	CMMFMdaAudioToneUtility* iProperties;
	};


#endif
