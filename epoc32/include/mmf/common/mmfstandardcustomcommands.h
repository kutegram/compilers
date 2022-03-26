// MmfStandardCustomCommands.h
//
// Copyright (c) Symbian Software Ltd 2002-2007.  All rights reserved.
//

#ifndef __MMFSTANDARDCUSTOMCOMMANDS_H
#define __MMFSTANDARDCUSTOMCOMMANDS_H

#include <mmf/common/mmfcontroller.h>
#include <mmf/common/mmfvideo.h>
#include <mmf/common/mmcaf.h>

class CMMFVideoFrameMessage;
class CFbsBitmap;
class CDesC8Array;

/**
@publishedAll

*/
const TInt KPlaybackRateNormal = 1;

/**
@publishedAll


Balance value for centre
*/
const TInt KMMFBalanceCenter = 0;

/**
@publishedAll


Balance value for max left
*/
const TInt KMMFBalanceMaxLeft = -100;

/**
@publishedAll


Balance value for max right
*/
const TInt KMMFBalanceMaxRight = 100;

/**
@publishedAll

*/
const TInt KMMFVideoCurrentFrame = -1;

/**
@publishedAll

*/
enum TMMFDSAEvent
	{
	EAbortDSA,
	EResumeDSA
	};

/**
@publishedAll


Interface UID and messages for the Audio Resource Notification API.
*/
const TUid KMMFEventCategoryAudioResourceAvailable = {0x101FD9F2};

/**
@internalComponent
*/
enum TMMFAudioResourceNotificationMessages
	{
	EMMFAudioResourceRegisterNotification,
	EMMFAudioResourceCancelRegisterNotification,
	EMMFAudioResourceGetNotificationData,
	EMMFAudioResourceWillResumePlay
	};

/**
@publishedAll


Interface UID and messages for the Audio Play Device API.
*/
const TUid KUidInterfaceMMFAudioPlayDevice = {0x101F76D6};

/**
@internalComponent
*/
enum TMMFAudioPlayDeviceMessages
	{
	EMMFAudioPlayDeviceSetVolume,
	EMMFAudioPlayDeviceGetMaxVolume,
	EMMFAudioPlayDeviceGetVolume,
	EMMFAudioPlayDeviceSetVolumeRamp,
	EMMFAudioPlayDeviceSetBalance,
	EMMFAudioPlayDeviceGetBalance
	};

/**
@publishedAll


Interface UID and messages for the Audio Record Device API.
*/
const TUid KUidInterfaceMMFAudioRecordDevice = {0x101F76D7};

/**
@internalComponent
*/
enum TMMFAudioRecordDeviceMessage
	{
	EMMFAudioRecordDeviceSetGain,
	EMMFAudioRecordDeviceGetMaxGain,
	EMMFAudioRecordDeviceGetGain,
	EMMFAudioRecordDeviceSetBalance,
	EMMFAudioRecordDeviceGetBalance
	};

/**
@publishedAll


Interface UID and messages for the Audio Play Controller API.
*/
const TUid KUidInterfaceMMFAudioPlayController = {0x101F76D8};

/**
@internalComponent
*/
enum TMMFAudioPlayControllerMessages
	{
	EMMFAudioPlayControllerSetPlaybackWindow,
	EMMFAudioPlayControllerDeletePlaybackWindow,
	EMMFAudioPlayControllerGetLoadingProgress
	};

/**
@publishedAll


Interface UID and messages for the Audio Record Controller API.
*/
const TUid KUidInterfaceMMFAudioRecordController = {0x101F76D9};

/**
@internalComponent
*/
enum TMMFAudioRecordControllerMessages
	{
	EMMFAudioRecordControllerGetRecordTimeAvailable,
	EMMFAudioRecordControllerSetMaxDuration,
	EMMFAudioRecordControllerSetMaxFileSize,
	EMMFAudioRecordControllerCrop,
	EMMFAudioRecordControllerAddMetaDataEntry,
	EMMFAudioRecordControllerRemoveMetaDataEntry,
	EMMFAudioRecordControllerReplaceMetaDataEntry
	};

/**
@publishedAll


Interface UID and messages for the Audio Controller API.
*/
const TUid KUidInterfaceMMFAudioController = {0x101F76DA};

/**
@internalComponent
*/
enum TMMFAudioControllerMessages
	{
	EMMFAudioControllerSetSourceSampleRate,
	EMMFAudioControllerSetSourceNumChannels,
	EMMFAudioControllerSetSourceFormat,
	EMMFAudioControllerSetSourceBitRate,
	EMMFAudioControllerSetSourceDataType,
	EMMFAudioControllerSetSinkSampleRate,
	EMMFAudioControllerSetSinkNumChannels,
	EMMFAudioControllerSetSinkFormat,
	EMMFAudioControllerSetSinkBitRate,
	EMMFAudioControllerSetSinkDataType,
	EMMFAudioControllerGetSourceSampleRate,
	EMMFAudioControllerGetSourceBitRate,
	EMMFAudioControllerGetSourceNumChannels,
	EMMFAudioControllerGetSourceFormat,
	EMMFAudioControllerGetSourceDataType,
	EMMFAudioControllerGetSinkSampleRate,
	EMMFAudioControllerGetSinkBitRate,
	EMMFAudioControllerGetSinkNumChannels,
	EMMFAudioControllerGetSinkFormat,
	EMMFAudioControllerGetSinkDataType,
	EMMFAudioControllerGetSupportedSourceSampleRates,
	EMMFAudioControllerGetSupportedSourceBitRates,
	EMMFAudioControllerGetSupportedSourceNumChannels,
	EMMFAudioControllerGetSupportedSourceDataTypes,
	EMMFAudioControllerGetSupportedSinkSampleRates,
	EMMFAudioControllerGetSupportedSinkBitRates,
	EMMFAudioControllerGetSupportedSinkNumChannels,
	EMMFAudioControllerGetSupportedSinkDataTypes,
	EMMFAudioControllerCopyArrayData,
	EMMFAudioControllerSetCodec
	};


/**
@publishedAll

*/
const TUid KUidInterfaceMMFVideoController = {0x101F76DB};

/**
@internalComponent
*/
enum TMMFVideoControllerMessages
	{
	EMMFVideoControllerGetAudioCodec,
	EMMFVideoControllerGetVideoBitRate,
	EMMFVideoControllerGetAudioBitRate,
	EMMFVideoControllerGetVideoFrameSize,
	EMMFVideoControllerSetFrameRate,
	EMMFVideoControllerGetFrameRate,
	EMMFVideoControllerGetVideoMimeType
	};

/**
@publishedAll

*/
const TUid KUidInterfaceMMFVideoPlayController = {0x101F7B73};

/**
@internalComponent
*/
enum TMMFVideoPlayControllerMessages
	{
	EMMFVideoPlayControllerPrepare,
	EMMFVideoPlayControllerGetFrame,
	EMMFVideoPlayControllerSetDisplayWindow,
	EMMFVideoPlayControllerGetAudioEnabled,
	EMMFVideoPlayControllerUpdateDisplayRegion,
	EMMFVideoPlayControllerDSAEvent,
	EMMFVideoPlayControllerPlay,
	EMMFVideoPlayControllerRefreshFrame,
	EMMFVideoPlayControllerGetLoadingProgress,
	EMMFVideoPlayControllerSetRotation,
	EMMFVideoPlayControllerGetRotation,
	EMMFVideoPlayControllerSetScaleFactor,
	EMMFVideoPlayControllerGetScaleFactor,
	EMMFVideoPlayControllerSetCropRegion,
	EMMFVideoPlayControllerGetCropRegion
	};

/**
@publishedAll

*/
const TUid KUidInterfaceMMFVideoRecordController = {0x101F7B74};

/**
@internalComponent
*/
enum TMMFVideoRecordControllerMessages
	{
	EMMFVideoRecordControllerSetVideoFormat,
	EMMFVideoRecordControllerSetVideoCodec,
	EMMFVideoRecordControllerSetAudioCodec,
	EMMFVideoRecordControllerSetVideoBitRate,
	EMMFVideoRecordControllerSetAudioBitRate,
	EMMFVideoRecordControllerSetVideoFrameSize,
	EMMFVideoRecordControllerSetMaxFileSize,
	EMMFVideoRecordControllerAddMetaDataEntry,
	EMMFVideoRecordControllerRemoveMetaDataEntry,
	EMMFVideoRecordControllerReplaceMetaDataEntry,
	EMMFVideoRecordControllerSetAudioEnabled,
	EMMFVideoRecordControllerPrepare,
	EMMFVideoRecordControllerSetCameraHandle,
	EMMFVideoRecordControllerGetRecordTimeAvailable,
	EMMFVideoRecordControllerGetSupportedSinkAudioTypes,
	EMMFVideoRecordControllerGetSupportedSinkVideoTypes,
	EMMFVideoRecordControllerCopyDescriptorArrayData,
	EMMFVideoRecordControllerCopyFourCCArrayData,
	EMMFVideoRecordControllerGetAudioEnabled // INC23777
	};


/**
@publishedAll

*/
const TUid KUidInterfaceMMFVideoDRMExt = {0x101F7C23};

/**
@internalComponent
*/
enum TMMFDRMIntentMessages
	{
	EMMFVideoDRMExtGetFrame
	};

/**
@publishedAll


Interface UID for the custom command that supports setting the initial screen for video on the controller.
*/
const TUid KUidInterfaceMMFVideoSetInitScreen = {0x102825F7};

/**
@internalComponent
*/
enum TMMFVideoScreenDeviceMessages
	{
	EMMFVideoSetInitScreenNumber
	};


/**
@publishedAll
@prototype
*/
const TUid KUidInterfaceMMFVideoPixelAspectRatio = {0x102831EF};

/**
@internalComponent
*/
enum TMMFVideoPixelAspectRatioMessages
	{
	EMMFVideoGetPixelAspectRatio,
	EMMFVideoSetPixelAspectRatio,
	EMMFVideoGetSupportedPixelAspectRatios,
	EMMFVideoPixelAspectRatioCopyArrayData
	};

/**
@publishedAll
@prototype
*/
const TUid KUidInterfaceMMFVideoAudioSamplingRateAndChannelConfig = {0x102831F0};

/**
@internalComponent
*/
enum TMMFVideoAudioSamplingRateAndChannelConfigMessages
	{
	EMMFVideoGetAudioChannels,
	EMMFVideoSetAudioChannels,
	EMMFVideoGetSupportedAudioChannels,
	EMMFVideoGetAudioSampleRate,
	EMMFVideoSetAudioSampleRate,
	EMMFVideoGetSupportedAudioSampleRates,
	EMMFVideoAudioSamplingRateAndChannelConfigCopyArrayData
	};

/**
@publishedAll


Client class to access Audio Play Device functionality.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.

*/
class RMMFAudioPlayDeviceCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	
	*/
	IMPORT_C RMMFAudioPlayDeviceCustomCommands(RMMFController& aController);

	/**
	Sets the volume of the sound device.

	@param  aVolume
	        The new volume.

	@return	One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetVolume(TInt aVolume) const;

	/**
	Gets the maximum volume supported by the sound device.

	@param  aMaxVolume
	        The maximum volume, filled in by the controller.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetMaxVolume(TInt& aMaxVolume) const;

	/**
	Gets the current playback volume.

	@param  aVolume
	        On return contains the current playback volume.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetVolume(TInt& aVolume) const;

	/**
	Sets a volume ramp.

	This will cause the sound device to start playing with zero volume,
	increasing the volume over aRampDuration microseconds.

	The volume ramp can be removed by setting the ramp duration to zero.

	@param  aRampDuration
	        The duration over which the volume is to be increased, in microseconds.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration) const;

	/**
	Sets the balance between the left and right stereo audio channels.

	@param  aBalance
	        Use a value between KMMFBalanceMaxLeft and KMMFBalanceMaxRight. Centre balance can be
	        restored by using KMMFBalanceCenter.

	@return	One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetBalance(TInt aBalance) const;

	/**
	Gets the balance between the left and right stereo audio channels.

	@param  aBalance
	        The current balance, filled in by the controller.

	@return One of the system-wide error codes.
	
	
	*/
	IMPORT_C TInt GetBalance(TInt& aBalance) const;
	};

/**
@publishedAll


Mixin class to be derived from controller plugins that could support the audio play device
custom commands.
*/
class MMMFAudioPlayDeviceCustomCommandImplementor
	{
public:

	/**
	Sets the volume of the sound device.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aVolume
	        The new volume.

	
	*/
	virtual void MapdSetVolumeL(TInt aVolume) = 0;

	/**
	Gets the maximum volume supported by the sound device.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aMaxVolume
	        The maximum volume, to be filled in by the controller plugin.

	
	*/
	virtual void MapdGetMaxVolumeL(TInt& aMaxVolume) = 0;

	/**
	Gets the current playback volume.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aVolume
	        The volume, to be filled in by the controller.

	
	*/
	virtual void MapdGetVolumeL(TInt& aVolume) = 0;

	/**
	Sets a volume ramp.

	This will cause the sound device to start playing with zero volume,
	increasing the volume over aRampDuration microseconds.

	The volume ramp can be removed by setting the ramp duration to zero.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aRampDuration
	        The duration over which the volume is to be increased, in microseconds.

	
	*/
	virtual void MapdSetVolumeRampL(const TTimeIntervalMicroSeconds& aRampDuration) = 0;

	/**
	Sets the balance between the left and right stereo audio channels.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aBalance
	        Use a value between KMMFBalanceMaxLeft and KMMFBalanceMaxRight. Centre balance can be
	        restored by using KMMFBalanceCenter.

	
	*/
	virtual void MapdSetBalanceL(TInt aBalance) = 0;

	/**
	Gets the balance between the left and right stereo audio channels.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aBalance
	        The current balance, filled in by the controller.

	
	*/
	virtual void MapdGetBalanceL(TInt& aBalance) = 0;
	};

