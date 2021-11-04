/*
* ==============================================================================
*  Name        : xmlengdocumentfragment.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Document fragment node functions
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

#ifndef XMLENGINE_DOCUMENTFRAGMENT_H_INCLUDED
#define XMLENGINE_DOCUMENTFRAGMENT_H_INCLUDED

#include "xmlengnode.h"



/** 
 * Instance of TXmlEngDocumentFragment class represents an document fragment of the DOM tree.
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class TXmlEngDocumentFragment : public TXmlEngNode
{
public:
    /** 
     * Default constructor
     *
     * @since S60 v3.1
     */
	inline TXmlEngDocumentFragment();

protected:
	/** 
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal Document fragment pointer
     */
	inline TXmlEngDocumentFragment(void* aInternal);
};

#include "xmlengdocumentfragment.inl"

#endif /* XMLENGINE_DOCUMENTFRAGMENT_H_INCLUDED */

