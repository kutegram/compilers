/*
* ==============================================================================
*  Name        : BrCtlDownloadObserver.h
*  Part of     : WebKit \ BrowserControl
*  Interface   : Browser Control API
*  Description : Handle download events
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


#ifndef BRCTLDOWNLOADOBSERVER_H
#define BRCTLDOWNLOADOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <BrCtlDefs.h>

// CONSTANTS

// MACROS

/**
* Defines the download events sent to the host application by the Download Manager.
* @attention For more information on aValue, see the HandleDownloadEventL function.
*/
enum TBrCtlDownloadEvent
    {
    /**
    * A download has started. The aValue associated with this 
    * event is the total size of the file to be downloaded. 
    * @see For more information on aValue, see HandleDownloadEventL.
    */
    EDownloadEventStarted,      
    /**
    * A download has completed. The aValue associated with this event 
    * is the total size of the file that was downloaded.
    */
    EDownloadEventCompleted,    
    /**
    * A download is in progress. The aValue associated with this event 
    * is the size of the file that was downloaded so far.
    */
    EDownloadEventProgress,     
    /** 
    * A download was canceled by the HandleDownloadCommandL function.
    */
    EDownloadEventCanceled,     
    /**
    * An error occurred in the Download Manager during a download operation.
    */
    EDownloadEventError,         
    /**
    * A download was paused. The aValue associated with this event 
    * is the size of the file that was downloaded before the pause occurred.
    */
    EDownloadEventPaused,   
    /**
    * A paused download was resumed. The aValue associated with this event 
    * is the size of the file that was downloaded so far.
    */
  EDownloadEventResumed,  
    /**
    * Notifies the host application as to whether or not a particular 
    * download can be paused. The aValue associated with this event is one of the following:
    * ETrue if the download can be paused
    * EFalse if the download cannot be paused
    */
  EDownloadEventPausable  
    };

// FORWARD DECLARATIONS
class CBrCtlInterface;

/**
* The MBrCtlDownloadObserver class handles download events.
*
* Usage:
*
* @code
*  #include <BrCtlDownloadObserver.h>
*
*  
* @see S60 Platform: Browser Control API Developer's Guide Version 2.0
* @lib BrowserEngine.lib
* @file BrCtlDownloadObserver.h
* @endcode     *
*/
class MBrCtlDownloadObserver
    {
    public: // New functions
        /**
        * Inform the host application that a new download has started using the Download Manager
        * @since 3.0
        * @param aTransactionID The ID of the transaction, it is unique as long as the transaction is on-going
        * @param aFileName Name of the file in which the downloaded content is stored
        * @param aContentType Type of content to be downloaded. For example:
        * Markup, Image, Cascading Style Sheet (CSS), Javascript, Netscape plug-in, Sound
        * @param aUrl The Url of the request to be done in the new window
        * @return ETrue if the file can be displayed or played while it is 
        * downloading (progressive download)
        * EFalse if the file cannot be displayed or played while it is downloading
        */
        virtual TBool NewDownloadL(TUint aTransactionID,
                                   const TDesC& aFileName,
                                   const TDesC& aContentType,
                                   const TDesC& aUrl) = 0;
                                   
        /**
        * Tells the host application to resume an incomplete download. 
        * After the host application restarts, this method is called 
        * for each file whose download was interrupted when the host application closed.
        * @since 3.0
        * @param aTransactionID ID of the transaction
        * This ID must be unique while the transaction is in progress.
        * @param aLength Length of the content previously downloaded
        * @param aFileName Name of the file in which the downloaded content is stored
        * @param aContentType Type of content downloaded. For example:
        * Markup, Image, Cascading Style Sheet (CSS), Javascript, Netscape plug-in, Sound 
        * @param aUrl URL of the source of the content to be done in the new window
        * @return None
        */
        virtual void ResumeDownloadL(TUint aTransactionID,
                                   TUint aLength,
                                   const TDesC& aFileName,
                                   const TDesC& aContentType,
                                   const TDesC& aUrl) = 0;



        /**
        * Informs the host application that one of the following download events is in progress:
        * NOTE: All events have the prefix EDownload:
        * EventStarted, EventCompleted, EventProgress, EventCanceled, EventError 
        * EventPaused, EventResumed, EventPausable
        * @since 3.0
        * @param aTransactionID The ID of the transaction, it is unique as long 
        * as the transaction is on-going
        * @param aDownloadEvent Event to be handled Examples:
        * EventStarted, EventCompleted, EventProgress, EventCanceled, EventError 
        * EventPaused, EventResumed, EventPausable
        * @param aValue Value associated with the event. Examples:
        * Total size of the downloaded file
        * Size of that was downloaded so far
        * @return void
        */
        virtual void HandleDownloadEventL(TUint aTransactionID, 
                                          TBrCtlDownloadEvent aDownloadEvent,
                                          TUint aValue) = 0;             

    };

#endif      // BRCTLDOWNLOADOBSERVER_H
            
// End of File