/**
@publishedAll


Custom command parser class to be used by controller plugins wishing to support
audio play device commands.

The controller plugin must be derived from MMMFAudioPlayDeviceCustomCommandImplementor
to use this class.

The controller plugin should create an object of this type and add it to the list of custom
command parsers in the controller framework. See the following example code for details.

@code
void CMMFAudioController::ConstructL()
	{
	// Construct custom command parsers
	CMMFAudioPlayDeviceCustomCommandParser* audPlayDevParser = CMMFAudioPlayDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audPlayDevParser);
	AddCustomCommandParserL(*audPlayDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audPlayDevParser

	CMMFAudioRecordDeviceCustomCommandParser* audRecDevParser = CMMFAudioRecordDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audRecDevParser);
	AddCustomCommandParserL(*audRecDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audRecDevParser

etc.
	}
@endcode


*/
class CMMFAudioPlayDeviceCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of handling audio play device commands.

	This function may leave with one of the system-wide error codes.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return	A pointer to the object created.

	
	*/
	IMPORT_C static CMMFAudioPlayDeviceCustomCommandParser* NewL(MMMFAudioPlayDeviceCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFAudioPlayDeviceCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);
private:

	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFAudioPlayDeviceCustomCommandParser(MMMFAudioPlayDeviceCustomCommandImplementor& aImplementor);
	// Internal request handling methods.
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetVolumeL(TMMFMessage& aMessage);
	TBool DoGetMaxVolumeL(TMMFMessage& aMessage);
	TBool DoGetVolumeL(TMMFMessage& aMessage);
	TBool DoSetVolumeRampL(TMMFMessage& aMessage);
	TBool DoSetBalanceL(TMMFMessage& aMessage);
	TBool DoGetBalanceL(TMMFMessage& aMessage);
private:
	/** The object that implements the audio play device interface */
	MMMFAudioPlayDeviceCustomCommandImplementor& iImplementor;
	};

/**
@publishedAll


Client class to access Audio Record Device functionality.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFAudioRecordDeviceCustomCommands : public RMMFCustomCommandsBase
	{
public:
	
	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	
	*/
	IMPORT_C RMMFAudioRecordDeviceCustomCommands(RMMFController& aController);

	/**
	Sets the gain of the sound device.

	@param  aGain
	        The new gain.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetGain(TInt aGain) const;

	/**
	Gets the maximum gain supported by the sound device.

	@param  aMaxGain
	        The maximum gain, filled in by the controller.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetMaxGain(TInt& aMaxGain) const;

	/**
	Gets the current recording gain.

	@param  aGain
	        The gain, filled in by the controller.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetGain(TInt& aGain) const;

	/**
	Sets the balance between the left and right stereo microphone channels.

	@param  aBalance
	        Use a value between KMMFBalanceMaxLeft and KMMFBalanceMaxRight. Centre balance can be 
	        restored by using KMMFBalanceCenter.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetBalance(TInt aBalance) const;

	/**
	Gets the balance between the left and right stereo microphone channels.

	@param  aBalance
	        The current balance, filled in by the controller.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetBalance(TInt& aBalance) const;
	};

/**
@publishedAll


Mixin class to be derived from controller plugins that could support the audio record device
custom commands.
*/
class MMMFAudioRecordDeviceCustomCommandImplementor
	{
public:

	/**
	Sets the gain of the sound device.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aGain
	        The new gain.

	
	*/
	virtual void MardSetGainL(TInt aGain) = 0;

	/**
	Gets the maximum gain supported by the sound device.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aMaxGain
	        The maximum gain, to be filled in by the controller plugin.

	
	*/
	virtual void MardGetMaxGainL(TInt& aMaxGain) = 0;

	/**
	Gets the current recording gain.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aGain
	        The gain, to be filled in by the controller.

	
	*/
	virtual void MardGetGainL(TInt& aGain) = 0;

	/**
	Sets the balance between the left and right stereo microphone channels.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aBalance
	        Use a value between KMMFBalanceMaxLeft and KMMFBalanceMaxRight. Centre balance can be
	        restored by using KMMFBalanceCenter.

	
	*/
	virtual void MardSetBalanceL(TInt aBalance) = 0;

	/**
	Gets the balance between the left and right stereo microphone channels.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aBalance
	        The current balance, filled in by the controller.

	
	*/
	virtual void MardGetBalanceL(TInt& aBalance) = 0;
	};

/**
@publishedAll


Custom command parser class to be used by controller plugins wishing to support
audio record device commands.

The controller plugin must be derived from MMMFAudioRecordDeviceCustomCommandImplementor
to use this class.

The controller plugin should create an object of this type and add it to the list of custom
command parsers in the controller framework.  See the following example code for details.

@code
void CMMFAudioController::ConstructL()
	{
	// Construct custom command parsers
	CMMFAudioPlayDeviceCustomCommandParser* audPlayDevParser = CMMFAudioPlayDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audPlayDevParser);
	AddCustomCommandParserL(*audPlayDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audPlayDevParser

	CMMFAudioRecordDeviceCustomCommandParser* audRecDevParser = CMMFAudioRecordDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audRecDevParser);
	AddCustomCommandParserL(*audRecDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audRecDevParser

etc.
	}
@endcode


*/
class CMMFAudioRecordDeviceCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of handling audio record device commands.

	This function may leave with one of the system-wide error codes.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFAudioRecordDeviceCustomCommandParser* NewL(MMMFAudioRecordDeviceCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFAudioRecordDeviceCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);
private:

	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFAudioRecordDeviceCustomCommandParser(MMMFAudioRecordDeviceCustomCommandImplementor& aImplementor);
	// Internal request handling methods.
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetGainL(TMMFMessage& aMessage);
	TBool DoGetMaxGainL(TMMFMessage& aMessage);
	TBool DoGetGainL(TMMFMessage& aMessage);
	TBool DoSetBalanceL(TMMFMessage& aMessage);
	TBool DoGetBalanceL(TMMFMessage& aMessage);
private:
	/** The object that implements the audio record device interface */
	MMMFAudioRecordDeviceCustomCommandImplementor& iImplementor;
	};


/**
@publishedAll


Client class to access functionality specific to an audio play controller.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFAudioPlayControllerCustomCommands : public RMMFCustomCommandsBase
	{
public:
	
	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	
	*/
	IMPORT_C RMMFAudioPlayControllerCustomCommands(RMMFController& aController);

	/**
	Sets a playback window.  The controller will start playing from the start of the window,
	and finish playing at the end of the window.

	@param  aStart
	        The start of the window, in microseconds.
	@param  aEnd
	        The end of the window, in microseconds.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetPlaybackWindow(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd) const;

	/**
	Removes a previously defined playback window.

	@return One of the system-wide error codes.
	
	*/
	IMPORT_C TInt DeletePlaybackWindow();

	/**
	Gets the audio loading progress as a percentage.

	@param  aPercentageProgress
	        The progress loading the clip, as a percentage.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetLoadingProgress(TInt& aPercentageProgress) const;
	};


/**
@publishedAll


Mixin class to be derived from controller plugins that could support the audio play controller
custom commands.
*/
class MMMFAudioPlayControllerCustomCommandImplementor
	{
public:

	/**
	Sets a playback window. The controller will start playing from the start of the window,
	and finish playing at the end of the window.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aStart
	        The start of the window, in microseconds.
	@param  aEnd
	        The end of the window, in microseconds.

	
	*/
	virtual void MapcSetPlaybackWindowL(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd) = 0;

	/**
	Removes a previously defined playback window.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	
	*/
	virtual void MapcDeletePlaybackWindowL() = 0;

	/**
	Gets the completion status of loading/rebuffering the current audio clip.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aPercentageComplete
	        The status of loading as a percentage completed.

	
	*/
	virtual void MapcGetLoadingProgressL(TInt& aPercentageComplete) = 0;
	};

/**
@publishedAll


Custom command parser class to be used by controller plugins wishing to support
audio play controller commands.

The controller plugin must be derived from MMMFAudioPlayControllerCustomCommandImplementor to use 
this class.

The controller plugin should create an object of this type and add it to the list of custom
command parsers in the controller framework. See the following example code for details.

@code
void CMMFAudioController::ConstructL()
	{
	// Construct custom command parsers
	CMMFAudioPlayDeviceCustomCommandParser* audPlayDevParser = CMMFAudioPlayDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audPlayDevParser);
	AddCustomCommandParserL(*audPlayDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audPlayDevParser

	CMMFAudioRecordDeviceCustomCommandParser* audRecDevParser = CMMFAudioRecordDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audRecDevParser);
	AddCustomCommandParserL(*audRecDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audRecDevParser

etc.
	}
@endcode


*/
class CMMFAudioPlayControllerCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of handling audio play controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFAudioPlayControllerCustomCommandParser* NewL(MMMFAudioPlayControllerCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFAudioPlayControllerCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);
private:

	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFAudioPlayControllerCustomCommandParser(MMMFAudioPlayControllerCustomCommandImplementor& aImplementor);
	// Internal request handling methods.
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetPlaybackWindowL(TMMFMessage& aMessage);
	TBool DoDeletePlaybackWindowL(TMMFMessage& aMessage);
	TBool DoGetLoadingProgressL(TMMFMessage& aMessage);
private:
	/** 
	The object that implements the audio play controller interface 
	*/
	MMMFAudioPlayControllerCustomCommandImplementor& iImplementor;
	};




/**
@publishedAll


Client class to access functionality specific to an audio record controller.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFAudioRecordControllerCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command	interface.

	
	*/
	IMPORT_C RMMFAudioRecordControllerCustomCommands(RMMFController& aController);

	/**
	Gets the (possibly estimated) record time left in the clip.

	@param  aTime
	        The record time available, in microseconds.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetRecordTimeAvailable(TTimeIntervalMicroSeconds& aTime) const;

	/**
	Sets the maximum duration of the recorded clip, in microseconds.

	@param  aMaxDuration
	        The maximum duration of the recorded clip, in microseconds.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetMaxDuration(const TTimeIntervalMicroSeconds& aMaxDuration) const;

	/**
	Sets the maximum size of the recorded clip, in bytes.

	@param  aMaxSize
	        The maximum size of the recorded clip, in bytes.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetMaxFileSize(TInt aMaxSize) const;

	/**
	Removes a portion from the clip, either from the current position to the beginning or the 
	current position to the end.

	@param  aToEnd
	        A boolean indicating whether to crop to the end. Crops to the end if set to ETrue, to 
			the beginning set to EFalse.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt Crop(TBool aToEnd);

	/**
	Adds meta data to the clip.

	@param  aNewEntry
	        The details of the new entry to be added.

	
	*/
	IMPORT_C void AddMetaDataEntryL(const CMMFMetaDataEntry& aNewEntry);

	/**
	Removes a meta data entry from the clip.

	@param  aIndex
	        The ID of the meta data entry to delete.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt RemoveMetaDataEntry(TInt aIndex);

	/**
	Replaces a meta data in the clip.

	@param  aIndex
	        The ID of the meta data entry to replace.
	@param  aNewEntry
	        The details of the new entry to be added.

	
	*/
	IMPORT_C void ReplaceMetaDataEntryL(TInt aIndex, const CMMFMetaDataEntry& aNewEntry);
	};

/**
@publishedAll


Mixin class to be derived from controller plugins that could support the audio record controller
custom commands.
*/
class MMMFAudioRecordControllerCustomCommandImplementor
	{
public:

	/**
	Gets the (possibly estimated) record time left in the clip.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aTime
	        The record time available, in microseconds.

	
	*/
	virtual void MarcGetRecordTimeAvailableL(TTimeIntervalMicroSeconds& aTime) = 0;

	/**
	Sets the maximum duration of the recorded clip, in microseconds.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aMaxDuration
	        The maximum duration of the recorded clip, in microseconds.

	
	*/
	virtual void MarcSetMaxDurationL(const TTimeIntervalMicroSeconds& aMaxDuration) = 0;

	/**
	Sets the maximum size of the recorded clip, in bytes.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aMaxSize
	        The maximum size of the recorded clip, in bytes.

	
	*/
	virtual void MarcSetMaxFileSizeL(TInt aMaxSize) = 0;

	/**
	Removes a portion from the clip, either from the current position to the beginning
	or the current position to the end.

	This function can leave with one of the system-wide error codes. The request will be
	completed with the leave code.

	@param  aToEnd
	        A boolean indicating whether to crop to the end or the beginning. ETrue to crop to the
	        end, EFalse to the beginning.

	
	*/
	virtual void MarcCropL(TBool aToEnd) = 0;

	/**
	Adds meta data to the clip.

	@param  aNewEntry
	        The details of the new entry to be added.

	
	*/
	virtual void MarcAddMetaDataEntryL(const CMMFMetaDataEntry& aNewEntry) = 0;

	/**
	Removes a meta data entry from the clip.

	@param  aIndex
	        The ID of the meta data entry to delete.

	
	*/
	virtual void MarcRemoveMetaDataEntryL(TInt aIndex) = 0;

	/**
	Replaces a meta data entry in the clip.

	@param  aIndex
	        The ID of the meta data entry to replace.
	@param  aNewEntry
	        The details of the new entry to be added.

	
	*/
	virtual void MarcReplaceMetaDataEntryL(TInt aIndex, const CMMFMetaDataEntry& aNewEntry) = 0;
	};

