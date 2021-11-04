// e32\include\e32ktran.h
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

/**
	@file
	@internalTechnology
*/

#ifndef __E32KTRAN_H__
#define __E32KTRAN_H__
#include <e32std.h>
#include <e32keys.h>
#include <e32base.h>
//
class TMaskedModifiers
	{
public:
	TUint iMask;
	TUint iValue;
	};
//
enum TPattern
	{
	EAnyKey=0x00,
	EAnyAlphaNumeric,
	EAnyAlpha,
	EAnyAlphaLowerCase,
	EAnyAlphaUpperCase,
	EAnyDecimalDigit,
	EAnyDigitGivenRadix,
	EAnyModifierKey,
	EMatchKey=0x40,
	EMatchKeyCaseInsens,
	EMatchLeftOrRight
	};
//
class TKeyCodePattern
	{
public:
	TUint16 iKeyCode;
	TInt8   iPattern;
	TInt8   iFiller;
	};
//
class TCaptureKey
	{
public:
	TMaskedModifiers iModifiers;
	TKeyCodePattern  iKeyCodePattern;
	TUint iApp;
	TUint iHandle;
	};
//
class TKeyData
	{
public:
	TInt  iModifiers;
	TInt  iApp;
	TInt  iHandle;
	TBool iIsCaptureKey;
	TUint iKeyCode;
	};
//
class CCaptureKeys: public CBase
	{
public:
	IMPORT_C CCaptureKeys();
	IMPORT_C ~CCaptureKeys();
	IMPORT_C void Construct();
	IMPORT_C void AddCaptureKeyL(const TCaptureKey &aCaptureKey);
	IMPORT_C void AddCaptureKeyL(const TCaptureKey &aCaptureKey, TUint8 aPriority);
	IMPORT_C void SetCaptureKey(TUint32 aHandle, const TCaptureKey &aCaptureKey);
	IMPORT_C void SetCaptureKey(TUint32 aHandle, const TCaptureKey &aCaptureKey, TUint8 aPriority);
	IMPORT_C void CancelCaptureKey(TUint32 aHandle);
	IMPORT_C void CancelAllCaptureKeys(TUint32 aApp);
	IMPORT_C void ProcessCaptureKeys(TKeyData &aKeyData) const;
protected:
	void CheckCaptureKey(const TCaptureKey &aCaptureKey);
	void removeCaptureKey(TUint index);
protected:
	RArray<TCaptureKey> iCKarray;
	};
//
class CKeyTranslator: public CBase
	{
public:
	IMPORT_C static CKeyTranslator *New();
	virtual TInt GetModifierState()=0;
	virtual void SetModifierState(TEventModifier aModifier,TModifierState aState)=0;
	virtual TBool TranslateKey(TUint aScanCode,TBool aKeyUp,const CCaptureKeys &aCaptureKeys,TKeyData &aKeyData)=0;
    virtual void UpdateModifiers(TInt aModifiers)=0;
    virtual TInt ChangeKeyData(const TDesC& aLibraryName)=0;
	};

#endif

