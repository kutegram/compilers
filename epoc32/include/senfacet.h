/*
* ==============================================================================
*  Name        : SenFacet.h
*  Part of     : Web Services Description
*  Interface   : 
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

#ifndef SEN_FACET_H
#define SEN_FACET_H

// INCLUDES
#include <SenBaseElement.h>

// CONSTANTS
_LIT8(KSenFacet,        "Facet");
_LIT8(KFacetAttrName,   "name");
_LIT8(KFacetAttrType,   "type");

// CLASS DECLARATION
class CSenFacet : public CSenBaseElement
    {
    public:
        
        /**
        * Basic constructor.
        */
        IMPORT_C static CSenFacet* NewL();

        /**
        * Basic constructor.
        * @param    aCopiedSource   source to copy facet data from.
        */
        IMPORT_C static CSenFacet* NewL(CSenElement& aCopiedSource);

        /**
        * Basic constructor.
        * @param aNsUri     The namespace URI of the new element
        * @param aLocalName The local name of the new element
        * @param aQName     The qualified name of the new element
        * @param aAttributes    The attributes of the new element
        * Leave codes:  
        *       KErrSenInvalidCharacters if aLocalName or aQName contains
        *       illegal characters.     
        *       KErrSenZeroLengthDescriptor if aLocalName or aQName is zero length.
        */
        IMPORT_C static CSenFacet* NewL(const TDesC8& aNsUri,
                                        const TDesC8& aLocalName,
                                        const TDesC8& aQName,
                                        const RAttributeArray& aAttributes);

        IMPORT_C virtual ~CSenFacet();

        // New functions
        
        /**
        * Setter for name.
        * @param aName  the name to be set.
        */
        IMPORT_C virtual void SetNameL(const TDesC8& aName);

        /**
        * Setter for type.
        * @param aType  the type to be set.
        */
        IMPORT_C virtual void SetTypeL(const TDesC8& aType);

        /**
        * Setter for value.
        * @param aValue the value to be set.
        */
        IMPORT_C virtual void SetValueL(const TDesC8& aValue);

        /**
        * Getter for name.
        * @return the name of the facet
        */
        IMPORT_C virtual TPtrC8 Name();

        /**
        * Getter for type.
        * @return the type of the facet
        */
        IMPORT_C virtual TPtrC8 Type();
    
        /**
        * Getter for value.
        * @return the value of the facet
        */
        IMPORT_C virtual TPtrC8 Value();

    protected:
        
        /**
        * C++ default constructor.
        */
        IMPORT_C CSenFacet();
        
        /**
        * By default Symbian 2nd phase constructors are private.
        */
        IMPORT_C void ConstructL(const TDesC8& aLocalName);
        IMPORT_C void ConstructL(CSenElement& aCopiedSource);
        IMPORT_C void ConstructL(const TDesC8& aNsUri,
                                 const TDesC8& aLocalName,
                                 const TDesC8& aQName,
                                 const RAttributeArray& aAttributes);
    };

#endif // SEN_FACET_H

// End of File
