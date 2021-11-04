// BITBASE.H
//
// Copyright (c) 1997-2004 Symbian Ltd.  All rights reserved.
//

#ifndef __BITBASE_H__
#define __BITBASE_H__

#include <gdi.h>

/**
@internalComponent
*/
class TSpriteBase
	{
public:
	virtual void Hide(const TRect& aRect,const TRegion* aRegion)=0;
	virtual void Reveal(const TRect& aRect,const TRegion* aRegion)=0;
	};

#endif

