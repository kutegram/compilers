/*
* ============================================================================
*  Name       : PtiUserDictionary.inl
*  Part of    : PtiEngine
*  Description: Inline methods for user dictionary class.
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

inline void CPtiUserDictionary::SetFileName(TDesC& aFileName)
	{
	iFileName.Copy(aFileName);
	}


inline TInt CPtiUserDictionary::Id() const
	{
	return iId;
	}


inline void CPtiUserDictionary::SetId(TInt aId)
	{
	iId = aId;
	}


inline TInt CPtiUserDictionary::Size() const
	{
	return iData->Length();
	}


inline TInt32 CPtiUserDictionary::CoreUID() const
	{
	return iCoreUID;
	}
	

inline void CPtiUserDictionary::SetCoreUID(TInt32 aUid)
	{
	iCoreUID = aUid;
	}


inline TPtr8 CPtiUserDictionary::Data()
	{
	return TPtr8(iData->Des());
	}


inline TBool CPtiUserDictionary::IsDefault() const
	{
	return iDefault;
	}


inline void CPtiUserDictionary::SetDefault(TBool aValue)
	{
	iDefault = aValue;
	}


inline TPtrC CPtiUserDictionary::FileName() const
	{
	return TPtrC(iFileName);
	}


inline TBool CPtiUserDictionary::UpdateFlag() const
	{
	return iUpdateFlag;
	}


inline void CPtiUserDictionary::SetUpdateFlag(TBool aFlag)	
	{
	iUpdateFlag = aFlag;
	}


inline TInt CPtiUserDictionary::SymbolClass() const
	{
	return iSymbolClass;		
	}


inline void CPtiUserDictionary::SetSymbolClass(TInt aSymbolClass)
	{
	iSymbolClass = aSymbolClass;
	}


// End of file
