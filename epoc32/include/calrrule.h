// CALRRULE.H
//
// Copyright (c) Symbian Software Ltd 2005. All rights reserved.
//
#ifndef __CALRRULE_H__
#define __CALRRULE_H__

#include <e32base.h>
#include <caltime.h>

/** Class representing iCal repeat types.

This supports the following standard iCal properties:
- FREQ (rule type), 
- DTSTART (start date), 
- UNTIL (end date), 
- COUNT (number of instances),
- INTERVAL (interval between instances), 
- BYDAY, 
- BYMONTHDAY, 
- BYYEARDAY, 
- WKST (start day of week).

Note that the repeat rule type (FREQ) must be set before any of the following 
properties can be set, since their behaviour is dependent on the rule type:
BYDAY, BYMONTHDAY, BYYEARDAY

The WKST parameter is only significant in weekly repeat rules with an interval of 
greater than 1.

The repeat rule type may not be changed once it has been set.

@publishedAll

*/
NONSHARABLE_CLASS(TCalRRule)
	{
public:
	/** Types of repeat rule. 
	
	@publishedAll
	
	*/	
	enum TType 
		{
		/** The type has not yet been defined. */
		EInvalid=0,
		/** Rule which repeats based on a number of days. */
		EDaily,
		/** Rule which repeats based on a number of weeks. */
		EWeekly,
		/** Rule which repeats based on a number of months. */
		EMonthly,
		/** Rule which repeats based on a number of years. */
		EYearly,
		};
		
	/** Class to represent a weekday within a month.
	
	Valid values of iWeekInMonth are 1, 2, 3, 4 for the 1st, 2nd, 3rd and 4th week of 
	the month, or -1 for the last week of the month.

	For example:
	The 3rd Wednesday would have iDay = EWednesday and iWeekInMonth = 3.
	The last Sunday would have iDay = ESunday and iWeekInMonth = -1.
	
	@publishedAll
	
	*/
	class TDayOfMonth
		{
	public:
		IMPORT_C TDayOfMonth(TDay aDay, TInt8 aWeekInMonth);
		IMPORT_C TDay Day() const;
		IMPORT_C TInt8 WeekInMonth() const;
	private:
		TDay iDay;
		TInt8 iWeekInMonth;
		};
	
	IMPORT_C TCalRRule();
	IMPORT_C TCalRRule(TType aType);
	
	IMPORT_C void SetType(TType aType);
	IMPORT_C TType Type() const;
	
	IMPORT_C void SetDtStart(const TCalTime& aTime);
	IMPORT_C TCalTime DtStart() const;
		
	IMPORT_C void SetUntil(const TCalTime& aTime);
	IMPORT_C TCalTime Until() const;
	
	IMPORT_C void SetCount(TUint aCount);
	IMPORT_C TUint Count() const;
	
	IMPORT_C void SetInterval(TInt aInterval);
	IMPORT_C TInt Interval() const;
	
	IMPORT_C void SetByDay(const RArray<TDay>& aDays); 
	IMPORT_C void GetByDayL(RArray<TDay>& aDays) const;
	
	IMPORT_C void SetByDay(const RArray<TDayOfMonth>& aDays); 
	IMPORT_C void GetByDayL(RArray<TDayOfMonth>& aDays) const;

	IMPORT_C void SetByMonthDay(const RArray<TInt>& aMonthDays);
	IMPORT_C void GetByMonthDayL(RArray<TInt>& aMonthDays) const;

	IMPORT_C void SetByMonth(const RArray<TMonth> aMonths);
	IMPORT_C void GetByMonthL(RArray<TMonth>& aMonths) const;

	IMPORT_C void SetWkSt(TDay aDay);
	IMPORT_C TDay WkSt() const;

	void SetUntilAndCount(const TCalTime& aTime, TUint aCount);

private:
	void InitialiseData();

	TUint MapToBitsWeekdays(TDay aDay);
	
	TBool GetNthBit(TUint aNum) const;
	void SetNthBit(TUint aNum);
		
private:
	TUint64	iBuffer; 	// stores BYDAY/BYMONTHDAY
	TCalTime iDtStart;
	TCalTime iUntil;
	TInt32  iReserved;
	TInt32  iReserved2;
	TInt	iCount;
	TDay	iWkSt;
	TType	iType;
	TUint8	iInterval;
	};

// __CALRRULE_H__
#endif
