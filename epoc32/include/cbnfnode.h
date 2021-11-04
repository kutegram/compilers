// CBNFNODE.H
// Copyright (c) Symbian Software Ltd 1999-2007. All rights reserved.
//
// BNF node header
//

#ifndef __CBNFNODE_H__
#define __CBNFNODE_H__

#include <e32base.h>
#include <cnode.h>

/** Declares that the "type" for node attributes is stored as a string. */
typedef const TDesC* CBNFNodeAttributeType;

#define _SHAREDSTRING(X) IMPORT_C static CBNFNodeAttributeType K##X();
#define _SHAREDSTRINGBODY(X) EXPORT_C CBNFNodeAttributeType CBNFNode::K##X() \
    { \
    _LIT(K##X, #X); \
    return &(K##X); \
    }


class CBNFNode : public CTypedNode<TInt, const TDesC*> 
/** Backus-Naur Form (BNF) node that forms part of a BNF tree (CBNFParser).

Node types are stored as TInts, and attribute types as descriptors.
@publishedAll

*/
{
public:
	//##ModelId=3B666BC70146
	IMPORT_C ~CBNFNode();

	//##ModelId=3B666BC70144
	IMPORT_C static CBNFNode* NewL(TInt aType);

    _SHAREDSTRING(PreRuleCallback)
    _SHAREDSTRING(PostRuleCallback)
    _SHAREDSTRING(Reference)
    _SHAREDSTRING(RangeStart)
    _SHAREDSTRING(RangeEnd)
    _SHAREDSTRING(NMoreCount)
    _SHAREDSTRING(NMoreMinimum)
    _SHAREDSTRING(NMoreMaximum)

protected:
    IMPORT_C CBNFNode(TInt aType);
};

// __CBNFNODE_H__
#endif
