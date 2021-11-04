/*
* =========================================================================
*  Name     : SenXmlProperties.h
*  Part of  : Nokia Web Services Framework
*  Created  : 2005-09-26 by Nokia
*  Descr.   : Superclass for XML based properties implementations
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


#ifndef SEN_XML_PROPERTIES_H
#define SEN_XML_PROPERTIES_H

#include <e32std.h>
#include <SenDomFragment.h>
#include <MSenProperties.h>

// FORWARD DECLARATIONS
class RWriteStream;
class CSenXmlReader;
class CSenPropertiesFragment;

// CONSTANTS
_LIT8(KSenXmlPropertiesLocalname,       "Properties");
_LIT8(KSenTypeAttributeName,            "Type");
_LIT8(KSenOmittedAttributeName,         "Omitted");
_LIT8(KSenOmittedTrueNoValue,            "");
_LIT8(KSenPropertyTrue,                 "true");
_LIT8(KSenPropertyFalse,                "false");


//_LIT8(KSenXmlPropertiesQualifiedname,  "props:Properties);
//_LIT8(KSenXmlPropertiesNamespace,      "urn:com.nokia.Sen.properties.1.0");

// CLASS DESCRIPTION

/*
* 
* This class provides XML based implementation, which is mainly targetted
* for further evolved subclasses, which extend this to more concrete classes,
* like CSenHttpTransportProperties. Class provides serialization of properties
* into XML.
* 
* Please bear in mind the following limitations:
* 
* 1. It is illegal to provide following property names as argument to 
*    any of the setter methods, as they become XML tags - local element
*    names - when properties object is serialized:
*      (a) zero-length descriptor
*      (b) descriptor starts with number and
*      (c) descriptor contains any of the 5 basic XML entities in 
*          unencoded form (&, ', ", <, >)
* 
* 2. It is illegal to provide following property values as argument to 
*    any of the setter methods, as they become XML element content when 
*    properties object is serialized:
*      (a) descriptor contains any of the 5 basic XML entities in
*      unencoded form (&, ', ", <, >)
* @lib SenUtils.lib
* @since S60 5.0
*/

