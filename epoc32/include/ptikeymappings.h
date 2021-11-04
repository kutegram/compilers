/*
* ============================================================================
*  Name       : PtiKeyMappings.h
*  Part of    : PtiEngine
*  Description: PtiLanguage class definitions.
*  Version:
*
*  Copyright © 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
#ifndef _PTI_KEY_MAPPINGS_H
#define _PTI_KEY_MAPPINGS_H

#include <e32base.h>
#include "PtiDefs.h"


const TInt KPtiKeyDataDeadKeySeparator = 0xffff;
const TInt KPtiPinyinMarker = 0x2460;
const TInt KPtiStrokeMarker = 0x2461;
const TInt KPtiZhuyinMarker = 0x2462;
const TInt KPtiCangjieMarker = 0x2463;
const TInt KPtiGetAllMarker = 0x2464;

// 
// CPtiQwertyKeymappingsExtension
//

NONSHARABLE_CLASS(CPtiQwertyKeymappingsExtension) : public CBase
	{
	public:
		static CPtiQwertyKeymappingsExtension* NewL();
		~CPtiQwertyKeymappingsExtension();		
	
	private:
		CPtiQwertyKeymappingsExtension();
	
	public:
		TUint16 iLastChar;	       // for Vietnamese 			
		TInt16 iLastTone;          // for Vietnamese
		TUint16 iReplaced;	       // for Vietnamese
		TPtiTextCase iVowelCase;   // for Vietnamese
		TPtiKey iLastToneKey;      // for Vietnamese			
	};


//
// TPtiKeyMapping
//

class TPtiKeyMapping
	{
	public:	
		TInt iIndex;
		TInt iNumChars;
	};

//
// MPtiKeyMappings
//
class MPtiKeyMappings
	{
	public:
		virtual ~MPtiKeyMappings() {}
		
		/**
		* Starts mapping new key. Will return first character bound to given
		* key in given text case. 		
		*
		* @param aKey   A key to be mapped.
		* @param aCase  Text case for mapping.
		* @param aMode  Input mode for mapping. This is needed if keymapping data contains
		*               characters for several input modes (used mainly with Chinese
		*               modes). This value will be matched to possible input mode control
		*               characters in keymapping data.
		* @return       First character bound to requested key.
		*/
		virtual TUint16 StartMapping(TPtiKey aKey,
			                         TPtiTextCase aCase,
									 TPtiEngineInputMode aMode = EPtiEngineInputModeNone) = 0;
		virtual TUint16 NextKey(TPtiKey aKey, TBool &aAppend, TPtiTextCase aCase) = 0;
		virtual TPtiKey CurrentKey() = 0;
		virtual TInt ReplaceKeyMapL(TPtiKey aKey, TDesC& aMap, TPtiTextCase aCase) = 0;
		virtual TPtiKey KeyForCharacter(TUint16 aChar) = 0;
		
		/**
		* Returns all keymapping data for current key, excluding first character
		* (which is expected to be "get all"-control character).
		* 
		* @param aCase  Text case for which data will be returned.
		* @return Constant descriptor pointing to keymap data.
		* @since 3.0
		*/		
		virtual TPtrC GetAll(TPtiTextCase aCase) = 0;					
	};



class CPtiMappings : public CBase
	{
	public:
		~CPtiMappings();
		
		/**
		* Returns constant pointer to all keymap data.
		*
		* @return Pointer to keymap data.
		*/		
		inline TPtrC Data() const;
		inline TInt DataSize() const;
		virtual TInt WriteData(TInt16* aDest);
		virtual TInt ChunkDataSize() const;

	protected:
		TPtiKey iCurrentKey;
		TInt iCurrentInternal;
		TInt iCurrentChar;
		RArray<TPtiKeyMapping> iMaps;
		HBufC* iData;
		TInt iReserved_1;
	};

//
// CPtiKeyMappings
// 

