/*
* ==============================================================================
*  Name        : DownloadsListDlgObserver.h
*  Part of     : Download Manager / UI Lib
*  Interface   : UI Lib, Dialog observer M class
*  Description : Dialog observer M class
*  Version     : -
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


#ifndef DOWNLOADSLISTDLGOBSERVER_H
#define DOWNLOADSLISTDLGOBSERVER_H

//  INCLUDES
#include <e32def.h>
#include <coedef.h>
#include <w32std.h>

// FORWARD DECLARATIONS
class CDownloadsListDlg;
class CEikMenuPane;

// CLASS DECLARATION

/**
*  Observer interface of CDownloadsListDlg.
*
*  @lib Download Manager UI Lib
*  @since Series 60 2.8
*/
NONSHARABLE_CLASS( MDownloadsListDlgObserver )
    {
    public:

        /**
        * Called for layouting the dialog before executing it.
        */
        virtual void PreLayoutDynInitL( CDownloadsListDlg& aDialog ) = 0;

        /**
        * Called for processing not dialog specific commands.
        */
        virtual void ProcessCommandL( CDownloadsListDlg& aDialog, TInt aCommandId ) = 0;

        /**
        * Called for initializing Options menu.
        */
        virtual void DynInitMenuPaneL( CDownloadsListDlg& aDialog, TInt aResourceId, CEikMenuPane* aMenuPane ) = 0;

        /**
        * Key events first forwarded to the observer.
        */
        virtual TKeyResponse OfferKeyEventL( CDownloadsListDlg& aDialog, const TKeyEvent& aKeyEvent, TEventCode aType ) = 0;

    };

#endif /* DOWNLOADSLISTDLGOBSERVER_H */

