/*
* ==============================================================================
*  Name        : MCLFProcessObserver.h
*  Part of     : Content Listing Framework
*  Interface   : SDK, Content Listing Framework API
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


#ifndef MCLFPROCESSOBSERVER_H
#define MCLFPROCESSOBSERVER_H

//  INCLUDES
#include <e32std.h>

// DATA TYPES
/**
* Content Listing Framework process events
*/
enum TCLFProcessEvent
    {
    /// CLF server starts update process
    ECLFUpdateStart = 0x0,
    /// CLF server update process is end
    ECLFUpdateStop = 0x1
    };

// FORWARD DECLARATIONS
class MCLFProcessObserverExt;

// CLASS DECLARATION

/**
*  Process observer interface for Content Listing Framework.
*  Implement this interface to get notified of process events. These process
*  events are generated when update process of CLF server is started
*  and finished.
*
*  @lib ContentListingFramework.lib
*  @since S60 3.1
*/
class MCLFProcessObserver
    {
    public: // New functions

        /**
        * Abstract method to handle CLF process event. This method is called
        * when process events are generated.
        * @since S60 3.1
        * @param aProcessEvent The process event that was generated.
        */
        virtual void HandleCLFProcessEventL( TCLFProcessEvent aProcessEvent ) = 0;

    protected:

        /**
        * Destructor.
        */
        virtual ~MCLFProcessObserver() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MCLFProcessObserverExt* Extension() { return NULL; }

    };

#endif      // MCLFProcessObserver_H

// End of File
