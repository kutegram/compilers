// CalDataExchange.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#ifndef __CCALDATAEXCHANGE_H__ 
#define __CCALDATAEXCHANGE_H__

#include <e32cmn.h>
#include <calentry.h>

class CCalSession;
class CCalDataExchangeImpl;
class RWriteStream;

const TInt KDefaultNumberOfEntriesToHandle = 10;

/** A call back class to show the progress of long-running operations.

When a long-running operation is carried out, this class is used to signal its progress, 
and when the function is complete.

@publishedAll

*/
class MCalDataExchangeCallBack
	{
public:
	/** Progress callback. 

	This calls the observing class with the percentage complete of the current operation.
	This also propagates any error to the observing class.

	@param aPercentageCompleted The percentage complete. */
	virtual void Progress(TInt aPercentageCompleted) = 0;

	/** Progress callback.

	This calls the observing class when the current operation is finished. */
	virtual void Completed() = 0;

	virtual TInt NumberOfEntriesToHandleAtOnce() { return KDefaultNumberOfEntriesToHandle; };
	};

/** 
This class provides functionality for importing and exporting vCal entries.
@publishedAll

*/
NONSHARABLE_CLASS(CCalDataExchange) : public CBase
	{
public:
	IMPORT_C static CCalDataExchange* NewL(CCalSession& aSession);
	IMPORT_C ~CCalDataExchange();
	
	IMPORT_C void ImportL(TUid aDataFormat, RReadStream& aReadStream, RPointerArray<CCalEntry>& aCalEntryArray);
	IMPORT_C void ImportL(TUid aDataFormat, RReadStream& aReadStream, RPointerArray<CCalEntry>& aCalEntryArray, TInt aFlags);
	IMPORT_C void ExportL(TUid aDataFormat, RWriteStream& aWriteStream, RPointerArray<CCalEntry>& aCalEntryArray);	
	
	IMPORT_C void ImportL(TUid aDataFormat, RReadStream& aReadStream, RPointerArray<CCalEntry>& aCalEntryArray, TInt aFlags, TInt aNumEntries);

	IMPORT_C void ImportAsyncL(TUid aDataFormat, RReadStream& aReadStream, RPointerArray<CCalEntry>& aCalEntryArray, MCalDataExchangeCallBack& aObserver, TInt aFlags);
	IMPORT_C void ExportAsyncL(TUid aDataFormat, RWriteStream& aWriteStream, RPointerArray<CCalEntry>& aCalEntryArray, MCalDataExchangeCallBack& aObserver);
	
private:
	CCalDataExchange();
	void ConstructL(CCalSession& aSession);
	
private:
	CCalDataExchangeImpl* iImpl;
	};
			
// __CCALDATAEXCHANGE_H__
#endif
