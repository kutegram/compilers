/*
* ==============================================================================
*  Name        : AknToolbarObserver.h
*  Part of     : EikStd 
*  Interface   : UI Framework APIs
*  Description : Observer for avkon toolbar
*  Version     : 1.0
*
*  Copyright (c) 2005 Nokia Corporation.
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


#ifndef __AKNTOOLBAROBSERVER_H__
#define __AKNTOOLBAROBSERVER_H__

// INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class CAknToolbar;

// CLASS DECLARATION

/**
*  The observer interface to handle toolbar events
*
*  @lib eikcoctl.lib
*  @since Series 60 3.1
*/
class MAknToolbarObserver
    {
    public:
        /**
         * Should be used to set the properties of some toolbar components 
         * before it is drawn.
         * @param aResourceId The resource ID for particular toolbar
         * @param aToolbar The toolbar object pointer
         */
        IMPORT_C virtual void DynInitToolbarL( TInt aResourceId, 
                                               CAknToolbar* aToolbar );
        
        /**
         * Handles toolbar events for a certain toolbar item.
         * @param aCommand The command ID of some toolbar item.
         */
        virtual void OfferToolbarEventL( TInt aCommand ) = 0;
    
    protected:
        IMPORT_C virtual TInt MAknToolbarObserver_Reserved_1();
        IMPORT_C virtual TInt MAknToolbarObserver_Reserved_2();
    };
    
#endif // __AKNTOOLBAROBSERVER_H__

// end of file