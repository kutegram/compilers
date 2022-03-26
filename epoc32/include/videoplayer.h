// VideoPlayer.h
//
// Copyright (c) Symbian Software Ltd 2002-2007.  All rights reserved.
//

#ifndef __VIDEOPLAYER_H__
#define __VIDEOPLAYER_H__

#include <w32std.h>
#include <fbs.h>
#include <f32file.h>
#include <mmf/common/mmfbase.h>
#include <mmf/common/mmfcontroller.h>
#include <mmf/common/mmfaudio.h>
#include <mmf/common/mmfstandardcustomcommands.h>
#include <mmf/common/mmfdrmcustomcommands.h>
#include <mda/common/base.h>
#include <mmf/common/mmfutilities.h>
#include <mmf/common/mmfcontrollerframeworkbase.h>
#include <mmf/common/mmcaf.h>
#include <mmfclntutility.h>

/**
@publishedAll


An interface to a set of video player callback functions.

The class is a mixin and is intended to be inherited by the client
class which is observing the video playing operation. The functions
encapsulated by this class are called when specific events occur in
the process of initialising and playing an video clip. A reference to
this object is passed as a parameter when constructing an audio player
utility object.


*/
class MVideoPlayerUtilityObserver
	{
public:

	/**
	Notification to the client that the opening of the video clip has completed,
	successfully, or otherwise.

	The status of the video sample after opening is given by aError. The following
	values imply same across all the devices.

	- KErrNone: the sample is ready to play;
	- KErrNotSupported: the controller plugin is not recognised or not supported;
	- KErrNotFound: the video sample cannot be found;
	- KErrNoMemory: there is insufficient memory to play this video sample.

	Other values are possible indicating a problem opening the video sample. These values
	are device dependent.

	The client must now call Prepare() on the video player utility before the
	video clip can be played or any of its properties (e.g. duration) can be
	queried.

	@param  aError
	        The status of the video player after initialisation.

	
	*/
	virtual void MvpuoOpenComplete(TInt aError) = 0;

	/**
	Notification to the client that the opening of the video clip has been prepared
	successfully, or otherwise.  This callback is called in response to a call to
	CVideoPlayerUtility::Prepare().

	The video clip may now be played, or have any of its properties (e.g. duration) queried.

	@param  aError
	        The status of the video player after initialisation.
	        This is either KErrNone if the open has completed successfully,
	        or one of the system wide error codes.
	
	
	*/
	virtual void MvpuoPrepareComplete(TInt aError) = 0;

	/**
	Notification that the frame requested by a call to GetFrameL is ready

	@param  aFrame
	        The returned frame. The bitmap will contain
	        the requested frame if the the error code is KErrNone (success).
	@param  aError
	        The status of the frame request.
	        This is either KErrNone if the frame request was successful,
	        or one of the system wide error codes.

	
	*/
	virtual void MvpuoFrameReady(CFbsBitmap& aFrame,TInt aError) = 0;

	/**
	Notification that video playback has completed. This is not called if
	playback is explicitly stopped by calling Stop.

	@param  aError
	        The status of playback.
	        This is either KErrNone if the playback was completed successfully,
	        or one of the system wide error codes.
	
	*/
	virtual void MvpuoPlayComplete(TInt aError) = 0;
	
	/**
	General event notification from controller. These events are specified by
	the supplier of the controller

	@param  aEvent
	        The event sent by the controller.

	
	*/
	virtual void MvpuoEvent(const TMMFEvent& aEvent) = 0;
	};
	
/**
@publishedAll


This is a mixin class that allows a client to receive notification of rebuffering
operations occurring in the video player


*/
class MVideoLoadingObserver
	{
public:

	/**
	Notification that video clip loading/rebuffering has started

	
	*/
	virtual void MvloLoadingStarted() = 0;

	/**
	Notification that video clip loading/rebuffering has completed

	
	*/
	virtual void MvloLoadingComplete() = 0;
	};

class CMMFVideoPlayerCallback;

