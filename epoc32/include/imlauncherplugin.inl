/*
* ==============================================================================
*  Name        : imlauncherplugin.inl
*  Part of     : IM Public API
*  Interface   : IM launcher plugin inline functions
*  Description : Interface for the IM application launching
*  Version     : 
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/
inline CImLauncherPlugin::CImLauncherPlugin()
    {
    }

inline CImLauncherPlugin::~CImLauncherPlugin()
    {
    // Destroy any instance variables and then
    // inform the framework that this specific 
    // instance of the interface has been destroyed.
    REComSession::DestroyedImplementation(iDtor_ID_Key);
    }

inline CImLauncherPlugin* CImLauncherPlugin::NewL(const TDesC8& aApplicationId)
    {
    // Set up the interface find for the default resolver.
    TEComResolverParams resolverParams;
    resolverParams.SetDataType(aApplicationId);
    resolverParams.SetWildcardMatch(EFalse);
    TAny* ptr = REComSession::CreateImplementationL(
                                        KImLauncherPluginUid,
                                        _FOFF(CImLauncherPlugin,iDtor_ID_Key),
                                        resolverParams);

    return REINTERPRET_CAST(CImLauncherPlugin*, ptr);
    }
