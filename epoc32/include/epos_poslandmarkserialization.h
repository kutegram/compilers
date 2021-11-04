/*
* ==============================================================================
*  Name        : EPos_PosLandmarkSerialization.h
*  Part of     : Mobile Location Framework / Landmarks
*  Interface   : SDK/S60, Landmarks API
*  Description : PosLandmarkSerialization class definition
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

#ifndef __EPOS_POSLANDMARKSERIALIZATION_H
#define __EPOS_POSLANDMARKSERIALIZATION_H

#include <e32base.h>

class CPosLandmark;

/**
 *  This class contains helper methods for landmark serialization.
 *  A landmark can be packed into a buffer with PackL method and unpacked
 *  back with UnpackL method.
 *
 *  @lib eposlandmarks.lib
 *  @since S60 3.1
 */
class PosLandmarkSerialization
    {
    public:
        /** Packs landmark object into a buffer.
         *
         *  All the data is preserved when packing. Database information is not stored.
         *  Packed landmark can be unpacked with @ref UnpackL method.
         *
         *  @param aLandmark The landmark to be packed.
         *  @return The buffer with the landmark data packed.
         *          Ownership is transferred to the client.
         */
        IMPORT_C static HBufC8* PackL( const CPosLandmark& aLandmark );

        /** Unpacks a landmark object, packed with @ref PackL method, from buffer.
         *
         *  All the data is preserved when packing, and restored exactly
         *  when unpacking. It means that landmark ID and
         *  category IDs are valid only for the database, this landmark was read from.
         *
         *  @param aBuffer The buffer containing landmark.
         *  @return The landmark unpacked. Ownership is transferred to client.
         *  @leave KErrCorrupt if buffer does not contain valid landmark package.
         */
        IMPORT_C static CPosLandmark* UnpackL( const TDesC8& aBuffer );
    };

#endif // __EPOS_POSLANDMARKSERIALIZATION_H