/**
@publishedAll


Custom command parser class to be used by controller plugins wishing to support
audio record controller commands.

The controller plugin must be derived from MMMFAudioRecordControllerCustomCommandImplementor
to use this class.

The controller plugin should create an object of this type and add it to the list of custom
command parsers in the controller framework.  See the following example code for details.

@code
void CMMFAudioController::ConstructL()
	{
	// Construct custom command parsers
	CMMFAudioPlayDeviceCustomCommandParser* audPlayDevParser = CMMFAudioPlayDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audPlayDevParser);
	AddCustomCommandParserL(*audPlayDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audPlayDevParser

	CMMFAudioRecordDeviceCustomCommandParser* audRecDevParser = CMMFAudioRecordDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audRecDevParser);
	AddCustomCommandParserL(*audRecDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audRecDevParser

etc.
	}
@endcode


*/
class CMMFAudioRecordControllerCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of handling audio record controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFAudioRecordControllerCustomCommandParser* NewL(MMMFAudioRecordControllerCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFAudioRecordControllerCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.
	
	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);
private:

	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFAudioRecordControllerCustomCommandParser(MMMFAudioRecordControllerCustomCommandImplementor& aImplementor);
	// Internal request handling methods.
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoGetRecordTimeAvailableL(TMMFMessage& aMessage);
	TBool DoSetMaxDurationL(TMMFMessage& aMessage);
	TBool DoSetMaxFileSizeL(TMMFMessage& aMessage);
	TBool DoCropL(TMMFMessage& aMessage);
	TBool DoAddMetaDataEntryL(TMMFMessage& aMessage);
	TBool DoRemoveMetaDataEntryL(TMMFMessage& aMessage);
	TBool DoReplaceMetaDataEntryL(TMMFMessage& aMessage);
private:
	/**	
	The object that implements the audio record controller interface.
	*/
	MMMFAudioRecordControllerCustomCommandImplementor& iImplementor;
	};


/**
@publishedAll


Client class to access functionality specific to an audio controller.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFAudioControllerCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command
	        interface.

	
	*/
	IMPORT_C RMMFAudioControllerCustomCommands(RMMFController& aController);

	/**
	Sets the sample rate of the data source in samples per second.

	@param  aSampleRate
	        The sample rate, in samples per second.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSourceSampleRate(TUint aSampleRate) const;

	/**
	Sets the bit rate of the data source in bits per second.

	@param  aRate
	        The bit rate, in bits per second.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSourceBitRate(TUint aRate) const;

	/**
	Sets the number of channels in the data source.	For example, one channel for mono, two channels 
	for stereo etc.

	@param  aNumChannels
	        The number of channels.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSourceNumChannels(TUint aNumChannels) const;

	/**
	Sets the format of the data source.

	The UID corresponds to the UID of the CMMFFormat-derived ECOM plugin to be used.

	@param  aFormatUid
	        The format plugin to be used.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSourceFormat(TUid aFormatUid) const;

	/**
	Sets the fourCC code of the source.

	@param  aDataType
	        The fourCC code.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSourceDataType(TFourCC aDataType) const;

	/**
	Sets the sample rate of the data sink in samples per second.

	@param  aSampleRate
	        The sample rate, in samples per second.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSinkSampleRate(TUint aSampleRate) const;

	/**
	Set the bit rate of the data sink in bits per second.

	@param  aRate
	        The bit rate, in bits per second.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSinkBitRate(TUint aRate) const;

	/**
	Sets the number of channels in the data sink. For example, one channel for mono, two channels 
	for stereo etc.

	@param  aNumChannels
	        The number of channels.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSinkNumChannels(TUint aNumChannels) const;

	/**
	Sets the format of the data sink.

	The UID corresponds to the UID of the CMMFFormat-derived ECOM plugin to be used.

	@param  aFormatUid
	        The format plugin to be used.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSinkFormat(TUid aFormatUid) const;

	/**
	Set the fourCC code of the sink.

	@param  aDataType
	        The fourCC code.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetSinkDataType(TFourCC aDataType) const;

	/**
	Sets the codec to be used. Useful when recording data.

	@param  aSourceDataType
	        The data type of the source of the codec.
	@param  aSinkDataType
	        The data type of the sink of the codec.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetCodec(TFourCC aSourceDataType, TFourCC aSinkDataType) const;

	/**
	Gets the sample rate of the data source in samples per second.

	@param  aRate
	        The sample rate, in samples per second.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSourceSampleRate(TUint& aRate) const;

	/**
	Gets the bit rate of the data source in bits per second.

	@param  aRate
	        The bit rate, in bits per second.
	
	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSourceBitRate(TUint& aRate) const;

	/**
	Gets the number of channels in the data source. For example, one channel for mono, two channels 
	for stereo etc.

	@param  aNumChannels
	        The number of channels.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSourceNumChannels(TUint& aNumChannels) const;

	/**
	Gets the format of the data source.

	The UID corresponds to the UID of the CMMFFormat-derived ECOM plugin being used.

	@param  aFormat
	        The format plugin being used.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSourceFormat(TUid& aFormat) const;

	/**
	Get the fourCC code of the source.

	@param  aDataType
	        The fourCC code.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSourceDataType(TFourCC& aDataType) const;

	/**
	Gets the sample rate of the data sink in samples per second.

	@param  aRate
	        The sample rate, in samples per second.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSinkSampleRate(TUint& aRate) const;

	/**
	Gets the bit rate of the data sink in bits per second.

	@param  aRate
	        The bit rate, in bits per second.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSinkBitRate(TUint& aRate) const;

	/**
	Gets the number of channels in the data sink. For example, one channel for mono, two channels 
	for stereo etc.

	@param  aNumChannels
	        The number of channels.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSinkNumChannels(TUint& aNumChannels) const;

	/**
	Gets the format of the data sink.

	The UID corresponds to the UID of the CMMFFormat-derived ECOM plugin being used.

	@param  aFormat
	        The format plugin being used.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSinkFormat(TUid& aFormat) const;

	/**
	Gets the fourCC code of the sink.

	@param  aDataType
	        The fourCC code.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetSinkDataType(TFourCC& aDataType) const;

	/**
	Gets the list of sample rates supported by the data source.

	Warning: Existing objects in this array will be removed by this function.

	@param  aSupportedRates
	        The supported rates.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetSupportedSourceSampleRatesL(RArray<TUint>& aSupportedRates) const;

	/**
	Gets the list of bit rates supported by the data source.

	Warning: Existing objects in this array will be removed by this function.

	@param  aSupportedRates
	        The supported rates.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetSupportedSourceBitRatesL(RArray<TUint>& aSupportedRates) const;

	/**
	Gets the list of channels supported by the data source (ie mono, stereo etc).

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedChannels
	        The supported channels.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetSupportedSourceNumChannelsL(RArray<TUint>& aSupportedChannels) const;

	/**
	Gets the list of fourCC codes supported by the data source.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedDataTypes
	        The supported data types.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetSupportedSourceDataTypesL(RArray<TFourCC>& aSupportedDataTypes) const;

	/**
	Gets the list of sample rates supported by the data sink.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedRates
	        The supported rates.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetSupportedSinkSampleRatesL(RArray<TUint>& aSupportedRates) const;

	/**
	Gets the list of bit rates supported by the data sink.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedRates
	        The supported rates.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetSupportedSinkBitRatesL(RArray<TUint>& aSupportedRates) const;

	/**
	Gets the list of channels supported by the data sink (ie mono, stereo etc).

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedChannels
	        The supported channels.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetSupportedSinkNumChannelsL(RArray<TUint>& aSupportedChannels) const;

	/**
	Gets the list of fourCC codes supported by the data sink.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedDataTypes
	        The supported data types.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetSupportedSinkDataTypesL(RArray<TFourCC>& aSupportedDataTypes) const;

private:
	void DoGetUintArrayL(RArray<TUint>& aArray, TMMFAudioControllerMessages aIpc) const;
	void DoGetFourCCArrayL(RArray<TFourCC>& aArray, TMMFAudioControllerMessages aIpc) const;
	};


/**
@publishedAll


Mixin class to be derived from controller plugins that could support the audio record controller
custom commands.
*/
class MMMFAudioControllerCustomCommandImplementor
	{
public:

	/**
	Sets the sample rate of the data source in samples per second.

	@param  aSampleRate
	        The sample rate, in samples per second.

	
	*/
	virtual void MacSetSourceSampleRateL(TUint aSampleRate) = 0;

	/**
	Sets the bit rate of the data source in bits per second.

	@param  aBitRate
	        The bit rate, in bits per second.

	
	*/
	virtual void MacSetSourceBitRateL(TUint aBitRate) = 0;

	/**
	Sets the number of channels in the data source.	For example, one channel for mono, two channels 
	for stereo etc.

	@param  aNumChannels
	        The number of channels.

	
	*/
	virtual void MacSetSourceNumChannelsL(TUint aNumChannels) = 0;

	/**
	Sets the format of the data source.	The UID corresponds to the UID of the CMMFFormat-derived 
	ECOM plugin to be used.

	@param  aFormatUid
	        The format plugin to be used.

	
	*/
	virtual void MacSetSourceFormatL(TUid aFormatUid) = 0;

	/**
	Sets the fourCC code of the source.

	@param  aDataType
	        The fourCC code.

	
	*/
	virtual void MacSetSourceDataTypeL(TFourCC aDataType) = 0;

	/**
	Sets the sample rate of the data sink in samples per second.

	@param  aSampleRate
	        The sample rate, in samples per second.

	
	*/
	virtual void MacSetSinkSampleRateL(TUint aSampleRate) = 0;

	/**
	Sets the bit rate of the data sink in bits per second.

	@param  aRate
	        The bit rate, in bits per second.

	
	*/
	virtual void MacSetSinkBitRateL(TUint aRate) = 0;

	/**
	Sets the number of channels in the data sink. For example, one channel for mono, two channels 
	for stereo etc.

	@param  aNumChannels
	        The number of channels.

	
	*/
	virtual void MacSetSinkNumChannelsL(TUint aNumChannels) = 0;

	/**
	Sets the format of the data sink. The UID corresponds to the uid of the CMMFFormat-derived ECOM 
	plugin to be used.

	@param  aFormatUid
	        The format plugin to be used.

	
	*/
	virtual void MacSetSinkFormatL(TUid aFormatUid) = 0;

	/**
	Sets the fourCC code of the sink.

	@param  aDataType
	        The fourCC code.

	
	*/
	virtual void MacSetSinkDataTypeL(TFourCC aDataType) = 0;

	/**
	Sets the codec to be used.  Useful when recording data.

	@param  aSourceDataType
	        The data type of the source of the codec.
	@param  aSinkDataType
	        The data type of the sink of the codec.

	
	*/
	virtual void MacSetCodecL(TFourCC aSourceDataType, TFourCC aSinkDataType) = 0;


	/**
	Gets the sample rate of the data source in samples per second.

	@param  aRate	
	        The sample rate, in samples per second.

	
	*/
	virtual void MacGetSourceSampleRateL(TUint& aRate) = 0;

	/**
	Gets the bit rate of the data source in bits per second.

	@param  aRate
	        The bit rate, in bits per second.

	
	*/
	virtual void MacGetSourceBitRateL(TUint& aRate) = 0;

	/**
	Gets the number of channels in the data source.	For example, one channel for mono, two channels 
	for stereo etc.

	@param  aNumChannels
	        The number of channels.

	
	*/
	virtual void MacGetSourceNumChannelsL(TUint& aNumChannels) = 0;

	/**
	Gets the format of the data source.	The UID corresponds to the uid of the CMMFFormat-derived 
	ECOM plugin being used.

	@param  aFormat
	        The format plugin being used.

	
	*/
	virtual void MacGetSourceFormatL(TUid& aFormat) = 0;

	/**
	Gets the fourCC code of the source.

	@param  aDataType
	        The fourCC code.

	
	*/
	virtual void MacGetSourceDataTypeL(TFourCC& aDataType) = 0;

	/**
	Gets the sample rate of the data sink in samples per second.

	@param  aRate
	        The sample rate, in samples per second.

	
	*/
	virtual void MacGetSinkSampleRateL(TUint& aRate) = 0;

	/**
	Gets the bit rate of the data sink in bits per second.

	@param  aRate
	        The bit rate, in bits per second.

	
	*/
	virtual void MacGetSinkBitRateL(TUint& aRate) = 0;

	/**
	Gets the number of channels in the data sink. For example, one channel for mono, two channels 
	for stereo etc.

	@param  aNumChannels
	        The number of channels.

	
	*/
	virtual void MacGetSinkNumChannelsL(TUint& aNumChannels) = 0;

	/**
	Gets the format of the data sink. The UID corresponds to the uid of the CMMFFormat-derived ECOM 
	plugin being used.

	@param  aFormat
	        The format plugin being used.

	
	*/
	virtual void MacGetSinkFormatL(TUid& aFormat) = 0;

	/**
	Gets the fourCC code of the sink.

	@param  aDataType
	        The fourCC code.

	
	*/
	virtual void MacGetSinkDataTypeL(TFourCC& aDataType) = 0;

	/**
	Gets the list of sample rates supported by the data source.

	@param  aSupportedRates
	        The supported rates.  Warning: Existing objects in this array will be removed by this method.

	
	*/
	virtual void MacGetSupportedSourceSampleRatesL(RArray<TUint>& aSupportedRates) = 0;

	/**
	Gets the list of bit rates supported by the data source.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedRates
	        The supported rates.

	
	*/
	virtual void MacGetSupportedSourceBitRatesL(RArray<TUint>& aSupportedRates) = 0;

	/**
	Gets the list of channels supported by the data source (ie mono, stereo etc).

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedChannels
	        The supported channels.

	
	*/
	virtual void MacGetSupportedSourceNumChannelsL(RArray<TUint>& aSupportedChannels) = 0;

	/**
	Gets the list of fourCC codes supported by the data source.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedDataTypes
	        The supported data types.

	
	*/
	virtual void MacGetSupportedSourceDataTypesL(RArray<TFourCC>& aSupportedDataTypes) = 0;

	/**
	Gets the list of sample rates supported by the data sink.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedRates
	        The supported rates.

	
	*/
	virtual void MacGetSupportedSinkSampleRatesL(RArray<TUint>& aSupportedRates) = 0;

	/**
	Gets the list of bit rates supported by the data sink.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedRates
	        The supported rates.

	
	*/
	virtual void MacGetSupportedSinkBitRatesL(RArray<TUint>& aSupportedRates) = 0;

	/**
	Gets the list of channels supported by the data sink (ie mono, stereo etc).

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedChannels
	        The supported channels.

	
	*/
	virtual void MacGetSupportedSinkNumChannelsL(RArray<TUint>& aSupportedChannels) = 0;

	/**
	Gets the list of fourCC codes supported by the data sink.

	Warning: Existing objects in this array will be removed by this method.

	@param  aSupportedDataTypes
	        The supported data types.

	
	*/
	virtual void MacGetSupportedSinkDataTypesL(RArray<TFourCC>& aSupportedDataTypes) = 0;
	};

