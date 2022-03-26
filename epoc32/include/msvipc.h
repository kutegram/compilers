// MSVIPC.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVIPC_H__)
#define __MSVIPC_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__MSVSTD_H__)
#include <msvstd.h>
#endif


//
const TInt KMsvNullOperation=0;
const TInt KMsvFirstOperation=1;

//
const TInt KMsvSessionBufferLength=0x1000;
const TInt KMsvProgressBufferLength=256;


// ***** NOTE!!!!! TMsvPackedChangeNotification::UnpackL() MUST be	****
// ***** updated when adding new types								*****
/**
@internalComponent

*/
enum TMsvServerChangeNotificationType 
	{
	EMsvNullNotification=-1,
	EMsvEntriesNoChange=0,
	EMsvEntriesCreated=1,
	EMsvEntriesChanged=2,
	EMsvEntriesDeleted=3,
	EMsvEntriesMoved=4,
	EMsvMtmGroupInstalled=5,
	EMsvMtmGroupDeInstalled=6,
	EMsvStoreDeleted=7,  
	EMsvCloseSession=8,
	EMsvIndexLoaded=9,
	EMsvIndexFailedToLoad=10,
	EMsvCorruptedIndexRebuilt=11,
	EMsvMediaChanged=12, // Note: I assume the following four follow each other in order
	EMsvMediaUnavailable=13,
	EMsvMediaAvailable=14,
	EMsvMediaIncorrect=15,
	EMsvCorruptedIndexRebuilding=16
	};


//**********************************
// TMsvPackedEntry
//**********************************
//
// Packs a TMsvEntry and the two associated descriptors into a buffer for
// sending across IPC. Also unpacks the data into a TMsvEntry and two heap 
// descriptors
//
//
class TMsvEntry;

class TMsvPackedEntry
/**
@internalComponent

*/
	{
public:
	IMPORT_C TMsvPackedEntry(HBufC8*& aBuffer);
	IMPORT_C TInt PackEntry(const TMsvEntry& aEntry);
	IMPORT_C void UnpackEntry(TMsvEntry& aEntry);
private:
	HBufC8*& iBuffer;
	};


//**********************************
// TMsvPackedEntryArray
//**********************************
//
// Packs 1+ TMsvEntry's and the associated descriptors into a buffer for
// sending across IPC. Also unpacks the data into a TMsvEntry and two heap 
// descriptors using indexed access
//
//

class TMsvPackedEntryArray
/**
@internalComponent

*/
	{
public:
	IMPORT_C TMsvPackedEntryArray(HBufC8*& aBuffer, TInt aCount=0);
	IMPORT_C TInt PackEntry(const TMsvEntry& aEntry);
	IMPORT_C TInt UnpackEntry(TInt aEntryIndex, TMsvEntry& aEntry);
	IMPORT_C void Reset();
private:
	TInt FindEntryInArray(TInt aIndex);
private:
	TInt	iIndex;
	TInt	iCount;
	const TUint8* iPos;
	HBufC8*& iBuffer;
	};


//**********************************
// TMsvChildrenDetails
//**********************************
//
// Contains the information about the number of children of an entry and how many
// have been sent in the main buffer
//

class TMsvChildrenDetails
/**
@internalComponent

*/
	{
public:
	IMPORT_C TMsvChildrenDetails();
public:
	TMsvId	iParentId;
	TInt	iTotalNumberChildren;
	TInt	iNumberChildrenInArray;
	TInt	iLastEntryInArray;
	};


//**********************************
// TMsvLocalOperationProgress
//**********************************
//
// Contains the information about a local operation
//

