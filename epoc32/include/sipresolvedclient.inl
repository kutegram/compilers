/*
* =============================================================================
*  Name          : SipResolvedClient.inl
*  Part of       : SIP Client Resolver
*  Description   : 
*  Version       : 1.0
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
* =============================================================================
*/
#ifndef SIPRESOLVEDCLIENT_INL
#define SIPRESOLVEDCLIENT_INL


// ---------------------------------------------------------------------------
// CSIPResolvedClient::CSIPResolvedClient 
// ---------------------------------------------------------------------------
//
inline CSIPResolvedClient::CSIPResolvedClient()
	{
	}

// ---------------------------------------------------------------------------
// CSIPResolvedClient::~CSIPResolvedClient 
// ---------------------------------------------------------------------------
//
inline CSIPResolvedClient::~CSIPResolvedClient()
	{
	REComSession::DestroyedImplementation( iInstanceKey );
	}
	
// ---------------------------------------------------------------------------
// CSIPResolvedClient::Capabilities
// ---------------------------------------------------------------------------
//
inline const TDesC8& CSIPResolvedClient::Capabilities() 
	{
	return KNullDesC8;
	}	

// SIPRESOLVEDCLIENT_INL
#endif

// End of File