/**
@publishedAll


Custom command parser class to be used by controller plugins wishing to support
audio controller commands.

The controller plugin must be derived from MMMFAudioControllerCustomCommandImplementor
to use this class.

The controller plugin should create an object of this type and add it to the list of custom
command parsers in the controller framework. See the following example code for details.

@code
void CMMFAudioController::ConstructL()
	{
	// Construct custom command parsers
	CMMFAudioPlayDeviceCustomCommandParser* audPlayDevParser = CMMFAudioPlayDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audPlayDevParser);
	AddCustomCommandParserL(*audPlayDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audPlayDevParser

	CMMFAudioRecordDeviceCustomCommandParser* audRecDevParser = CMMFAudioRecordDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audRecDevParser);
	AddCustomCommandParserL(*audRecDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audRecDevParser

etc.
	}
@endcode


*/
class CMMFAudioControllerCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of handling audio controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFAudioControllerCustomCommandParser* NewL(MMMFAudioControllerCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFAudioControllerCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);
private:
	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFAudioControllerCustomCommandParser(MMMFAudioControllerCustomCommandImplementor& aImplementor);
	// Internal request handling methods.
	void DoHandleRequestL(TMMFMessage& aMessage);

	TBool DoSetSourceSampleRateL(TMMFMessage& aMessage);
	TBool DoSetSourceNumChannelsL(TMMFMessage& aMessage);
	TBool DoSetSourceFormatL(TMMFMessage& aMessage);
	TBool DoSetSinkSampleRateL(TMMFMessage& aMessage);
	TBool DoSetSinkNumChannelsL(TMMFMessage& aMessage);
	TBool DoSetSinkFormatL(TMMFMessage& aMessage);
	TBool DoSetCodecL(TMMFMessage& aMessage);
	TBool DoSetSourceBitRateL(TMMFMessage& aMessage);
	TBool DoSetSourceDataTypeL(TMMFMessage& aMessage);
	TBool DoSetSinkBitRateL(TMMFMessage& aMessage);
	TBool DoSetSinkDataTypeL(TMMFMessage& aMessage);
	TBool DoGetSourceSampleRateL(TMMFMessage& aMessage);
	TBool DoGetSourceBitRateL(TMMFMessage& aMessage);
	TBool DoGetSourceNumChannelsL(TMMFMessage& aMessage);
	TBool DoGetSourceFormatL(TMMFMessage& aMessage);
	TBool DoGetSourceDataTypeL(TMMFMessage& aMessage);
	TBool DoGetSinkSampleRateL(TMMFMessage& aMessage);
	TBool DoGetSinkBitRateL(TMMFMessage& aMessage);
	TBool DoGetSinkNumChannelsL(TMMFMessage& aMessage);
	TBool DoGetSinkFormatL(TMMFMessage& aMessage);
	TBool DoGetSinkDataTypeL(TMMFMessage& aMessage);
	TBool DoGetSupportedSourceSampleRatesL(TMMFMessage& aMessage);
	TBool DoGetSupportedSourceBitRatesL(TMMFMessage& aMessage);
	TBool DoGetSupportedSourceNumChannelsL(TMMFMessage& aMessage);
	TBool DoGetSupportedSourceDataTypesL(TMMFMessage& aMessage);
	TBool DoGetSupportedSinkSampleRatesL(TMMFMessage& aMessage);
	TBool DoGetSupportedSinkBitRatesL(TMMFMessage& aMessage);
	TBool DoGetSupportedSinkNumChannelsL(TMMFMessage& aMessage);
	TBool DoGetSupportedSinkDataTypesL(TMMFMessage& aMessage);
	TBool DoCopyArrayDataL(TMMFMessage& aMessage);

	void DoCreateBufFromUintArrayL(RArray<TUint>& aArray);
	void DoCreateBufFromFourCCArrayL(RArray<TFourCC>& aArray);
private:
	/** 
	The object that implements the audio record controller interface 
	*/
	MMMFAudioControllerCustomCommandImplementor& iImplementor;

	CBufFlat* iDataCopyBuffer;
	};


class RWindow;

/**
@publishedAll


Client class to access functionality specific to a video controller.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFVideoControllerCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	
	*/
	IMPORT_C RMMFVideoControllerCustomCommands(RMMFController& aController);

	/**
	Gets the frame size of the clip.

	@param  aVideoFrameSize
	        The frame size, in pixels.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetVideoFrameSize(TSize& aVideoFrameSize) const;

	/**
	Gets the audio type.

	@param  aCodec
	        The FourCC of the audio codec.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetAudioCodec(TFourCC& aCodec) const;

	/**
	Gets the video bit rate.

	@param  aBitRate	
	        The bit rate of the video stream. If this value is KMMFVariableVideoBitRate it signifies
	        a variable bit rate.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetVideoBitRate(TInt& aBitRate) const;

	/**
	Gets the audio bit rate.

	@param aBitRate
	       The bit rate of the audio stream.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetAudioBitRate(TInt& aBitRate) const;

	/**
	Sets the frame rate of the clip.

	@param  aFramesPerSecond
	        The number of frames per second.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetFrameRate(TReal32 aFramesPerSecond) const;

	/**
	Gets the frame rate of the clip.

	@param  aFramesPerSecond
	        The number of frames per second, filled in by the controller plugin.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetFrameRate(TReal32& aFramesPerSecond) const;

	/**
	Gets the video clip MIME type.

	@param  aMimeType
	        The Mime type of the current clip.

	
	*/
	IMPORT_C TInt GetVideoMimeType(TDes8& aMimeType) const;
	};

