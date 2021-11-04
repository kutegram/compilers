/*
* ==============================================================================
*  Name        : xmlengnode.inl
*  Part of     : XMLEngine / DOM Xpath C++ Wrapper
*  Description : Node functions implementation
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

inline TXmlEngNode::TXmlEngNode()
        : iInternal(NULL) {}

inline TXmlEngNode::TXmlEngNode(void* aInternal)
        : iInternal(aInternal) {}

inline TBool TXmlEngNode::IsNull() const
    {return iInternal == NULL;}

inline TBool TXmlEngNode::NotNull() const
    {return iInternal != NULL;}

// ------------------------------------------------------------------------
// Compares nodes.
//
// The nodes are the same if they are referring to the same in-memory
// data structure. 
// ------------------------------------------------------------------------
//
inline TBool TXmlEngNode::IsSameNode(TXmlEngNode aOther) const
    {return iInternal == aOther.iInternal;}

// ------------------------------------------------------------------------
// Moves the node to another part of the tree or another document
// The node is unliked from current postion (if any) and appended
// to the its new parent.
//
// @note 
// In many cases this method call should be followed by ReconcileNamespacesL() on the moved node
// ------------------------------------------------------------------------
//
inline TXmlEngNode TXmlEngNode::MoveTo(TXmlEngNode aParent)
    {return aParent.AppendChildL(Unlink());}

inline TXmlEngAttr& TXmlEngNode::AsAttr() const                    
    {return *reinterpret_cast<TXmlEngAttr*>(const_cast<TXmlEngNode*>(this));}

inline TXmlEngElement&     TXmlEngNode::AsElement() const                    
    {return *reinterpret_cast<TXmlEngElement*>(const_cast<TXmlEngNode*>(this));}

inline TXmlEngTextNode& TXmlEngNode::AsText() const    
    {return *reinterpret_cast<TXmlEngTextNode*>(const_cast<TXmlEngNode*>(this));}

inline TXmlEngBinaryContainer& TXmlEngNode::AsBinaryContainer() const    
    {return *reinterpret_cast<TXmlEngBinaryContainer*>(const_cast<TXmlEngNode*>(this));}

inline TXmlEngChunkContainer& TXmlEngNode::AsChunkContainer() const    
    {return *reinterpret_cast<TXmlEngChunkContainer*>(const_cast<TXmlEngNode*>(this));}   

inline TXmlEngFileContainer& TXmlEngNode::AsFileContainer() const    
    {return *reinterpret_cast<TXmlEngFileContainer*>(const_cast<TXmlEngNode*>(this));} 

inline TXmlEngDataContainer& TXmlEngNode::AsDataContainer() const    
    {return *reinterpret_cast<TXmlEngDataContainer*>(const_cast<TXmlEngNode*>(this));}      

inline TXmlEngNamespace& TXmlEngNode::AsNamespace() const
    {return *reinterpret_cast<TXmlEngNamespace*>(const_cast<TXmlEngNode*>(this));}

inline TXmlEngComment& TXmlEngNode::AsComment() const        
    {return *reinterpret_cast<TXmlEngComment*>(const_cast<TXmlEngNode*>(this));}

inline TXmlEngCDATASection& TXmlEngNode::AsCDATASection()    const
    {return *reinterpret_cast<TXmlEngCDATASection*>(const_cast<TXmlEngNode*>(this));}


inline TXmlEngEntityReference& TXmlEngNode::AsEntityReference() const
    {return *reinterpret_cast<TXmlEngEntityReference*>(const_cast<TXmlEngNode*>(this));}

inline TXmlEngProcessingInstruction& TXmlEngNode::AsProcessingInstruction() const
    {return *reinterpret_cast<TXmlEngProcessingInstruction*>(const_cast<TXmlEngNode*>(this));}

