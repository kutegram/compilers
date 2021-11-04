/*
* ============================================================================
*  Name        : AiwVariant.inl
*  Part of     : Application Interworking Framework / ServiceHandler
*  Interface   : SDK, AIW Generic Parameter API
*  Description : Inline function implementations of class TAiwVariant.
*  Version     :
*
*  Copyright © 2003-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ============================================================================
*/


inline TAiwVariant::TAiwVariant() : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    iData.iBufC = NULL;
    iData.iBufC8 = NULL;
    Reset();
    }

inline TAiwVariant::TAiwVariant(TInt32 aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {   
    Set(aValue);
    }

inline TAiwVariant::TAiwVariant(const TUid& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    Set(aValue);
    }

inline TAiwVariant::TAiwVariant(const TDesC& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    iData.iBufC = NULL;
    Set(aValue);
    }

inline TAiwVariant::TAiwVariant(const HBufC* aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    iData.iBufC = NULL;
    if(aValue)
        Set(*aValue);
    else
        Reset();    
    }

inline TAiwVariant::TAiwVariant(const TTime& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    Set(aValue);
    }

inline TAiwVariant::TAiwVariant(const TDesC8& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    iData.iBufC8 = NULL;
    Set(aValue);
    }


inline TAiwVariant::TAiwVariant(const RFile& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    Set(aValue);
    }


inline TVariantTypeId TAiwVariant::TypeId() const
    {
    return static_cast<TVariantTypeId>(iTypeId);
    }

inline TBool TAiwVariant::IsEmpty() const
    {
    return (iTypeId == EVariantTypeNull);
    }

inline void TAiwVariant::Set(const HBufC* aValue)
    {
    Set(*aValue);
    }

inline TAiwVariant& TAiwVariant::operator=(TInt32 aValue)
    {
    Set(aValue);
    return *this;
    }

inline TAiwVariant& TAiwVariant::operator=(const TUid& aValue)
    {
    Set(aValue);
    return *this;
    }

inline TAiwVariant& TAiwVariant::operator=(const TDesC& aValue)
    {
    Set(aValue);
    return *this;
    }

inline TAiwVariant& TAiwVariant::operator=(const HBufC* aValue)
    {
    Set(*aValue);
    return *this;
    }

inline TAiwVariant& TAiwVariant::operator=(const TTime& aValue)
    {
    Set(aValue);
    return *this;
    }


inline TAiwVariant& TAiwVariant::operator=(const TDesC8& aValue)
    {
    Set(aValue);    
    return *this;
    }


inline TAiwVariant& TAiwVariant::operator=(const RFile& aValue)
    {
    Set(aValue);
    return *this;
    }


inline TBool operator!=(const TAiwVariant& aLhs, const TAiwVariant& aRhs)
    {
    return !(aLhs == aRhs);
    }

// End of file
