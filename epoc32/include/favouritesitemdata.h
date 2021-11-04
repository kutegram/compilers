/*
* ==============================================================================
*  Name        : FavouritesItemData.h 
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Declaration of FavouritesItemData
*  Version     : %Version%
*
*  Copyright (C) 2002 Nokia Corporation.
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

#ifndef FAVOURITES_ITEM_DATA_H
#define FAVOURITES_ITEM_DATA_H

//  INCLUDES

#include <e32base.h>

// FORWARD DECLARATION

class RWriteStream;
class RReadStream;

// CLASS DECLARATION

/**
* MFavouritesItemData is the Mixin class for representing extra data for a favourites item.
*/
class MFavouritesItemData
    {

    public:     // streaming

        /**
        * Externalize into a stream.
        * @since 0.9       
        * @param aStream The stream to externalize to.
        */
        IMPORT_C virtual void ExternalizeL( RWriteStream& aStream ) const = 0;

        /**
        * Internalize from a stream.
        * @since 0.9       
        * @param aStream The stream to externalize from.
        */
        IMPORT_C virtual void InternalizeL( RReadStream& aStream ) = 0;

    };

#endif
            
// End of File
