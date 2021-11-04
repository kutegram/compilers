// e32\include\e32debug.h
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

#ifndef __E32DEBUG_H__
#define __E32DEBUG_H__
#include <e32std.h>			// TThreadId

/**	@publishedPartner
	@removed
*/
const TInt KMaxProfiles=64;

/**	@publishedPartner
	@removed
*/
class TProfile
    {
public:
    TInt iTime;
    TInt iCount;
    };
//

/**	@publishedPartner
	
*/
class RDebug
	{
public:
    IMPORT_C static void Printf(const char*, ...);
    IMPORT_C static void RawPrint(const TDesC8& aDes);
    IMPORT_C static TInt Print(TRefByValue<const TDesC> aFmt,...);
    IMPORT_C static void RawPrint(const TDesC16& aDes);
	};

#endif

