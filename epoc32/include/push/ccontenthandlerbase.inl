// CContentHandlerBase.inl
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
// 

// Local includes
//

/** @file
@publishedPartner

*/

// System includes
//
#include <ecom/ecom.h>
#include <push/ccontenthandlerbase.h>
#include <push/pushlog.h>
#include <push/pluginkiller.h>


/** 
Constructor. 
*/
inline CContentHandlerBase::CContentHandlerBase()
: CPushHandlerBase()
	{
	}


/** 
Destructor. 
*/
inline CContentHandlerBase::~CContentHandlerBase()
	{
	__LOG_PTR_DEBUG("CContentHandlerBase:: Destructor Called");
	Cancel();
	delete iMessage;
	}


/** 
Finds and instantiates an ECom WAP Push Content Handler plug-in that matches 
the specified media type.

@param aMatchData 
Media type.

@return 
WAP Push plug-in that handles the specified media type.
*/
inline CContentHandlerBase* CContentHandlerBase::NewL(const TDesC& aMatchData)
	{
	// Call base class interface CPushHandlerBase::NewL()
	return REINTERPRET_CAST(CContentHandlerBase*, 
							CPushHandlerBase::NewL(aMatchData, KUidPushContentHandlerBase));
	}


/** 
Sets a parent message server entry for any output to be saved in the message 
server.

@param aParentID 
ID of the parent message server entry. This is stored in iParentID. 
*/
inline void CContentHandlerBase::SetParent(TMsvId aParentID)
	{
	iParentID = aParentID;
	}


/** 
Provides clean-up for the plug-in.

A derived class calls this when handling of the message is complete: it deletes 
the plug-in, and if the asynchronous request iAcknowledge flag is set, sets 
the status with the passed error code.

@param aError 
Error code. 
*/
inline void CContentHandlerBase::Complete(TInt aError)
	{
	__LOG_PTR_DEBUG("CContentHandlerPluginBase:: Complete Called");
	if (iAcknowledge)
		SignalConfirmationStatus(aError);
	iPluginKiller->KillPushPlugin();
	}	


/** 
Utility that completes this active object with KErrNone. 
*/
inline void CContentHandlerBase::IdleComplete()
	{
	TRequestStatus* pS = &iStatus;
	User::RequestComplete(pS,KErrNone);
	SetActive();
	}
