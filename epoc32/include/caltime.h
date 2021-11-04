// caltime.h
//
// Copyright (c) Symbian Software Ltd 2005. All rights reserved.
//

#ifndef __CALTIME_H__
#define __CALTIME_H__

#include <e32base.h>

/** Represents a date/time, as used in the Calendar API.

This stores a single TTime, which may be set in UTC or local or floating local 
time, and can be retrieved in either UTC or system local time.

There are references to null time throughout the Interim API - this means Time::NullTTime().

@publishedAll

*/
NONSHARABLE_CLASS(TCalTime)
	{
public:

	/** The time mode for a calendar time
	@publishedAll
	
	*/
	enum TTimeMode
		{
		/** Floating time. */
		EFloating,
		/** Fixed time in UTC format. */
		EFixedUtc,
		/** Fixed time in local time with time zone reference format. */
		EFixedTimeZone
		};

public:
	IMPORT_C TCalTime();
	
	IMPORT_C void SetTimeLocalFloatingL(const TTime& aLocalTime);
	IMPORT_C void SetTimeUtcL(const TTime& aUtcTime);
	IMPORT_C void SetTimeLocalL(const TTime& aLocalTime);
	IMPORT_C TTimeMode TimeMode() const; 
	IMPORT_C TTime TimeUtcL() const;
	IMPORT_C TTime TimeLocalL() const;
	
	IMPORT_C static TTime MaxTime();
	IMPORT_C static TTime MinTime();
private:
	TTime	iTime;
	TUint8	iTimeMode;  
	TInt8	iReserved1;
	TInt16 	iReserved2;
	};
	
// __CALTIME_H__
#endif
