// EIKSRV.PAN
//
// Copyright (c) Symbian Software Ltd 1997-2006. All rights reserved.
//
#ifndef __EIKSRV_PAN__
#define __EIKSRV_PAN__

/**
@publishedPartner

*/
#define __EIKON_SERVER _L("Eikon server")

/**
@internalComponent
*/
enum TEikServPanic
	{
	EEikServPanicNotifyBadDescriptor,
	EEikServPanicAlarmAlertServiceNotSupported,
	EEikServPanicNoTaskListDialog,
	EEikServPanicTaskNull,
	EEsPanicAlarmAlert,
	EEikServPanicAlarmAlertServerAlreadyConnected,
	EEikServEnvPanicNullAppUi,
	EEikServPanicNoSuchLabelInAlarm,
	EEikServPanicDriveIndexOutOfRange,
	EEikServPanicNotiferArrayNotNull,
	EEikServPanicChannelIndexOutOfRange,
	EEikServPanicNullObservedList,
	EEikServPanicQueueIndexOutOfRange,
	EEikServPanicNotifyAlertQueueEmpty,
	EEikSrvClientPanicInconsistentMessageParameters,
	};

/**
@internalComponent
*/
GLREF_C void Panic(TEikServPanic aPanic);

// __EIKSRV_PAN__
#endif
