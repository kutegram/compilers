/*
* ==============================================================================
*  Name        : ActiveFavouritesDbNotifier.h 
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Declaration of CActiveFavouritesDbNotifier.
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

#ifndef ACTIVE_FAVOURITES_DB_NOTIFIER_H
#define ACTIVE_FAVOURITES_DB_NOTIFIER_H

//  INCLUDES

#include <e32base.h>
#include <d32dbms.h>
#include <FavouritesDbNotifier.h>

// FORWARD DECLARATION

class RFavouritesDb;
class MFavouritesDbObserver;

// CLASS DECLARATION

/**
* ActiveFavouritesDbNotifier is an Active object encapsulating a favourites database notifier. 
* Once this notifier is Start()-ed, it keeps watching the database and notifies the
* observer, until the database is closed by all clients (i.e. released by
* DBMS), or it is DoCancel()-led.
*/
class CActiveFavouritesDbNotifier : public CActive
    {
    public:     // Constructor and destructor

        /**
        * Constructor.
        * @since 0.9 
        * @param aDb The favourites database to watch for.
        * @param aObserver The Observer to be notified about database events.
        */
        IMPORT_C CActiveFavouritesDbNotifier( RFavouritesDb& aDb, MFavouritesDbObserver& aObserver );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CActiveFavouritesDbNotifier();

    protected:  // from CActive

        /**
        * Invoked when the outstanding request completes.
        * @since 0.9
        * @return void 
        */
        IMPORT_C void RunL();

        /**
        * Cancel any outstading request. It's implementation of the Cancel protocol;
        * @since 0.9
        * @return void 
        */
        IMPORT_C void DoCancel();

    public:     // new methods

        /**
        * Start the notifier. The notification request is automatically
        * renewed until it is cancelled, or the database is closed by
        * all clients (i.e. released by DBMS).
        * @since 0.9
        * @return Error code.
        */
        IMPORT_C TInt Start();

    private:

        /**
        * Request database change notification from the Favourites Engine.
        * @since 0.9
        * @return void 
        */
        void NotifyChange();

    private:    // data

        RFavouritesDbNotifier iNotifier;    ///< Notifier object.
        RFavouritesDb& iDb;                 ///< Handle to the database.
        MFavouritesDbObserver* iObserver;   ///< Pointer to observer.
    };

#endif
            
// End of File
