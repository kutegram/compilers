// EIKSVDEF.H
//
// Copyright (c) 1997-2006 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKSVDEF_H__
#define __EIKSVDEF_H__

/**
@publishedPartner

*/
enum
	{
	KExternalKeyModifier=0,
	KExternalKey1=EKeyDictaphoneStop,
	KExternalKey2=EKeyDictaphonePlay,
	KExternalKey3=EKeyDictaphoneRecord,
	KExternalKeyModifierMask=EAllStdModifiers|EModifierFunc
	};

/**
@publishedPartner

*/
const TUid KUidExternalKeyHandlerAppStream={0x10000117};

/**
@publishedPartner
@deprecated
*/
const TUid KUidDictaphoneFileStream={0x100001CF};

/**
@internalComponent
*/
_LIT(__EIKON_SERVER_NAME,"EikonServer");

/**
@publishedPartner

*/
enum TEikServEvent
	{
	EEikServExit,
	EEikServChangePasswordMode,
	EEikServShowTaskList,
	EEikServHideTaskList,
	};

/**
@publishedPartner

*/
enum { KNumOfSideButtons=5, KNumOfAppButtons=9 };

/**
@publishedPartner

*/
_LIT(EIKON_SERVER_BACKDROP_WINDOW_GROUP_NAME,"EiksrvBackdrop");

// __EIKSVDEF_H__
#endif
