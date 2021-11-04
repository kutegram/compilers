/**
 * @file MetaContainer.inl
 * @internalTechnology
 *
 * Copyright (c) 2004 Symbian Ltd.  All rights reserved.
 */

#ifndef __METACONTAINER_INL__
#define __METACONTAINER_INL__

namespace Meta
{

template<class ELEMENT>
RMetaDataContainer<ELEMENT>* RMetaDataContainer<ELEMENT>::LoadL(TPtrC8& aDes)
/**
 * This function instantiates a container of meta objects and loads its content
 * from a descriptor.
 */
    {
    RMetaDataContainer<ELEMENT>* cont = new (ELeave) RMetaDataContainer<ELEMENT>;
	User::LeaveIfError(cont->Load(aDes));
	return cont;
    }

template<class ELEMENT>
inline RMetaDataContainer<ELEMENT>::RMetaDataContainer()
/**
 * Constructor
 */
	{
	}

template<class ELEMENT>
SMetaData* RMetaDataContainer<ELEMENT>::LoadElementL(TPtrC8& aDes)
/**
 * This helper function instantiates a single meta object (element) and loads
 * its content from a descriptor.
 */
	{
	return ELEMENT::LoadL(aDes);
	}

}	// namespace Meta
// __METACONTAINER_INL__
#endif