/**
@publishedAll


Client class to access functionality specific to a video playback controller.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFVideoPlayControllerCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	
	*/
	IMPORT_C RMMFVideoPlayControllerCustomCommands(RMMFController& aController);

	/**
	Prepares the video clip to be accessed.

	A call to this function tells the loaded controller plugin to finalise its configuration
	and to prepare to start reading the video clip.  It is not possible to play the video clip
	or query any of its properties (e.g. duration, meta data etc.) until the controller plugin
	has signified the completion of this method by generating a KMMFEventCategoryVideoPrepareComplete
	event.

	
	*/
	IMPORT_C TInt Prepare();

	/**
	Asks the controller to store the current frame to a bitmap. 

	The video play controller will send an event to the client on completion of the task.

	@param  aBitmap
	        The handle of the CFbsBitmap object to retrieve the frame to.
	@param  aStatus
	        The active object to call back on.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void GetFrame(CFbsBitmap& aBitmap, TRequestStatus& aStatus);

	/**
	Sets the screen region to be used to display the video.

	@param  aWindowRect
	        The window rectangle.
	@param  aClipRect
	        The clip rectangle.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetDisplayWindow(const TRect& aWindowRect, const TRect& aClipRect) const;

	/**
	Updates the display region.

	@param  aRegion
	        The valid region to display to.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt UpdateDisplayRegion(const TRegion& aRegion) const;

	/**
	Queries whether audio is enabled.

	@param  aEnabled
	        A boolean indicating whether audio is enabled.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetAudioEnabled(TBool& aEnabled) const;

	/**
	Sends a direct screen access event to controller.

	@param  aDSAEvent
	        The direct screen access event.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt DirectScreenAccessEvent(const TMMFDSAEvent aDSAEvent) const;

	/**
 	Sets a time window for video playback.

 	@param  aStart
	        The start time in milliseconds relative to the start of the video clip.
  	@param  aEnd
	        The end time in milliseconds relative to the start of the video clip.

  	@return One of the system-wide error codes.

  	
	*/
	IMPORT_C TInt Play(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd) const;

	/**
  	Requests the controller to redraw the current frame.

  	@return One of the system-wide error codes.

  	
	*/
	IMPORT_C TInt RefreshFrame() const;

	/**
	Gets the video loading progress as a percentage.

	@param  aPercentageProgress
	        The progress loading the clip, as a percentage.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetLoadingProgress(TInt& aPercentageProgress) const;

	/**
	Rotates the video image on the screen.

	@param  aRotation
	        The desired rotation to apply.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetRotation(TVideoRotation aRotation) const;

	/**
	Queries the rotation that is currently applied to the video image.

	@param  aRotation
	        The applied rotation.

	@return One of the system wide error codes.

	
	*/
	IMPORT_C TInt GetRotation(TVideoRotation& aRotation) const;

	/**
	Scales the video image to a specified percentage of its original size.

	@param  aWidthPercentage
	        The percentage (100 = original size) to be used to scale the width of the video image.
	@param  aHeightPercentage
	        The percentage (100 = original size) to be used to scale the height of the video image. 
	        If this is not equal to aWidthPercentage then the image may be distorted.
	@param  aAntiAliasFiltering
	        True if anti-aliasing filtering should be used. If the plugin does not
	        support this kind of processing, this value will be ignored.

	@return One of the system wide error codes.

	
	*/
	IMPORT_C TInt SetScaleFactor(TReal32 aWidthPercentage, TReal32 aHeightPercentage, TBool aAntiAliasFiltering) const;

	/**
	Gets the scale factor currently applied to the video image.

	@param  aWidthPercentage
	        On return, will contain the percentage (100 = original size) used to scale the width
	        of the video image.
	@param  aHeightPercentage
	        On return. will contain the percentage (100 = original size) used to scale the height 
	        of the video image.
	@param  aAntiAliasFiltering
	        True if anti-aliasing filtering is being used

	@return One of the system wide error codes.

	
	*/
	IMPORT_C TInt GetScaleFactor(TReal32& aWidthPercentage, TReal32& aHeightPercentage, TBool& aAntiAliasFiltering) const;

	/**
	Selects a region of the video image to be displayed.

	@param  aCropRegion
	        The dimensions of the crop region, relative to the video image.

	@return One of the system wide error codes.

	
	*/
	IMPORT_C TInt SetCropRegion(const TRect& aCropRegion) const;

	/**
	Gets the crop region currently applied to the image.

	@param  aCropRegion
	        The dimensions of the crop region, relative to the video image. If no crop region has
	        been applied, the full dimensions of the video image will be returned.
	
	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetCropRegion(TRect& aCropRegion) const;


private:
	TPckgBuf<TMMFVideoConfig> iConfigPackage;
	};

/**
@publishedAll


Client class to access functionality specific to a video recorder controller.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFVideoRecordControllerCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	
	*/
	IMPORT_C RMMFVideoRecordControllerCustomCommands(RMMFController& aController);

	/**
	Sets the format for the video to record.

	@param  aVideoFormatUid
	        The UID of the video format.

	@return This method will return with one of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetVideoFormat(TUid aVideoFormatUid) const;

	/**
	Sets the video codec for recording.

	@param  aVideoCodec
	        The MIME type of the video codec.

	@return	One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetVideoCodec(const TDesC8& aVideoCodec) const;

	/**
	Sets the video bit rate.

	@param  aBitRate
	        The bit rate of the video stream.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetVideoBitRate(TInt aBitRate) const;

	/**
	Sets the audio bit rate.

	@param  aBitRate
	        The bit rate of the audio stream.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetAudioBitRate(TInt aBitRate) const;

	/**
	Sets the audio codec for recording.

	@param  aAudioCodec
	        The FourCC code of the audio codec.

	@return	One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetAudioCodec(TFourCC aAudioCodec) const;

	/**
	Sets the frame size of the clip.

	@param  aVideoFrameSize
	        The frame size, in pixels.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetVideoFrameSize(TSize aVideoFrameSize) const;

	/**
	Sets the maximum size of the recorded clip, in bytes.

	@param  aMaxSize
	        The maximum size of the recorded clip, in bytes. This can be called with the parameter 
	        KMMFNoMaxClipSize which signifies no maximum file size.

	@return	One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetMaxFileSize(TInt aMaxSize) const;

	/**
	Adds meta data to the clip.

	@param  aNewEntry
	        The details of the new entry to be added.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C void AddMetaDataEntryL(const CMMFMetaDataEntry& aNewEntry)const;

	/**
	Removes a meta data entry from the clip.

	@param  aIndex
	        The ID of the meta data entry to delete.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt RemoveMetaDataEntry(TInt aIndex)const;

	/**
	Replaces a meta data in the clip.

	@param  aIndex
	        The ID of the meta data entry to replace.
	@param  aNewEntry
	        The details of the new entry to be added.

	
	*/
	IMPORT_C void ReplaceMetaDataEntryL(TInt aIndex, const CMMFMetaDataEntry& aNewEntry)const;

	/**
	Sets whether audio is enabled.

	@param  aEnable
	        A boolean indicating if audio should be enabled.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetAudioEnabled(TBool aEnable) const;

	/**
	Prepares the controller for recording. This should be called before the first attempt to record 
	with the controller.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt Prepare() const;

	/**
	Sets the handle of the camera to use.

	@param  aCameraHandle
	        The handle of the camera to use.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt SetCameraHandle(TInt aCameraHandle) const;

	/**
	Gets the (possibly estimated) record time left in the clip.

	@param  aTime
	        The record time available, in microseconds.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetRecordTimeAvailable(TTimeIntervalMicroSeconds& aTime) const;

	/**
	Gets the supported sink audio types.

	@param  aSupportedDataTypes
	        The supported data types.

	
	*/
	IMPORT_C TInt GetSupportedSinkAudioTypes(RArray<TFourCC>& aSupportedDataTypes) const;

	/**
	Gets the supported sink video types.

	@param  aDataTypes
	        The supported data types.

	
	*/
	IMPORT_C TInt GetSupportedSinkVideoTypes(CDesC8Array& aDataTypes) const;

	// INC23777
	/**
	Retrieves whether audio is enabled.

	@param  aEnabled
	        A boolean indicating whether audio is enabled.

	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt GetAudioEnabled(TBool& aEnabled) const;

private:
	void DoGetCDesC8ArrayL(CDesC8Array& aArray, TMMFVideoRecordControllerMessages aIpc) const;
	void DoGetFourCCArrayL(RArray<TFourCC>& aArray) const;
	};



/**
@publishedAll


Mixin class to be derived from controller plugins that could support the video record controller 
custom commands.
*/
class MMMFVideoRecordControllerCustomCommandImplementor
	{
public:

	/**
	Sets the format for the video to record.

	@param  aVideoFormatUid
	        The UID of the video format.

	@return One of the system-wide error codes.

	
	*/
	virtual void MvrcSetVideoFormatL(TUid aVideoFormatUid)=0;

	/**
	Sets the video codec for recording.

	@param  aVideoCodec
	        The MIME type of the video codec.

	@return One of the system-wide error codes.

	
	*/
	virtual void MvrcSetVideoCodecL(const TDesC8& aVideoCodec)=0;

	/**
	Sets the audio codec for recording.

	@param  aAudioCodec
	        The FourCC code of the audio codec.

	@return One of the system-wide error codes.

	
	*/
	virtual void MvrcSetAudioCodecL(TFourCC aAudioCodec)=0;

	/**
	Sets the video bit rate.

	@param  aBitRate
	        The bit rate of the video stream. This can be called with the parameter 
	        KMMFVariableVideoBitRate which specifies a variable bit rate.

	@return One of the system-wide error codes.

	
	*/
	virtual void MvrcSetVideoBitRateL(TInt& aBitRate)=0;

	/**
	Sets the audio bit rate.

	@param  aBitRate
	        The bit rate of the audio stream.

	@return One of the system-wide error codes.

	
	*/
	virtual void MvrcSetAudioBitRateL(TInt& aBitRate)=0;

	/**
	Adds meta data to the clip.

	@param  aNewEntry
	        The details of the new entry to be added.

	
	*/
	virtual void MvrcAddMetaDataEntryL(const CMMFMetaDataEntry& aNewEntry)=0;

	/**
	Removes a meta data entry from the clip.

	@param  aIndex
	        The ID of the meta data entry to delete.

	
	*/
	virtual void MvrcRemoveMetaDataEntryL(TInt aIndex)=0;

	/**
	Replaces a meta data in the clip.

	@param  aIndex
	        The ID of the meta data entry to replace.
	@param  aNewEntry
	        The details of the new entry to be added.

	
	*/
	virtual void MvrcReplaceMetaDataEntryL(TInt aIndex, const CMMFMetaDataEntry& aNewEntry)=0;

	/**
	Sets the maximum file size.

	@param  aMaxFileSize
	        The maximum file size allowed for recording. This can be called with the parameter
	        KMMFNoMaxClipSize which signifies no maximum file size.

	
	*/
	virtual void MvrcSetMaxFileSizeL(TInt aMaxFileSize)=0;

	/**
	Sets whether audio is enabled.

	@param  aEnable
	        A boolean indicating if audio is enabled.

	
	*/
	virtual void MvrcSetAudioEnabledL(TBool aEnable)=0;

	/**
	Sets the frame size for the video recording.

	@param  aFrameSize
	        The frame size for recording.

	
	*/
	virtual void MvrcSetVideoFrameSizeL(TSize aFrameSize)=0;

	/**
	Prepares the controller for recording. This needs to be called before
	the first call to Record().

	
	*/
	virtual void MvrcPrepareL()=0;

	/**
	Sets the handle of the camera to use for recording.

	
	*/
	virtual void MvrcSetCameraHandleL(TInt aCameraHandle)=0;

	/**
	Gets the (possibly estimated) record time left in the clip.

	@param  aTime
	        The record time available, in microseconds.

	
	*/
	virtual void MvrcGetRecordTimeAvailableL(TTimeIntervalMicroSeconds& aTime) = 0;

	/**
	Gets the supported sink audio types.

	@param  aDataTypes
	        The supported data types.

	@return One of the system-wide error codes.

	
	*/
	virtual void MvrcGetSupportedSinkAudioTypesL(RArray<TFourCC>& aDataTypes)=0;

	/**
	Gets the supported sink video types.

	@param  aDataTypes
	        The supported data types.

	@return One of the system-wide error codes.

	
	*/
	virtual void MvrcGetSupportedSinkVideoTypesL(CDesC8Array& aDataTypes)=0;

	//INC23777
	/**
	Indicates if the audio is enabled.

	@param  aEnabled
	        A boolean indicating if the audio is enabled.

	
	*/
	virtual void MvrcGetAudioEnabledL(TBool& aEnabled)=0;
	};


/**
@publishedAll


Client class to access functionality specific to a video playback controller.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class MMMFVideoPlayControllerCustomCommandImplementor
	{
public:

	/**
	Prepares the video clip to be accessed.

	A call to this method tells the controller plugin to finalise its configuration
	and to prepare to start reading the video clip.  It is not possible to play the video clip
	or query any of its properties (e.g. duration, meta data etc.) until the controller plugin
	has signified the completion of this method by generating a 
	KMMFEventCategoryVideoPrepareComplete event.

	
	*/
	virtual void MvpcPrepare()=0;

	/**
	Gets a frame previously requested from the controller.

	@param  aVideoFrame
	        The handle of bitmap to retrieve frame to.

	
	*/
	virtual void MvpcGetFrameL(MMMFVideoFrameMessage& aVideoFrame)=0;

	/**
	Indicates whether audio is enabled.

	@param  aEnabled
	        On return, contains a boolean indicating whether audio is enabled.

	
	*/
	virtual void MvpcGetAudioEnabledL(TBool& aEnabled)=0;

	/**
	Sets the screen region to be used to display the video.

	@param  aClipRect
	        The clip rect used to display the video.

	
	*/
	virtual void MvpcSetDisplayWindowL(const TRect& aWindowRect, const TRect& aClipRect) = 0;

	/**
	Updates the region to display.

	@param  aRegion
	        A TRegion containing the current display regions, ownership of the TRegion is not
	        transferred.

	
	*/
	virtual void MvpcUpdateDisplayRegionL(const TRegion& aRegion) = 0;

	/**
	Pauses/Resumes video playback. This is to be used with direct screen access
	to indicate that the display has changed and should not be written to. This
	does not affect audio playback.

	@param  aDSAEvent
	        Whether the video display should be active.

	
	*/
	virtual void MvpcDirectScreenAccessEventL(const TMMFDSAEvent aDSAEvent) = 0;

	/**
 	Sets a time window for video playback.

 	@param  aStart
	        Start time in milliseconds relative to the start of the video clip.
  	@param  aEnd
	        End time in milliseconds relative to the start of the video clip.

  	
	*/
	virtual void MvpcPlayL(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd) = 0;
	
	/**
  	Requests the controller to redraw the current frame.

  	
	*/
	virtual void MvpcRefreshFrameL() = 0;

	/**
	Gets the progress of loading a video clip.

	@param  aPercentageComplete
	        The progress loading the clip, as a percentage.

	
	*/
	virtual void MvpcGetLoadingProgressL(TInt& aPercentageComplete) = 0;

	/**
	Rotates the video image on the screen.

	@param  aRotation
	        The desired rotation to apply.

	
	*/
	virtual void MvpcSetRotationL(TVideoRotation aRotation) = 0;

	/**
	Queries the rotation that is currently applied to the video image.

	@param  aRotation
	        The applied rotation.

	
	*/
	virtual void MvpcGetRotationL(TVideoRotation& aRotation) = 0;

	/**
	Scales the video image to a specified percentage of its original size.

	@param  aWidthPercentage
	        The percentage (100 = original size) to be used to scale the width of the video image.
	@param  aHeightPercentage
	        The percentage (100 = original size) to be used to scale the height of the video image. 
	        If this is not equal to aWidthPercentage then the image may be distorted.
	@param  aAntiAliasFiltering
	        A boolean indicating if anit-aliasing filtering should be used. ETrue if anti-aliasing 
	        should be used.  If the plugin does not support this kind of processing, this value will 
	        be ignored.

	
	*/
	virtual void MvpcSetScaleFactorL(TReal32 aWidthPercentage, TReal32 aHeightPercentage, TBool aAntiAliasFiltering) = 0;

	/**
	Gets the scale factor currently applied to the video image.

	@param  aWidthPercentage
	        The percentage (100 = original size) used to scale the width of the video image will be 
	        copied into here.
	@param  aHeightPercentage
	        The percentage (100 = original size) used to scale the height of the video image will be 
	        copied into here.
	@param  aAntiAliasFiltering
	        A boolean indicating if anti-aliasing filtering should be used. ETrue if anti-aliasing 
	        filtering is being used, EFalse if not.

	
	*/
	virtual void MvpcGetScaleFactorL(TReal32& aWidthPercentage, TReal32& aHeightPercentage, TBool& aAntiAliasFiltering) = 0;

	/**
	Selects a region of the video image to be displayed.

	@param  aCropRegion
	        The dimensions of the crop region, relative to the video image.

	
	*/
	virtual void MvpcSetCropRegionL(const TRect& aCropRegion) = 0;

	/**
	Gets the crop region currently applied to the image

	@param  aCropRegion
	        The dimensions of the crop region, relative to the video image. If no crop region has 
	        been applied, the full dimensions of the video image will be returned.

	
	*/
	virtual void MvpcGetCropRegionL(TRect& aCropRegion) = 0;
	};



/**
@publishedAll


Mixin class to be derived from controller plugins that could support the video record controller
custom commands.
*/
class MMMFVideoControllerCustomCommandImplementor
	{
public:

	/**
	Gets the frame size of the clip.

	@param  aVideoFrameSize
	        The frame size, in pixels.

	
	*/
	virtual void MvcGetVideoFrameSizeL(TSize& aVideoFrameSize)=0;

	/**
	Gets the audio type.

	@param  aCodec
	        The FourCC of the audio codec.

	
	*/
	virtual void MvcGetAudioCodecL(TFourCC& aCodec)=0;

	/**
	Gets the video bit rate.

	@param  aBitRate
	        The bit rate of the video stream. If this value is KMMFVariableVideoBitRate it signifies
	        a variable bit rate.

	
	*/
	virtual void MvcGetVideoBitRateL(TInt& aBitRate)=0;

	/**
	Gets the audio bit rate.

	@param  aBitRate
	        The bit rate of the audio stream.

	
	*/
	virtual void MvcGetAudioBitRateL(TInt& aBitRate)=0;

	/**
	Sets the frame rate of the clip.

	@param  aFramesPerSecond
	        The number of frames per second.

	
	*/
	virtual void MvcSetFrameRateL(TReal32 aFramesPerSecond)=0;

	/**
	Gets the frame rate of the clip.

	@param  aFramesPerSecond
	        The number of frames per second, filled in by the controller plugin.

	
	*/
	virtual void MvcGetFrameRateL(TReal32& aFramesPerSecond)=0;

	/**
	Gets the supported sink video types.

	@param  aMimeType
	        The supported data types.

	
	*/
	virtual void MvcGetVideoMimeTypeL(TDes8& aMimeType)=0;
	};


