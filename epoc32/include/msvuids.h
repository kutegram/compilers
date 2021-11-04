// MSVUIDS.H
//
// Copyright (c) 1998-2007 Symbian Ltd.  All rights reserved.
//
/**
* @file
* @publishedAll
* 
*/
#if !defined(__MSVUIDS_H__)
#define __MSVUIDS_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif


/**
* Entry type Uids
* @publishedAll
* 
*/
const TUid KUidMsvNullEntry={0};
/**
* Root entry of entire index 
* @publishedAll
* 
*/
const TUid KUidMsvRootEntry={KUidMsvRootEntryValue};
// Service 
/**
* @publishedAll
* 
*/
const TUid KUidMsvServiceEntry={KUidMsvServiceEntryValue};
// Folder 
/**
* @publishedAll
* 
*/
const TUid KUidMsvFolderEntry={KUidMsvFolderEntryValue};
// Message
/**
* @publishedAll
* 
*/
const TUid KUidMsvMessageEntry={KUidMsvMessageEntryValue};
// Entry 
/**
* @publishedAll
* 
*/
const TUid KUidMsvAttachmentEntry={KUidMsvAttachmentEntryValue};

// Local Service Uid
// An operation that affects only local entries. 
/**
* @publishedAll
* 
*/
const TUid KUidMsvLocalServiceMtm={KUidMsvLocalServiceMtmValue};
//An operation performed by the Message Server. 
/**
* @publishedAll
* 
*/
const TUid KUidMsvServerMtm={KUidMsvServerMtmValue};
#endif
