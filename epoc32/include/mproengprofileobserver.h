/*
* ==============================================================================
*  Name        : MProEngProfileObserver.h
*  Part of     : Profiles / Profiles Engine Wrapper
*  Interface   : SDK, Profiles Engine Wrapper
*  Description :
*  Version     :
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia. All rights are reserved. Copying, including
*  reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef MPROENGPROFILEOBSERVER_H
#define MPROENGPROFILEOBSERVER_H

//  INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class MProEngProfileObserverExt;

// CLASS DECLARATION

/**
* Profile modification observer interface.
* Implement this interface to get notifications of changes in the data of a
* selected profile.
*
*  @lib ProfileEngine.lib
*  @since Series 60 3.1
*/
class MProEngProfileObserver
    {
    public: // New functions

        /**
        * Abstract method for handling profile modification event.
        * This method is called when one of client chosen profiles has been
        * modified some way.
        * @since S60 3.1
        * @param aProfileId The ID of the profile that was modified. If there
        * has been many simultaneous changes in Profiles data, so that one
        * profile cannot be identified, this is KErrNotFound. In this case,
        * client gets this notification as many times as there are profiles
        * he has requested notifications about. The savest way is to use
        * own handlers for every profile of interest.
        */
        virtual void HandleProfileModifiedL( TInt aProfileId ) = 0;

        /**
         * Error handler for handling the errors in the profile modification
         * notification process. If HandleProfileModifiedL() leaves,
         * this method is called with the leave code. This method has
         * default empty implementation.
         * @since S60 3.1
         * @param aError the code of the error which occurred during
         *        notification process.
         */
        virtual void HandleProfileNotificationError(
                TInt /* aError */ ) {};

    protected:

        /**
        * Destructor.
        */
        virtual ~MProEngProfileObserver() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MProEngProfileObserverExt* Extension() { return NULL; }

    };

#endif      // MPROENGPROFILEOBSERVER_H

// End of File

