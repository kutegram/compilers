/*
* ==============================================================================
*  Name        : SenHostletConnection.h
*  Part of     : Web Services Hostlet Connection
*  Interface   : 
*  Description : CSenHostletConnection offers public API for
*                applications to to provide locally, invocable
                 services (identified by unique endpoint URI)
                 to service consumers.
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

#ifndef SEN_HOSTLET_CONNECTION_H
#define SEN_HOSTLET_CONNECTION_H

//  INCLUDES
#include <e32base.h> // for CActive

#include <MSenHostlet.h>
#include <MSenServiceDescription.h>
#include <SenServiceConnection.h>
#include <SenSoapEnvelope.h>
#include <SenFragment.h>

// CONSTANTS

const TInt KErrSenEndpointReserved                   =  -30317;


// FORWARD DECLARATIONS
class CSenServicePattern;

// CLASS DECLARATION
class CSenHostletConnection : public CActive
    {
    public: // Constructors and destructor

        /**
        * Constructs a new hostlet connection, utilizing the service description
        * provided by MSenHostlet::ServiceDescriptionL() callback implementation.
        * Leave codes:
        * - KErrSenEndpointReserved if the endpoint specified in hostlet 
        *   implementation already exists and is reserved for some other
        *   use (hostlet).
        * @return a pointer to a newly created hostlet connection
        */
        IMPORT_C static CSenHostletConnection* NewL(MSenHostlet& aProvider);

        /**
        * Constructs a new hostlet connection, utilizing the service description
        * provided by MSenHostlet::ServiceDescriptionL() callback implementation.
        * Leave codes:
        * - KErrSenEndpointReserved if the endpoint specified in hostlet 
        *   implementation already exists and is reserved for some other
        *   use (hostlet).
        * @return a pointer to a newly created hostlet connection, which is also
        *  left on the cleanup stack.
        */
        IMPORT_C static CSenHostletConnection* NewLC(MSenHostlet& aProvider);

        /**
        * Method for responding to incoming message. This asynchronous method
        * will send a response for the request that was received by the hostlet
        * implementation in the ServiceL callback. After the response has been
        * delivered to service consumer who made the request, the following
        * callback will be invoked:
        *       MSenHostlet::OnServiceCompleteL
        * @return KErrNone, if response was successfully pre-processed by
        * the hostlet connection - it does not mean, that it was yet 
        * received by the consumer, as this method is asynchronous.
        * If the response cannot be processed, some system-wide error
        * code is returned.    
        *         KErrAlreadyExists, if response was already provided 
        *         for this request
        */
        virtual TInt RespondL(MSenHostletResponse& aResponse) = 0;
        

       /* Getter for full, (live) service desctiption for this hostlet connection */
//       virtual TInt ServiceDescriptionL(CSenXmlServiceDescription*& apSessionDescription) = 0;

        /**
        * Getter for the identifier  of this connection.
        * @return the identifier as integer.
        */        
        virtual TInt Identifier() = 0;

           
    protected:
        /**
        * C++ default constructor.
        */
        CSenHostletConnection();
    
    };

//SEN_HOSTLET_CONNECTION_H
#endif

// End of File

