/*
* ==============================================================================
*  Name        : MProEngProfileName.h
*  Part of     : Profiles Engine / Profiles Engine Wrapper
*  Interface   : SDK, Profiles Engine Wrapper
*  Description : 
*  Version     : 
*
*  Copyright © 3.12 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef MPROENGPROFILENAME_H
#define MPROENGPROFILENAME_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class MProEngProfileNameExt; 

// CLASS DECLARATION

/**
*  Profile name interface.
*  This interface offers methods to get profile ID and to get and set the
*  profile name.
*
*  @lib N/A
*  @since 3.1
*/
class MProEngProfileName
    {
    protected:  // Destructor

        virtual ~MProEngProfileName() {};

    public:
        /**
        * Returns ID of the profile.
        * @since 3.1
        * @return Returns ID of the profile.
        */
        virtual TInt Id() const = 0;

        /**
        * Returns the name of the profile.
        * @since 3.1
        * @return Returns name of the profile.
        */
        virtual const TDesC& Name() const = 0;

        /**
        * Set the name of the profile.
        * @since 3.1
        * @param aName Name of the profile.
        * @return KErrNone if succesful,
        *         KErrAccessDenied if name setting of this profile is read-only,
        *         KErrAlreadyExists if the name is already used by another
        *         profile.
        *         
        */
        virtual TInt SetNameL( const TDesC& aName ) = 0;

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MProEngProfileNameExt* Extension() { return NULL; }

    };

#endif      // MPROENGPROFILENAME_H

// End of File

