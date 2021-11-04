// MSVIDS.H
//
// Copyright (c) Symbian Software Ltd 1998-2007.  All rights reserved.
//

/**
* @file
* @publishedAll
* 
*/

#if !defined(__MSVIDS_H__)
#define __MSVIDS_H__
#if !defined(__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif
#if !defined(__MSVSTD_H__)
#include <msvstd.h>
#endif

// Predefined entry ids - values #defined in MSVSTD.HRH

/**
A NULL ID. 
This is typically used to indicate that the ID has not yet been set. It can 
also be used to "park" a CMsvServerEntry so that it doesn't lock an index 
entry.
@publishedAll

@see TMsvId
@see KMsvNullIndexEntryIdValue
*/
const TMsvId KMsvNullIndexEntryId=KMsvNullIndexEntryIdValue;//0

/**
Temporary ID used for testing purpose
@internalAll

@see TMsvId
@see KMsvTempIndexEntryIdValue
*/
const TMsvId KMsvTempIndexEntryId=KMsvTempIndexEntryIdValue;//1

/**
ID of root entry of entire index
@publishedAll

@see TMsvId
@see KMsvRootIndexEntryIdValue
*/
const TMsvId KMsvRootIndexEntryId=KMsvRootIndexEntryIdValue;//0x1000

/**
ID of local service (containing the standard folders)
@publishedAll

@see TMsvId
@see KMsvLocalServiceIndexEntryIdValue
*/
const TMsvId KMsvLocalServiceIndexEntryId=KMsvLocalServiceIndexEntryIdValue;//0x1001

/**
ID of Inbox folder 
@publishedAll

@see TMsvId
@see KMsvGlobalInBoxIndexEntryIdValue
*/
const TMsvId KMsvGlobalInBoxIndexEntryId=KMsvGlobalInBoxIndexEntryIdValue;//0x1002

/**
ID of Outbox folder
@publishedAll

@see TMsvId
@see KMsvGlobalOutBoxIndexEntryIdValue
*/
const TMsvId KMsvGlobalOutBoxIndexEntryId=KMsvGlobalOutBoxIndexEntryIdValue;//0x1003

/**
ID of Draft folder
@publishedAll

@see TMsvId
@see KMsvDraftEntryIdValue
*/
const TMsvId KMsvDraftEntryId=KMsvDraftEntryIdValue; //0x1004

/**
ID of Sent folder
@publishedAll

@see TMsvId
@see KMsvSentEntryIdValue
*/
const TMsvId KMsvSentEntryId=KMsvSentEntryIdValue; //0x1005

/**
ID of Deleted folder - Invisible folder
@publishedAll

@see TMsvId
@see KMsvDeletedEntryFolderEntryIdValue
*/
const TMsvId KMsvDeletedEntryFolderEntryId=KMsvDeletedEntryFolderEntryIdValue;//0x1006

/**
ID used to indicate Unknown/Invalid Service entry folder
@publishedAll

@see TMsvId
@see KMsvUnkownServiceIndexEntryIdValue
*/
const TMsvId KMsvUnknownServiceIndexEntryId=KMsvUnkownServiceIndexEntryIdValue; //0x1007

/**
@internalAll

@see TMsvId
*/
const TMsvId KFirstFreeEntryId=0x100000;

/**
Uid for POPService
@publishedAll

*/
const TUid KUidPOPService = {0x2000BB68};

/**
Uid for IMAPService
@publishedAll

*/
const TUid KUidIMAPService = {0x2000BB69};

/**
Uid for SMTPService
@publishedAll

*/
const TUid KUidSMTPService = {0x2000BB6A};

/**
Uid for SendAs2Service
@publishedAll

*/
const TUid KUidSendAs2Service = {0x2000BB6B};

/**
Uid for SMSService
@publishedAll

*/
const TUid KUidSMSService = {0x2000BB6C};

#endif
