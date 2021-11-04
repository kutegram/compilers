/*
* ==============================================================================
*  Name        : aknpreviewpopupobserver.h
*  Part of     : UI Framework Core / Avkon
*  Description : Preview popup observer.
*  Version     : 1.0
*
*  Copyright © 2005-2007 Nokia. All rights reserved.
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

#ifndef AKNPREVIEWPOPUPOBSERVER_H
#define AKNPREVIEWPOPUPOBSERVER_H

// FORWARD DECLARATIONS
class CAknPreviewPopUpController;

// CLASS DECLARATION

/**
*  Interface for observing preview popup events.
*
*  @lib avkon.lib
*  @since S60 3.2
*/
class MAknPreviewPopUpObserver
    {    
    public:
    
        /** Preview popup event types. */
        enum TPreviewPopUpEvent
                {                
                /** Preview popup is shown. */
                EPreviewPopUpShown,
                /** Preview popup is hidden. */
                EPreviewPopUpHidden
                };

    public:
   
        /**
        * Called by the preview popup when an appropriate event takes place. 
        * @param aController Pointer to the sender of the event.
        * @param aEvent Event type.
        */
        virtual void HandlePreviewPopUpEventL(
            CAknPreviewPopUpController* aController,
            TPreviewPopUpEvent aEvent ) = 0;
    };

#endif // AKNPREVIEWPOPUPOBSERVER_H

//  End of File  
