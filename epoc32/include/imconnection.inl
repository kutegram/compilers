/*
* ==============================================================================
*  Name        : imconnection.inl
*  Part of     : IM SDK API
*  Description : IM Connection inline functions
*  Version     : 1.0
*
*  Copyright (c) 2004, 2005 Nokia Corporation.
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
inline CImConnection::CImConnection()
	{
	}

inline CImConnection::~CImConnection()
	{
	// Destroy any instance variables and then
	// inform the framework that this specific 
	// instance of the interface has been destroyed.
	REComSession::DestroyedImplementation(iDtor_ID_Key);

    }

inline CImConnection* CImConnection::NewL(const TDesC& aClientId)
    {
    // Set up the interface find for the default resolver.
    
    TUid KDefaultImplemantationUid = {0x101FB0CA};
    TAny* ptr = REComSession::CreateImplementationL(
        KDefaultImplemantationUid, 
        _FOFF(CImConnection,iDtor_ID_Key),
        (TAny*) &aClientId);
    
    
    return REINTERPRET_CAST(CImConnection*, ptr);
    }

