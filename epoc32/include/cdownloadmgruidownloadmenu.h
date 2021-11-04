/*
* ==============================================================================
*  Name        : CDownloadMgrUiDownloadMenu.h
*  Part of     : Download Manager / UI Lib
*  Interface   : UI Lib, Download Menu
*  Description : Supports Download Menu
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


#ifndef CDOWNLOADMGRUIDOWNLOADMENU_H
#define CDOWNLOADMGRUIDOWNLOADMENU_H

//  INCLUDES
#include <E32BASE.H>

// FORWARD DECLARATIONS
class CEikMenuPane;
class CCoeEnv;
class CDownloadMenuExtension;

// CLASS DECLARATION

/**
*  Download menu support.
*
*  @lib Download Manager UI Lib
*  @since Series 60 2.8
*/
NONSHARABLE_CLASS( CDownloadMgrUiDownloadMenu ) : public CBase
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        static CDownloadMgrUiDownloadMenu* NewL( CCoeEnv& aCoeEnv );
        
        /**
        * Destructor.
        */
        virtual ~CDownloadMgrUiDownloadMenu();

    public: // New functions
        
        /**
        * Inserts a menu item in the client application's menu to access 
        * the Downloads List.
        * @since Series 60 2.8
        * @param aCommandId Command ID of the menu item
        * @param aMenuPane The item is inserted into this menu pane
        * @param aPreviousId The item is inserted after this command ID
        * @return -
        */
        IMPORT_C void AddMenuL( TInt aCommandId, 
                                CEikMenuPane& aMenuPane, 
                                TInt aPreviousId );

    protected:

        /**
        * C++ default constructor.
        */
        CDownloadMgrUiDownloadMenu( CCoeEnv& aCoeEnv );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    protected:  // Data

        CDownloadMenuExtension* iExtension; ///< Extension class. Owned.

        CCoeEnv& iCoeEnv; ///< Reference to CONE environment.

    };

#endif /* CDOWNLOADMGRUIDOWNLOADMENU_H */
