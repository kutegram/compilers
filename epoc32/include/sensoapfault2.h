/*
* ==============================================================================
*  Name        : SenSoapFault2.h
*  Part of     : Web Services Framework / Utils
*  Interface   : 
*  Description : This utility class represents SOAP fault element according to
*                SOAP fault specification. 
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

#ifndef SEN_SOAP_FAULT_H
#define SEN_SOAP_FAULT_H

//  INCLUDES
#include <SenDomFragmentBase.h>
#include <SenSoapConstants.h>

// CLASS DECLARATION

/**
* This utility class represents SOAP fault element according to SOAP fault 
* specification. 
* SOAP fault element has following child elements: 
*  faultcode, 
*  faultstring, 
*  faultactor 
*  detail
*
*  
*  
*/
class CSenSoapFault2 : public CSenDomFragmentBase
    {
    public:  // Constructors and destructor
        
        /**
        * Copy constructor, making a copy of the original source element.
        * 
        * @param aElement   Element which is copied into SoapFault.
        */
        IMPORT_C static CSenSoapFault2* NewL(TXmlEngElement& aElement);

        /**
        * Constructor which, takes
        * 1) TXmlEngElement which is already owned by other Fragment and
        * 2) RSenDocument which is owned by that same other Fragment.
        * Constructor takes a copy of RSenDocument => given element
        * will be destructed when both original Fragment and
        * CSenSoapFault2 have been destructed. Given element will
        * be root element of CSenSoapFault2.
        *
        * 
        * @param aElement   Soap Fault element.
        * @param aDocument  Original document holding given Soap Fault
        *                   element.
        */
        IMPORT_C static CSenSoapFault2* NewL(TXmlEngElement& aElement,
                                             RSenDocument& aDocument);

        /**
        * Basic constructor.
        * 
        * @param aNsUri is the XML namespace of this SOAP fault
        * @param aLocalName is the localname for this SOAP fault
        * @param aQName is the qualifiedname for this SOAP fault
        * @param aAttributes are the XML attributes for this SOAP fault
        * Parameters are used to construct the soap fault.
        */
        IMPORT_C static CSenSoapFault2* NewL(const TDesC8& aNsUri,
                                            const TDesC8& aLocalName,
                                            const TDesC8& aPrefix,
                                            const RAttributeArray& aAttributes,
                                            TXmlEngElement& aElement,
                                            RSenDocument& aDocument);
            
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CSenSoapFault2();

        // New functions
        
        /**
        * 
        * @return the content of <faultcode> element as UTF-8 form string
        * or KNullDesC8, if element is not available
        */
        IMPORT_C TPtrC8 FaultCode();

		/**
		* 
		* @return the content of <Subcode> element as UTF-8 form string
		* or KNullDesC8, if element is not available
		*/
		IMPORT_C TPtrC8 FaultSubcode();

		/**
        * 
        * @return the content of <faultstring> element as UTF-8 form string
        * or KNullDesC8, if element is not available
        */
        IMPORT_C TPtrC8 FaultString();

        /**
        * 
        * @return the content of <faultactor> element as UTF-8 form string
        * or KNullDesC8, if element is not available
        */
        IMPORT_C TPtrC8 FaultActor();

        /**
        * 
        * @return the content of <detail> element as UTF-8 form string
        * or KNullDesC8, if element is not available
        */
        IMPORT_C TPtrC8 Detail();
        
    protected:  
        
        /**
        * C++ default constructor
        */
        IMPORT_C CSenSoapFault2();
        
        /**
        * Basic ConstructL function
        * 
        * @param aElement is the TXmlEngElement from which data to this
        *                 SOAP fault object is to be copied.
        */
        IMPORT_C void ConstructL(TXmlEngElement& aElement);

        /**
        * ConstructL method which takes
        * 1) TXmlEngElement which is already owned by other Fragment and
        * 2) RSenDocument which is owned by that same other Fragment.
        * Constructor takes a copy of RSenDocument => given element
        * will be destructed when both original Fragment and
        * CSenSoapFault2 have been destructed. Given element will
        * be root element of CSenSoapFault2.
        *
        * 
        * @param aElement   Soap Fault element.
        * @param aDocument  Original document holding given Soap Fault
        *                   element.
        */
        IMPORT_C void ConstructL(TXmlEngElement& aElement, RSenDocument& aDocument);

        /**
        * Basic ConstructL function
        * 
        * @param aNsUri is the XML namespace URI of this SOAP fault
        * @param aLocalName is the XML localname URI of this SOAP fault
        * @param aQName is the XML qualifiedname URI of this SOAP fault
        * @param aAttributes are the XML attributes for this SOAP fault
        */
        IMPORT_C void ConstructL(const TDesC8& aNsUri,
                                 const TDesC8& aLocalName,
                                 const TDesC8& aPrefix,
                                 const RAttributeArray& aAttributes,
                                 TXmlEngElement& aElement,
                                 RSenDocument& aDocument);
    };

// SEN_SOAP_ENVELOPE_H
#endif

// End of File
