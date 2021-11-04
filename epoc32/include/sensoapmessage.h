/*
* ==============================================================================
*  Name        : SenSoapMessage.h
*  Part of     : Web Services Framework / Utils
*  Interface   : 
*  Description : CSenSoapMessage is an utility class offering capability to
*                 parse XML SOAP envelope and manipulation methods to alter its
*                 contents.
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

#ifndef SEN_SOAP_MESSAGE_H
#define SEN_SOAP_MESSAGE_H

//  INCLUDES
#include <SenWsSecurityHeader.h>
#include <SenSoapEnvelope.h>

// CLASS DECLARATION

/**
* CSenSoapMessage extends basic SOAP envelope functionality by
* offering methods to set the security header and security token.
* @lib SenUtils.lib
* @since Series60 3.0
*/
class CSenSoapMessage : public CSenSoapEnvelope
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phase constructor.
        */
        IMPORT_C static CSenSoapMessage* NewL();

        /**
        * Two-phase constructor.
        * @param    aVersion version of SOAP (1.1 or 1.2)
        * @since S60 5.0
        */
        IMPORT_C static CSenSoapMessage* NewL(TSOAPVersion aVersion);
        
        /**
        * Two-phase constructor.
        * @param    aVersion version of SOAP (1.1 or 1.2)
        * @param    aSecurityNs seurity namespace version . 
        *           KSecuritySchemeXmlNs from 2003 , or KSecurityXmlNs from 2004
        * @since S60 5.0
        */
        IMPORT_C static CSenSoapMessage* NewL(TSOAPVersion aVersion, const TDesC8& aSecurityNs);
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CSenSoapMessage();

        // New functions
        
        /**
        * Sets a new security header for the soap message. If existant, the
        * old security header is deleted and new one with given data is added.
        * @since Series60 3.0
        * @param    aData    Data to be used in the security header.
        */
        IMPORT_C void SetSecurityHeaderL(const TDesC8& aData);
        
        /**
        * Adds new token (content) to current security header, 
        * appending to existing. The token is appended after the
        * current content of security token. Method instantiates
        * and adds default security header (without data), if 
        * such was not set in beforehand.
        * @since Series60 3.0
        * @param    aNewToken    Token to be inserted.
        * @return    KErrNone or some system-wide Symbian error codes.
        */
        IMPORT_C TInt AddSecurityTokenL(const TDesC8& aNewToken);    
        
    protected:  
    
        /**
         *    C++ default constructor.
         */
        IMPORT_C CSenSoapMessage::CSenSoapMessage();

        // New functions
        
        /**
        * Helper function to make a new security header.
        * @since Series60 3.0
        * @param    aData    Default=NULL. Data to be set in the security header.
        * @return    new security header, which is located in the cleanup stack.
        *            Caller takes ownership.
        */
        IMPORT_C virtual CSenWsSecurityHeader* NewSecurityHeaderLC(
                                                    const TDesC8* aData=NULL);

        // Functions from base classes
        
        // From CSenSoapEnvelope 
        
        /**
        * Implements functionality to parse SOAP header if one is found
        * during parsing the envelope.
        * Extends basic functionality from SOAP envelope by recognizing
        * and parsing <Security> element under following namespace:
        * http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd
        * All other headers are parsed using superclass (SOAP envelope)
        * functionality.
        * @since Series60 3.0
        * @param aNsUri            The namespace URI of the new element
        * @param aLocalName        The local name of the new element
        * @param aQName            The qualified name of the new element
        * @param aAttributes    The attributes of the new element
        */
        IMPORT_C virtual void ParseHeaderL(const TDesC8& aNsUri,
                                           const TDesC8& aLocalName,
                                           const TDesC8& aQName,
                                           const RAttributeArray& aAttributes);

        /**
        * This method should be called from the deriving classes ConstructL() methods. 
        * @since Series60 3.0
        */
        IMPORT_C void BaseConstructL();

        /**
        * This method should be called from the deriving classes ConstructL() methods. 
        * @since S60 5.0
        */
        IMPORT_C void BaseConstructL(TSOAPVersion aVersion);
        
        /**
        * This method should be called from the deriving classes ConstructL() methods.
        * @param    aVersion version of SOAP (1.1 or 1.2)
        * @param    aSecurityNs seurity namespace version . 
        *           KSecuritySchemeXmlNs from 2003 , or KSecurityXmlNs from 2004
        * @since S60 5.0
        */
        IMPORT_C void BaseConstructL(TSOAPVersion aVersion, const TDesC8& aSecurityNs);

    protected: // Data
        // Owned, but element not owned
        CSenWsSecurityHeader* ipSecurityHeader; 
    };

#endif // SEN_SOAP_MESSAGE_H

// End of File


