/*
* ==============================================================================
*  Name        : CDownloadMgrUiLibRegistry.h
*  Part of     : Download Manager / UI Lib
*  Interface   : UI Lib, UI Lib registration interface
*  Description : Supports registration of UI Lib modules.
*  Version     : -
*
*  Copyright � 2002-2004 Nokia. All rights reserved.
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


#ifndef CDOWNLOADMGRUILIBREGISTRY_H
#define CDOWNLOADMGRUILIBREGISTRY_H

//  INCLUDES
#include <e32std.H>
#include <e32base.h>

// FORWARD DECLARATIONS
class CDownloadMgrUiUserInteractions;
class CDownloadMgrUiDownloadsList;
class RHttpDownloadMgr;
class RHttpDownload;
class CUiLibRegistryExtension;

// CLASS DECLARATION

/**
*  This abstarct class represents an accessor for the resources of the UI Lib Registry.
*/
NONSHARABLE_CLASS( MDownloadMgrUiLibRegModel )
    {
    public:

        /**
        * Third UID of the Client App, which installed UI Lib.
        * This is the UID with which RHttpDownloadMgr was connected.
        */
        virtual TUid ClientAppUid() const = 0;

        /**
        * Is Downloads List installed?
        */
        virtual TBool DownloadsListInstalled() const = 0;

        /**
        * Reference to the Downloads List.
        */
        virtual CDownloadMgrUiDownloadsList& DownloadsList() const = 0;

        /**
        * Is User Interactions installed?
        */
        virtual TBool UserInteractionsInstalled() const = 0;

        /**
        * Reference to the User Interactions.
        */
        virtual CDownloadMgrUiUserInteractions& UserInteractions() const = 0;

        /**
        * Reference to the observed DMgr session.
        */
        virtual RHttpDownloadMgr& DownloadMgr() const = 0;

        /**
        * All download in Download Manager session.
        */
        virtual TInt DownloadCount() const = 0;

    };

/**
*  Supports registration of a User Interactions and a Downloads List component.
*/
NONSHARABLE_CLASS( CDownloadMgrUiLibRegistry ) : public CBase,
                                                 public MDownloadMgrUiLibRegModel
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        * @param aDownloadMgr The initial Download Manager session
        */
        IMPORT_C static CDownloadMgrUiLibRegistry* NewL( RHttpDownloadMgr& aDownloadMgr );
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CDownloadMgrUiLibRegistry();

    public: // New functions

        // ******* Register User Interactions and Downloads List

        /**
        * Register a User Interactions.
        * The created component will be owned by the Registry.
        * @return Reference to the constructed object.
        */
        IMPORT_C CDownloadMgrUiUserInteractions& RegisterUserInteractionsL();

        /**
        * Register a Downloads List.
        * The created component will be owned by the Registry.
        * @return Reference to the constructed object.
        */
        IMPORT_C CDownloadMgrUiDownloadsList& RegisterDownloadsListL();

    public: // Functions from MDownloadMgrUiLibRegModel

        virtual TUid ClientAppUid() const;
        virtual TBool DownloadsListInstalled() const;
        virtual CDownloadMgrUiDownloadsList& DownloadsList() const;
        virtual TBool UserInteractionsInstalled() const;
        virtual CDownloadMgrUiUserInteractions& UserInteractions() const;
        virtual RHttpDownloadMgr& DownloadMgr() const;
        virtual TInt DownloadCount() const;

    private: // Constructors

        /**
        * C++ default constructor.
        */
        CDownloadMgrUiLibRegistry( RHttpDownloadMgr& aDownloadMgr );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private: // New functions

        /**
        * Set registered UI components as observers of iDownloadMgr.
        */
        void SetUiComponentsAsObserversL();

        /**
        * Remove registered UI components as observers from iDownloadMgr.
        */
        void RemoveUiComponentsAsObservers();

    private: // Data

        CUiLibRegistryExtension* iExtension; ///< Extension class. Owned.

        // UI components
        CDownloadMgrUiUserInteractions* iUserInteractions; // Owned.
        CDownloadMgrUiDownloadsList*    iDownloadsList; // Owned.

        // Observed DM session
        RHttpDownloadMgr& iDownloadMgr; ///< Observed.
        TUid iClientAppUid;
    };

#endif /* CDOWNLOADMGRUILIBREGISTRY_H */
