/*
* ==============================================================================
*  Name        : EPos_PosLmCategorySerialization.h
*  Part of     : Mobile Location Framework / Landmarks
*  Interface   : SDK/S60, Landmarks API
*  Description : PosLmCategorySerialization class definition
*  Version     : %version: 2 %
*
*  Copyright © 2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.0
*/

#ifndef __EPOS_POSCATEGORYSERIALIZATION_H_
#define __EPOS_POSCATEGORYSERIALIZATION_H_

#include <e32base.h>

class CPosLandmarkCategory;

/**
 *  This class contains helper methods for landmark category serialization.
 *  A landmark category can be packed into a buffer with PackL method and unpacked
 *  back with UnpackL method.
 *
 *  @lib eposlandmarks.lib
 *  @since S60 3.1
 */
class PosLmCategorySerialization
    {
    public:
        /** Packs category object into a buffer.
         *
         *  All the data is preserved when packing. Database information is not stored.
         *  Packed category can be unpacked with @ref UnpackL method.
         *
         *  @param aCategory The category to be packed.
         *  @return The buffer with the category data packed.
         *          Ownership is transferred to the client.
         */
        IMPORT_C static HBufC8* PackL( const CPosLandmarkCategory& aCategory );

        /** Unpacks a category object, packed with @ref PackL method, from buffer.
         *
         *  All the data is preserved when packing, and restored exactly
         *  when unpacking. It means that category ID is valid only for the database,
         *  this category was read from.
         *
         *  @param aBuffer The buffer containing category.
         *  @return The category unpacked. Ownership is transferred to client.
         *  @leave KErrCorrupt if buffer does not contain valid category package.
         */
        IMPORT_C static CPosLandmarkCategory* UnpackL( const TDesC8& aBuffer );
    };

#endif // __EPOS_POSCATEGORYSERIALIZATION_H_
