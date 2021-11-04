/*
* =============================================================================
*  Name        : MNcnNotification.inl
*  Part of     : Ncn Notification API
*  Description : Inline methods for ECom plug-in use.
*  Version     :
*
*  Copyright © 2006 Nokia Corporation.
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

// ----------------------------------------------------------------------------
// MEMBER FUNCTIONS
// ----------------------------------------------------------------------------
//

// ----------------------------------------------------------------------------
// MNcnNotification::~MNcnNotification
//
// Destructor.
// ----------------------------------------------------------------------------
//
inline MNcnNotification::~MNcnNotification()
    {
    REComSession::DestroyedImplementation( iDtor_ID_Key );
    }

// ----------------------------------------------------------------------------
// MNcnNotification::CreateMNcnNotificationL
//
// ECom factory method.
// ----------------------------------------------------------------------------
//
inline MNcnNotification* MNcnNotification::CreateMNcnNotificationL()
    {
    TInt32 keyOffset = _FOFF( MNcnNotification,
                              iDtor_ID_Key );
    _LIT8(KDefaultImplementation,"NcnNotification");
	TEComResolverParams resolverParams;
	resolverParams.SetDataType( KDefaultImplementation() );
	resolverParams.SetWildcardMatch (ETrue);
    TAny* obj =
        REComSession::CreateImplementationL( KNcnNotificationInterfaceUid,
                                             keyOffset,
                                             resolverParams );
    return reinterpret_cast<MNcnNotification*> ( obj );
    }

// End of file
