// CNoDeleteAttribute.h
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved. 
//

#ifndef __CNODELETEATTRIBUTE_H__
#define __CNODELETEATTRIBUTE_H__

// System includes
//
#include <e32base.h>



template <class T>
class CNoDeleteAttributeT : public CBase
/**
    @publishedAll
    
*/
	{
public:

	CNoDeleteAttributeT(T aAttribute) : iAttribute(aAttribute) {};
	~CNoDeleteAttributeT() {};

	T Attribute() { return iAttribute; }
	void SetAttribute(T aAttribute) { iAttribute = aAttribute; }

protected:

	T iAttribute;

	};

// __CNODELETEATTRIBUTE_H__
#endif
