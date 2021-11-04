/*
* ==============================================================================
*  Name        : xmlengnodelist.h 
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Node list inline functions
*  Version     : %version: 2 % 
*
*  Copyright © 2006-2006 Nokia. All rights reserved.
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

#ifndef XMLENGINE_NODELIST_H_INCLUDED
#define XMLENGINE_NODELIST_H_INCLUDED

#include "xmlengnode.h"
#include "xmlengnodelist_impl.h"



/**
 * Template implements list container.
 *
 * List may contain different types of nodes.
 * Node pointer is casted to specify node type when
 * is returned by Next() method.
 *
 * @lib XmlEngineDOM.lib
 * @since S60 v3.2
 */
template<class T> 
class RXmlEngNodeList
{
public:
    /**
     * Get list length.
     *
     * @since S60 v3.2
     * @return Number of nodes in a node list
     */
	inline TInt Count() const;

    /**
     * Checks whether next node exists in a node list
     *
     * @since S60 v3.2
     * @return TRUE if next node exists, FALSE otherwise
     */
	inline TBool HasNext() const;

    /**
     * Retrieves next node from a node list
     *
     * @since S60 v3.2
     * @return Next node 
     */
	inline T Next();

    /**
     * Closes a node list
     *
     * @since S60 v3.2
     */
	inline void Close();

private:
    friend class TXmlEngNode;
    friend class TXmlEngElement;

    /*
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

    /** List with nodes */
	RXmlEngNodeListImpl iList;
};

/**
 * Template implements list container for nodes.
 *
 * Specialization for trivial case: list of TXmlEngNode objects
 * No "thin wrapper" pattern needed, operate directly on NodeListImpl
 *
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
template<>
class RXmlEngNodeList<TXmlEngNode>: public RXmlEngNodeListImpl {};



#include "xmlengnodelist.inl"

#endif /* XMLENGINE_NODELIST_H_INCLUDED */
