// DelimitedParserCommon.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

/**
	@file DelimitedParserCommon.h
	Comments :
	@publishedAll
	
 */

#ifndef __DELIMITEDPARSERCOMMON_H__
#define __DELIMITEDPARSERCOMMON_H__

// System includes
//
#include <e32base.h>

/**
enum TDelimitedDataParseMode
Enum defining the modes for the delimited data parser.
@publishedAll


*/
enum TDelimitedDataParseMode
	{
	/** 
		Unparsed soecifier 
	*/
	EDelimitedDataNotParsed = 0,
	/** 
		Specifier for parsing from left to right  
	*/
	EDelimitedDataForward,
	/** 
		Specifier for parsing from right to left  
	*/
	EDelimitedDataReverse
	};

// __DELIMITEDPARSERCOMMON_H__
#endif

