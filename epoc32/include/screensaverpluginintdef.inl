/*
* ============================================================================
*  Name       : ScreensaverpluginIntDef.inl
*  Part of    : Screensaver
*  Description: Inline functions for CScreensaverPluginInterfaceDefinition class
*  Version:
*
*  Copyright © 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

//  INCLUDES

#include <Ecom\ECom.h>   			// For REComSession
#include <ScreensaverpluginIntDef.hrh>	// For KCScreensaverPluginInterfaceDefinitionUid

// CONSTANTS

// -----------------------------------------------------------------------------
// CScreensaverPluginInterfaceDefinition::NewL
// -----------------------------------------------------------------------------
//
inline CScreensaverPluginInterfaceDefinition* 
       CScreensaverPluginInterfaceDefinition::NewL(TUid aImplementationUid)
    {
    // Create an instance of an object of CScreensaverPluginInterfaceDefinition type
    // using aImplementationUid as identification
    TAny* ptr = REComSession::
                CreateImplementationL(aImplementationUid,
                                     _FOFF(CScreensaverPluginInterfaceDefinition,iDtor_ID_Key));
    return reinterpret_cast<CScreensaverPluginInterfaceDefinition*>(ptr);
    }

       

// -----------------------------------------------------------------------------
// CScreensaverPluginInterfaceDefinition::ListImplementationsL
// -----------------------------------------------------------------------------
//
inline void CScreensaverPluginInterfaceDefinition::
            ListImplementationsL(RImplInfoPtrArray& aImplInfoArray)
    {
    REComSession::ListImplementationsL(TUid::Uid(KCScreensaverPluginInterfaceDefinitionUid), aImplInfoArray);
    }

// -----------------------------------------------------------------------------
// CScreensaverPluginInterfaceDefinition::~CScreensaverPluginInterfaceDefinition
// -----------------------------------------------------------------------------
//
inline CScreensaverPluginInterfaceDefinition::~CScreensaverPluginInterfaceDefinition()
    {
    REComSession::DestroyedImplementation(iDtor_ID_Key);
    }

// End of file.