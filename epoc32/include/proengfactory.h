/*
* ==============================================================================
*  Name        : ProEngFactory.h
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


#ifndef PROENGFACTORY_H
#define PROENGFACTORY_H

//  INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class RFs;
class MProEngEngine;
class MProEngAlertToneSeeker;
class MProEngNotifyHandler;

// CLASS DECLARATION

/**
*  Factory for Profiles Engine Wrapper.
*  You can create new instances of Profiles Engines, Notification Handlers and
*  Alert Tone Seekers by using this factory.<br><br>
*  Example:
*  @code
*  // Create a new instance of Profiles Engine:
*  MProEngEngine* engine =
*      ProEngFactory::NewEngineLC();
*
*  // Create a new instance of Notification Handler:
*  MProEngNotifyHandler* notifyHandler =
*      ProEngFactory::NewNotifyHandlerL();
*
*  // Create a new instance of Alert Tone Seeker:
*  MProEngAlertToneSeeker* toneSeeker =
*      ProEngFactory::NewAlertToneSeekerL();
*  @endcode
*
*  @lib ProfileEngine.lib
*  @since Series 60 3.1
*/
class ProEngFactory
    {
    public: // New functions

        /**
        * Create a new instance of Profiles Engine.
        * @since Series 60 3.1
        * @return New instance of Profiles Engine.
        *         Ownership is transferred to the client application.
        */
        IMPORT_C static MProEngEngine* NewEngineL();

        /**
        * Create a new instance of Profiles Engine. The created object is
        * pushed into the cleanup stack.
        * @since Series 60 3.1
        * @return New instance of Profiles Engine.
        *         Ownership is transferred to the client application.
        */
        IMPORT_C static MProEngEngine* NewEngineLC();

        /**
        * Create a new instance of Profiles Engine.
        * @since Series 60 3.1
        * @param aFs A reference to an open file server session. aFs must
        *        remain connected for the lifetime of the returned object.
        * @return New instance of Profiles Engine.
        *         Ownership is transferred to the client application.
        */
        IMPORT_C static MProEngEngine* NewEngineL( RFs& aFs );

        /**
        * Create a new instance of Profiles Engine. The created object is
        * pushed into the cleanup stack.
        * @since Series 60 3.1
        * @param aFs A reference to an open file server session. aFs must
        *        remain connected for the lifetime of the returned object.
        * @return New instance of Profiles Engine.
        *         Ownership is transferred to the client application.
        */
        IMPORT_C static MProEngEngine* NewEngineLC( RFs& aFs );

        /**
        * Create a new instance of Profiles Notification Handler.
        * @since Series 60 3.1
        * @return New instance of Notification Handler.
        *         Ownership is transferred to the client application.
        */
        IMPORT_C static MProEngNotifyHandler* NewNotifyHandlerL();

        /**
        * Create a new instance of Profiles Alert Tone Seeker.
        * @since Series 60 3.1
        * @return New instance of Alert Tone Seeker.
        *         Ownership is transferred to the client application.
        */
        IMPORT_C static MProEngAlertToneSeeker* NewAlertToneSeekerL();

    private:

        // Prohibit C++ default constructor.
        ProEngFactory();
        // Prohibit Destructor.
        ~ProEngFactory();

    };

#endif      // PROENGFACTORY_H

// End of File

