/*
* ==============================================================================
*  Name        : FavouritesDbIncremental.h  
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Declaration of RFavouritesDbIncremental
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

#ifndef FAVOURITES_DB_INCREMENTAL_H
#define FAVOURITES_DB_INCREMENTAL_H

//  INCLUDES

#include <FavouritesHandle.h>

// FORWARD DECLARATIONS

class RFavouritesDb;

// CLASS DECLARATION

/**
* Incremental object for Favourites Engine.
* This class provides incremental database administration (recovery,
* compaction). Usually client does not need to use this class.
*/
class RFavouritesDbIncremental: public RFavouritesHandle
    {
    public:     // update

        /**
        * Start incremental recovery on the given database.
        * @since 0.9 
        * @param aDb The database to be recovered.
        * @param aStep Placeholder for the step counter to be returned.
        * @return Error code.
        */
        IMPORT_C TInt Recover( RFavouritesDb& aDb, TInt& aStep );

        /**
        * Start incremental compaction on the given database.
        * @since 0.9 
        * @param aDb The database to be compacted.
        * @param aStep Placeholder for the step counter to be returned.
        * @return Error code.
        */
        IMPORT_C TInt Compact( RFavouritesDb& aDb, TInt& aStep );

        /**
        * Perform next step of incremental operation.
        * @since 0.9 
        * @param aStep Step counter.
        * @return Error code.
        */
        IMPORT_C TInt Next( TInt& aStep );

    };

#endif
            
// End of File
