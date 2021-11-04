/*
* =========================================================================
*  Name        : MSenHostletResponse.h
*  Part of     : Web Services
*  Description : 
*  Version     : 
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
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

#ifndef MSEN_HOSTLET_RESPONSE_H
#define MSEN_HOSTLET_RESPONSE_H

#include <e32base.h>

// FORWARD DECLARE
class MSenProperties;
class MSenMessage;


class MSenHostletResponse
    {
    public:
        /**
        *  Set the response
        * @param aResponseUtf8 is the response that this hostlet is providing
        * @param aCode can be set to error code, in case that request is not
        * accepted by this hostlet.
        * @param aResponseProperties may be provided in order to pass (transport)
        * properties with the response.
        * @param aResponseMessage may be provided in order to pass concrete
        * message object with the response (like libxml2 based SOAP-ENV,
        * CSenSoapEnvelope2)
        */
        virtual void SetResponseUtf8L(const TDesC8& aResponseUtf8, 
                                      const TInt aResponseCode = KErrNone, 
                                      MSenProperties* aResponseProperties = NULL,
                                      MSenMessage* apMessage = NULL) = 0;
        
        /**
        * Getter for request (transaction) ID
        * @return the id of the request to which this is a response for
        */ 
        virtual TInt RequestId() const = 0;
        
        /**
        * Getter for response data
        * @return the set response as UTF-8 descriptor
        */
        virtual TPtrC8 ResponseUtf8() = 0;

        /**
        * Getter for response code
        * @return the response code (KErrNone or some error) that hostlet has provided
        */
        virtual TInt ResponseCode() const = 0;
        
        /**
        * Getter for response properties
        */
        virtual MSenProperties* ResponseProperties() = 0;
    };

// MSEN_HOSTLET_RESPONSE_H
#endif
