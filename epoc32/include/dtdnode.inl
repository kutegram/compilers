// DTDNODE.INL
// Copyright (C) Symbian LTD, 1999
//
// DTD nodes inline functions
//



//*******************************************************************
// DTD Node
//*******************************************************************/

inline CDTDNode::CDTDNode() : CBNFNode(0)
	{
	}

/** Destructor. */
inline CDTDNode::~CDTDNode()
	{
	}

/** Allocates and constructs a new parentless node.

@return New DTD node
*/
inline CDTDNode* CDTDNode::NewL()
	{
	CTypedNode<TInt,const TDesC*>* aNode = CTypedNode<TInt,const TDesC*>::NewL( 0, 0 );
	return REINTERPRET_CAST(CDTDNode*,aNode);
	}

/** Adds the completed attribute to the node. */
inline void CDTDNode::AddCompletedAttributeL()
	{
	AddAttributeL(CompletedAttrID(),NULL);
	}

