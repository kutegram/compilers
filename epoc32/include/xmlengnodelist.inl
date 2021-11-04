/*
* ============================================================================
*  Name        : xmlengnodelist.inl 
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Description : Node list inline functions
*  Version     : %version: 3 % 
*
*  Copyright © 2006-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/



// -----------------------------------------------------------------------------
// Retrieves number of items in node list
// -----------------------------------------------------------------------------
//
template<class T> inline TInt RXmlEngNodeList<T>::Count() const
    {
    return iList.Count();
    }
    
// -----------------------------------------------------------------------------
// Returns true if this node has next sibling, false otherwise.
// -----------------------------------------------------------------------------
//
template<class T> inline TBool RXmlEngNodeList<T>::HasNext() const
    {
    return iList.HasNext();
    }    

// -----------------------------------------------------------------------------
// Retrieves next node
// -----------------------------------------------------------------------------
//
template<class T> inline T RXmlEngNodeList<T>::Next()
    {
    TXmlEngNode t = iList.Next(); 
    return *(static_cast<T*>(&t));
    }

// -----------------------------------------------------------------------------
// Closes node list
// -----------------------------------------------------------------------------
//
template<class T> inline void RXmlEngNodeList<T>::Close()
    {
    iList.Close();
    }

// -----------------------------------------------------------------------------
// Opens node list
// -----------------------------------------------------------------------------
//
template<class T> inline void RXmlEngNodeList<T>::OpenL( 
			void* aHead,
			TXmlEngNode::TXmlEngDOMNodeType aType,
			const TDesC8&	aName,
			const TDesC8&	aNs) 
    {
    iList.OpenL(aHead, aType, aName, aNs);    
    }

// -----------------------------------------------------------------------------
// Opens node list
// -----------------------------------------------------------------------------
//
template<class T> inline void RXmlEngNodeList<T>::Open( 
			void* aHead,
			TXmlEngNode::TXmlEngDOMNodeType aType)
    {
    iList.Open(aHead, aType);    
    }

