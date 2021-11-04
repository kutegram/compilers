/**
 * @file MetaData.inl
 * @internalTechnology
 *
 * Copyright (c) 2004 Symbian Ltd.  All rights reserved.
 */

#ifndef __METADATA_INL__
#define __METADATA_INL__

namespace Meta
{


STypeId::STypeId()
/**
 * Constructor
 */
	{
	iUid.iUid = 0;
	iType = 0;
	}

STypeId::STypeId(TUint32 aUid, TUint32 aTypeId)
/**
 * Constructor
 */
	{
	iUid.iUid = aUid;
	iType = aTypeId;
	}

}	// namespace Meta
// __METADATA_INL__
#endif
