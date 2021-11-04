/*
* ==============================================================================
*  Name        : BrCtlWindowObserver.h
*  Part of     : WebKit \ BrowserControl
*  Interface   : Browser Control API
*  Description : Handle multiple windows events such as open/close/etc
*  Version     : 3.0
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


#ifndef BRCTLWINDOWOBSERVER_H
#define BRCTLWINDOWOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <BrCtlDefs.h>

// CONSTANTS

// MACROS

// DATA TYPES
enum TBrCtlWindowCommand
    {
    EFocusWindow,
    EUnfocusWindow,
    EShowWindow,
    ECloseWindow
    };

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CBrCtlInterface;

/**
* The MBrCtlWindowObserver class handles window events such open/close/etc
*
* Usage:
*
* @code
*  #include <BrCtlWindowObserver.h>
*
* @see S60 Platform: Browser Control API Developer's Guide Version 2.0
* @lib BrowserEngine.lib
* @since 3.0
* @file BrCtlWindowObserver.h
* @endcode     *
*/
class MBrCtlWindowObserver
    {
    public: // New functions
        /**
        * Request the host applicaion to open the URL in a new window
        * @since 3.0
        * @param aUrl The Url of the request to be done in the new window
        * @param aTargetName The name of the new window
        * @param aUserInitiated ETrue if the new window is initiated by a user event (click)
        * @param aMethod The method to be used for fetching the supplied url
        * @param aContentType If the method is POST, this is the content type of the data to be posted 
        * @param aPostData If the method is POST, this is the data to be posted 
        * @param aBoundary The boundary used if the content is multipart/form-data
        * @param aReserved For future use
        * @return Return Value is the new browser control associated with the new window
        */
        virtual CBrCtlInterface* OpenWindowL(TDesC& aUrl, TDesC* aTargetName, TBool aUserInitiated, 
             TAny* aReserved) = 0;

        /**
        * Find a window by target name
        * @since 3.0
        * @param aTargetName name of the window to find
        * @return Return Value is the browser control associated with the window name
        */
        virtual CBrCtlInterface* FindWindowL( const TDesC& aTargetName ) const = 0;             

        /**
        * Handle window events such as close/focus etc
        * @since 3.0
        * @param aTargetName name of the window to send the event to
        * @param aCommand Command to pass to the window
        * @return void
        */
        virtual void HandleWindowCommandL( const TDesC& aTargetName, TBrCtlWindowCommand aCommand ) = 0;
    };

#endif      // BRCTLWINDOWOBSERVER_H
            
// End of File
