// calsession.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#ifndef __CALSESSION_H__
#define __CALSESSION_H__

#include <badesca.h>
#include <calchangecallback.h>
#include <calcommon.h>
#include <calnotification.h>

class CCalSessionImpl;

/** A handle to the calendar file.

When the client instantiates a CCalSession, it will connect to the calendar server. 
In turn, the client can use its APIs, for instance to create or open a calendar file.

The agenda data in the file can be accessed as entries. To access the entries, clients should
use class CCalEntryView or CCalInstanceView to process the entry data. However, both view classes 
require the handle to the file which is represented by this class.

@publishedAll

*/
NONSHARABLE_CLASS(CCalSession) : public CBase
    {
public:
	IMPORT_C static CCalSession* NewL();
	IMPORT_C ~CCalSession();

	IMPORT_C void CreateCalFileL(const TDesC&  aFileName) const;
	IMPORT_C void OpenL(const TDesC& aFileName) const;
	IMPORT_C const TDesC& DefaultFileNameL() const; 
	IMPORT_C void DeleteCalFileL(const TDesC& aFileName) const;
	IMPORT_C CDesCArray* ListCalFilesL() const;

	IMPORT_C void StartChangeNotification(MCalChangeCallBack2& aCallBack, const CCalChangeNotificationFilter& aFilter);
	IMPORT_C void StopChangeNotification();
	IMPORT_C void DisableChangeBroadcast();
	IMPORT_C void EnableChangeBroadcast();
	
	IMPORT_C void _DebugSetHeapFailL(RAllocator::TAllocFail aFail, TInt aRate);
	IMPORT_C TInt _DebugRequestAllocatedCellsL(TInt& aTotalAllocSize);
	
	IMPORT_C void EnablePubSubNotificationsL();
	IMPORT_C void DisablePubSubNotificationsL();
	
	IMPORT_C void FileIdL(TCalFileId& aCalFileId) const;
	IMPORT_C void GetFileNameL(TCalPubSubData aPubSubData, TDes& aFileName) const;
	IMPORT_C TBool IsFileNameL(TCalPubSubData aPubSubData, const TDesC& aFileName) const;
	IMPORT_C TBool IsOpenedFileL(TCalPubSubData aPubSubData) const;

	// deprecated
	IMPORT_C void StartChangeNotification(MCalChangeCallBack* aCallBack, MCalChangeCallBack::TChangeEntryType aChangeEntryType,	TBool aIncludeUndatedTodos,	TTime aFilterStartTime,	TTime aFilterEndTime);
	
public:
	CCalSessionImpl& Impl() const;
	  
private:
	CCalSession();
	void ConstructL();
private:
	CCalSessionImpl* iImpl;
	};
	
// __CALSESSION_H__
#endif
