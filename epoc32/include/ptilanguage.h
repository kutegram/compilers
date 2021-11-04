/*
* ============================================================================
*  Name       : PtiLanguage.h
*  Part of    : PtiEngine
*  Description: PtiLanguage class definitions.
*  Version:
*
*  Copyright © 2003-2005 Nokia Corporation.
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
#ifndef _PTI_LANGUAGE_H
#define _PTI_LANGUAGE_H	

// INCLUDES
#include <e32base.h>
#include <f32file.h>
#include <barsc.h>
#include <barsread.h>
#include "PtiDefs.h"

const TInt KMaxMultitapResourceFileName = 20;
const TInt KMaxQwertyResourceFileName = 32;

// FORWARD DECLARATIONS
class MPtiKeyMappings;
class MPtiCore;

class TPtiCoreBinding
	{
	public:
		TInt iInputMode;
		MPtiCore* iCore;
	};


/**
* Client side interface for querying PtiEngine language related attributes. 
* All PtiEngine client side API methods related to handling languages access
* languages through this interface class. 
*/
class MPtiLanguage
	{
	public:
		/**
		* Returns a boolean value indicating whether this language supports
		* requested input mode. 
		*
		* @param aMode A input mode to be queried.
		* @return ETrue if this language supports requested input mode.
		*         EFalse otherwise.
		*/
		virtual TBool HasInputMode(TPtiEngineInputMode aMode) const = 0;
		
		/**
		* Returns list of all inputmodes currently supported by this language.
		*
		* @param aResult List of supported input modes will be stored here.
		*/		
		virtual void GetAvailableInputModesL(CArrayFix<TInt>* aResult) = 0;
		
		/**
		* Returns Symbian OS language code for this language.
		*
		* @return Symbian OS language code.
		*/		
		virtual TInt  LanguageCode() const = 0;
		
		/**
		* Returns localized name for this language.
		*
		* @return A constant pointer to localized language name.
		*/		
		virtual TPtrC LocalizedName() const = 0;
	};



/**
* Implementation class for a PtiEngine language. This class is used
* mainly in PtiEngine and core objects code and it implements clients side 
* language interface class.
* PtiEngine maintains language list containing instances of this class. 
* CPtiCoreLanguage class also maintains list of <core <-> input mode> bindings. 
*/ 
NONSHARABLE_CLASS(CPtiCoreLanguage) : public CBase, public MPtiLanguage
	{
	public:
		IMPORT_C static CPtiCoreLanguage* NewL();
		IMPORT_C ~CPtiCoreLanguage();
		
		/**
		* Sets multitapping keymappings.
		*
		* @param aMappings Pointer to keymappings object to be set.
		*/	
		IMPORT_C void SetKeyMappings(MPtiKeyMappings* aMappings);
		
		/**
		* Sets qwerty keymappings.
		*
		* @param aMappings Pointer to keymappings object to be set.
		*/			
		IMPORT_C void SetQwertyKeyMappings(MPtiKeyMappings* aMappings);
		
		/**
		* Sets Symbian OS language code for this language.
		*
		* @param aCode Language code to be set.
		*/
		IMPORT_C void SetLanguageCode(TInt aCode);
		
		/**
		* Returns pointer to multitapping keymappings object. 
		*
		* @return Pointer to current multitapping keymappings.
		*         NULL if no multitapping keymappings available.		
		*/
		IMPORT_C MPtiKeyMappings* GetKeymappings() const;
		
		/**
		* Returns pointer to qwerty keymappings object. 
		*
		* @return Pointer to current qwerty keymappings.
		*         NULL if no qwerty keymappings available.
		*/
		IMPORT_C MPtiKeyMappings* GetQwertyKeymappings() const;
		
		/**
		* Resets current multitapping keymappings.		
		*/
		IMPORT_C void ClearMultitapping();
		
		/**
		* Resets current qwerty keymappings.		
		*/		
		IMPORT_C void ClearQwerty();
		
		/**
		* Sets localized language name.
		*
		* @param aName Language name to be set.
		*/
		IMPORT_C void SetLocalizedName(const TDesC& aName);
		
		/**
		* Returns descriptor pointing to localized language name.
		*
		* @return Localoized language name descriptor.
		*/
		IMPORT_C TDes& LocalizedNameDes();
		
		/**
		* Returns core object for given input mode.
		*
		* @aMode  Input mode to be queried. 
		* @return Pointer to core object.
		*         NULL if no core object is asigned to given input mode.
		*/		
		IMPORT_C MPtiCore* GetCore(TPtiEngineInputMode aMode);
		
		/**
		* Sets core object for given input mode. If input mode already
		* has a core object asigned to it, it will be replaced.
		* 
		* @param aCore Pointer to core object 
		* @param aMode Input mode for core object.
		*/
		IMPORT_C void SetCore(MPtiCore *aCore, TPtiEngineInputMode aMode);

		/**
		* Returns an array of available input modes for this language object. 
		*
		* @param  aResult   Resulting input mode list. 
		*/
		IMPORT_C void GetAvailableInputModesL(CArrayFix<TInt>* aResult);

		/**
		* Returns an array of available input modes for this language object. 
		*
		* @param  aResult   Resulting input mode list. 
		* @since  3.0
		*/
		IMPORT_C void GetAvailableInputModesL(RArray<TInt>& aResult);

		/**
		* Returns a boolean value indicating whether this language
		* supports given input mode.
		*
		* @param   aMode  Input mode to be queried.
		* @return  ETrue  if input mode is supported.
		*          EFalse otherwise.
		*/
		IMPORT_C TBool HasInputMode(TPtiEngineInputMode aMode) const;
				
		/**
		* Returns Symbian OS language code for this language object.
		*
		* @return Language code			
		*/		
		inline TInt  LanguageCode() const;
		
		/**
		* Returns constant descriptor pointing to localized name for
		* this language.
		*
		* @return Localized language name.
		*/ 
		inline TPtrC LocalizedName() const;
		
		/**
		* Returns a boolean value indicating whether given core object is
		* already asigned to some input mode for this language.
		* 
		* @param  aCore A core object to be queried.
		* @return ETrue if given core object is asigned to any input mode.
		*         EFalse otherwise.
		*/
		IMPORT_C TBool HasCore(MPtiCore* aCore) const;
		
		/**
		* Removes detachs given core object from all input modes it is attached to.
		*
		* @param aCore A core object to be detached.
		*/
		IMPORT_C void RemoveCore(MPtiCore* aCore);
		
		void SetKeymappingFileIndex(TUint16 aIndex);
		void SetQwertyKeymappingFileIndex(TUint16 aIndex);
		
	private:
		CPtiCoreLanguage();
		void ConstructL();
		void Clear();
		void LoadKeymappingsL() const;
		void LoadQwertyKeymappingsL() const;
		inline TInt KeymappingFileIndex() const;
		inline TInt QwertyKeymappingFileIndex() const;
		
	private:
		TInt iLanguageCode;
		mutable MPtiKeyMappings* iKeyMappings;
		mutable MPtiKeyMappings* iQwertyKeyMappings;
		TBuf<KMaxLanguageNameLength> iLocalizedName;
		RArray<TPtiCoreBinding> iCores;		
		TInt iIndices;   // Indices for keymapping resource files inside directory.
		                 // Both ITU-T and qwerty are stored in this same variable.
	};

#include <PtiLanguage.inl>

#endif // _PTI_LANGUAGE_H

// End of file

