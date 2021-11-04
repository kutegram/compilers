/*
* ==============================================================================
*  Name        : xmlengentityreference.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Entity reference node functions
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

#ifndef XMLENGINE_ENTITYREFERENCE_H_INCLUDED
#define XMLENGINE_ENTITYREFERENCE_H_INCLUDED

#include "xmlengnode.h"


/** 
 * Instance of TXmlEngEntityReference class represents an XML entity reference in the DOM tree.
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class TXmlEngEntityReference : public TXmlEngNode
{
public:
	/** 
     * Default constructor
     *
     * @since S60 v3.1
     */
	inline TXmlEngEntityReference();

protected:
	/** 
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal Entity reference pointer
     */
	inline TXmlEngEntityReference(void* aInternal);
};

#include "xmlengentityreference.inl"

#endif /* XMLENGINE_ENTITYREFERENCE_H_INCLUDED */

