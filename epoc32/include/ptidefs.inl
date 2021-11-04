/*
* ============================================================================
*  Name       : PtiDefs.inl
*  Part of    : PtiEngine
*  Description: Inline methods for PtiDefs.h files
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

inline TBool TPtiCoreInfo::WordCompletion() const
	{
	return ((iCapsBits & EWordCompletion) != 0);
	}


inline TBool TPtiCoreInfo::Reordering() const
	{
	return ((iCapsBits & EReordering) != 0);
	}


inline TInt TPtiCoreInfo::MaximumWordLength() const
	{
	return iMaxWordLength;  
	}


inline TBool TPtiCoreInfo::NextWordPrediction() const
	{
	return ((iCapsBits & ENextWordPrediction) != 0);
	}


inline TPtrC TPtiCoreInfo::VendorString() const
	{
	return iVendorIdStr;
	}


inline TUint32 TPtiCoreInfo::CapsBits() const
	{
	return iCapsBits;
	}


inline void TPtiCoreInfo::SetCapsBits(TUint32 aBits)
	{
	iCapsBits |= aBits;
	}


inline void TPtiCoreInfo::SetVendorString(const TDesC& aStr)
	{
	iVendorIdStr.Set(aStr);
	}


inline void TPtiCoreInfo::SetMaxWordLength(TInt aMaxLen) 
	{
	iMaxWordLength = aMaxLen;
	}
	

inline TInt32 TPtiCoreInfo::Uid() const
	{
	return iUid;
	}


inline void TPtiCoreInfo::SetUid(TInt32 aUid)
	{
	iUid = aUid;
	}

	
inline TInt TPtiCoreInfo::MaximumNumberOfCandidates() const
	{
	return iMaxNumberOfCandidates;
	}


inline void TPtiCoreInfo::SetMaxNumberOfCandidates(TInt aMax)
	{
	iMaxNumberOfCandidates = aMax;
	}


inline TUint32 TPtiCoreInfo::CharConversions() const
	{
	return iCharConversions;
	}


inline void TPtiCoreInfo::SetCharConversions(TUint32 aConvs)
	{
	iCharConversions = aConvs;
	}


inline void TPtiCoreInfo::SetSpellings(TUint32 aSpellings)
	{
	iSpellings = aSpellings;
	}


inline TUint32 TPtiCoreInfo::Spellings() const
	{
	return iSpellings;
	}

// End of file
