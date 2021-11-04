// localtypes.h
//
// Copyright (c) 2000-2007 By Symbian Software Ltd. All Rights Reserved.
//

/**
 @file
 Contains local type declarations for ezlib library
 @publishedAll
 
*/

#ifndef _LOCAL_TYPES_H_
#define _LOCAL_TYPES_H_

#include <e32std.h>
#include <e32base.h>

#ifndef NULL
#define NULL 0
#endif

typedef TUint8	TByte;
typedef TUint8 	TUtf8;
typedef TUint32	TOffset;

typedef TText16	TUnicode;

const TInt kNoError = 0;
const TInt kError	= -1;

#endif /* !_LOCAL_TYPES_H_*/

