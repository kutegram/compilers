/*
* ============================================================================
*  Name        : FavouritesSession.inl 
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Implementation of inline methods of class RFavouritesSession.
*  Version     : %Version%
*
*  Copyright (C) 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef FAVOURITES_SESSION_INL
#define FAVOURITES_SESSION_INL

// ---------------------------------------------------------
// RFavouritesSession::SendReceive
// ---------------------------------------------------------
//

void RFavouritesSession::SendReceive
( TInt aFunction, const TIpcArgs& aArgs, TRequestStatus& aStatus ) const
    {
    RSessionBase::SendReceive( aFunction, aArgs, aStatus );
    }

// ---------------------------------------------------------
// RFavouritesSession::SendReceive
// ---------------------------------------------------------
//
inline TInt RFavouritesSession::SendReceive
( TInt aFunction, const TIpcArgs& aArgs ) const
    {
    return RSessionBase::SendReceive( aFunction, aArgs );
    }

// ---------------------------------------------------------
// RFavouritesSession::SendReceive
// ---------------------------------------------------------
//
inline TInt RFavouritesSession::SendReceive( TInt aFunction ) const
    {
    return RSessionBase::SendReceive( aFunction );
    }

#endif
            
// End of File
