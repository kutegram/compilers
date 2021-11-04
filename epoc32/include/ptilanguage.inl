/*
* ============================================================================
*  Name       : PtiLanguage.inl
*  Part of    : PtiEngine
*  Description: Inline methods for PtiLanguage class.
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



inline TInt CPtiCoreLanguage::LanguageCode() const
	{
	return iLanguageCode;
	}


inline TPtrC CPtiCoreLanguage::LocalizedName() const
	{
	return TPtrC(iLocalizedName);
	}


inline TInt CPtiCoreLanguage::KeymappingFileIndex() const
	{
	return (iIndices & 0xffff);	
	}


inline TInt CPtiCoreLanguage::QwertyKeymappingFileIndex() const
	{
	return ((iIndices & 0xffff0000)	>> 16);
	}
	

// End of file