NONSHARABLE_CLASS(CPtiKeyMappings) : public CPtiMappings, public MPtiKeyMappings
	{
	public:	
		IMPORT_C static CPtiKeyMappings* NewL(TDesC& aData);
		IMPORT_C static CPtiKeyMappings* NewL(TInt16* aData);		
		IMPORT_C ~CPtiKeyMappings();
		
		/**
		* Start mapping for given key.
		*
		* @param aKey  Key code for key.
		* @param aCase Cuurrent text case.
		* @param aMode Current input mode. Default value works for most cases.
		* @return First character for given key. 
		*/
		IMPORT_C TUint16 StartMapping(TPtiKey aKey,
			                         TPtiTextCase aCase,
									 TPtiEngineInputMode aMode = EPtiEngineInputModeNone);										 
									 
		IMPORT_C TUint16 NextKey(TPtiKey aKey, TBool &aAppend, TPtiTextCase aCase);
		
		/**
		* Returns key code for key currently being mapped (relates to StartMapping and NextKey).
		*
		* @return Key code for key currently being mapped.
		*/
		inline TPtiKey CurrentKey();
		
		/**
		* Replaces keymapping data for given key.
		*		
		* @param  aKey  Key code for key to be replaced.
		* @param  aMap  New keymapping data for aKey.
		* @param  aCase Text case.
		* @return KErrNone if succesfull
		*         Otherwise system wide error code.
		*/
		IMPORT_C TInt ReplaceKeyMapL(TPtiKey aKey, TDesC& aMap, TPtiTextCase aCase);
		
		/**
		* Scans through keymapping data and returns key code for given character.
		*
		* @param  aChar A character to be queried.
		* @return Key code for mtaching key.
		*         EPtiKeyNone if no matching keys found.
		*/
		IMPORT_C TPtiKey KeyForCharacter(TUint16 aChar);
		
		/**
		* Returns keymapping data for given key.
		*
		* @param aKey    A key to be queried.
		* @param aResult Descritor where resulting data is stored.
		* @param aCase   Text case		 
		*/
		IMPORT_C void GetDataForKey(TPtiKey aKey, TDes& aResult, TPtiTextCase aCase);
								
		/**
		* Returns all keymapping data for current key, excluding first character
		* (which is expected to be "get all"-control character).
		* 
		* @param aCase  Text case for which data will be returned.
		* @return Constant descriptor pointing to keymap data.
		* @since 3.0
		*/		
		TPtrC GetAll(TPtiTextCase aCase);							

	private:		
		CPtiKeyMappings();
		void ConstructL(TDesC& aData);
		void ConstructL(TInt16* aData);
		TUint16 NextChar(TPtiTextCase aCase);
		void KeyCodeToInternal(TPtiKey aKey);
		TPtiKey InternalToKeyCode(TInt aInternal);
	};