class TMsvLocalOperationProgress
/** Encapsulates progress information returned by a local operation. A local operation 
is a CMsvOperation-derived object returned by a function that affects only 
local entries. For example, such a function would be a CMsvEntry::ChangeL() 
call on a local entry. You can check if the operation is local from CMsvOperation::Mtm(): 
a local operation returns a value of KUidMsvLocalServiceMtm. 

Progress information is obtained, in a packaged format, by calling CMsvOperation::ProgressL(). 
Understanding the TMsvLocalOperationProgress structure enables an application 
to use that information for a local operation.  
@publishedAll

*/
	{
public:
/** Defines the possible values for the type of operation progress report. 
@publishedAll

*/
	enum TLocalOperation
						{	
	/** Default value for new TMsvLocalOperationProgress */
							ELocalNone=0,
	/** Move operation */
							ELocalMove,
	/** Delete operation */
							ELocalDelete,
	/** Copy operation */
							ELocalCopy,
	/** Create operation */
							ELocalNew,
	/** Change operation */
							ELocalChanged
							};
public:
	IMPORT_C TMsvLocalOperationProgress();
public:
	/** The type of operation on which the progress is reporting */
	TLocalOperation iType;
	/** The number of entries on which the operation was or will be attempted */
	TInt iTotalNumberOfEntries;
	/** The number of entries on which the operation has been successful */
	TInt iNumberCompleted;	
	/** The number of entries on which the operation has failed */
	TInt iNumberFailed;	
	/** The number of entries on which the operation has yet to be attempted */
	TInt iNumberRemaining;	
	/** The error code for the latest failed operation */
	TInt iError;
	/** This contains different information for different operation types:
	
	1. copying a single entry: ID of the new entry
	
	2. moving an entry: ID of the entry moved
	
	3. copying or moving multiple entries: ID of the first entry in the selection */
	TMsvId	iId;
	};

//**********************************
// TMsvServerOperationProgress
//**********************************
/** Encapsulates progress information returned by a non-MTM specific Message Server 
operation. 

You can check if an operation has this type of progress information by calling 
CMsvOperation::Mtm(): a suitable operation returns a value of KUidMsvServerMtm. 

Progress information is obtained, in a packaged format, by calling CMsvOperation::ProgressL(). 
Understanding the TMsvServerOperationProgress class enables an application 
to use that information for a Message Server operation. 

@see TMsvLocalOperationProgress 
@see CMsvSession::CopyStoreL() 
@see CMsvSession::DeleteStoreL()
@publishedAll

*/

class TMsvServerOperationProgress
	{
public:

	enum TMsvServerOperationType 
		{ 
		/** No operation in progress. */
		EMsvNoOperation = 0, 
		/** Change drive operation in progress.
	
		@see CMsvSession::ChangeDriveL() */
		EMsvChangeDriveOperation
		
		,
 		/** Copy Store operation in progress.
 		@see CMsvSession::CopyStoreL() */
 		EMsvCopyOperation,
 		
 		/** Delete Store operation in progress.
 		@see CMsvSession::DeleteStoreL() */
 		EMsvDeleteOperation
 		
 				
 		 };
	//
public:
	IMPORT_C TMsvServerOperationProgress();
	TMsvServerOperationProgress(TMsvServerOperationType aType);
	//
public:
	/** The type of operation in progress. */
	TMsvServerOperationType iOperationType;
	};

		
//**********************************
// TMsvIndexProgress
//**********************************

class TMsvIndexProgress
/** Provides details of index loading progress. 

@see TMsvIndexLoadProgress 
@publishedAll

*/
	{
public:
	IMPORT_C TMsvIndexProgress();
	//
public:
	/** Total number of entries in the index. */
	TInt iTotal;
	/** Number of entries created so far. */
	TInt iCompleted;
	/** Number of entries remaining. */
	TInt iRemaining;
	/** ID of entry last created. */
	TMsvId iId;
	};


//**********************************
// TMsvIndexLoadProgress
//**********************************

class TMsvIndexLoadProgress : public TMsvServerOperationProgress
/** Progress information for an operation controlling the Message Server loading 
its index. 

Such an operation can occur when the Message Server changes drive.

@see CMsvOperation
@see CMsvSession::ChangeDriveL() 
@publishedAll

*/
	{
public:
	/** States for the index loading process. 
@publishedAll

*/
	enum TIndexState 
		{
		/** Index loading has not begun. */
		EIndexNotLoaded = 0, 
		/** Index loading is in progress. */
		EIndexLoading, 
		/** Index is being built. */
		EIndexRebuilding, 
		/** Index loading is complete. */
		EIndexComplete};
	//
public:
	IMPORT_C TMsvIndexLoadProgress();
	//
public:
	/** Stores any errors that prevented the index being loaded. */
	TInt iError;
	/** Current state of the index loading process. */
	TIndexState iState;
	/** Details of the index loading progress. */
	TMsvIndexProgress iIndex;
	};



//**********************************
// TMsvCopyProgress
//**********************************

