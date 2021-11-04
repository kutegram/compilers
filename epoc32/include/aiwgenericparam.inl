/*
* ============================================================================
*  Name        : AiwGenericParam.inl
*  Part of     : Application Interworking Framework / ServiceHandler
*  Interface   : SDK, AIW Generic Parameter API
*  Description : Inline function implementations of class TAiwGenericParam.
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

inline TAiwGenericParam::TAiwGenericParam() :
    iSemanticId(EGenericParamUnspecified), iValue()
    {
    }

inline TAiwGenericParam::TAiwGenericParam(TGenericParamId aSemanticId) :
    iSemanticId(aSemanticId), iValue()
    {
    }

inline TAiwGenericParam::TAiwGenericParam(TGenericParamId aSemanticId, 
    const TAiwVariant& aValue) : 
    iSemanticId(aSemanticId), iValue(aValue)
    {
    }

inline void TAiwGenericParam::SetSemanticId(TGenericParamId aSemanticId)
    {
    iSemanticId = aSemanticId;
    }

inline TGenericParamId TAiwGenericParam::SemanticId() const
    {
    return iSemanticId;
    }

inline TAiwVariant& TAiwGenericParam::Value()
    {
    return iValue;
    }

inline const TAiwVariant& TAiwGenericParam::Value() const
    {
    return iValue;
    }

inline void TAiwGenericParam::Reset()
    {
    iSemanticId = EGenericParamUnspecified;
    iValue.Reset();
    }

inline TBool operator!=(const TAiwGenericParam& aLhs, 
    const TAiwGenericParam& aRhs)
    {
    return !(aLhs == aRhs);
    }

// End of file

