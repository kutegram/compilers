// 
// WAPlog.h
//
//  Copyright (c) Symbian Software Ltd 1997-2007.  All rights reserved.
//
// Comments: WAP Logging public header, defines the name of the 
//			 file to use for WAP activity logging messages
// 

#if !defined(__WAPLOG_H__)
#define __WAPLOG_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#ifdef _DEBUG
/**
@publishedAll
@deprecated
*/
_LIT(KWapLogFileName,"WAPLog.html");
#define __LOG_WAP_FILE_NAME KWapLogFileName
#else
#define __LOG_WAP_FILE_NAME
#endif

#endif
