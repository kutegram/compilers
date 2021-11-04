// MSVFTEXT.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

//**********************************
// CMsvFindText
//**********************************

inline TBool CMsvFindText::FoundText() const
/** Returns the result of the asynchronous search for a matching text string.

@return ETrue if there is a match, otherwise EFalse. */
	{
	return iFoundText;
	}
