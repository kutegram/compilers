/*
* ==============================================================================
*  Name        : AknTouchPaneObserver.h
*  Part of     : EikStd / EikCoCtl
*  Interface   : UI Framework / Touch pane API
*  Description : File contains an interface for a touch pane observer.
*  Version     : %version: 1 %
*
*  Copyright © 2005, 2006 Nokia. All rights reserved.
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


#ifndef AKNTOUCHPANEOBSERVER_H
#define AKNTOUCHPANEOBSERVER_H

// CLASS DECLARATION

/**
 * The MAknTouchPaneObserver interface allows a touch pane observer to pick up
 * changes in the size or position of the touch pane. Such events will be as a
 * result of layout changes which cause an actual change in the touch pane
 * rectangle.
 */
class MAknTouchPaneObserver
    {
    public:

        /**
        * Handles a change in the size or position of touch pane.
        * This function is called when touch pane changes its size or position.
        */
        virtual void HandleTouchPaneSizeChange() = 0;

    };

#endif // AKNTOUCHPANEOBSERVER_H

// End of file

