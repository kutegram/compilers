//  BIOUUIDS.H
//
//	Copyright (c) 1999-2007 Symbian Software Ltd.  All rights reserved.
//
// Contains the TUid defines for the Bio Messaging 
//

/**
* @file
* @publishedAll
* 
*/

#if !defined(__BIOUTILS_H__)
#define __BIOUTILS_H__

//forward declarations
/**
* @publishedAll
* 
*/
class TUid;
/**
*UID of the Smart Message Parser DLL.
* @publishedPartner
* 
*/
const TUid KUidSmartMessageParserDll    = { 0x10001251};
/**
* BIO specific error/panic code base. 
* @publishedPartner
* 
*/
const TInt KBIOMessageBaseError				= -505;
/**
* BIO message not found error. 
* @publishedPartner
* 
*/
const TInt KBIOMessageNotFound				= KBIOMessageBaseError;
/**
* BIO server MTM already active error. 
* @publishedPartner
* 
*/
const TInt KBIOMessageSvrMtmNotInactive		= KBIOMessageBaseError-1;
/**
* No BIO parser error. 
* @publishedPartner
* 
*/
const TInt KBIOMessageNoParserCreated		= KBIOMessageBaseError-2;  
/** 
* BIO parser in use error. 
* @publishedPartner
* 
*/
const TInt KBIOMessageParserDllStillInUse	= KBIOMessageBaseError-3;  
/**    
* BIO operation already active error. 
* @publishedPartner
* 
*/
const TInt KBIOMessageOperationNotInactive	= KBIOMessageBaseError-4;
/**
* BIO server MTM operation not supported. 
* @publishedPartner
* 
*/
const TInt KBIOMessageSvrNotSupported		= KBIOMessageBaseError-5;
/**
* Unused. 
* @internalComponent
* @removed
*/
const TUid KUidMsvNbsEditor={0x10001264};

//  New BIO Messaging TUids
/**
* Stream ID used for storing parsed BIO data.
* @internalAll
* 
*/
const TUid KUidMsvBIODataStream			= {0x10005268}; // stream used for storing parsed data

//  BIO Mtm components

/**
* BIO message type UID. 
* @publishedAll
* 
*/
const TUid KUidBIOMessageTypeMtm		= {0x10001262};
/**
* BIO client MTM UID. 
* @internalTechnology
* 
*/
const TUid KUidBIOMessageClientMtmDll	= {0x1000125A}; //previously NBSC, now BIOC
/**
* BIO server MTM UID. 
* @internalTechnology
* 
*/
const TUid KUidBIOMessageServerMtmDll	= {0x1000125C}; //previously NBSS, now BIOS
/**
* BIO UI MTM UID. 
* @internalTechnology
* 
*/
const TUid KUidBIOMessageUiLayerMtmDll	= {0x10001265}; //previously NBUM, now BIUM
/**
* BIO message viewer UID. 
* @internalTechnology
* 
*/
const TUid KUidBIOMessageViewerApp		= {0x10001264}; //previously NBED,now BIED

#endif *__BIOUTILS_H__
