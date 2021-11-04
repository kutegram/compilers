/*
* ==============================================================================
*  Name        : XmlEngNodeList_impl.h 
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Node list implementation functions
*  Version     : %version: 3 % 
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

#ifndef XMLENGINE_NODELIST_IMPL_H_INCLUDED
#define XMLENGINE_NODELIST_IMPL_H_INCLUDED

#include <e32def.h>
#include "xmlengnode.h"

/** 
 * Class implements list container.
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.2
 */
class RXmlEngNodeListImpl
{
public:

    /**
     *  Default constructor
     *
     * @since S60 v3.2
     */
    IMPORT_C RXmlEngNodeListImpl();

    /** 
     * Closes node list
     *
     * @since S60 v3.2
     */
    IMPORT_C void Close();

    /** 
     * Get list length.
     *
     * @since S60 v3.2
     * @return Number of nodes in a node list
     */
    IMPORT_C TInt  Count() const;

    /** 
     * Checks whether next node exists in a node list
     *
     * @since S60 v3.2
     * @return TRUE if next node exists, FALSE otherwise
     */
    IMPORT_C TBool HasNext() const;

    /** 
     * Retrieves next node from a node list
     *
     * @since S60 v3.2
     * @return Next node 
     */
    IMPORT_C TXmlEngNode Next();

    /** 
     * Opens node.
     *
     * @since S60 v3.2
     * @param aHead node pointer to the node from which the searching 
            of list elements is started
     * @param aType type of list elements
     * @param aName name of list elements 
     * @param aNs namespace of list elements
     *
     * @note If aType is NULL, aName and aNs are ignored
     */
    void OpenL( 
			void* aHead,
			TXmlEngNode::TXmlEngDOMNodeType aType,
			const TDesC8&	aName = KNullDesC8,
			const TDesC8&	aNs = KNullDesC8);

    /** 
     * Opens node.
     *
     * @since S60 v3.2
     * @param aHead node pointer to the node from which the searching 
            of list elements is started
     * @param aType type of list elements
     */
    void Open( 
			void* aHead,
			TXmlEngNode::TXmlEngDOMNodeType aType);

private:

    void* FindNextNode(void* aCurrentNode) const;

    void*	        iCurrentNode;
	TInt		    iType;  // NodeType:4 bits (0-3) & MatchName flag (bit 4)
	unsigned char*	iName;
	unsigned char*	iNsUri;
};

TBool StrEqualOrNull(const void* aStr1, const void* aStr2);
			


#endif /* XMLENGINE_NODELIST_IMPL_H_INCLUDED */
