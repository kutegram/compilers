/*
* ============================================================================
*  Name        : RFavouritesSession.h
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Declaration of RFavouritesSession
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

#ifndef FAVOURITES_SESSION_H
#define FAVOURITES_SESSION_H

//  INCLUDES

#include <e32base.h>

// CLASS DECLARATION

/**
* RFavouritesSession is the Favourites Engine Session.
* It represents the connection to the Favourites Engine Server.
*/
class RFavouritesSession : public RSessionBase
    {
    public:     // New methods

        /**
        * Get version.
        * @since 0.9       
        * @return Version.
        */
        IMPORT_C static TVersion Version();

        /**
        * Connect to Favourites Server.
        * @since 0.9       
        * @return Error code.
        */
        IMPORT_C TInt Connect();

        /**
        * Start checking the number of allocated object through this session.
        * @since 0.9       
        * @return void
        */
        IMPORT_C void ResourceMark();

        /**
        * Check that the number of allocated object through this session
        * matches the same of when the last call to ResourceMark was made.
        * @since 0.9       
        * @return void
        */
        IMPORT_C void ResourceCheck();

        /**
        * Get number of allocated object through this session.
        * @since 0.9       
        * @return void
        */
        IMPORT_C TInt ResourceCount();

        /**
        * Delete database.
        * @param aName Database name.
        * @since 0.9       
        * @return ErrorCode
        */
        IMPORT_C TInt DeleteDatabase( const TDesC& aName );

        /**
        * Simulate a heap allocation failure for server heap. Has empty
        * implementation for the UDEB server.
        * @since 0.9       
        * @param aType Type of heap failure simulation.
        * @param aRate Rate of failure.
        * @return void 
        */
        IMPORT_C void __DbgSetAllocFail
            ( RAllocator::TAllocFail aType, TInt aRate );

    public:     // But not exported

        /**
        * Message passing routine.
        * @since 0.9       
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @param aStatus Request status.
        */
        inline void SendReceive
            (
            TInt aFunction,
            const TIpcArgs& aArgs,
            TRequestStatus& aStatus
            ) const;

        /**
        * Message passing routine.
        * @since 0.9       
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @return Error code.
        */
        inline TInt SendReceive( TInt aFunction, const TIpcArgs& aArgs ) const;

        /**
        * Message passing routine.
        * @since 0.9       
        * @param aFunction Function.
        * @return Error code.
        */
        inline TInt SendReceive( TInt aFunction ) const;

    private:    // New methods

        /**
        * Connect to Favourites Server.
        * @since 0.9       
        * @return Error code.
        */
        TInt DoConnect();

    };

#endif

#include <FavouritesSession.inl>

// End of File