/**
@publishedAll


Custom command parser class to be used by controller plugins wishing to support
video controller commands.

The controller plugin must be derived from MMMFVideoControllerCustomCommandImplementor
to use this class.

The controller plugin should create an object of this type and add it to the list of custom
command parsers in the controller framework.  See the following example code for details.

@code
void CMMFAudioController::ConstructL()
	{
	// Construct custom command parsers
	CMMFAudioPlayDeviceCustomCommandParser* audPlayDevParser = CMMFAudioPlayDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audPlayDevParser);
	AddCustomCommandParserL(*audPlayDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audPlayDevParser

	CMMFAudioRecordDeviceCustomCommandParser* audRecDevParser = CMMFAudioRecordDeviceCustomCommandParser::NewL(*this);
	CleanupStack::PushL(audRecDevParser);
	AddCustomCommandParserL(*audRecDevParser); //parser now owned by controller framework
	CleanupStack::Pop();//audRecDevParser

etc.
	}
@endcode



*/
class CMMFVideoControllerCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of handling video controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return	A pointer to the object created.

	
	*/
	IMPORT_C static CMMFVideoControllerCustomCommandParser* NewL(MMMFVideoControllerCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFVideoControllerCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);
private:

	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFVideoControllerCustomCommandParser(MMMFVideoControllerCustomCommandImplementor& aImplementor);
	// Internal request handling methods.
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoGetAudioCodecL(TMMFMessage& aMessage);

	TBool DoGetAudioBitRateL(TMMFMessage& aMessage);
	TBool DoGetVideoBitRateL(TMMFMessage& aMessage);
	TBool DoGetVideoFrameSizeL(TMMFMessage& aMessage);
	TBool DoSetFrameRateL(TMMFMessage& aMessage);
	TBool DoGetFrameRateL(TMMFMessage& aMessage);
	TBool DoGetVideoMimeTypeL(TMMFMessage& aMessage);
private:
	/** 
	The object that implements the video record controller interface 
	*/
	MMMFVideoControllerCustomCommandImplementor& iImplementor;
	};

/**
@publishedAll


Custom command parser class to be used by controller plugins wishing to support video play 
controller commands.

The controller plugin must be derived from MMMFVideoPlayControllerCustomCommandImplementor to use 
this class. The controller plugin should create an object of this type and add it to the list of 
custom command parsers in the controller framework.
*/
class CMMFVideoPlayControllerCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of handling video controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFVideoPlayControllerCustomCommandParser* NewL(MMMFVideoPlayControllerCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFVideoPlayControllerCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);
private:
	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFVideoPlayControllerCustomCommandParser(MMMFVideoPlayControllerCustomCommandImplementor& aImplementor);
	// Internal request handling methods.
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoRequestFrameL(TMMFMessage& aMessage);
	TBool DoGetFrameL(TMMFMessage& aMessage);
	TBool DoSetDisplayWindowL(TMMFMessage& aMessage);
	TBool DoUpdateDisplayRegionL(TMMFMessage& aMessage);
	TBool DoGetAudioEnabledL(TMMFMessage& aMessage);
	TBool DoDirectScreenAccessEventL(TMMFMessage& aMessage);
	TBool DoPlayL(TMMFMessage& aMessage);
	TBool DoRefreshFrameL(TMMFMessage& aMessage);
	TBool DoGetLoadingProgressL(TMMFMessage& aMessage);
	TBool DoPrepareL(TMMFMessage& aMessage);
	TBool DoSetRotationL(TMMFMessage& aMessage);
	TBool DoGetRotationL(TMMFMessage& aMessage);
	TBool DoSetScaleFactorL(TMMFMessage& aMessage);
	TBool DoGetScaleFactorL(TMMFMessage& aMessage);
	TBool DoSetCropRegionL(TMMFMessage& aMessage);
	TBool DoGetCropRegionL(TMMFMessage& aMessage);


private:
	/** 
	The object that implements the video record controller interface 
	*/
	MMMFVideoPlayControllerCustomCommandImplementor& iImplementor;
	CMMFVideoFrameMessage* iVideoFrameMessage;
	};

/**
@publishedAll


Custom command parser class to be used by controller plugins wishing to support video record 
controller commands.

The controller plugin must be derived from MMMFVideoRecordControllerCustomCommandImplementor to use 
this class. The controller plugin should create an object of this type and add it to the list of 
custom command parsers in the controller framework.
*/
class CMMFVideoRecordControllerCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of handling video controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFVideoRecordControllerCustomCommandParser* NewL(MMMFVideoRecordControllerCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFVideoRecordControllerCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);
private:
	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFVideoRecordControllerCustomCommandParser(MMMFVideoRecordControllerCustomCommandImplementor& aImplementor);
	// Internal request handling methods.
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetVideoFormatL(TMMFMessage& aMessage);
	TBool DoSetAudioBitRateL(TMMFMessage& aMessage);
	TBool DoSetVideoBitRateL(TMMFMessage& aMessage);
	TBool DoSetVideoCodecL(TMMFMessage& aMessage);
	TBool DoSetAudioCodecL(TMMFMessage& aMessage);
	TBool DoAddMetaDataEntryL(TMMFMessage& aMessage);
	TBool DoRemoveMetaDataEntryL(TMMFMessage& aMessage);
	TBool DoReplaceMetaDataEntryL(TMMFMessage& aMessage);
	TBool DoSetMaxFileSizeL(TMMFMessage& aMessage);
	TBool DoSetAudioEnabledL(TMMFMessage& aMessage);
	TBool DoSetVideoFrameSizeL(TMMFMessage& aMessage);
	TBool DoPrepareL(TMMFMessage& aMessage);
	TBool DoSetCameraHandleL(TMMFMessage& aMessage);
	TBool DoGetRecordTimeAvailableL(TMMFMessage& aMessage);

	TBool DoGetSupportedSinkAudioTypesL(TMMFMessage& aMessage);
	TBool DoGetSupportedSinkVideoTypesL(TMMFMessage& aMessage);

	TInt32 DoCreateBufFromCDesC8ArrayL(CDesC8Array& aArray);
	TBool DoCopyCDesC8ArrayDataL(TMMFMessage& aMessage);

	TBool DoCopyFourCCArrayDataL(TMMFMessage& aMessage);
	void DoCreateBufFromFourCCArrayL(RArray<TFourCC>& aArray);
	TBool DoGetAudioEnabledL(TMMFMessage& aMessage); // (INC23777)

private:
	/** 
	The object that implements the video record controller interface 
	*/
	MMMFVideoRecordControllerCustomCommandImplementor& iImplementor;
	CBufFlat* iDataCopyBuffer;
	};



/**
@publishedAll


Client class to allow the client to specify DRM Intent.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFVideoDRMExtCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	
	*/
	IMPORT_C RMMFVideoDRMExtCustomCommands(RMMFController& aController);

	/**
	Gets a frame previously requested from the controller.

	@param  aBitmap
	        The handle of bitmap to retrieve frame to.
	@param  aIntent
	        The DRM Intent to pass in.
	@param  aStatus
	        The active object to call back on.
	*/
	IMPORT_C void GetFrame(CFbsBitmap& aBitmap, ContentAccess::TIntent aIntent, TRequestStatus& aStatus);

private:
	TPckgBuf<TMMFVideoConfig> iConfigPackage;
	TPckgBuf<ContentAccess::TIntent> iIntentPackage;
	};



/**
@publishedAll


Mixin class to be derived from controller plugins that could support the DRM Intent
custom commands.
*/
class MMMFVideoDRMExtCustomCommandImplementor
	{
public:

	/**
	Gets a frame previously requested from the controller.

	@param  aVideoFrame
	        The callback interface to allow the caller to retrieve a bitmap.
	@param  aIntent
	        The DRM Intent to supply.
	*/
	virtual void MvdeGetFrameL(MMMFVideoFrameMessage& aVideoFrame, ContentAccess::TIntent aIntent)=0;
	};


/**
@publishedAll


Client class to provide DRM extensions to video controllers.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.
*/
class CMMFVideoDRMExtCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of DRM Intent controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFVideoDRMExtCustomCommandParser* NewL(MMMFVideoDRMExtCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFVideoDRMExtCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.
	
	*/
	CMMFVideoDRMExtCustomCommandParser(MMMFVideoDRMExtCustomCommandImplementor& aImplementor);
	// Internal request handling methods.

	void DoGetFrameL(TMMFMessage& aMessage);

private:
	MMMFVideoDRMExtCustomCommandImplementor& iImplementor;
	CMMFVideoFrameMessage* iVideoFrameMessage;
	};

/**
@publishedAll


Client class to allow the client to register notification .

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.


*/
class RMMFResourceNotificationCustomCommands : public RMMFCustomCommandsBase
	{
public:
	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	
	*/
	IMPORT_C RMMFResourceNotificationCustomCommands(RMMFController& aController);
	
	/**
	Registers the Event for Notification when resource is avaliable.

	@param aEventType
		The Event to notify the client.
		
	@param aNotificationRegistrationData
		Notification registration specific data.

	@return An error code indicating if the registration was successful. KErrNone on success, 
		otherwise another of the system-wide error codes.
	*/
	IMPORT_C TInt RegisterAsClient(TUid aEventType,const TDesC8& aNotificationRegistrationData);
	
	/**
	Cancels the registered notification event.

	@param  aEventType
		The Event to notify the client.
		
	@return An error code indicating if the cancel registration was successful. KErrNone on success, 
		otherwise another of the system-wide error codes.
	*/
	IMPORT_C TInt CancelRegisterAsClient(TUid aEventType);
	
	/**
	Gets the notification data for the event.
	
	@param  aEventType
		The Event to notify the client.
		
	@param aNotificationData
		The Notification data for the client to resume the play.
		
	@return An error code indicating if the get notification data was successful. KErrNone on success, 
		otherwise another of the system-wide error codes.
	*/
	IMPORT_C TInt GetResourceNotificationData(TUid aEventType,TDes8& aNotificationData);
	
	/**
	Waits for the client to resume the play even after the default timer expires.

	@return An error code indicating if the registration was successful. KErrNone on success, 
			otherwise any of the system-wide error codes.
	*/
	IMPORT_C TInt WillResumePlay();
	};

/**
@publishedAll


Mixin class to be derived from controller plugins that could support the audio resource notification
custom commands.
*/
class MMMFResourceNotificationCustomCommandImplementor
	{
public:
	/**
	Registers the Event for Notification when resource is available.

	@param aEventType
		The event which the client is notified of.
		
	@param aNotificationRegistrationData
		Notification registration specific data, which has been reserved for future use.
		
	@leave	This method may leave with one of the system-wide error codes.  KErrNotReady if there is no
			data sink.
	*/
	virtual void MarnRegisterAsClientL(TUid aEventType,const TDesC8& aNotificationRegistrationData) = 0;
	
	/**
	Cancels the registered notification event.

	@param  aEventType
		The event to cancel.
		
	@leave This method may leave with one of the system-wide error codes.  KErrNotReady if there is no
			data sink.
	*/
	virtual void MarnCancelRegisterAsClientL(TUid aEventType) = 0;
	
	/**
	Gets the notification data for the event.
	
	@param  aEventType
		The event which the client is notified of.
		
	@param aNotificationData
		The Notification data for the client to resume playing.
		
	@leave This method may leave with one of the system-wide error codes.  KErrNotReady if there is no
			data sink, KErrArgument if unable to provide the notification data.
	*/
	virtual void MarnGetResourceNotificationDataL(TUid aEventType,TDes8& aNotificationData) = 0;
	
	/**
	Waits for the client to resume the play even after the default timer expires.
		
	@leave This method may leave with one of the system-wide error codes.  KErrNotReady if there is no
			data sink.
	*/
	virtual void MarnWillResumePlayL() = 0;
	};

/**
@publishedAll


Client class to provide Audio resource notification controllers.

The class uses the custom command function of the controller plugin, and removes the necessity
for the client to formulate the custom commands.
*/
class CMMFResourceNotificationCustomCommandParser: public CMMFCustomCommandParserBase
	{
public:	
	/**
	Creates a new custom command parser capable of handling resource notification controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFResourceNotificationCustomCommandParser* NewL(MMMFResourceNotificationCustomCommandImplementor& aImplementor);
	
	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFResourceNotificationCustomCommandParser();
	
	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	
	*/
	CMMFResourceNotificationCustomCommandParser(MMMFResourceNotificationCustomCommandImplementor& aImplementor);
	void DoHandleRequestL(TMMFMessage& aMessage);
	// Internal request handling methods.
	TBool DoRegisterAsClientL(TMMFMessage& aMessage);
	TBool DoCancelRegisterAsClientL(TMMFMessage& aMessage);
	TBool DoGetResourceNotificationDataL(TMMFMessage& aMessage);
	TBool DoWillResumePlayL(TMMFMessage& aMessage);
private:
    MMMFResourceNotificationCustomCommandImplementor& iImplementor;
	};

/**
@publishedPartner
@prototype

Client class to allow setting the initial screen for video display.

*/
class RMMFVideoSetInitScreenCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	*/
	IMPORT_C RMMFVideoSetInitScreenCustomCommands(RMMFController& aController);

	/**
	Sets the initial screen number for the video display on the controller.

	@param  aScreenNumber
	        The screen number
	
	*/
	IMPORT_C TInt SetInitScreenNumber(TInt aScreenNumber);
	};



/**
@publishedPartner
@prototype

Mixin class to be derived from controller plugins that could support setting the initial screen for displaying video.
*/
class MMMFVideoSetInitScreenCustomCommandImplementor
	{
public:

	/**
	Sets the initial screen number.

	@param  aScreenNumber
	        The screen number
	*/
	virtual void MvsdSetInitScreenNumber(TInt aScreenNumber)=0;
	};


