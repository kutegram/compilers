// MSVRUIDS.H
//
// Copyright (c) 1998-2007 Symbian Ltd.  All rights reserved.
//
/**
* @file
* @publishedAll
* 
*/
#if !defined(__MSVREGUD_H__)
#define __MSVREGUD_H__

#include <e32base.h>
#include <msvstd.hrh>

/**
* @internalAll
* 
*/
const TInt KMsvNumMtmDllTypes=4;
/**
* @internalAll
* 
*/
const TUid KUidMsvDataComponent     ={0x10003C69};
// Server-side MTM 
/**
* @publishedAll
* 
*/
const TUid KUidMtmServerComponent	={KUidMtmServerComponentVal};
// Client-side MTM 
/**
* @publishedAll
* 
*/
const TUid KUidMtmClientComponent	={KUidMtmClientComponentVal};
// User Interface MTM
/**
* @internalAll
* 
*/
const TUid KUidMtmUiComponent		={KUidMtmUiComponentVal};
// UI Data MTM 
/**
* @internalAll
* 
*/
const TUid KUidMtmUiDataComponent	={KUidMtmUiDataComponentVal};
/**
* @internalTechnology
* 
*/
const TUid KMsvDllType1Uid={0x10003C62}; 
/**
* @internalTechnology
* 
*/
const TUid KMsvDllType2Uid={0x10003C63};
/**
* @internalTechnology
* 
*/
const TUid KMsvDllType3Uid={0x10003C64};
/**
* @internalTechnology
* 
*/
const TUid KMsvDllType4Uid={0x10003C65};
/**
* @internalTechnology
* 
*/
const TUid KMsvDllType5Uid={0x10003C66};
/**
* @internalTechnology
* 
*/
const TUid KMsvDllType6Uid={0x10003C67};
/**
* @internalComponent
* 
*/
const TUid KUidMtmMultipleComponent	={0x10004845}; 

#endif
