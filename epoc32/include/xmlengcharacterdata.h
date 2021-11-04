/*
* ==============================================================================
*  Name        : xmlengcharacterdata.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : All text nodes functions
*  Version     : %version: 2 %
*
*  Copyright © 2004-2006 Nokia. All rights reserved.
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

#ifndef XMLENGINE_CHARACTERDATA_H_INCLUDED
#define XMLENGINE_CHARACTERDATA_H_INCLUDED

#include "xmlengnode.h"

/**
* Instance of TXmlEngCharacterData class represents all kinds of XML text nodes 
* (i.e. text node, comment node) in the DOM tree.
*
* Describe DOM action for nodes that contains text data.
* DOM spec: 
* http://www.w3.org/TR/2004/REC-DOM-Level-3-Core-20040407/core.html#ID-FF21A306
*
* @lib XmlEngineDOM.lib
* @since S60 v3.1
*/
class TXmlEngCharacterData : public TXmlEngNode
{
public:

    /**
     * Get content of the node.
     *
     * @since S60 v3.1
     * @return String with nodes content
     * 
     * This method applies to TXmlEngCDATASection, TXmlEngComment and TXmlEngTextNode nodes.
     */
    IMPORT_C TPtrC8 Contents() const;
    
    /**
     * Sets contents of basic character nodes: TXmlEngTextNode, TXmlEngComment, TXmlEngCDATASection
     *
     * @since S60 v3.1
     * @param aNewContents  The actual value to store
     * 
     * The input is taken as non-escaped: for example, 
     * aNewContents = "123 > 34 && P" will be serialized as "123 &gt; 34 &amp;&amp; P"
     * 
     * Escaped contents may be set only for TXmlEngElement and TXmlEngAttr nodes.
     * @see TXmlEngAttr::SetEscapedValueL(const TDesC8&), TXmlEngElement::SetEscapedTextL(const TDesC8&), 
     */
    IMPORT_C void SetContentsL(const TDesC8& aNewContents);

    /**
     * Extends the contents of the node by appending aString
     *
     * @since S60 v3.1
     * @param aString Content to be added to current content
     */
    IMPORT_C void AppendContentsL(const TDesC8& aString);

    /**
     * Get length of the content
     *
     * @since S60 v3.1
     * @return Number of characters in the contents
     */
    IMPORT_C TUint Length() const;

protected:
    /**
     * Default constructor
	 *
     * @since S60 v3.1
     */
	inline TXmlEngCharacterData(); // protected from API users

    /**
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal node pointer
     */
	inline TXmlEngCharacterData(void* aInternal);
};


#include "xmlengcharacterdata.inl"

#endif /* XMLENGINE_CHARACTERDATA_H_INCLUDED */

