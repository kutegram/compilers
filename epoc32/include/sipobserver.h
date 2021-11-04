/*
* ==============================================================================
*  Name        : sipobserver.h
*  Part of     : SIP Client
*  Interface   : SDK API, SIP Client API
*  Description : 
*  Version     : 1.0
*
*  Copyright (c) 2005 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef MSIPOBSERVER_H
#define MSIPOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class CSIPServerTransaction;

// CLASS DECLARATION

/**
*  @publishedAll
*  
*
*  An interface to be implemented by user of CSIP.
*  Interface allows to be able to receive SIP request from the SIP connection
*  that has not been initialized by the user.
*
*  
*/
class MSIPObserver
    {    
    public: // New functions
        /**
        * A SIP request has been received from the network.
        * This function is called when the SIP request was received using such
        * an IAP, for which the application has not created a CSIPConnection
        * object.
        * @pre aTransaction != 0
        * @param aIapId The IapId from which the SIP request was received.
        * @param aTransaction contains local address, remote address of a SIP
        *        message, as well as optional SIP message method, headers and
        *        body. The ownership is transferred.
        */
        virtual void IncomingRequest(TUint32 aIapId,
                                     CSIPServerTransaction* aTransaction) = 0;

        /**
        * The received SIP request time-outed and it is invalid i.e. cannot be used
        * anymore.
        * This will be called if the user fails to create a SIP connection and
        * does not send an appropriate SIP response.
        * @param aTransaction The time-outed transaction.
        */
        virtual void TimedOut(CSIPServerTransaction& aTransaction) = 0;
    };

#endif
