/*
* ==============================================================================
*  Name        : MProEngProfileNameArrayObserver.h
*  Part of     : Profiles / Profiles Engine Wrapper
*  Interface   : SDK, Profiles Engine Wrapper
*  Description : Profile name array modification observer interface.
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


#ifndef MPROENGPROFILENAMEARRAYOBSERVER_H
#define MPROENGPROFILENAMEARRAYOBSERVER_H

//  INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class MProEngProfileNameArrayObserverExt;

// CLASS DECLARATION

/**
* Profile name array modification observer interface.
* Implement this interface to get notifications of changes in the data of a
* selected profile.
*
*  @lib ProfileEngine.lib
*  @since Series 60 3.1
*/
class MProEngProfileNameArrayObserver
    {
    public: // New functions

        /**
        * Abstract method for handling profile name array modification event.
        * This method is called when the contents of profile name array is
        * changed some way. These cases include:
        * - a profile has been created,
        * - a profile has been deleted,
        * - the name of a profile has been changed.
        * Note, that when there has been many simultaneous changes in Profiles
        * data so that it cannot be identified what has changed, then this
        * method may be called even if nothing hasn't actually changed in the
        * name array content.
        * @since S60 3.1
        */
        virtual void HandleProfileNameArrayModificationL() = 0;

        /**
         * Error handler for handling the errors in the profile name array
         * modification notification process.
         * If HandleProfileNameArrayModificationL() leaves, this method is
         * called with the leave code. This method has default empty
         * implementation.
         * @since S60 3.1
         * @param aError the code of the error which occurred during
         *        notification process.
         */
        virtual void HandleProfileNameArrayNotificationError(
                TInt /* aError */ ) {};

    protected:

        /**
        * Destructor.
        */
        virtual ~MProEngProfileNameArrayObserver() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MProEngProfileNameArrayObserverExt* Extension() { return NULL; }

    };

#endif      // MPROENGPROFILENAMEARRAYOBSERVER_H

// End of File

