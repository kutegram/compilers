/*
* ============================================================================
*  Name       : PtiLanguageDatabase.h
*  Part of    : PtiEngine
*  Description: Language database class declaration.
*  Version:
*
*  Copyright © 2005 Nokia Corporation.
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
#ifndef _PTI_LANGUAGE_DATABASE_H
#define _PTI_LANGUAGE_DATABASE_H

// INCLUDES
#include <badesca.h> 
#include "PtiDefs.h"

class TPtiLangDatabaseMapping
	{
	public:
		TInt iUid;
		TInt iLangCode;
	};	


class MPtiLanguageDatabase
	{
	public:
		virtual TInt CoreUID() const = 0;
		virtual TInt NumLanguages() const = 0;
		virtual TInt LanguageCode(TInt aIndex) const = 0;
		virtual TInt SubLanguageCode(TInt aIndex) const = 0;
		virtual TInt8* LangData(TInt aIndex) const = 0;
		virtual TInt8* LangData(TInt aIndex, TAny* aNativeParams) const = 0;
		virtual TInt8* PinyinPhraseData() const = 0;
		virtual TInt8* ZhuyinPhraseData() const = 0;
		virtual TInt NativeId(TInt aIndex) const = 0;
	};


class CPtiLanguageDatabase : public CBase, public MPtiLanguageDatabase
	{
	public: 
		IMPORT_C static CPtiLanguageDatabase* CreateDatabaseL(TUid aImplUid);
		IMPORT_C static CArrayFix<TInt>* ListDatabasesLC(TInt aCoreUid);
		IMPORT_C static TInt LanguageCodeForUid(TInt aUid);
		IMPORT_C static TInt CreateMappingTableL(TInt aCoreUid, RArray<TPtiLangDatabaseMapping>& aResult);

	public: 
		IMPORT_C ~CPtiLanguageDatabase();
			
	public: // Empty default implementations.
		IMPORT_C TInt CoreUID() const;
		IMPORT_C TInt NumLanguages() const;
		IMPORT_C TInt LanguageCode(TInt aIndex) const;
		IMPORT_C TInt SubLanguageCode(TInt aIndex) const;
		IMPORT_C TInt8* LangData(TInt aIndex) const;
		IMPORT_C TInt8* LangData(TInt aIndex, TAny* aNativeParams) const;
		IMPORT_C TInt8* PinyinPhraseData() const;
		IMPORT_C TInt8* ZhuyinPhraseData() const;
		IMPORT_C TInt NativeId(TInt aIndex) const;

	public:
		inline void SetDestructorKeyId(TInt aDtorKeyId);

	private:
		TInt iDtorKeyId;
		TInt Reserved_1;
	};


inline void CPtiLanguageDatabase::SetDestructorKeyId(TInt aDtorKeyId)
	{
	iDtorKeyId = aDtorKeyId;
	}

#endif // _PTI_LANGUAGE_DATABASE_H

// End of file


