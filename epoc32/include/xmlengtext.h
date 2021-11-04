/*
* ==============================================================================
*  Name        : xmlengtext.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Text node functions
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

#ifndef XMLENGINE_TEXT_H_INCLUDED
#define XMLENGINE_TEXT_H_INCLUDED

#include "xmlengcharacterdata.h"



/**
 * The TXmlEngTextNode interface inherits from TXmlEngCharacterData and represents the textual content 
 * (termed "character data" in XML) of an Element or TXmlEngAttr. 
 *
 * If there is no markup inside an element's content, the text is contained in a single object 
 * of the TXmlEngTextNode interface that is the only child of the element. If there is markup, 
 * it is parsed into the information items (elements, comments, etc.) and TXmlEngTextNode nodes that 
 * form the list of children of the element.
 * 
 * When a document is first made available via the DOM, there is only one TXmlEngTextNode node for each 
 * block of text. Users may create adjacent TXmlEngTextNode nodes that represent the contents of a given 
 * element without any intervening markup, but should be aware that there is no way to 
 * represent the separations between these nodes in XML or HTML, so they will not (in general) 
 * persist between DOM editing sessions. 
 * 
 * No lexical check is done on the content of a TXmlEngTextNode node and, depending on its position in 
 * the document, some characters must be escaped during serialization using character references; 
 * e.g. the characters "<&" if the textual content is part of an element or of an attribute, 
 * the character sequence "]]>" when part of an element, the quotation mark character " or 
 * the apostrophe character ' when part of an attribute. 
 * 
 * <b>DOM Level 3 spec:</b>
 * <p>http://www.w3.org/TR/2004/REC-DOM-Level-3-Core-20040407/core.html#ID-1312295772
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class TXmlEngTextNode : public TXmlEngCharacterData
{
public:
    /**
     * Default constructor
     *
     * @since S60 v3.1
     */
	inline TXmlEngTextNode();

    /**
     * Check if element content is whitespace.
     *
     * @since S60 v3.1
     * @return TRUE if is only whitespace
     */
    IMPORT_C TBool IsElementContentWhitespace() const;

protected:
    /**
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal Text node pointer
     */
    inline TXmlEngTextNode(void* aInternal);
};



#include "xmlengtext.inl"

#endif /* XMLENGINE_TEXT_H_INCLUDED */
