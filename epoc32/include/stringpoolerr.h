// StringPoolErr.h
//
// Copyright (c) Symbian Ltd. 2001
//

#ifndef __STRINGPOOLERR_H
#define __STRINGPOOLERR_H

#include <e32std.h>
#include <e32base.h>

class StringPoolPanic
/**
@internalComponent
*/
	{
public:
	enum TStringPoolPanic
		{
		EComparisonBetweenTwoStringPoolsNotAllowed=0,// We are trying to compare a string from one string pool to a string from another string pool
		EIllegalUseOfNullString,
		ECreatingStringWithWrongCase,
        EStringNotTableEntry,
        EStringTableNotFound
		};
	static void Panic(TStringPoolPanic aPanic);
	};

inline void StringPoolPanic::Panic(StringPoolPanic::TStringPoolPanic aPanic)
	{
	_LIT(KStringPoolPanic,"StringPool");
	User::Panic(KStringPoolPanic,aPanic);
	}

// __STRINGPOOLERR_H
#endif

