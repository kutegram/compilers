// APGNOTIF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APGNOTIF_H__
#define __APGNOTIF_H__

#include <apgcli.h>


class MApaAppListServObserver
/**
MApaAppListServObserver

@publishedPartner

*/
	{
public:
	enum TApaAppListEvent
		{
		EAppListChanged=1
		};
	virtual void HandleAppListEvent(TInt aEvent)=0;
protected:
	IMPORT_C MApaAppListServObserver();
private:
	IMPORT_C virtual void MApaAppListServObserver_Reserved1();
	IMPORT_C virtual void MApaAppListServObserver_Reserved2();
private:
	TInt iMApaAppListServObserver_Reserved1;
	};


class CApaAppListNotifier : public CActive
/** An application list change notifier. 

It provides notification whenever an application is added or deleted.

@publishedPartner
*/
	{
public:
	IMPORT_C ~CApaAppListNotifier();
	IMPORT_C static CApaAppListNotifier* NewL(MApaAppListServObserver* aObserver, TPriority aPriority);
private: // from CActive
	void DoCancel();
	void RunL();
private:
	CApaAppListNotifier(MApaAppListServObserver& aObserver, TPriority aPriority);
	void ConstructL();
private:
	MApaAppListServObserver& iObserver;
	RApaLsSession iLsSession;
	};

#endif
