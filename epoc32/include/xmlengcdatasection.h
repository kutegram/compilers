/*
* ==============================================================================
*  Name        : xmlengcdatasection.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : CDATASection node functions
*  Version     : %version: 2 %
*
*  Copyright © 2004-2005 Nokia. All rights reserved.
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

#ifndef XMLENGINE_CDATASECTION_H_INCLUDED
#define XMLENGINE_CDATASECTION_H_INCLUDED

#include "xmlengtext.h"

/** 
 * Instance of TXmlEngCDATASection class represents an XML CDATASection in the DOM tree.
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class TXmlEngCDATASection : public TXmlEngTextNode
{
public:
    /** 
     * Default constructor
     */
	inline TXmlEngCDATASection();

    
protected:
    /** 
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal CDATASection pointer
     */
	inline TXmlEngCDATASection(void* aInternal);
};



#include "xmlengcdatasection.inl"

#endif /* XMLENGINE_CDATASECTION_H_INCLUDED */
