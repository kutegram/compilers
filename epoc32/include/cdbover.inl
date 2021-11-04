// Copyright (c) Symbian Software Ltd. 2006-2007.  All rights reserved.
//
// cdbover.inl
//

/**
@file
@deprecated since v9.1. Functionality is replaced with commsdat.

CCommDbOverrideSettings inline functions
*/

#if !defined(__CDBOVER_INL__)
#define __CDBOVER_INL__

#include <cdbover.h>
#include <commdb.h>

inline CCommDbOverrideSettings::TParamList CCommDbOverrideSettings::PartialFull() const
/**
Returns the value set in the constructor.

@return An enumeration which determines whether this set of override values is full or partial. 
*/
	{
	return iPartialFull;
	}

#endif

