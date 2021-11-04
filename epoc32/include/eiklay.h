// EIKLAY.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKLAY_H__
#define __EIKLAY_H__

#include <frmtlay.h>

class TAvkonEditorCustomWrap : public MFormCustomWrap
	{
public:
	enum
		{
		EAvkSpaceLineBreakClass=MTmCustom::ELineBreakClasses, // 29
		EAvkLineBreakClasses
		};

public:
	// overrides of line break functions from MFormCustomWrap
	TUint LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const;
	TBool LineBreakPossible(TUint aPrevClass,TUint aNextClass,TBool aHaveSpaces) const;
	};

#endif // __EIKLAY_H__
