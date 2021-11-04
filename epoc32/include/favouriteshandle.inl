/*
* ==============================================================================
*  Name        : FavouritesHandle.inl  
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Implementation of inline methods of class RFavouritesHandle.
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

#ifndef FAVOURITES_HANDLE_INL
#define FAVOURITES_HANDLE_INL

/**
 * Implementation of RFavouritesHandle::RFavouritesHandle()
 * @since 0.9       
 */

RFavouritesHandle::RFavouritesHandle(): iHandle( 0 )
    {
    }

/**
 * Implementation of RFavouritesHandle::Handle()
 * @since 0.9       
 * @return the handle 
 */

TInt RFavouritesHandle::Handle() const
    {
    return iHandle;
    }

#endif
            
// End of File
