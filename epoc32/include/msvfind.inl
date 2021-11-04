// MSVFIND.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

//**********************************
// CMsvFindOperation
//**********************************

inline const CMsvFindResultSelection& CMsvFindOperation::GetFindResult() const
/** Returns the result of the search operation.

If the search operation is still in progress, then the results returned are 
those that have been found at the time of this call.

@return A reference to the search operation results. */
	{
	return *iFindResultSel;
	}
