/*
* ==============================================================================
*  Name        : BrCtlLayoutObserver.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Handle scrollbar and tab events
*  Version     : %Version%
*
*    Copyright (c) 2006, Nokia Corporation
*    All rights reserved.
*  
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions
*   are met:
*  
*      * Redistributions of source code must retain the above copyright
*        notice, this list of conditions and the following disclaimer.
*      * Redistributions in binary form must reproduce the above copyright
*        notice, this list of conditions and the following disclaimer in
*        the documentation and/or other materials provided with the
*        distribution.
*      * Neither the name of the Nokia Corporation nor the names of its
*        contributors may be used to endorse or promote products derived
*        from this software without specific prior written permission.
*  
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
*   USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
*   DAMAGE.
*  
*    Please see file patentlicense.txt for further grants.
* ==============================================================================
*/


#ifndef BRCTLLAYOUTOBSERVER_H
#define BRCTLLAYOUTOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>


/**
* Defines whether a page is to be read from left-to-right or from right-to-left.
*/
enum TBrCtlLayout
  {
  EOriginTopLeft, ///< Page is to be read from left-to-right
  EOriginTopRight ///< Page is to be read from right-to-left
  };

enum TBrCtlTabDirection
    {
    ETabLeft,
    ETabRight,
    ETabUp,
    ETabDown
    };

/**
* The MBrCtlLayoutObserver class receives 
* scrolling events when the host application draws the scrollbar. 
*
* Usage:
*
* @code
*  #include <BrCtlLayoutObserver.h>
*
*  
* @see S60 Platform: Browser Control API Developer's Guide Version 2.0
* @lib BrowserEngine.lib
* @file BrCtlLayoutObserver.h
* @endcode     *
*/
class MBrCtlLayoutObserver
    {
    public: // New functions
        
        /**
        * Update the position of vertical scrollbar.
        * @since 2.8
        * @param aDocumentHeight The total height of the markup page
        * @param aDisplayHeight The height of the display
        * @param aDisplayPosY The current Y position
        * @return void
        */
        virtual void UpdateBrowserVScrollBarL(TInt aDocumentHeight, 
                                              TInt aDisplayHeight,
                                              TInt aDisplayPosY ) = 0;

        /**
        * Update the position of horizontal scrollbar.
        * @since 2.8
        * @param aDocumentWidth The total width of the markup page
        * @param aDisplayWidth The width of the display
        * @param aDisplayPosX The current X position
        * @return void
        */
        virtual void UpdateBrowserHScrollBarL(TInt aDocumentWidth, 
                                              TInt aDisplayWidth,
                                              TInt aDisplayPosX ) = 0;

        /**
        * Inform the layout of the page: right to left or left to right. 
        * Useful when the application draws the scrollbar itself.
        * @since 2.8
        * @param aNewLayout RTL (right to left) or LTR (left to right)
        * @return void
        * @attention This function is useful when the host application draws the scrollbar.
        * In RTL pages, the scroll bar should be on the left side. 
        */
        virtual void NotifyLayoutChange( TBrCtlLayout aNewLayout ) = 0;
        
        /**
        * Update the title of the page in history view
        * @since 3.0
        * @param aTitle Title of the page
        * @return void
        */
        virtual void UpdateTitleL( const TDesC& aTitle ) = 0;        
    };

#endif      // BRCTLLAYOUTOBSERVER_H
            
// End of File