/**
@publishedPartner
@prototype

Custom command parser class to be used by controller plugins wishing to support setting the initial screen
number for the video display.

The controller plugin should create an object of this type and add it to the list of custom command parsers 
in the controller framework. The controller plugin must be derived from MMMFVideoSetInitScreenCustomCommandImplementor 
to use this class. 
*/
class CMMFVideoSetInitScreenCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser that supports setting screen device for video dusplay.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	*/
	IMPORT_C static CMMFVideoSetInitScreenCustomCommandParser* NewL(MMMFVideoSetInitScreenCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	*/
	IMPORT_C ~CMMFVideoSetInitScreenCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.
	*/
	CMMFVideoSetInitScreenCustomCommandParser(MMMFVideoSetInitScreenCustomCommandImplementor& aImplementor);
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetInitScreenNumberL(TMMFMessage& aMessage);

private:
	MMMFVideoSetInitScreenCustomCommandImplementor& iImplementor;
	};


/**
@publishedPartner
@prototype

Client class to allow setting and getting the pixel aspect ratio for video recording.

*/
class RMMFVideoPixelAspectRatioCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	*/
	IMPORT_C RMMFVideoPixelAspectRatioCustomCommands(RMMFController& aController);

	/**
	Sets the pixel aspect ratio for the video recording on the controller.

	@param  aAspectRatio
	        The new pixel aspect ratio. The default pixel aspect ratio is 1:1.
	
	@return One of the system-wide error codes.
	
	*/
	IMPORT_C TInt SetPixelAspectRatio(const TVideoAspectRatio& aAspectRatio);
	
	/**
	Gets the current pixel aspect ratio for the video recording on the controller.

	@param  aAspectRatio
	        The current video pixel aspect ratio.

	@return One of the system-wide error codes.	
	*/
	IMPORT_C TInt GetPixelAspectRatio(TVideoAspectRatio& aAspectRatio) const;
	
	/**
	Gets the list of supported pixel aspect ratios for the video recording on the controller.

	@param  aAspectRatios
	        The supported pixel aspect ratios.
	
	@leave	This method may leave with one of the system-wide error codes.
	*/
	IMPORT_C void GetSupportedPixelAspectRatiosL(RArray<TVideoAspectRatio>& aAspectRatios) const;

private:
	void DoGetVideoPixelAspectRatioArrayL(RArray<TVideoAspectRatio>& aArray, TMMFVideoPixelAspectRatioMessages aIpc) const;
	};


/**
@publishedPartner
@prototype

Mixin class to be derived from controller plug-ins that could support setting and getting the pixel aspect ratio for video recording. 
*/
class MMMFVideoPixelAspectRatioCustomCommandImplementor
	{
public:

	/**
	Sets the pixel aspect ratio.

	@param  aAspectRatio
	        The pixel aspect ratio to use.
	*/
	virtual void MvparSetPixelAspectRatioL(const TVideoAspectRatio& aAspectRatio) = 0;

	/**
	Gets the current pixel aspect ratio.

	@param  aAspectRatio
	        The current pixel aspect ratio.
	*/
	virtual void MvparGetPixelAspectRatioL(TVideoAspectRatio& aAspectRatio) = 0;
	
	/**
	Gets the list of supported pixel aspect ratios.

	@param  aAspectRatios
	        The list of supported pixel aspect ratios.
	*/
	virtual void MvparGetSupportedPixelAspectRatiosL(RArray<TVideoAspectRatio>& aAspectRatios) = 0;
	};


/**
@publishedPartner
@prototype

Custom command parser class to be used by controller plug-ins wishing to support setting and getting the pixel aspect 
ratio for the video recording.

The controller plug-in should create an object of this type and add it to the list of custom command parsers 
in the controller framework. The controller plug-in must be derived from MMMFVideoPixelAspectRatioCustomCommandImplementor 
to use this class. 
*/
class CMMFVideoPixelAspectRatioCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser that supports setting and getting pixel aspect ratio for video recording.

	@param  aImplementor
	        A reference to the controller plug-in that owns this new object.

	@return A pointer to the object created.

	*/
	IMPORT_C static CMMFVideoPixelAspectRatioCustomCommandParser* NewL(MMMFVideoPixelAspectRatioCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	*/
	IMPORT_C ~CMMFVideoPixelAspectRatioCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	CMMFVideoPixelAspectRatioCustomCommandParser(MMMFVideoPixelAspectRatioCustomCommandImplementor& aImplementor);
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetPixelAspectRatioL(TMMFMessage& aMessage);
	TBool DoGetPixelAspectRatioL(TMMFMessage& aMessage);
	TBool DoGetSupportedPixelAspectRatiosL(TMMFMessage& aMessage);
	TBool DoCopyArrayDataL(TMMFMessage& aMessage);
	void DoCreateBufFromVideoAspectRatioArrayL(RArray<TVideoAspectRatio>& aArray);

private:
	MMMFVideoPixelAspectRatioCustomCommandImplementor& iImplementor;
	
	CBufFlat* iDataCopyBuffer;
	};


/**
@publishedPartner
@prototype

Client class to allow the audio sampling rate and channels configuration for video recording.

*/
class RMMFVideoAudioSamplingRateAndChannelConfigCustomCommands : public RMMFCustomCommandsBase
	{
public:

	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.

	*/
	IMPORT_C RMMFVideoAudioSamplingRateAndChannelConfigCustomCommands(RMMFController& aController);

	/**
	Sets the number of audio channels to record (1 for mono, 2 for stereo).

	@param  aChannels
	        The number of audio channels to record.

	@return One of the system-wide error codes.
	
	*/
	IMPORT_C TInt SetAudioChannels(const TUint aChannels);

	/**
	Gets the current number of audio channels to record (1 for mono, 2 for stereo).

	@param  aChannels
	        The current number of audio channels to record.

	@return One of the system-wide error codes.
	
	*/
	IMPORT_C TInt GetAudioChannels(TUint& aChannels) const;

	/**
	Gets the list of supported number of audio channels for video recording.

	@param  aChannels
	        The supported numbers of audio channels.
	
	@leave	This method may leave with one of the system-wide error codes.
	*/
	IMPORT_C void GetSupportedAudioChannelsL(RArray<TUint>& aChannels) const;
	
	/**
	Sets the audio sample rate for video recording.

	@param  aSampleRate
	        The sample rate for audio recording.

	@return One of the system-wide error codes.
	
	*/
	IMPORT_C TInt SetAudioSampleRate(const TUint aSampleRate);

	/**
	Gets the current audio sample rate for recording.

	@param  aSampleRate
	        The current audio sample rate for recording.

	@return One of the system-wide error codes.
	
	*/
	IMPORT_C TInt GetAudioSampleRate(TUint& aSampleRate) const;

	/**
	Gets the list of supported audio sample rates for video recording.

	@param  aSampleRates
	        The supported audio sample rates.
	
	@leave	This method may leave with one of the system-wide error codes.
	*/
	IMPORT_C void GetSupportedAudioSampleRatesL(RArray<TUint>& aSampleRates) const;
	
private:
	void DoGetUintArrayL(RArray<TUint>& aArray, TMMFVideoAudioSamplingRateAndChannelConfigMessages aIpc) const;
	};


/**
@publishedPartner
@prototype

Mixin class to be derived from controller plug-ins that could support the audio sampling rate and channels configuration. 
*/
class MMMFVideoAudioSamplingRateAndChannelConfigCustomCommandImplementor
	{
public:

	/**
	Sets the number of audio channels.

	@param  aChannels
	        The number of audio channels to use.
	*/
	virtual void MvasrccSetAudioChannelsL(const TUint aChannels) = 0;

	/**
	Gets the current number of audio channels.

	@param  aChannels
	        The current number of audio channels.
	*/
	virtual void MvasrccGetAudioChannelsL(TUint& aChannels) = 0;

	/**
	Gets the list of supported number of audio channels.

	@param  aChannels
	        The list of supported number of audio channels.
	*/
	virtual void MvasrccGetSupportedAudioChannelsL(RArray<TUint>& aChannels) = 0;
	
	/**
	Sets the audio sample rate.

	@param  aSampleRate
	        The audio sample rate to use.
	*/
	virtual void MvasrccSetAudioSampleRateL(const TUint aSampleRate) = 0;

	/**
	Gets the current audio sample rate.

	@param  aSampleRate
	        The current audio sample rate.
	*/
	virtual void MvasrccGetAudioSampleRateL(TUint& aSampleRate) = 0;

	/**
	Gets the list of supported audio sample rates.

	@param  aSampleRates
	        The list of supported audio sample rates.
	*/
	virtual void MvasrccGetSupportedAudioSampleRatesL(RArray<TUint>& aSampleRates) = 0;
	};

/**
@publishedPartner
@prototype

Custom command parser class to be used by controller plug-ins wishing to support the audio sampling rate and channels
configuration for the video recording.

The controller plug-in should create an object of this type and add it to the list of custom command parsers 
in the controller framework. The controller plug-in must be derived from MMMFVideoAudioSamplingRateAndChannelConfigCustomCommandImplementor 
to use this class. 
*/
class CMMFVideoAudioSamplingRateAndChannelConfigCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser that supports the audio sampling rate and channels configuration for video recording.

	@param  aImplementor
	        A reference to the controller plug-in that owns this new object.

	@return A pointer to the object created.

	*/
	IMPORT_C static CMMFVideoAudioSamplingRateAndChannelConfigCustomCommandParser* NewL(MMMFVideoAudioSamplingRateAndChannelConfigCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	*/
	IMPORT_C ~CMMFVideoAudioSamplingRateAndChannelConfigCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	CMMFVideoAudioSamplingRateAndChannelConfigCustomCommandParser(MMMFVideoAudioSamplingRateAndChannelConfigCustomCommandImplementor& aImplementor);
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetAudioChannelsL(TMMFMessage& aMessage);
	TBool DoGetAudioChannelsL(TMMFMessage& aMessage);
	TBool DoGetSupportedAudioChannelsL(TMMFMessage& aMessage);
	
	TBool DoSetAudioSampleRateL(TMMFMessage& aMessage);
	TBool DoGetAudioSampleRateL(TMMFMessage& aMessage);
	TBool DoGetSupportedAudioSampleRatesL(TMMFMessage& aMessage);
	
	TBool DoCopyArrayDataL(TMMFMessage& aMessage);
	
	void DoCreateBufFromUintArrayL(RArray<TUint>& aArray);

private:
	MMMFVideoAudioSamplingRateAndChannelConfigCustomCommandImplementor& iImplementor;
	
	CBufFlat* iDataCopyBuffer;
	};

/**
@publishedPartner
@prototype
*/
const TUid KUidInterfaceMMFVideoPlayExt = {0x10283437};	

/**
Mixin class to be derived from controller plug-ins that could support
play velocity, enabling/disabling audio/video, and auto scaling.

@publishedPartner
@prototype
*/	
class MMMFVideoPlayControllerExtCustomCommandImplementor
	{
public:

	/**
	Sets play velocity. 
	Behaviour is same as CVideoPlayerUtility::SetPlayVelocityL
	
	@see CVideoPlayerUtility::SetPlayVelocityL
	*/
	virtual void MvpecSetPlayVelocityL(TInt aVelocity)=0;
	
	/**
	Gets play velocity.
	Behaviour is same as CVideoPlayerUtility::PlayVelocityL	
	
	@see CVideoPlayerUtility::PlayVelocityL
	*/
	virtual TInt MvpecPlayVelocityL()=0;
	
	/**
	Steps through frames in pause mode.
	Behaviour is same as CVideoPlayerUtility::StepFrameL	
		
	@see CVideoPlayerUtility::StepFrameL
	*/
	virtual void MvpecStepFrameL(TInt aStep)=0;
	
	/**
	Gets play rate capabilities.
	Behaviour is same as CVideoPlayerUtility::GetPlayRateCapabilitiesL	
		
	@see CVideoPlayerUtility::GetPlayRateCapabilitiesL
	*/
	virtual void MvpecGetPlayRateCapabilitiesL(TVideoPlayRateCapabilities& aCapabilities)=0;
	
	/**
	Enables/Disables video playback.
	Behaviour is same as CVideoPlayerUtility::SetVideoEnabledL	
	
	@see CVideoPlayerUtility::SetVideoEnabledL
	*/
	virtual void MvpecSetVideoEnabledL(TBool aVideoEnabled)=0;
	
	/**
    Queries whether video playback is currently enabled or not.
	Behaviour is same as CVideoPlayerUtility::VideoEnabledL	
	
	@see CVideoPlayerUtility::VideoEnabledL
	*/
	virtual TBool MvpecVideoEnabledL()=0;
	
	/**
	Enables or disables audio playback.
	Behaviour is same as CVideoPlayerUtility::SetAudioEnabled	
	
	@see CVideoPlayerUtility::SetAudioEnabled
	*/
	virtual void MvpecSetAudioEnabledL(TBool aAudioEnabled)=0;
	
	/**
	Sets Auto scale mode.
	Behaviour is same as CVideoPlayerUtility::SetAutoScaleL	
	
	@see CVideoPlayerUtility::SetAutoScaleL
	*/
	virtual void MvpecSetAutoScaleL(TAutoScaleType aScaleType, TInt aHorizPos, TInt aVertPos)=0;
	};

