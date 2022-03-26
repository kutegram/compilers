/*
* ==============================================================================
*  Name        : BrCtlBrCtlSpecialLoadObserver.h
*  Part of     : WebKit \ BrowserControl
*  Interface   : Browser Control API
*  Description : Handle special load events such as network connection, deal with non-http or non-html requests
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


#ifndef BRCTLSPECIALLOADOBSERVER_H
#define BRCTLSPECIALLOADOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <apmstd.h> 
#include <ApEngineConsts.h>
#include <badesca.h>

// CONSTANTS

// MACROS

// DATA TYPES
enum TBrCtlDownloadParam
    {
    EParamRequestUrl, ///< URL requested
    EParamRealm, ///< Realm (if www)
    EParamUsername, ///< User name (if www authentication)
    EParamPassword, ///< Password (if www authentication)
    EParamProxyRealm, ///< Realm in the case of proxy authentication
    EParamProxyUsername, ///< User name (if proxy authentication)
    EParamProxyPassword, ///< Password (if proxy authentication)
    EParamRawRequestHeader, ///< Request header in the form: Header:Value
    EParamReceivedContentType, ///< Type of content received
    EParamExpectedContentType, ///< Type of content expected to appear in the markup <object> tag.
    EParamTotalContentLength, ///< Expected length of the content
    EParamReceivedContentLength, ///< Length of the content already received
    EParamReceivedContent, ///< Body of the content received
    EParamRawResponseHeader, ///< Response header in the form: Header: Value
    EParamLocalFileName, ///< Name of the file containing the content to be downloaded
    EParamCharset, ///< Character set of the content to be downloaded
    EParamRefererHeader, ///< Referrer header used in the download request, if applicable
    EParamTransactionId ///< Transaction ID 
    };

// FUNCTION PROTOTYPES


/**
* The MBrCtlSpecialLoadObserver class handles special load events, such as 
* network connection, non-HTTP(S) load requests, and non-HTML responses.
*
* Usage:
*
* @code
*  #include <BrCtlSpecialLoadObserver.h>
*
*  
* @see S60 Platform: Browser Control API Developer's Guide Version 2.0
* @lib BrowserEngine.lib
* @file BrCtlSpecialLoadObserver.h
* @endcode     *
*/
class MBrCtlSpecialLoadObserver
    {
    public: // New functions
        /**
        * Request to create a network connection.
        * @since 2.8
        * @param aConnectionPtr Pointer to the network connection. It must 
        * be type casted to an integer. If NULL, the Proxy Filter creates 
        * a network connection automatically. It must be type casted to an integer.
        * @param aSockSvrHandle A handle to the socket server.
        * @param aNewConn A flag if a new connection was created. If the 
        * connection is not new, proxy filter optimization will not read 
        * the proxy again from CommsBd.
        * ETrue if a new connection was created.
        * EFalse if a previously created connection was used.
        * @param aBearerType Bearer type of the new connection. For example, GPRS, WCDMA.
        * TapBearerType is defined in ApEngineConsts.h.
        * @return void
        * @attention This function is called for every HTTP request for which 
        * the content was not found in the cache. This function is called 
        * whether or not a connection was established in a previous request. 
        * The host application determines whether to create a new connection 
        * or to use an existing connection. 
        */
        virtual void NetworkConnectionNeededL(TInt* aConnectionPtr,
                                              TInt* aSockSvrHandle,
                                              TBool* aNewConn,
                                              TApBearerType* aBearerType) = 0;

        /**
        * Requests the host application to handle non-HTTP requests. It is expected that the 
        * host application will call the Scheme Dispatcher to handle these requests.
        * @since 2.8
        * @param aTypeArray Array of request parameters. Examples: URL, referrer header
        * @param aDesArray Array of values corresponding to the types in aTypeArray
        * @return ETrue if the host application handles the scheme.
        * EFalse if the host application cannot handle the scheme.
        * @attention The browser checks the scheme to determine whether or 
        * not it is supported. The browser supports the following schemes:
        * File scheme, HTTP scheme or HTTPS scheme
        * If the URL contains a scheme that the browser does not 
        * support, such as RTSP, then the host application should pass the 
        * content to an application that can handle that scheme. 
        */
        virtual TBool HandleRequestL(RArray<TUint>* aTypeArray, CDesCArrayFlat* aDesArray) = 0;

        /**
        * Request the host applicaion to handle downloads
        * @since 2.8
        * @param aTypeArray array of download parameter types
        * @param aDesArray array of values associated with the types in the type array
        * @return ETrue if handled by the host application
        * EFalse if not handled by the host application
        * @attention The host application should call the Download Manager to 
        * handle non-HTML content. 
        * Only GET requests are supported because the Browser Control must 
        * cancel the transaction before the Download Manager can take over. 
        * If a POST request is cancelled, the server may enter an unpredictable state.
        * For POST requests, the Browser Control downloads the content before calling 
        * this function. It stores the content in a file whose name is passed to the 
        * host application by using the EParamLocalFileName parameter. The host 
        * application should check whether this parameter was passed by the 
        * Browser Control to determine whether the Browser Control already downloaded 
        * the content. If not, the host application should download the content.
        */
        virtual TBool HandleDownloadL(RArray<TUint>* aTypeArray, CDesCArrayFlat* aDesArray) = 0;

    };

#endif      // BRCTLSPECIALLOADOBSERVER_H
            
// End of File
