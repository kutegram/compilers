/*
* ==============================================================================
*  Name        : MCLFChangedItemObserver.h
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


#ifndef MCLFCHANGEDITEMOBSERVER_H
#define MCLFCHANGEDITEMOBSERVER_H

//  INCLUDES
#include <CLFContentListing.h>
#include <e32std.h>

// FORWARD DECLARATIONS
class MCLFChangedItemObserverExt;

// CLASS DECLARATION

/**
*  Changed Item Observer interface.
*  Implement this interface to get notifications of changed,
*  new or deleted items.
*
*  @lib ContentListingFramework.lib
*  @since S60 3.1
*/
class MCLFChangedItemObserver
    {
    public: // New functions

        /**
        * Abstract method for handling item change event. This method is
        * called when, for example, some item is renamed.
        * @since S60 3.1
        * @param aItemIDArray List of Item IDs of changed items.
        */
        virtual void HandleItemChangeL(
                            const TArray<TCLFItemId>& aItemIDArray ) = 0;

        /**
        * Abstract method for handling errors. This method can be used to
        * handle errors in changed item event.
        * @since S60 3.1
        * @param aError System wide error code.
        */
        virtual void HandleError( TInt aError ) = 0;

    protected:

        /**
        * Destructor.
        */
        virtual ~MCLFChangedItemObserver() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MCLFChangedItemObserverExt* Extension() { return NULL; }

    };

#endif      // MCLFCHANGEDITEMOBSERVER_H

// End of File