/**
Used for commands between RMMFVideoPlayControllerExtCustomCommands and 
CMMFVideoPlayControllerExtCustomCommandParser classes.

@internalComponent
*/
enum TMMFVideoPlayControllerExtCustomCommandConfigMessages
	{
	EMMFVideoPlayControllerSetPlayVelocity = 0,
	EMMFVideoPlayControllerPlayVelocity,
	EMMFVideoPlayControllerStepFrame,
	EMMFVideoPlayControllerGetPlayRateCapabilities,
	EMMFVideoPlayControllerSetVideoEnabled,
	EMMFVideoPlayControllerVideoEnabled,
	EMMFVideoPlayControllerSetAudioEnabled,
	EMMFVideoPlayControllerSetAutoScale
	};
/**
@internalComponent
*/
class TMMFVideoPlayAutoScaleParams
	{
public:
	TAutoScaleType iScaleType;
	TInt iHorizPos;
	TInt iVertPos;
	};
	
/**
Custom command parser class to be used by controller plug-ins wishing to support play velocity, 
enabling/disabling audio/video, and auto scaling.

The controller plug-in should create an object of this type and add it to the list of custom command parsers 
in the controller framework. The controller plug-in must be derived from MMMFVideoPlayControllerExtCustomCommandImplementor 
to use this class. 

@publishedPartner
@prototype
*/
class CMMFVideoPlayControllerExtCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser that supports the video rate control and auto scaling.

	@param  aImplementor
	        A reference to the controller plug-in that owns this new object.

	@return A pointer to the object created.

	*/
	IMPORT_C static CMMFVideoPlayControllerExtCustomCommandParser* NewL(MMMFVideoPlayControllerExtCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	*/
	IMPORT_C ~CMMFVideoPlayControllerExtCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	CMMFVideoPlayControllerExtCustomCommandParser(MMMFVideoPlayControllerExtCustomCommandImplementor& aImplementor);
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetPlayVelocityL(TMMFMessage& aMessage);
	TBool DoPlayVelocityL(TMMFMessage& aMessage);
	TBool DoStepFrameL(TMMFMessage& aMessage);
	TBool DoGetPlayRateCapabilitiesL(TMMFMessage& aMessage);
	TBool DoSetVideoEnabledL(TMMFMessage& aMessage);
	TBool DoVideoEnabledL(TMMFMessage& aMessage);
	TBool DoSetAudioEnabledL(TMMFMessage& aMessage);
	TBool DoSetAutoScaleL(TMMFMessage& aMessage);
private:
	MMMFVideoPlayControllerExtCustomCommandImplementor& iImplementor;
	};

/**
Resource class to be used by player utility for sending custom commands.

@publishedPartner
@prototype
*/	
class RMMFVideoPlayControllerExtCustomCommands: public RMMFCustomCommandsBase
	{
public:
	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.
	*/
	IMPORT_C RMMFVideoPlayControllerExtCustomCommands(RMMFController& aController);
	
	/**
	Sets play velocity.
	Behaviour is same as CVideoPlayerUtility::SetPlayVelocityL
		
	@param  aVelocity 
			Velocity of the playback.

	@return One of the system-wide error codes.	

	@see CVideoPlayerUtility::SetPlayVelocityL	
	*/
	IMPORT_C TInt SetPlayVelocity(TInt aVelocity);

	/**
	Gets play velocity.
	Behaviour is same as CVideoPlayerUtility::PlayVelocityL	

	@param  aVelocity 
			Velocity of the playback.

	@return One of the system-wide error codes.	
		
	@see CVideoPlayerUtility::PlayVelocityL
	*/
	IMPORT_C TInt PlayVelocity(TInt &aVelocity)const;

	/**
	Steps through frames in pause mode.
	Behaviour is same as CVideoPlayerUtility::StepFrameL	

	@param  aStep 
			Count indicating number of frames to step playback position.

	@return One of the system-wide error codes.

	@see CVideoPlayerUtility::StepFrameL
	*/
	IMPORT_C TInt StepFrame(TInt aStep);
	
	/**
	Gets play rate capabilities.
	Behaviour is same as CVideoPlayerUtility::GetPlayRateCapabilitiesL	

    @param aCapabilities Playback rate capabilities

	@return One of the system-wide error codes.
		
	@see CVideoPlayerUtility::GetPlayRateCapabilitiesL
	*/
	IMPORT_C TInt GetPlayRateCapabilities(TVideoPlayRateCapabilities& aCapabilities)const;

	/**
	Enables/Disables video playback.
	Behaviour is same as CVideoPlayerUtility::SetVideoEnabledL	
    
    @param aVideoEnabled ETrue to enable video playback, EFalse to disable

	@return One of the system-wide error codes.    	

	@see CVideoPlayerUtility::SetVideoEnabledL
	*/
	IMPORT_C TInt SetVideoEnabled(TBool aVideoEnabled);
	
	/**
    Queries whether video playback is currently enabled or not.
	Behaviour is same as CVideoPlayerUtility::VideoEnabledL

    @param aVideoEnabled 
    	   Out parameter returns ETrue if video playback is enabled, EFalse if not.

	@return One of the system-wide error codes.
	
	@see CVideoPlayerUtility::VideoEnabledL
	*/
	IMPORT_C TInt VideoEnabled(TBool &aVideoEnabled)const;
	
	/**
	Enables or disables audio playback.
	Behaviour is same as CVideoPlayerUtility::SetAudioEnabledL

    @param aVideoEnabled ETrue to enable audio playback, EFalse to disable		

	@return One of the system-wide error codes.

	@see CVideoPlayerUtility::SetAudioEnabledL
	*/
	IMPORT_C TInt SetAudioEnabled(TBool aAudioEnabled);

	/**
	Sets Auto scale mode.
 	Behaviour is same as CVideoPlayerUtility::SetAutoScaleL
	
    @param aScaleType Automatic scaling type
    @param aHorizPos Video picture horizontal position, relative to the
                     video window.
    @param aVertPos Video picture vertical position, relative to the
                     video window.
	@return One of the system-wide error codes.
		
	@see CVideoPlayerUtility::SetAutoScaleL
	*/
	IMPORT_C TInt SetAutoScale(TAutoScaleType aScaleType, TInt aHorizPos, TInt aVertPos);
	};

/**
@publishedPartner
@prototype
*/
const TUid KUidInterfaceMMFVideoRecorderExt = {0x10283438};

/**
Mixin class to be derived from controller plug-ins that could support quality and enabling video. 

@publishedPartner
@prototype
*/	
class MMMFVideoRecordControllerExtCustomCommandImplementor
	{
public:

	/**
	Enabled or disables video in recorder.
	Behaviour is same as CVideoRecorderUtility::SetVideoEnabledL	

	@see CVideoRecorderUtility::SetVideoEnabledL
	*/
    virtual void MvrecSetVideoEnabledL(TBool aEnabled)=0;
	/**
	Gets the flag that indicates video enabled or not.
	Behaviour is same as CVideoRecorderUtility::VideoEnabledL	

	@see CVideoRecorderUtility::VideoEnabledL
	*/
    virtual TBool MvrecVideoEnabledL() const=0;
	/**
	Sets the quality of video being recorded.
	Behaviour is same as CVideoRecorderUtility::SetVideoQualityL	

	@see CVideoRecorderUtility::SetVideoQualityL
	*/
    virtual void MvrecSetVideoQualityL(TInt aQuality)=0;
	/**
	Gets video quality level set using SetVideoQualityL.
	Behaviour is same as CVideoRecorderUtility::VideoQualityL	

	@see CVideoRecorderUtility::VideoQualityL
	*/
    virtual TInt MvrecVideoQualityL() const=0;
	/**
	Sets the video framerate to fixed.
	Behaviour is same as CVideoRecorderUtility::SetVideoFrameRateFixedL	

	@see CVideoRecorderUtility::SetVideoFrameRateFixedL
	*/
    virtual void MvrecSetVideoFrameRateFixedL(TBool aFixedFrameRate)=0;
	/**
	Gets FrameRateFixed flag set using SetVideoFrameRateFixedL.
	Behaviour is same as CVideoRecorderUtility::VideoFrameRateFixedL	

	@see CVideoRecorderUtility::VideoFrameRateFixedL
	*/
    virtual TBool MvrecVideoFrameRateFixedL() const=0;
	};

/**
@internalComponent
*/
enum TMMFVideoRecorderExtCustomCommandConfigMessages
	{
	EMMFVideoRecordControllerSetVideoEnabled = 0,
	EMMFVideoRecordControllerVideoEnabled,
	EMMFVideoRecordControllerSetVideoQuality,	
	EMMFVideoRecordControllerVideoQuality,
	EMMFVideoRecordControllerSetVideoFrameRateFixed,
	EMMFVideoRecordControllerVideoFrameRateFixed
	};

/**
Custom command parser class to be used by controller plug-ins wishing to implement VideoRecorderExt custom commands.

The controller plug-in should create an object of this type and add it to the list of custom command parsers 
in the controller framework. The controller plug-in must be derived from MMMFVideoRecordControllerExtCustomCommandImplementor
to use this class.

@publishedPartner
@prototype
*/
class CMMFVideoRecordControllerExtCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser that supports the video rate control and auto scaling.

	@param  aImplementor A reference to the controller plug-in that owns this new object.
	@return A pointer to the object created.
	*/
	IMPORT_C static CMMFVideoRecordControllerExtCustomCommandParser* NewL(MMMFVideoRecordControllerExtCustomCommandImplementor& aImplementor);

	/**
	Destructor.
	*/
	IMPORT_C ~CMMFVideoRecordControllerExtCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage The message to be handled.
	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	CMMFVideoRecordControllerExtCustomCommandParser(MMMFVideoRecordControllerExtCustomCommandImplementor& aImplementor);
	void DoHandleRequestL(TMMFMessage& aMessage);
	TBool DoSetVideoEnabledL(TMMFMessage& aMessage);
	TBool DoVideoEnabledL(TMMFMessage& aMessage);
	TBool DoSetVideoQualityL(TMMFMessage& aMessage);
	TBool DoVideoQualityL(TMMFMessage& aMessage);
	TBool DoSetVideoFrameRateFixedL(TMMFMessage& aMessage);
	TBool DoVideoFrameRateFixedL(TMMFMessage& aMessage);
private:
	MMMFVideoRecordControllerExtCustomCommandImplementor& iImplementor;
	};

/**
Resource class to be used by Recorder utility for sending custom commands.

@publishedPartner
@prototype
*/	
class RMMFVideoRecordControllerExtCustomCommands: public RMMFCustomCommandsBase
	{
public:
	/**
	Constructor.

	@param  aController
	        The client side controller object to be used by this custom command interface.
	@return One of the system-wide error codes.
	*/
	IMPORT_C RMMFVideoRecordControllerExtCustomCommands(RMMFController& aController);
	
	/**
	Enabled or disables video in recorder.
	Behaviour is same as CVideoRecorderUtility::SetVideoEnabledL	

    @param aEnabled ETrue to enable video recording, EFalse to enable it

	@return One of the system-wide error codes.	
	@see CVideoRecorderUtility::SetVideoEnabledL
	*/
    IMPORT_C TInt SetVideoEnabled(TBool aEnabled);
    
	/**
	Gets the flag that indicates video enabled or not.
	Behaviour is same as CVideoRecorderUtility::VideoEnabledL	

    @param aEnabled 
    	   Out parameter returns ETrue if video recording is enabled , EFalse otherwise.

	@return One of the system-wide error codes.	
	@see CVideoRecorderUtility::VideoEnabledL
	*/
    IMPORT_C TInt VideoEnabled(TBool &aEnabled) const;
    
	/**
	Sets the quality of video being recorded.
	Behaviour is same as CVideoRecorderUtility::SetVideoQualityL	

    @param aQuality Video quality, in the range of 0 to 100, inclusive.

	@return One of the system-wide error codes.	
	@see CVideoRecorderUtility::SetVideoQualityL
	*/
    IMPORT_C TInt SetVideoQuality(TInt aQuality);
    
	/**
	Gets video quality level set using SetVideoQualityL.
	Behaviour is same as CVideoRecorderUtility::VideoQualityL	
    
    @param aQuality Out parameter returning Video quality in the range 0-100.
    
    @return One of the system-wide error codes.	
	@see CVideoRecorderUtility::VideoQualityL
	*/
    IMPORT_C TInt VideoQuality(TInt &aQuality) const;
    
	/**
	Sets the video framerate to fixed.
	Behaviour is same as CVideoRecorderUtility::SetVideoFrameRateFixedL	
	
    @param aFixedFrameRate ETrue to request a fixed framerate, EFalse to
                          request a variable framerate.

	@return One of the system-wide error codes.	
	@see CVideoRecorderUtility::SetVideoFrameRateFixedL
	*/
    IMPORT_C TInt SetVideoFrameRateFixed(TBool aFixedFrameRate);
    
	/**
	Gets FrameRateFixed flag set using SetVideoFrameRateFixedL.
	Behaviour is same as CVideoRecorderUtility::VideoFrameRateFixedL	

    @param aFixedFrameRate Out parameter returns ETrue if fixed framerate
     						is enabled, EFalse otherwise.
    
	@return One of the system-wide error codes.	
	@see CVideoRecorderUtility::VideoFrameRateFixedL
	*/
    IMPORT_C TInt VideoFrameRateFixed(TBool &aFixedFrameRate) const;
    };

#endif
