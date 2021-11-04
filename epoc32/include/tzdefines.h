// TZDEFINES.H
//
// Copyright (c) 1997-2007 Symbian Software Ltd. All rights reserved.
//
#ifndef __TZDEFINES_H__
#define __TZDEFINES_H__

/** Time Zone Rule Day Rules.
@publishedAll

*/
enum TTzRuleDay
	{
	ETzFixedDate			= 0,	// e.g. 11th October
	ETzDayAfterDate,				// e.g. first Sunday after 8th October
	ETzDayBeforeDate,				// e.g. Sunday before 7th October
	ETzDayInLastWeekOfMonth			// e.g. last Sunday in October
	};

/**
this const must match the last TTzRuleDay enumeration;
'int' is deliberately used because this file is shared with non Symbian C++ environments 
@internalComponent
*/
const int KValidatedLastDayRule = ETzDayInLastWeekOfMonth;

/** Time reference.
@publishedAll

*/
enum TTzTimeReference
	{
	ETzUtcTimeReference	= 0,
	ETzStdTimeReference,
	ETzWallTimeReference	// Local time
	};

/**
this const must match the last TTzTimeReference enumeration 
'int' is deliberately used because this file is shared with non Symbian C++ environments 
@internalComponent
*/
const int KValidatedLastTimeReference = ETzWallTimeReference;
#endif
