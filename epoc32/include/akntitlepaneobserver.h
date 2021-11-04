
/*
* ============================================================================
*  Name     : akntitlepaneobserver.h
*  Part of  : AVKON
*
*  Description:
*     Interface class for titlepane. This observer is used
*     by applications to observe when title pane has been actioned. 
*
*  Version:
*
*  Copyright © 2005 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef AKNTITLEPANEOBSERVER_H
#define AKNTITLEPANEOBSERVER_H

#include <e32base.h>

class MAknTitlePaneObserver
    {
public:
    enum TAknTitlePaneEvents
        {
        EAknTitlePaneTapped
        }; 
        
public:
    /**
    * HandleTitlePaneEventL is used in observers to handle title pane events.
    *
    * @param aEventID TAknTitlePaneEvents type title pane event
    */
    virtual void HandleTitlePaneEventL( TInt aEventID ) = 0; 
    };

#endif // AKNTITLEPANEOBSERVER_H
