// EIKSVFTY.H
//
// Copyright (c) 1997-2006 Symbian Ltd.  All rights reserved.
//
// Standard factory definitions

#ifndef __EIKSVFTY_H__
#define __EIKSVFTY_H__

// System includes
#include <e32base.h>

// Classes referenced
class TASShdAlarm;
class CEikAlmControlSupervisor;
class MEikSrvNotifierBase2;

/** Creates an interface object to a plug-in server side notifier.

@publishedAll

*/
typedef CArrayPtr<MEikSrvNotifierBase2>* (*CreateEikSrvNotifierBase)();

/**
@publishedPartner 

*/
class MEikNotifyAlertCompletionObserver
	{
public:
	virtual void HandleAlertCompletion(const TInt aButtonVal)=0;
protected:
	IMPORT_C MEikNotifyAlertCompletionObserver();
private:
	IMPORT_C virtual void MEikNotifyAlertCompletionObserver_Reserved1();
	IMPORT_C virtual void MEikNotifyAlertCompletionObserver_Reserved2();
private:
	TInt iMEikNotifyAlertCompletionObserver_Reserved1;
	};


/**
@publishedPartner 

*/
class MEikServNotifyAlert
	{
public:
	virtual void Release()=0;
	virtual void DisplayNotifier(const TDesC& aTitle,const TDesC& aLabel,const TDesC& aBut1,const TDesC& aBut2, MEikNotifyAlertCompletionObserver* aObserver)=0;
protected:
	IMPORT_C MEikServNotifyAlert();
private:
	IMPORT_C virtual void MEikServNotifyAlert_Reserved1();
	IMPORT_C virtual void MEikServNotifyAlert_Reserved2();
private:
	TInt iMEikServNotifyAlert_Reserved1;
	};


/**
@publishedPartner 

*/
class MEikServAlarm
	{
public:
	virtual void Release()=0;
	virtual void ShowAlarm()=0;
	virtual void HideAlarm()=0;
	virtual TInt CurrentServerState() const=0;
	virtual void UpdateSoundPauseTimeInterval(TInt aMinutes)=0;
	virtual void UpdateForAlarmServerState(TInt aNewAlarmServerState)=0;
	virtual void UpdateAlarmInfo(const TASShdAlarm& aAlarm,const TFullName& aOwner)=0;
	virtual void StartPlayAlarmL(const TDesC& aAlarmName)=0;
	virtual void StopPlayAlarm()=0;
protected:
	IMPORT_C MEikServAlarm();
private:
	IMPORT_C virtual void MEikServAlarm_Reserved1();
	IMPORT_C virtual void MEikServAlarm_Reserved2();
private:
	TInt iMEikServAlarm_Reserved1;
	};


/**
@publishedPartner 

*/
class MEikServAlarmFactory
	{
	public:
		virtual MEikServAlarm* NewAlarmL(CEikAlmControlSupervisor& aSupervisor)=0;
protected:
	IMPORT_C MEikServAlarmFactory();
private:
	IMPORT_C virtual void MEikServAlarmFactory_Reserved1();
	IMPORT_C virtual void MEikServAlarmFactory_Reserved2();
private:
	TInt iMEikServAlarmFactory_Reserved1;
	};

// __EIKSVFTY_H__
#endif
