/*
* ============================================================================
*  Name        : xmlengnamespace.inl 
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Description : Namespace node functions
*  Version     : %version: 2 % 
*
*  Copyright © 2004-2006 Nokia.  All rights reserved.
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
// Default constructor
// -----------------------------------------------------------------------------
//
inline TXmlEngNamespace::TXmlEngNamespace():TXmlEngNode(NULL)
    {
    }
    
// -----------------------------------------------------------------------------
// Workaround to avoid misuse of TXmlEngNode::NamespaceUri() method, which should not 
// be applied to TXmlEngNamespace node. Since the name of the inherited method from 
// TXmlEngNode is too similar to TXmlEngNamespace::Uri(), NamespaceUri() is disabled for 
// direct use. 
//		
// If NamespaceUri() is called on the TXmlEngNamespace object that is downcasted to 
// TXmlEngNode, then NamespaceUri()'s result equals to result of Uri() method.
// -----------------------------------------------------------------------------
//
inline TPtrC8 TXmlEngNamespace::NamespaceUri()
    {
    return KNullDesC8();
    }    

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
//
inline TXmlEngNamespace::TXmlEngNamespace(void* aPtr):TXmlEngNode(aPtr)
    {
    }
    
