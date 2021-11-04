// calcommon.h
//
// Copyright (c) Symbian Software Ltd 2005. All rights reserved.
//

#ifndef __CALCOMMON_H__
#define __CALCOMMON_H__

#include <caltime.h>

typedef TUint32 TCalLocalUid;
typedef TInt64 TCalFileId;

/** Utility class containing common calendar-related  enums.

@publishedAll

*/
class CalCommon
	{
public:

	/** Entry filter used in the entry view and instance view, filter flags are defined by TCalViewFilterFlags
	@publishedAll
	
	*/
	typedef TUint TCalViewFilter;
	
	/** Entry filter flags used in the entry view and instance view. 
	@publishedAll
	
	*/
	enum TCalViewFilterFlags	
		{
		/** Include timed appointments. */
		EIncludeAppts=0x01,				
		/** Include appointments which only have a start time. */	
		EIncludeReminder=0x02,				
		/** Include all-day events. */
		EIncludeEvents=0x04,				
		/** Include anniversaries. */
		EIncludeAnnivs=0x08,				
		/** Include completed todos. */
		EIncludeCompletedTodos=0x10,					
		/** Include incompleted todos. */
		EIncludeIncompletedTodos=0x20,	
		/** Remove non-alarmed entries. This flag cannot be used by itself. */
		EIncludeAlarmedOnly=0x40,
		/** Include next only instance of a repeat entry. */
		EIncludeRptsNextInstanceOnly=0x80,
		/** Include all entries (appointments, day events, anniversaries and todos). */
		EIncludeAll=EIncludeAppts|EIncludeReminder|EIncludeEvents|EIncludeAnnivs|
		EIncludeCompletedTodos|EIncludeIncompletedTodos,
		};
		
	/** The range of instances referred to in a recurrence ID or instance view. 
	@publishedAll
	
	*/
	enum TRecurrenceRange
		{
		/** Only this instance is referenced. */
		EThisOnly,
		/** This and all other instances are referenced. */
		EThisAndAll,
		/** This and all future instances are referenced. */
		EThisAndFuture,
		/** This and all previous instances are referenced. */
		EThisAndPrior
		};
		
	
	/** Search filter for use in the CCalInstanceView::FindInstanceL() function.
	@publishedAll
	
	*/
	enum TCalSearchBehaviour
		{
		/** Search for folded text. */
		EFoldedTextSearch=0x0,
		/** Search for the exact text. */
		EExactTextSearch=0x1,
		};
		
	/** Class to implement a time range in the Instance view and Entry view.
	@publishedAll
	
	*/	
	class TCalTimeRange
		{
	public:
		IMPORT_C TCalTimeRange(TCalTime aStartTime, TCalTime aEndTime);		
			
		IMPORT_C TCalTime StartTime() const;
		IMPORT_C TCalTime EndTime() const;
	private:
		TCalTime iStartTime;
		TCalTime iEndTime;
		};
		
	};
// __CALCOMMON_H__
#endif
