/*
* ==============================================================================
*  Name        : FavouritesFile.h 
*  Part of     : Favourites Engine
*  Interface   : Favourites Engine API
*  Description : Declaration of FavouritesFile
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

#ifndef FAVOURITES_FILE_H
#define FAVOURITES_FILE_H

//  INCLUDES

#include <FavouritesHandle.h>

// FORWARD DECLARATION

class RFavouritesDb;
class CFavouritesFileImpl;

// CLASS DECLARATION

/**
* RFavouritesFile is a class derived from RFavouritesHandle. 
* Each favourites item or folder can have an associated file
* with arbitrary content.
*/
class RFavouritesFile: public RFavouritesHandle
    {

    public:     // Constructor and destructor
        
        /**
        * Constructor.
        * @since 0.9       
        */
        inline RFavouritesFile();

        /**
        * Close this object.
        * @since 0.9       
        * @return void
        */
        IMPORT_C void Close();

        /**
        * Open existing file with shared read-access.
        * @since 0.9       
        * @param aDb Database handle.
        * @param aUid Uid of item.
        * @return Error code.
        */
        IMPORT_C TInt Open( RFavouritesDb& aDb, TInt aUid );

        /**
        * Create new file / replace existing with exclusive write-access.
        * Existing content of the file, if any, is lost.
        * @since 0.9       
        * @param aDb Database handle.
        * @param aUid Uid of item.
        * @return Error code.
        */
        IMPORT_C TInt Replace( RFavouritesDb& aDb, TInt aUid );

    public:     // new methods

        /**
        * Read from file.
        * @since 0.9       
        * @param aDes Descriptor into which binary data is read. Any existing
        * contents are overwritten. On return, its length is set to the number
        * of bytes read.
        * @return Error code.
        */
        IMPORT_C TInt Read( TDes8& aDes ) const;

        /**
        * Writes to file.
        * @since 0.9       
        * @param aDes Descriptor from which binary data is written.
        * @return Error code.
        */
        IMPORT_C TInt Write( const TDesC8& aDes );

		/**
		* Get the size of the file.
        * @since 0.9       
		* @param aSize Gives back the size of the file.
		* @return Error code.
		*/
		IMPORT_C TInt Size(TInt &aSize) const;
		
    private:    // new methods

        /**
        * Implementation of Open functions.
        * @since 0.9       
        * @param aDb Database handle.
        * @param aUid Uid of item.
        * @param aFunction Function.
        * @return Error code.
        */
        TInt DoOpen( RFavouritesDb& aDb, TInt aUid, TInt aFunction );

    private:    // data

        CFavouritesFileImpl* iImpl;  ///< Implementation. Owned.

    };

#include <FavouritesFile.inl>

#endif

// End of File
