// APFDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APFDEF_H__
#define __APFDEF_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

// generic file extensions etc.

/**
@internalTechnology
*/
_LIT(KExeAppFileExtension,".exe");

#if (((defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)) || defined(UI_FRAMEWORKS_V1_REMNANT_FOR_JAVA_MIDLET_INSTALLER))
/**
@internalTechnology
*/
_LIT(KAppFileExtension,".app");

/**
@internalTechnology
*/
_LIT(KAppInfoFileExtension,".aif");

/**
@internalComponent
*/
_LIT(KSystemControlFileExtension,".ctl");

/**
@internalComponent
*/
_LIT(KApaCaptionFileSuffix,"_Caption");

/**
@internalComponent
*/
const TInt KApparcExtraLengthOfCaptionFileName=15;
// #if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)
#endif

/**
@internalTechnology
*/
_LIT(KIniFileExtension,".ini");

/**
@internalTechnology
*/
_LIT(KAppResourceFileExtension,".rsc");

//
// paths etc.

#if (((defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)) || defined(UI_FRAMEWORKS_V1_REMNANT_FOR_JAVA_MIDLET_INSTALLER))
class Apfile
/**
@internalComponent
@deprecated
*/
	{
public:
	IMPORT_C static TPtrC TempPath();
	};
#endif


#endif
