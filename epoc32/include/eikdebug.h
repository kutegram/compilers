// EIKDEBUG.H
//
// Copyright (c) Symbian Software Ltd 1997-2006.  All rights reserved.
//

/**  @file
@publishedAll
@deprecated
*/

#ifndef __EIKDEBUG_H__
#define __EIKDEBUG_H__

//#define UIKON_OOM_TESTING		// enabling the testing requires also adding the FBSRV.LIB to eiksrvs and console mmp file.

#if defined(UIKON_OOM_TESTING)
#define __SHOW_FAIL_RATE(aFormatString, aFailRate) RDebug::Print(aFormatString,aFailRate)
#else
#define __SHOW_FAIL_RATE(aFormatString, aFailRate)
#endif

//#define _LOGGING // enabling RDebug::Print
#ifdef _LOGGING
#include <e32debug.h>

#define DEBUGPRINT1(_p1) RDebug::Print(_p1)
#define DEBUGPRINT2(_p1,_p2) RDebug::Print(_p1,_p2)
#define DEBUGPRINT3(_p1,_p2,_p3) RDebug::Print(_p1,_p2,_p3)
#define DEBUGPRINT4(_p1,_p2,_p3,_p4) RDebug::Print(_p1,_p2,_p3,_p4)
#else
#define DEBUGPRINT1(_p1)
#define DEBUGPRINT2(_p1,_p2)
#define DEBUGPRINT3(_p1,_p2,_p3)
#define DEBUGPRINT4(_p1,_p2,_p3,_p4)
#endif



//
//	class CEikDebugPreferences
//

/**
@internalComponent
*/
NONSHARABLE_CLASS(CEikDebugPreferences) : public CBase
	{
public:
	enum TFlag
		{
		EFlagDebugKeysOn				=0x00000001,
		EFlagOOMTestingOnAppStartUp		=0x00000002,
		EFlagOOMTestingOnEiksrvStartUp	=0x00000004,
		EFlagOOMTestingOnConsoleStartUp	=0x00000008
		};
public:
	IMPORT_C static CEikDebugPreferences* New();
	IMPORT_C static CEikDebugPreferences* NewL();
	IMPORT_C static CEikDebugPreferences* NewLC();
	IMPORT_C ~CEikDebugPreferences();
	IMPORT_C void StoreL(RFs& aFileServerSession);
	IMPORT_C TInt Restore(RFs& aFileServerSession); // can be used with or without a CTrapHandler being currently installed
	IMPORT_C void RestoreL(RFs& aFileServerSession);
	IMPORT_C void SetKeysOn(const TBool& aDebugKeysOn);
	IMPORT_C TBool KeysOn() const;
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	inline void SetFlags(TUint aFlags);
	inline TUint Flags() const;
private:
	CEikDebugPreferences();
private:
	TUint iFlags;
	TUint iSpare;
	};

inline void CEikDebugPreferences::SetFlags(TUint aFlags)
	{
	iFlags=aFlags;
	}

inline TUint CEikDebugPreferences::Flags() const
	{
	return iFlags;
	}

// __EIKDEBUG_H__
#endif