/** Progress information for the copy operation. 

@see CMsvOperation
@see CMsvSession::CopyStoreL() 
@publishedAll

*/
class TMsvCopyProgress : public TMsvServerOperationProgress
	{
public:
/** States for the copy operation. 
@publishedAll

*/
	enum TCopyState 
		{
		/** Operation not yet started */
		ENotYetStarted = 0,
		/** Mail Store is being locked */
		ELock, 
		/** Initialising Copy operation */
		EInitCopy,
		/** Mail Store is being copied */
		ECopyStore, 
		/** Mail Store is being unlocked. */
		EUnlock,
		/** Operation completed */
		ECompleted
		};
		
	/** Stores any errors that the operation encountered. */
	TInt iError;
	TInt iTotal;      // Total number of items to be copied
	TInt iCurrent;    // Current item number being copied
 	TCopyState iState;
	
public:
    IMPORT_C TMsvCopyProgress();
	};


//**********************************
// TMsvDeleteProgress
//**********************************

/** Progress information for the delete operation.
 
@see CMsvOperation
@see CMsvSession::DeleteStoreL() 
@publishedAll

*/
class TMsvDeleteProgress : public TMsvServerOperationProgress
	{
public:
/** States for the delete operation. 
@publishedAll

*/
	enum TDeleteState 
		{
		/** Operation not yet started */
		ENotYetStarted = 0,
		/** Mail Store is being deleted */
		EDeleteStore, 
		/** Operation is complete */
		ECompleted
		};
		
	/** Stores any errors that the operation encountered. */
	TInt iError;
	TDeleteState iState;
	
public:
    IMPORT_C TMsvDeleteProgress();
	};



//**********************************
// TMsvPackedOperation
//**********************************
//
// Packs an operation, the selection, and some associated parameters (TInt) into the
// IPC buffer
//
//

class TMsvPackedOperation
/**
@internalComponent

*/
	{
public:
	IMPORT_C TMsvPackedOperation(HBufC8*& aBuffer);
	IMPORT_C TInt Pack(const CMsvEntrySelection& aSelection, TInt aParameter1=0, TInt aParameter2=0);
	IMPORT_C void UnpackL(CMsvEntrySelection& aSelection, TInt& aParameter1, TInt& aParameter2);
private:
	HBufC8*& iBuffer;
	};


//**********************************
// TMsvPackedChangeNotification
//**********************************
//
// Packs the CMsvEntrySelection of index entries that have been changed, and also 
// the integer describing the type of change. There is a limit of KMsvPackedChangeLimit
// top the number of entry ids that can be sent at one time
//
//

typedef TBuf8<128> TMsvNotifBuffer;

class TMsvPackedChangeNotification
/**
@internalComponent

*/
	{
public:
	enum {	KMsvChangeNotificationNumberOfTInts=4,
			KMsvPackedChangeLimit=28, // 32-KMsvChangeNotificationNumberOfTInts
			}; 
public:
	IMPORT_C TMsvPackedChangeNotification(TMsvNotifBuffer& aBuffer);
	inline void Pack(TMsvServerChangeNotificationType aChangeType, const CMsvEntrySelection& aSelection, TInt aParameter1, TInt aParameter2);
	IMPORT_C void Pack(TMsvServerChangeNotificationType aChangeType, const CMsvEntrySelection& aSelection, TInt aParameter1, TInt aParameter2, TInt aStartIndex, TInt aFinishIndex);
	IMPORT_C void Pack(TMsvServerChangeNotificationType aChangeType, TMsvId aId, TInt aParameter1, TInt aParameter2);
	IMPORT_C void UnpackL(TMsvServerChangeNotificationType& aChangeType, CMsvEntrySelection& aSelection, TInt& aParameter1, TInt& aParameter2);
private:
	TMsvNotifBuffer& iBuffer;
	};

//**********************************
// TMsvPackedEntryFilter
//**********************************

class TMsvPackedEntryFilter
/**
@internalComponent

*/
	{
public:
	TMsvPackedEntryFilter(HBufC8*& aBuffer);
	TInt PackFilter(const CMsvEntryFilter& aFilter);
	void UnpackFilter(CMsvEntryFilter& aFilter);
private:
	HBufC8*& iBuffer;
	};


#include <msvipc.inl>

#endif

