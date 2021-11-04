/**
 * @file MetaContainer.h
 * @internalTechnology
 *
 * Copyright (c) Symbian Software Ltd. 2004-2007.  All rights reserved.
 */

#if (!defined METACONTAINER_H)
#define METACONTAINER_H

#include <e32base.h>
#include <e32std.h>
#include <comms-infras/metadata.h>


namespace Meta
{

class RMetaDataContainerBase : public RPointerArray<SMetaData>
/**

Container of meta objects.
Base class.
Derived containers need to implement static LoadL.

@internalComponent
*/
    {
public:
	IMPORT_C explicit RMetaDataContainerBase();

    IMPORT_C void Copy(const RMetaDataContainerBase& aMetaContainer);
    IMPORT_C TInt Store(TDes8& aDes) const;

    IMPORT_C TInt Load(TPtrC8& aDes);
	IMPORT_C TInt Length() const;

	IMPORT_C STypeId GetTypeId() const;

protected:
	virtual SMetaData* LoadElementL(TPtrC8& aDes) = 0;
    };

template<class ELEMENT>
class RMetaDataContainer : public RMetaDataContainerBase
/**

Templated container of meta objects that implements static LoadL.
Meta object type (template parameter) needs to implement its own static LoadL.

@internalComponent
*/
	{
public:
	static RMetaDataContainer<ELEMENT>* LoadL(TPtrC8& aDes);

	explicit inline RMetaDataContainer();

protected:
	virtual SMetaData* LoadElementL(TPtrC8& aDes);
	};

typedef RMetaDataContainer<SMetaDataECom> RMetaDataEComContainer;

} //namespace Meta

#include <comms-infras/metacontainer.inl>

//METACONTAINER_H
#endif

