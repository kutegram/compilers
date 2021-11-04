/*
* ============================================================================
*  Name       : PtiUserDicEntry.inl
*  Part of    : PtiEngine
*  Description: Inline methods for user dictionary interface.
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


inline TPtiUserDictionaryEntry::TPtiUserDictionaryEntry()
	{
	}


inline TPtiUserDictionaryEntry::TPtiUserDictionaryEntry(const TDesC& aWord) : iEntry(aWord)
	{
	}


inline TPtrC TPtiUserDictionaryEntry::Word() const
	{
	return TPtrC(iEntry);
	}


inline TPtrC TPtiUserDictionaryEntry::Reading() const
	{
	return TPtrC(iEntry);
	}


inline void TPtiUserDictionaryEntry::SetWord(TDesC& aWord, TDesC& /*aReading*/)
	{
	iEntry.Copy(aWord);
	}


inline void TPtiUserDictionaryEntry::SetWord(TDesC& aWord)
	{
	iEntry.Copy(aWord);
	}


// End of file
