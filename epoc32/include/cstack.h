// CStack.h
//
// Copyright (c) Symbian Software Ltd 2000-2007. All rights reserved.
//

// A template class to provide a classic stack like interface & functionality
// The entries on the stack are owned (i.e. deleted) by the stack if the 
// StackOwnsEntry argument is ETrue

#ifndef __CSTACK_H__
#define __CSTACK_H__

#include <e32base.h>

#pragma warning (disable : 4127) // conditional expression is constant


/**	
	@file
	@publishedAll
	
*/


template <class T, TBool StackOwnsEntry>
class CStack : /*protected CArrayPtrSeg<T>*/ public CArrayPtrSeg<T>
	{
public:
	inline CStack();
	inline ~CStack();

	inline void Clear();		
	inline TBool IsEmpty() const;
	inline void PushL(T* aItem);
	inline T* Pop();
	inline T* Head() const;
	inline T* Last() const;		
	};

#include <cstack.inl>

#pragma warning ( default : 4127 ) // conditional expression is constant

// __CSTACK_H__
#endif
