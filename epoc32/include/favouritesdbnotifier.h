/*
* ==============================================================================
*  Name        : FavouritesDbNotifier.h  
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Declaration of FavouritesDbNotifier
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

#ifndef FAVOURITES_DB_NOTIFIER_H
#define FAVOURITES_DB_NOTIFIER_H

//  INCLUDES

#include <FavouritesHandle.h>

// FORWARD DECLARATIONS

class RFavouritesDb;

// CLASS DECLARATION

/**
* RFavouritesDbNotifier is the Favourites database change notifier 
* for the Favourites Engine. It provides notification of database changes.
*/
class RFavouritesDbNotifier: public RFavouritesHandle
    {
    public:     // update

        /**
        * Open the notifier.
        * @since 0.9 
        * @param aDb The database to be watched.
        * @return Error code.
        */
        IMPORT_C TInt Open( RFavouritesDb& aDb );

        /**
        * Request notification about all database events.
        * @since 0.9 
        * @param aStatus Request status.
        * @return void 
        */
        IMPORT_C void NotifyAllEvents( TRequestStatus& aStatus );

        /**
        * Request notification about database changes.
        * @since 0.9 
        * @param aStatus Request status.
        * @return void
        */
        IMPORT_C void NotifyChange( TRequestStatus& aStatus );

        /**
        * Cancel the outstanding request (if any).
        * @since 0.9 
        * @return void
        */
        IMPORT_C void Cancel();

    };

#endif
            
// End of File