/**
@publishedAll


Plays sampled video data.

The class offers a simple interface to open, play and obtain information from sampled video data. 
The video data can be provided using files, descriptors or URLs.

Note: 
Some video formats also allow the storing of audio data. To accommodate this, this class contains 
audio functions that can manipulate such data.

While this class is abstract, NewL() constructs, initialises and returns pointers to instances of 
concrete classes derived from this abstract class. This concrete class is part of the MMF 
implementation and is private.


*/
class CVideoPlayerUtility : public CBase,
							public MMMFClientUtility
	{
	class CBody;
public:

	~CVideoPlayerUtility();

	IMPORT_C static CVideoPlayerUtility* NewL(MVideoPlayerUtilityObserver& aObserver,
											  TInt aPriority,
											  TMdaPriorityPreference aPref,
											  RWsSession& aWs,
											  CWsScreenDevice& aScreenDevice,
											  RWindowBase& aWindow,
											  const TRect& aScreenRect,
											  const TRect& aClipRect);

	IMPORT_C void OpenFileL(const TDesC& aFileName,TUid aControllerUid = KNullUid);
	IMPORT_C void OpenFileL(const RFile& aFileName, TUid aControllerUid = KNullUid);

	IMPORT_C void OpenFileL(const TMMSource& aSource, TUid aControllerUid = KNullUid);

	IMPORT_C void OpenDesL(const TDesC8& aDescriptor,TUid aControllerUid = KNullUid);

	IMPORT_C void OpenUrlL(const TDesC& aUrl, TInt aIapId = KUseDefaultIap, const TDesC8& aMimeType=KNullDesC8, TUid aControllerUid = KNullUid);

	IMPORT_C void Prepare();

	IMPORT_C void Close();

	IMPORT_C void Play();

	IMPORT_C void Play(const TTimeIntervalMicroSeconds& aStartPoint, const TTimeIntervalMicroSeconds& aEndPoint);

	IMPORT_C TInt Stop();

	IMPORT_C void PauseL();

	IMPORT_C void SetPriorityL(TInt aPriority, TMdaPriorityPreference aPref);

	IMPORT_C void PriorityL(TInt& aPriority, TMdaPriorityPreference& aPref) const;

	IMPORT_C void SetDisplayWindowL(RWsSession& aWs,CWsScreenDevice& aScreenDevice,RWindowBase& aWindow,const TRect& aWindowRect,const TRect& aClipRect);

	IMPORT_C void RegisterForVideoLoadingNotification(MVideoLoadingObserver& aCallback);

	IMPORT_C void GetVideoLoadingProgressL(TInt& aPercentageComplete);

	IMPORT_C void GetFrameL(TDisplayMode aDisplayMode);

	IMPORT_C void GetFrameL(TDisplayMode aDisplayMode, ContentAccess::TIntent aIntent);

	IMPORT_C void RefreshFrameL();

	IMPORT_C TReal32 VideoFrameRateL() const;

	IMPORT_C void SetVideoFrameRateL(TReal32 aFramesPerSecond);

	IMPORT_C void VideoFrameSizeL(TSize& aSize) const;

	IMPORT_C const TDesC8& VideoFormatMimeType() const;

	IMPORT_C TInt VideoBitRateL() const;

	IMPORT_C TInt AudioBitRateL() const;

	IMPORT_C TFourCC AudioTypeL() const;

	IMPORT_C TBool AudioEnabledL() const;

	IMPORT_C void SetPositionL(const TTimeIntervalMicroSeconds& aPosition);

	IMPORT_C TTimeIntervalMicroSeconds PositionL() const;

	IMPORT_C TTimeIntervalMicroSeconds DurationL() const;

	IMPORT_C void SetVolumeL(TInt aVolume);

	IMPORT_C TInt Volume() const;

	IMPORT_C TInt MaxVolume() const;

	IMPORT_C void SetBalanceL(TInt aBalance);

	IMPORT_C TInt Balance()const;

	IMPORT_C void SetRotationL(TVideoRotation aRotation);

	IMPORT_C TVideoRotation RotationL() const;

	IMPORT_C void SetScaleFactorL(TReal32 aWidthPercentage, TReal32 aHeightPercentage, TBool aAntiAliasFiltering);

	IMPORT_C void GetScaleFactorL(TReal32& aWidthPercentage, TReal32& aHeightPercentage, TBool& aAntiAliasFiltering) const;

	IMPORT_C void SetCropRegionL(const TRect& aCropRegion);

	IMPORT_C void GetCropRegionL(TRect& aCropRegion) const;

	IMPORT_C TInt NumberOfMetaDataEntriesL() const;

	IMPORT_C CMMFMetaDataEntry* MetaDataEntryL(TInt aIndex) const;

	IMPORT_C const CMMFControllerImplementationInformation& ControllerImplementationInformationL();

	IMPORT_C TInt CustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom);

	IMPORT_C TInt CustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2);

	IMPORT_C void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom, TRequestStatus& aStatus);

	IMPORT_C void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TRequestStatus& aStatus);

	IMPORT_C MMMFDRMCustomCommand* GetDRMCustomCommand();

	IMPORT_C void StopDirectScreenAccessL();
	
	IMPORT_C void StartDirectScreenAccessL();

	IMPORT_C TInt RegisterAudioResourceNotification(MMMFAudioResourceNotificationCallback& aCallback, TUid aNotificationEventUid, const TDesC8& aNotificationRegistrationData = KNullDesC8);

	IMPORT_C TInt CancelRegisterAudioResourceNotification(TUid aNotificationEventId);
    
	IMPORT_C TInt WillResumePlay();
	
	IMPORT_C TInt SetInitScreenNumber(TInt aScreenNumber);

	// SetPlayVelocityL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C void SetPlayVelocityL(TInt aVelocity);

	// PlayVelocityL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C TInt PlayVelocityL() const;

	// StepFrameL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C void StepFrameL(TInt aStep);
	
	// GetPlayRateCapabilitiesL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C void GetPlayRateCapabilitiesL(TVideoPlayRateCapabilities& aCapabilities) const;
	
	// SetVideoEnabledL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C void SetVideoEnabledL(TBool aVideoEnabled);

	// VideoEnabledL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C TBool VideoEnabledL() const;

	// SetAudioEnabledL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C void SetAudioEnabledL(TBool aAudioEnabled);

	// SetAutoScaleL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C void SetAutoScaleL(TAutoScaleType aScaleType);

	// SetAutoScaleL() is publishedPartner and prototype as it is not yet used by licensees,
	// and there is a possibility that it may change on licensee request for a short period.
	// It will eventually be moved to publishedAll and released.
	IMPORT_C void SetAutoScaleL(TAutoScaleType aScaleType, TInt aHorizPos, TInt aVertPos);	
private:
	enum TMMFVideoPlayerState
		{
		EStopped,
		EOpening,
		EPaused,
		EPlaying		
		};

private:
	CBody* iBody;

	friend class CBody;
	friend class CTestStepUnitMMFVidClient;
public:
	class CTestView;
	friend class CTestView;
	};

#endif
