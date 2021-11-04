/*
* ==============================================================================
*  Name        : BrCtlSoftkeysObserver.h
*  Part of     : WebKit \ BrowserControl
*  Interface   : Browser Control API
*  Description : Handle softkeys updates
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


#ifndef BRCTLSOFTKEYSOBSERVER_H
#define BRCTLSOFTKEYSOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>

/**
* Identifies which softkey is to be used
*/
enum TBrCtlKeySoftkey
    {
    EKeyRight, ///< Use the right softkey
    EKeyLeft   ///< Use the left softkey
    };

enum TBrCtlSoftkeyChangeReason
    {
    EChangeReasonElementType,
    EChangeReasonLoad,
    EChangeReasonIdle
    };

/**
* The MBrCtlSoftkeysObserver class handles requests to change the softkeys. 
*
* Usage:
*
* @code
*  #include <BrCtlSoftkeysObserver.h>
*
*  
* @see S60 Platform: Browser Control API Developer's Guide Version 2.0
* @lib BrowserEngine.lib
* @file BrCtlSoftkeysObserver.h
* @endcode     *
*/
class MBrCtlSoftkeysObserver
    {
    public: // New functions
        
        /**
        * Requests the host application to change a softkey. 
        * The host application may or may not change the softkey.
        * @since 2.8
        * @param aKeySoftkey Determines whether to update the left softkey or the right softkey.
        * Values:
        * EKeyRight to update the right softkey
        * EKeyLeft to update the left softkey
        * @param aLabel The label associated with the softkey update
        * @param aCommandId The command to use if the softkey is selected by the user
        * @param aBrCtlSoftkeyChangeReason Reason for the softkey change 
        * Value: EChangeReasonIdle (The other values are reserved for future use.)
        * @return void
        */
        virtual void UpdateSoftkeyL(TBrCtlKeySoftkey aKeySoftkey,
                                    const TDesC& aLabel,
                                    TUint32 aCommandId,
                                    TBrCtlSoftkeyChangeReason aBrCtlSoftkeyChangeReason) = 0;
    };

#endif      // BRCTLSOFTKEYSOBSERVER_H   
            
// End of File
