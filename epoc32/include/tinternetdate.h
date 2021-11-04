// tinternetdate.h
//
// Copyright (c) Symbian Software Ltd 2002-2007. All rights reserved.
//

/**
	@file tinternetdate.h
	Comments :	This file contains the class TInternetDate
	
	@publishedAll
	
*/
  

#ifndef		__TINTERNETDATE_H__
#define		__TINTERNETDATE_H__

#include <e32std.h>

/**
Stores dates in universal time and provides parsing of internet style dates 
into TDateTime and RFC 1123 (updates RFC 822) dates.

Supports parsing of the following date formats:
Sun, 06 Nov 1994 08:49:37 GMT  ; RFC 822, updated by RFC 1123
Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036
Sun Nov  6 08:49:37 1994       ; ANSI C's asctime() format

All dates are store relative to Universal Time and not local time. 

@publishedAll


*/
class TInternetDate
	{
public:	
/** 
	Enum defining internet date formats.
	@publishedAll
	
	
 */
	enum TInternetDateFormat
		{
		/** 
			Rfc 1123 Compliant date format 
		*/
		ERfc1123Format
		};

	inline TInternetDate();


	inline TInternetDate(TDateTime aUniversalTime);

	IMPORT_C void SetDateL(const TDesC8& aDate);

	IMPORT_C const TDateTime& DateTime();

	IMPORT_C HBufC8* InternetDateTimeL(TInternetDateFormat aInternetDateFormat);

private:
	/**
	A date and time object
	*/
	TDateTime iDateTime;
	};


/**
	Intended Usage:	Default Constructor. Used when setting dates that are in a text format using SetDateL
	
	
*/
inline TInternetDate::TInternetDate()
	{}

/**
	Intended Usage:	Constructor. Used when setting a date that you later want parsed into an internet text format
	
	
	@param			aUniversalTime	a time that should correspond to Universal Time.
*/
inline TInternetDate::TInternetDate(TDateTime aUniversalTime) :
	iDateTime(aUniversalTime)
	{}


//	__TINTERNETDATE_H__
#endif
