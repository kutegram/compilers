/*
* =========================================================================
*  Name        : MSenHostletRequest.h
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

#ifndef MSEN_HOSTLET_REQUEST_H
#define MSEN_HOSTLET_REQUEST_H

#include <e32base.h>

#include <MSenProperties.h>

// FORWARD DECLARATIONS
class CSenIdentifier;

class MSenHostletRequest
    {
    public:
        /**
        * Getter for the request - it may either be plain (SOAP) request body,
        * or complete request including all the (SOAP) headers, depending
        * of whether or not the provider wishes to receive complete client
        * messages.
        * @see MSenProvider for more information about complete client
        *      messages facet.
        */
        virtual TPtrC8 RequestUtf8() const = 0;

        /**
        * Getter for requester's thread ID
        */
        virtual TPtrC ThreadId() const = 0;

        /** 
        * Getter for requester's consumer ID
        */
        virtual TPtrC8 ConsumerId() const = 0;

        /** 
        * Getter for request ID (transaction ID)
        */
        virtual TInt RequestId() const = 0;
        
        /**
        * Getter for request's properties and properties type
        * @param aType provides the (class) type of the retuned properties.
        * This enum can be used to select corresponding properties class
        * to de-serialize the properties descriptor into a more convenient
        * properties class instance.
        * @return the (transport) properties associated with this message.
        */
        virtual TPtrC8 Properties(MSenProperties::TSenPropertiesClassType& aType) const = 0;

        //virtual const CSenIdentifier& Requester() const = 0;
    };

// MSEN_HOSTLET_REQUEST_H
#endif
