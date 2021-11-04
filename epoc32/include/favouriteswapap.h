/*
* ============================================================================
*  Name        : FavouritesWapAp.h 
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Declaration of FavouritesWapAp
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

#ifndef FAVOURITES_WAP_AP_H
#define FAVOURITES_WAP_AP_H

//  INCLUDES
#include <e32base.h>
#include <s32strm.h>

// CLASS DECLARATION

/**
* TFavouritesWapAp is the representation one the Access Point used in favourites. 
* In addition to the AP Uid-s an item may hold "Use default" and "Unset/Null" values.
*/
class TFavouritesWapAp
    {

    public:     // construction
        
        /**
        * C++ default constructor. Initializes to "Default".
        * @since 0.9       
        */
        IMPORT_C TFavouritesWapAp();

    public:     // operators

        /**
        * Assignment operator (from another TFavouritesWapAp).
        * @since 0.9       
        * @param aAp AP to assign from.
        * @return TFavouritesWapAp
        */
        IMPORT_C TFavouritesWapAp& operator= ( const TFavouritesWapAp& aAp );

        /**
        * Assignment operator (from TUint32).
        * "Null" and "Default" properties cleared.
        * @since 0.9       
        * @param aApId AP id to assign from.
        * @return TFavouritesWapAp
        */
        IMPORT_C TFavouritesWapAp& operator= ( TUint32 aApId );

    public:     // setters

        /**
        * Set value is unset. Any previous value is lost.
        * @since 0.9       
        * @return void
        */
        IMPORT_C void SetNull();

        /**
        * Set value is "Default". Any previous value is lost.
        * @since 0.9  
        * @return void     
        */
        IMPORT_C void SetDefault();

        /**
        * Set value. "Null" and "Default" properties cleared.
        * @since 0.9       
        * @param aApId AP id to set.
        * @return void
        */
        IMPORT_C void SetApId( TUint32 aApId );

    public:     // getters

        /**
        * Check if value is unset.
        * @since 0.9       
        * @return ETrue if value is unset.
        */
        IMPORT_C TBool IsNull() const;

        /**
        * Check if value is "Default".
        * @since 0.9       
        * @return ETrue if value is "Default".
        */
        IMPORT_C TBool IsDefault() const;

        /**
        * Get the AP id. If the value is "Null" or "Default", this method
        * panics. Check those before calling this method!
        * @since 0.9       
        * @return AP id.
        */
        IMPORT_C TUint32 ApId() const;

    public:     // (But not exported): Streaming

        /**
        * Externalize into a stream.
        * @since 0.9       
        * @param aStream The stream to externalize to.
        * @return void 
        */
        void ExternalizeL( RWriteStream& aStream ) const;

        /**
        * Internalize from a stream.
        * @since 0.9       
        * @param aStream The stream to externalize from.
        */
        void InternalizeL( RReadStream& aStream );

    private:    // friends

        /// RFavouritesTable writes this into database.
        friend class RFavouritesSrvTable;

    private:    // types

        /**
        * This enum holds the value kind ("Null", "Default" or just normal).
        */
        enum TValueKind
            {
            ENormal,    ///< Has real value (not special).
            ENull,      ///< Has "Null" value.
            EDefault    ///< Has "Default value".
            };

    private:    // data

        /**
        * AP id. Meaningless if value is "Null" or "Default".
        */
        TUint32 iApId;

        /**
        * Value kind.
        */
        TValueKind iValueKind;
    };

#endif
            
// End of File
