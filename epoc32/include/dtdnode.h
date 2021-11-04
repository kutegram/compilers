// DTDNODE.H
// Copyright (c) Symbian Software Ltd 1999-2007. All rights reserved.
//
// DTD node header
//

#if !defined(__CDTDNODE_H__)
#define __CDTDNODE_H__

#include <e32base.h>
#include <cbnfnode.h>

class CDTDNode : public CBNFNode
/**
Document Type Definition (DTD) node that forms part of a DTD tree.
@publishedAll

*/
{
public:
	//##ModelId=3B66675300CE
	inline ~CDTDNode();

	//##ModelId=3B66675300CD
	static inline CDTDNode* NewL();
	//##ModelId=3B66675300CC
	inline void AddCompletedAttributeL();

	//##ModelId=3B66675300C4
	const TDesC* CompletedAttrID();

	enum{ // attribute IDs start at -6000
		KCompletedAttrID = -6000
	};
private:
	//##ModelId=3B66675300C3
	inline CDTDNode();
};


#include <dtdnode.inl>

// __CDTDNODE_H__
#endif
