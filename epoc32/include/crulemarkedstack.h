// CRuleMarkedStack.h
//
// Copyright (c) Symbian Software Ltd 2000-2007. All rights reserved.
//

// A speciales marked stack specifically for PARSE rules.
// Allows a rule stack to merge rules upto a given mark type.

#ifndef __CRULEMARKEDSTACK_H__
#define __CRULEMARKEDSTACK_H__


// includes
#include <e32base.h>
#include <cmarkedstack.h>
#include <cbnfnode.h>

#pragma warning (disable : 4127) // conditional expression is constant


template <TBool StackOwnsEntry>
class CRuleMarkedStack : public CMarkedStack<CBNFNode, StackOwnsEntry>
/**	
@publishedAll

*/
	{
public:
	void MergeToMarkL(TInt aMarkType);
	};

#include <crulemarkedstack.inl>

#pragma warning ( default : 4127 ) // conditional expression is constant

// __CRULEMARKEDSTACK_H__
#endif
