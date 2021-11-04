/*
* ==============================================================================
*  Name        : SenDomFragment.h
*  Part of     : Web Services Xml
*  Interface   : 
*  Description : Class implements DOM fragment functionality
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

#ifndef SEN_DOM_FRAGMENT_H
#define SEN_DOM_FRAGMENT_H

//  INCLUDES
#include <SenBaseFragment.h>

// FORWARD DECLARATIONS
class RFileLogger;

// CLASS DECLARATION

/**
* Class implements DOM fragment functionality
* The implementation further extends CSenBaseFragment
* functionality. In DOM fragment, all child elements
* are parsed into separate element objects. This makes
* it possible to reference any child which offer methods
* declared in XML element interface. Any such element
* can also be easily extracted (detached) from this
* root DOM fragmet.
* @lib SenXML.dll
* @since Series60 3.0
*/
class CSenDomFragment : public CSenBaseFragment
    {
    public:  // Constructors and destructor
        
        /**
        * Basic contructor. Should be used only for parsing new fragments etc. 
        * Constructing DomFragments for other use should be done with at least 
        * localname parameter.
        * @since Series60 3.0
        */
        IMPORT_C static CSenDomFragment* NewL();

        /**
        * Basic constructor.
        * @since Series60 3.0
        * @param aElement Element to copy construction data from.
        */
        IMPORT_C static CSenDomFragment* NewL(
            const CSenElement& aElement);

        /**
        * Basic constructor.
        * @since Series60 3.0
        * @param aLocalName is the XML localname of this fragment
        * Leave codes:  
        *       KErrSenInvalidCharacters if aLocalName contains
        *       illegal characters.     
        *       KErrSenZeroLengthDescriptor if aLocalName is zero length.
        */
        IMPORT_C static CSenDomFragment* NewL(const TDesC8& aLocalName);

        /**
        * Basic constructor.
        * @since Series60 3.0
        * @param aNsUri is the XML namespace user of this fragment
        * @param aLocalName is the XML localname of this fragment
        * Leave codes:  
        *       KErrSenInvalidCharacters if aLocalName contains
        *       illegal characters.     
        *       KErrSenZeroLengthDescriptor if aLocalName is zero length.
        */
        IMPORT_C static CSenDomFragment* NewL(const TDesC8& aNsUri,
                                              const TDesC8& aLocalName);

        /**
        * Basic constructor.
        * @since Series60 3.0
        * @param aNsUri is the XML namespace user of this fragment
        * @param aLocalName is the XML localname of this fragment
        * @param aQName is the XML qualifiedname of this fragment
        * Leave codes:  
        *       KErrSenInvalidCharacters if aLocalName or aQName contains
        *       illegal characters.     
        *       KErrSenZeroLengthDescriptor if aLocalName or aQName is zero length.
        */
        IMPORT_C static CSenDomFragment* NewL(const TDesC8& aNsUri,
                                              const TDesC8& aLocalName,
                                              const TDesC8& aQName);

        /**
        * Basic constructor.
        * @since Series60 3.0
        * @param aNsUri is the XML namespace of this fragment
        * @param aLocalName is the XML localname of this fragment
        * @param aQName is the qualifiedname of this fragment
        * @param aAttrs are the XML attributes of this fragment
        * Leave codes:  
        *       KErrSenInvalidCharacters if aLocalName or aQName contains
        *       illegal characters.     
        *       KErrSenZeroLengthDescriptor if aLocalName or aQName is zero length.
        */
        IMPORT_C static CSenDomFragment* NewL(const TDesC8& aNsUri,
                                              const TDesC8& aLocalName,
                                              const TDesC8& aQName,
                                              const RAttributeArray& aAttrs);

        /**
        * Basic constructor.
        * @since Series60 3.0
        * @param aNsUri is the XML namespace of this fragment
        * @param aLocalName is the XML localname of this fragment
        * @param aQName is the qualifiedname of this fragment
        * @param aAttrs are the XML attributes of this fragment
        * @param aParent is the parent XML element of this fragment
        * Leave codes:  
        *       KErrSenInvalidCharacters if aLocalName or aQName contains
        *       illegal characters.     
        *       KErrSenZeroLengthDescriptor if aLocalName or aQName is zero length.
        */
        IMPORT_C static CSenDomFragment* NewL(const TDesC8& aNsUri,
                                              const TDesC8& aLocalName,
                                              const TDesC8& aQName,
                                              const RAttributeArray& aAttrs,
                                              CSenElement& aParent);

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CSenDomFragment();

        // New functions
    
        /**
        * Initiates the parsing chain where new delegate will be created with
        * given parameters and parsing will be delegated to it. Should not be
        * called externally.
        * @since Series60 3.0
        * @param aNsUri     The namespace URI of the new element
        * @param aLocalName The local name of the new element
        * @param aQName     The qualified name of the new element
        * @param aAttrs     The attributes of the new element
        */
        IMPORT_C virtual void ExpandL(const TDesC8& aNsUri,
                                      const TDesC8& aLocalName,
                                      const TDesC8& aQName,
                                      const RAttributeArray& aAttrs);
                                      
        // Functions from base classes

        // From CSenBaseFragment
        
        /**
        * Resumes the parsing. Usually called by the delegate fragment which was
        *                       parsing itself after DelegateParsingL().
        * @since Series60 3.0
        * @param aNsUri     The namespace URI of the current element
        * @param aLocalName The local name of the current element
        * @param aQName     The qualified name of the current element
        */
        IMPORT_C void ResumeParsingFromL(const TDesC8& aNsUri,
                                         const TDesC8& aLocalName,
                                         const TDesC8& aQName);

        /**
        * Sets the reader for this fragment and sets this to be the 
        * content handler of the following SAX events.
        * @since Series60 3.0
        * @param aReader:   Reader to be used.
        */
        IMPORT_C virtual void ParseWithL(CSenXmlReader& aReader);

        /**
        * Sets the attributes for the fragment.
        * @since Series60 3.0
        * @param aAttrs the array of attributes.
        */
        IMPORT_C virtual void SetAttributesL(const RAttributeArray& aAttrs);

    protected:  
        
        /**
        * C++ default constructor.
        */
        IMPORT_C CSenDomFragment();

        /**
        * "ConstructL" method for calling the base classes ones.
        * @since Series60 3.0
        * @param aElement is the XML element of this fragment.
        */
        IMPORT_C void BaseConstructL(const CSenElement& aElement);

        /**
        * "ConstructL" method for calling the base classes ones.
        * @since Series60 3.0
        * @param aLocalName The local name of the element
        */
        IMPORT_C void BaseConstructL(const TDesC8& aLocalName);

        /**
        * "ConstructL" method for calling the base classes ones.
        * @since Series60 3.0
        * @param aNsUri     The namespace URI of the element
        * @param aLocalName The local name of the element
        */
        IMPORT_C void BaseConstructL(const TDesC8& aNsUri,
                                     const TDesC8& aLocalName);

        /**
        * "ConstructL" method for calling the base classes ones.
        * @since Series60 3.0
        * @param aNsUri     The namespace URI of the element
        * @param aLocalName The local name of the element
        * @param aQName     The qualified name of the element
        */
        IMPORT_C void BaseConstructL(const TDesC8& aNsUri,
                                     const TDesC8& aLocalName,
                                     const TDesC8& aQName);

        /**
        * "ConstructL" method for calling the base classes ones.
        * @since Series60 3.0
        * @param aNsUri     The namespace URI of the element
        * @param aLocalName The local name of the element
        * @param aQName     The qualified name of the element
        * @param aAttrs     The attributes of the element
        */
        IMPORT_C void BaseConstructL(const TDesC8& aNsUri,
                                     const TDesC8& aLocalName,
                                     const TDesC8& aQName,
                                     const RAttributeArray& aAttrs);

        /**
        * "ConstructL" method for calling the base classes ones.
        * @since Series60 3.0
        * @param aNsUri     The namespace URI of the element
        * @param aLocalName The local name of the element
        * @param aQName     The qualified name of the element
        * @param aAttrs     The attributes of the element
        * @param aParent    The parent of the element
        */
        IMPORT_C void BaseConstructL(const TDesC8& aNsUri,
                                     const TDesC8& aLocalName,
                                     const TDesC8& aQName,
                                     const RAttributeArray& aAttrs,
                                     CSenElement& aParent);

        /**
        * "ConstructL" method for calling the base classes ones.
        * @since Series60 3.0
        * @param aReader is the XML reader for this fragment.
        */
        IMPORT_C void BaseConstructL(CSenXmlReader& aReader);
        
        // Functions from base classes
        
        /**
         *  Callback functions which implement the XML content handler interface.
         *  Inheriting classes can override these.
         */
         
        // From CSenBaseFragment 
        
        /**
        * @since Series60 3.0
        * @param aNsUri     The namespace URI of the element
        * @param aLocalName The local name of the element
        * @param aQName     The qualified name of the element
        * @param aAttrs     The attributes of the element
        */
        IMPORT_C virtual void StartElementL(const TDesC8& aNsUri,
                                            const TDesC8& aLocalName,
                                            const TDesC8& aQName,
                                            const RAttributeArray& aAttrs);
        
        /**
        * Callback functions which implement the XML content handler interface.
        * This one is called when content is starting.
        * @since Series60 3.0
        * @param aChars     The content characters.
        * @param aStart     The starting index
        * @param aLength    The length of the characters.
        */
        IMPORT_C virtual void CharactersL(const TDesC8& aChars,TInt aStart,TInt aLength);

        /**
        * Overriding content writing from CSenBaseFragment to do nothing in
        * DOM fragment (because the tree is expanded).
        * @since Series60 3.0
        * @param aNsUri     not used
        * @param aLocalName not used
        * @param aQName     not used
        * @param aAttrs     not used
        */
        IMPORT_C void WriteStartElementL(const TDesC8& aNsUri,
                                         const TDesC8& aLocalName,
                                         const TDesC8& aQName,
                                         const RAttributeArray& aAttrs);

        /**
        * Overriding content writing from CSenBaseFragment to do nothing in
        * DOM fragment (because the tree is expanded).
        * @since Series60 3.0
        * @param aNsUri     not used
        * @param aLocalName not used
        * @param aQName     not used
        */
        IMPORT_C void WriteEndElementL(const TDesC8& aNsUri,
                                       const TDesC8& aLocalName,
                                       const TDesC8& aQName);

    protected: // Data
        CSenDomFragment* ipDomDelegate;
    };

#endif //SEN_DOM_FRAGMENT_H

// End of File



