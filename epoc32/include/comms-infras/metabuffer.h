// MetaBuffer.h
// Copyright (c) Symbian Software Ltd. 2004-2007.  All rights reserved.
/**
 * @file MetaBuffer.h
 * @internalTechnology
 *
 */

#if (!defined METABUFFER_H)
#define METABUFFER_H

#include <comms-infras/metatypevariablelen.h>

namespace Meta
{

class TMetaBuf8 : public TMetaVarLen8<RBuf8>
/**

Implementation of MMetaType for dynamicaly allocated RBuf8

@internalComponent

*/
	{
public:
	inline static MMetaType* NewL(const TAny* aMem, const TAny* aData);

	IMPORT_C virtual TInt Load(TPtrC8& aBuffer);
	IMPORT_C virtual TInt Store(TDes8& aBuffer) const;
	IMPORT_C virtual void Copy(const TAny* aData);
	IMPORT_C virtual TInt Length() const;

protected:
	TMetaBuf8(const TAny* aData) :
		TMetaVarLen8<RBuf8>( aData )
		{
		}
	};

class TMetaBuf16 : public TMetaVarLen16<RBuf16>
/**

Implementation of MMetaType for dynamicaly allocated RBuf16

@internalComponent

*/
	{
public:
	inline static MMetaType* NewL(const TAny* aMem, const TAny* aData);

	IMPORT_C virtual TInt Load(TPtrC8& aBuffer);
	IMPORT_C virtual TInt Store(TDes8& aBuffer) const;
	IMPORT_C virtual void Copy(const TAny* aData);
	IMPORT_C virtual TInt Length() const;

protected:
	TMetaBuf16(const TAny* aData) :
		TMetaVarLen16<RBuf16>( aData )
		{
		}

	};

MMetaType* TMetaBuf8::NewL(const TAny* aMem, const TAny* aData)
/**
 * Instantiates a meta type for RBuf8.
 * Used for attribure registration (in the data v-table).
 */
    {
    return ::new ((TUint8*)aMem) TMetaBuf8(aData);
    }

MMetaType* TMetaBuf16::NewL(const TAny* aMem, const TAny* aData)
/**
 * Instantiates a meta type for RBuf8.
 * Used for attribure registration (in the data v-table).
 */
    {
    return ::new ((TUint8*)aMem) TMetaBuf16(aData);
    }


#if defined(_UNICODE)
typedef TMetaBuf16 TMetaBuf;
#else
typedef TMetaBuf8 TMetaBuf;
#endif
} //namespace Meta


//METABUFFER_H
#endif
