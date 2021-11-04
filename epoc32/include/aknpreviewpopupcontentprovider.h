/*
* ==============================================================================
*  Name        : aknpreviewpopupcontentprovider.h
*  Part of     : UI Framework Core / Avkon
*  Description : Interface used for asynchronous content building for preview 
*                popup.
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

#ifndef AKNPREVIEWPOPUPCONTENTPROVIDER_H
#define AKNPREVIEWPOPUPCONTENTPROVIDER_H

// CLASS DECLARATION

/**
*  Interface used for asynchronous content building for a preview popup.
*
*  @lib avkon.lib
*  @since S60 3.2
*/
class MAknPreviewPopUpContentProvider
    {
    public: // New functions

        /**
        * Called by the preview popup controller when content building should be
        * started.
        */
        virtual void StartContentBuildingL() = 0;
        
        /**
        * Called by the preview popup controller if ongoing content building
        * operation should be cancelled.
        */
        virtual void CancelContentBuilding() = 0;
    };

#endif // AKNPREVIEWPOPUPCONTENTPROVIDER_H

//  End of File  
