/*
* ==============================================================================
*  Name        : MProEngProfileActivationObserver.h
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


#ifndef MPROENGPROFILEACTIVATIONOBSERVER_H
#define MPROENGPROFILEACTIVATIONOBSERVER_H

//  INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class MProEngProfileActivationObserverExt;

// CLASS DECLARATION

/**
* Profile activation observer interface.
* Implement this interface to get notifications when the current active profile
* changes.
*
*  @lib ProfileEngine.lib
*  @since Series 60 3.1
*/
class MProEngProfileActivationObserver
    {
    public: // New functions

        /**
        * Abstract method for handling profile activation event. This method is
        * called always when a profile is activated, even if the current active
        * profile is re-activated.
        * @since S60 3.1
        * @param aProfileId The ID of the new active profile.
        */
        virtual void HandleProfileActivatedL( TInt aProfileId ) = 0;
                                         
        /**
         * Error handler for handling the errors in the profile activation
         * notification process. If HandleProfileActivatedL() leaves, this
         * method is called with the leave code. This method has default empty
         * implementation.
         * @since S60 3.1
         * @param aError the code of the error which occurred during
         *        notification process.
         */
        virtual void HandleProfileActivationNotificationError(
                TInt /* aError */ ) {};


    protected:

        /**
        * Destructor.
        */
        virtual ~MProEngProfileActivationObserver() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MProEngProfileActivationObserverExt* Extension() {return NULL;}

    };

#endif      // MPROENGPROFILEACTIVATIONOBSERVER_H

// End of File