class CSenXmlProperties : public CBase, public MSenProperties
    {
    public:

        /**
        * Basic constructor.
        * @return a pointer to new CSenXmlProperties class instance.
        */
        IMPORT_C static CSenXmlProperties* NewL();
        /**
        * Basic constructor.
        * @return a pointer to new CSenXmlProperties class instance.
        */        
        IMPORT_C static CSenXmlProperties* NewLC();

        /**
        * Basic constructor.
		* @param aXmlUtf8 
    	* @param aParser It is a XML reader        
        * @return a pointer to new CSenTransportProperties class instance.
        */
        IMPORT_C static CSenXmlProperties* NewL(const TDesC8& aXmlUtf8,
                                       CSenXmlReader& aParser);
        /**
        * Basic constructor.
		* @param aXmlUtf8 
    	* @param aParser It is a XML reader        
        * @return a pointer to new CSenTransportProperties class instance.
        */
        IMPORT_C static CSenXmlProperties* NewLC(const TDesC8& aXmlUtf8,
                                        CSenXmlReader& aParser);

        /**
        * Basic constructor.
		* @param aElement
        * @return a pointer to new CSenXmlProperties class instance.
        */
        IMPORT_C static CSenXmlProperties* NewL(const CSenElement& aElement);
        /**
        * Basic constructor.
		* @param aElement
        * @return a pointer to new CSenXmlProperties class instance.
        */        
        IMPORT_C static CSenXmlProperties* NewLC(const CSenElement& aElement);

        // From MSenProperties
        virtual void SetReader(CSenXmlReader& aReader);
        virtual TSenPropertiesClassType PropertiesClassType();
        virtual void WriteToL(RWriteStream& aWriteStream);
        virtual void ReadFromL(const TDesC8& aBuffer);
        virtual HBufC8* AsUtf8L();
        virtual HBufC8* AsUtf8LC();
        virtual TBool IsSafeToCast(TSenPropertiesClassType aClass);
        
        virtual MSenProperties* Clone(TInt& aOkOrError) const;
        virtual MSenProperties* CloneL() const;

        /**
        * @see MSenProperties
        * Leave codes: 
        *      KErrSenInvalidCharacters if aName contains illegal characters.     
        *      KErrSenZeroLengthDescriptor if aName is zero length.
        */
        virtual TInt SetPropertyL(const TDesC8& aName,
                                  const TDesC8& aValue);

        virtual TInt PropertyL(const TDesC8& aName, TPtrC8& aValue);
        
        /**
        * @see MSenProperties
        * Leave codes: 
        *      KErrSenInvalidCharacters if aName contains illegal characters.     
        *      KErrSenZeroLengthDescriptor if aName is zero length.
        */
        virtual TInt SetIntPropertyL(const TDesC8& aName,
                                     const TInt aValue);
                                     
        virtual TInt IntPropertyL(const TDesC8& aName,
                                  TInt& aValue);
        /**
        * @see MSenProperties
        * Leave codes: 
        *      KErrSenInvalidCharacters if aName contains illegal characters.     
        *      KErrSenZeroLengthDescriptor if aName is zero length.
        */
        virtual TInt SetBoolPropertyL(const TDesC8& aName,
                                      const TBool aValue);
                                      
        virtual TInt BoolPropertyL(const TDesC8& aName,
                                   TBool& aValue);        
        virtual TInt SetOmittedL(const TDesC8& aName, TBool aValue);

        virtual TInt RemovePropertyL(const TDesC8& aName);
        /**
        * Destructor.
        */
        virtual ~CSenXmlProperties();
        
        /**
        * Sets new property. 
        *
        * If property with given name does not exist, 
        * new property with given value will be added. Otherwise the value of 
        * existing property will be updated.
        *
        * @since Series60
        * @param aName         Name of the property, which can be later used to
        *                      refer the given value.
        * @param aValue        Is the value of this property.
        * @param aType         Is the type of this property.
        * @return              KErrNone if no error, or some of the system wide
        *                      error codes.
        */
        virtual TInt SetPropertyL(const TDesC8& aName, 
                                  const TDesC8& aValue,
                                  const TDesC8& aType);

        /**
        * Gets the value of the property behind certain name.
        * @since Series60
        * @param aName    The name identifying this property.
        * @param aValue   A TPtrC8 reference to be filled in with the value of
        *                 the property.
        * @param aType    A TPtrC8 reference to be filled in with the type of
        *                 the property.
        * @return         KErrNone if no error, or some of the system wide
        *                 error codes.     
        */
        virtual TInt PropertyL(const TDesC8& aName, 
                               TPtrC8& aValue,
                               TPtrC8& aType);
    
    protected: // base class functions

        virtual void BaseConstructL(const TDesC8& aLocalname, 
                                    const TDesC8& aXml,
                                    CSenXmlReader* aParser = NULL);

        virtual void BaseConstructL(const TDesC8& aNamespace, 
                                    const TDesC8& aLocalname, 
                                    const TDesC8& aXml,
                                    CSenXmlReader* aParser = NULL);

        virtual void BaseConstructL(const TDesC8& aNamespace, 
                                    const TDesC8& aLocalname, 
                                    const TDesC8& aQualifiedName, 
                                    const TDesC8& aXml,
                                    CSenXmlReader* aParser = NULL);

        virtual void BaseConstructL(const CSenElement& aElement);

    protected:
        /**
        * Constructor.
        */
        CSenXmlProperties();

    protected:
        CSenPropertiesFragment*     ipFragment; // owned
        CSenXmlReader*              ipReader;   // owned
    };

#endif // SEN_XML_PROPERTIES_H