NONSHARABLE_CLASS(CPtiQwertyKeyMappings) : public CPtiMappings, public MPtiKeyMappings
	{
	private:
		CPtiQwertyKeyMappings();
	public:	 
		IMPORT_C static CPtiQwertyKeyMappings* NewL(TDesC& aData);
		IMPORT_C static CPtiQwertyKeyMappings* NewL(TInt16* aData);		
		IMPORT_C ~CPtiQwertyKeyMappings();
		
		/**
		* Start mapping for given key.
		*
		* @param aKey  Key code for key.
		* @param aCase Cuurrent text case.
		* @param aMode Current input mode. Default value works for most cases.
		* @return First character for given key. 
		*/		
		IMPORT_C TUint16 StartMapping(TPtiKey aKey,
			                          TPtiTextCase aCase,
									  TPtiEngineInputMode aMode = EPtiEngineInputModeNone);
		IMPORT_C TUint16 NextKey(TPtiKey aKey, TBool &aAppend, TPtiTextCase aCase);
		
		/**
		* Returns key code for key currently being mapped (relates to StartMapping and NextKey).
		*
		* @return Key code for key currently being mapped.
		*/		
		inline TPtiKey CurrentKey();
		
		/**
		* Replaces keymapping data for given key.
		*		
		* @param  aKey  Key code for key to be replaced.
		* @param  aMap  New keymapping data for aKey.
		* @param  aCase Text case.
		* @return KErrNone if succesfull
		*         Otherwise system wide error code.
		*/		
		IMPORT_C TInt ReplaceKeyMapL(TPtiKey aKey, TDesC& aMap, TPtiTextCase aCase);
		
		/**
		* Scans through keymapping data and returns key code for given character.
		*
		* @param  aChar A character to be queried.
		* @return Key code for mtaching key.
		*         EPtiKeyNone if no matching keys found.
		*/		
		IMPORT_C TPtiKey KeyForCharacter(TUint16 aChar);
		
		/**
		* Returns keymapping data for given key.
		*
		* @param aKey    A key to be queried.
		* @param aResult Descritor where resulting data is stored.
		* @param aCase   Text case		 
		*/		
		IMPORT_C void GetDataForKey(TPtiKey aKey, TDes& aResult, TPtiTextCase aCase);
		
		inline TBool DeadKeyRootFlag() const;
		inline TUint16 DeadKeyRootChar() const;
		TInt WriteData(TInt16* aDest);
		TInt ChunkDataSize() const;
		inline TBool VowelSequenceFlag() const;
		inline TUint16 VowelSequenceResult() const;
		inline void ClearVowelSequence();
		inline TInt16 DeadKey() const;
		inline void ClearDeadKey();
		inline void ClearLastChar();
		inline void SetLastChar(TInt aLastChar);
		inline TInt GetLastChar() const;
		inline TUint16 ReplacedCharacter();
		inline void SetLastKey(TPtiKey aKey);
		inline TPtiTextCase VowelCase() const;
		inline void ResetVietnameseVowelSequenceAndToneMarks();
		inline TPtiKey LastKey() const;

		/**
		* Returns all keymapping data for current key, excluding first character
		* (which is expected to be "get all"-control character).
		* 
		* @param aCase  Text case for which data will be returned.
		* @return Constant descriptor pointing to keymap data.
		* @since 3.0
		*/		
		TPtrC GetAll(TPtiTextCase aCase);							
		
		inline void SetFlag(TInt aFlag);
		inline void ResetFlag(TInt aFlag);			

	public:
		enum
			{
			EDeadKeyRootFlag = 0x01,
			EVowelSeqFlag    = 0x02,
			EPrevKeyInUpperCase = 0x04,
			ETrackVietnameseToneMarksAndVowels = 0x08
			};
						
	private:			
		void ConstructL(TDesC& aData);
		void ConstructL(TInt16* aData);
		TUint16 NextChar(TPtiTextCase aCase);
		TBool KeyCodeToInternal(TPtiKey aKey);
		TPtiKey InternalToKeyCode(TInt aInternal);
		TUint16 GetDeadKeyChar(TInt aStartIndex);
		inline TInt DeadKeyIndex(TUint16 aDeadKeyUnicode);
		inline TBool IsDeadKeyCode(TUint16 aChar) const;
		inline TBool IsModeControlChar(TUint16 aChar) const;
		TUint16 GetCharForMode(TPtiEngineInputMode aMode, TInt aIndex, TInt aNumChars, TBool aSkipFirst); 
		TBool DoesModeCharMatchToInputMode(TUint16 aChar, TPtiEngineInputMode aMode) const;
		TUint16 VowelSequence(TPtiKey aKey1, TPtiKey aKey2, TPtiTextCase aCase) const;	
		TUint16 VietnameseToneMark(TUint16 aPrevChar, TPtiKey aKey);
		TUint16 RepeatingVowelSequence(TPtiKey aKey);
		TPtiKey VowelSeqRootKey(TUint16 aChar);

	private:
		RArray<TPtiKeyMapping> iDeadKeyMaps;
		HBufC* iDeadKeyData;			
		TInt16 iDeadKey;
		TInt16 iDeadKeyRootChar;
		TInt16 iVowelSeqResult;
		TPtiKey iLastKey;
		TInt iFlags;
		CPtiQwertyKeymappingsExtension* iExtension;
	};


