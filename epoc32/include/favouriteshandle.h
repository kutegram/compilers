/*
* ==============================================================================
*  Name        : FavouritesHandle.h 
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Declaration of RFavouritesHandle
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

#ifndef FAVOURITES_HANDLE_H
#define FAVOURITES_HANDLE_H

//  INCLUDES

#include <e32base.h>
#include <FavouritesSession.h>

// CLASS DECLARATION

/**
* RFavouritesHandle is the favourite object handle.
*/
class RFavouritesHandle
    {

    public:     // Constructor and destructor
        
        /**
        * Constructor.
        * @since 0.9       
        */
        inline RFavouritesHandle();

        /**
        * Close the object.
        * @since 0.9       
        * return void
        */
        IMPORT_C void Close();

    public:     // New methods

        /**
        * Get handle number.
        * @since 0.9       
        * @return Handle number.
        */
        inline TInt Handle() const;

    protected:  // New methods

        /**
        * Open the object.
        * @since 0.9       
        * @param aSess Session to be used.
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @return Error code.
        */
        TInt Open
            (
            RFavouritesSession& aSess,
            TInt aFunction,
            const TIpcArgs& aArgs
            );

        /**
        * Open this object using other object.
        * @since 0.9       
        * @param aHandle Handle used to open this object.
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @return Error code.
        */
        TInt Open
            (
            RFavouritesHandle& aHandle,
            TInt aFunction,
            const TIpcArgs& aArgs
            );

        /**
        * Message passing routine.
        * @since 0.9       
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @param aStatus Request status.
        */
        void SendReceive
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
        TInt SendReceive( TInt aFunction, const TIpcArgs& aArgs ) const;

        /**
        * Message passing routine.
        * @since 0.9       
        * @param aFunction Function.
        * @return Error code.
        */
        TInt SendReceive( TInt aFunction ) const;

    protected:  // Data

        RFavouritesSession iSess;   ///< Session handle.
        TInt iHandle;               ///< Handle number.

    };

#include <FavouritesHandle.inl>

#endif
            
// End of File
