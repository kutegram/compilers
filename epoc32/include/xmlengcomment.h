/*
* ==============================================================================
*  Name        : xmlengcomment.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Comment node functions
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

#ifndef XMLENGINE_COMMENT_H_INCLUDED
#define XMLENGINE_COMMENT_H_INCLUDED

#include "xmlengcharacterdata.h"

/** 
 * Instance of TXmlEngComment class represents an XML comments in the DOM tree.
 * 
 * DOM spec: http://www.w3.org/TR/2004/REC-DOM-Level-3-Core-20040407/core.html#ID-FF21A306
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class TXmlEngComment : public TXmlEngCharacterData
{
public:
    /** 
     * Default constructor
     *
     * @since S60 v3.1
     */
    inline TXmlEngComment();

protected:
    /** 
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal Comment pointer
     */
    inline TXmlEngComment(void* aInternal);
};

#include "xmlengcomment.inl"

#endif /* XMLENGINE_COMMENT_H_INCLUDED */