inline TPtiKey CPtiKeyMappings::CurrentKey()
	{
	return iCurrentKey;
	}



inline TPtrC CPtiMappings::Data() const
	{
	if (iData)
		{
		return iData->Des();
		}

	return TPtrC();
	}


inline TInt CPtiMappings::DataSize() const
	{
	if (iData)
		{
		return iData->Size();
		}

	return 0;
	}



inline TPtiKey CPtiQwertyKeyMappings::CurrentKey()
	{
	return iCurrentKey;
	}


inline TInt CPtiQwertyKeyMappings::DeadKeyIndex(TUint16 aDeadKeyUnicode)
	{
	return (aDeadKeyUnicode & 0x00ff);
	}


inline TBool CPtiQwertyKeyMappings::IsDeadKeyCode(TUint16 aChar) const
	{
	if (((aChar & 0xff00) == 0xf000) &&
	    ((aChar & 0xff) <= 5))
		{
		return ETrue;	
		}
		
	return EFalse;	
	}


inline TBool CPtiQwertyKeyMappings::DeadKeyRootFlag() const
	{
	return (iFlags & EDeadKeyRootFlag) != 0;		
	}


inline TBool CPtiQwertyKeyMappings::IsModeControlChar(TUint16 aChar) const
	{
	if ((aChar == KPtiPinyinMarker) ||
		(aChar == KPtiStrokeMarker) ||
		(aChar == KPtiZhuyinMarker) ||
		(aChar == KPtiCangjieMarker))
		{	
		return ETrue;
		}

	return EFalse;
	}


inline TBool CPtiQwertyKeyMappings::VowelSequenceFlag() const
	{
	return (iFlags & EVowelSeqFlag) != 0;
	}


inline void CPtiQwertyKeyMappings::SetFlag(TInt aFlag)
	{
	iFlags |= aFlag;	
	}

inline void CPtiQwertyKeyMappings::ResetFlag(TInt aFlag)
	{	
	iFlags &= ~aFlag;	
	}


inline TUint16 CPtiQwertyKeyMappings::VowelSequenceResult() const
	{
	return iVowelSeqResult;
	}


inline void CPtiQwertyKeyMappings::ClearVowelSequence()
	{
	iLastKey = EPtiKeyNone;
	}
	
	
inline TUint16 CPtiQwertyKeyMappings::DeadKeyRootChar() const
	{
	return iDeadKeyRootChar;	
	}
	
	
inline TInt16 CPtiQwertyKeyMappings::DeadKey() const
	{
	return iDeadKey;	
	}	


inline void CPtiQwertyKeyMappings::ClearDeadKey()
	{
	iDeadKey = 0;
	}
	
	
inline void CPtiQwertyKeyMappings::ClearLastChar()
	{
	iExtension->iLastChar = 0;
	}

	
inline void CPtiQwertyKeyMappings::SetLastChar(TInt aLastChar)
	{
	iExtension->iLastChar = (TUint16)aLastChar;
	}
	
	
inline TInt CPtiQwertyKeyMappings::GetLastChar() const
	{
	return iExtension->iLastChar;
	}
	
	
inline TUint16 CPtiQwertyKeyMappings::ReplacedCharacter()
	{	
	return iExtension->iReplaced;
	}

		
inline void CPtiQwertyKeyMappings::SetLastKey(TPtiKey aKey)
	{
	iLastKey = aKey;	
	}
		

inline TPtiTextCase CPtiQwertyKeyMappings::VowelCase() const
	{
	return iExtension->iVowelCase;
	}


inline void CPtiQwertyKeyMappings::ResetVietnameseVowelSequenceAndToneMarks()
	{
	iExtension->iLastChar = 0;
	iExtension->iReplaced = 0;
	iExtension->iLastTone = 0;
	iVowelSeqResult = 0;
	iLastKey = EPtiKeyNone;
	ResetFlag(EVowelSeqFlag);
	}
	

inline TPtiKey CPtiQwertyKeyMappings::LastKey() const
	{
	return iLastKey;
	}
	
	
#endif // _PTI_KEY_MAPPINGS_H

