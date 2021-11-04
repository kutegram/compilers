// Copyright (c) Symbian Software Ltd. 2006-2007.  All rights reserved.
//
// cdbstore.inl
//

/**
@file
@deprecated since v9.1. Functionality is replaced with commsdat.

CStoreableOverrideSettings class inline functions
*/

#ifndef __CDBSTORE_INL__
#define __CDBSTORE_INL__

#include <cdbstore.h>

inline CBufStore* CStoreableOverrideSettings::GetStore() const
/** 
Accesses the buffer store.
@deprecated 7.0 There is no need for this store - none of the above functions use this
store. If a client needs a store it should create its own.
@return The pointer to the memory store object.
*/
	{
	return iStore;
	}

#endif

