// calInstanceView.h
//
// Copyright (c) Symbian Software Ltd 2005. All rights reserved.
//
#ifndef __CALINSTANCEVIEW_H__
#define __CALINSTANCEVIEW_H__

#include <e32std.h>
#include <e32base.h>

#include <calentry.h>
#include <calentryview.h>
#include <calcommon.h>

class CCalInstance;
class CCalInstanceViewImpl;
class CCalSession;
class MCalProgressCallBack;
class TCalTime;

/** View class for accessing instances of calendar entries.

Once a session to a calendar file has been created, a view to the session
can be created.

An instance is a calendar entry, a repeated instance of a calendar entry, 
or an RDate added to an entry.

This view can be used to search for instances and also to delete instances.

@publishedAll

*/
NONSHARABLE_CLASS(CCalInstanceView) : public CBase
    {	
public:

	/** Parameter struct for storing search data.
	This contains a descriptor to store search text and an enum to describe the text search behaviour.

	@publishedAll
	
	*/
	class TCalSearchParams
		{
	public:
		IMPORT_C TCalSearchParams(const TDesC& aText, CalCommon::TCalSearchBehaviour aBehaviour);
		IMPORT_C const TDesC& Text() const;
		IMPORT_C CalCommon::TCalSearchBehaviour Behaviour() const;
	
	private:
		TPtrC iSearchText;
		CalCommon::TCalSearchBehaviour iSearchBehaviour;
		};
		
	IMPORT_C static CCalInstanceView* NewL(CCalSession& aSession, MCalProgressCallBack& aProgressCallBack);
	IMPORT_C ~CCalInstanceView();
	
	IMPORT_C void FindInstanceL(RPointerArray<CCalInstance>& aInstanceList, 
					   			CalCommon::TCalViewFilter aCalViewFilter, 
					   			const CalCommon::TCalTimeRange& aTimeRange) const;
	
	IMPORT_C void FindInstanceL(RPointerArray<CCalInstance>& aMatchedInstanceList,
								CalCommon::TCalViewFilter aCalViewFilter, 
								const CalCommon::TCalTimeRange& aTimeRange, 
								const TCalSearchParams& aSearchParams) const;
					   
	IMPORT_C void DeleteL(CCalInstance* aInstance, CalCommon::TRecurrenceRange aWhichInstances);
								
	IMPORT_C TCalTime NextInstanceL(CalCommon::TCalViewFilter aCalViewFilter, const TCalTime& aStartDate) const;
	IMPORT_C TCalTime PreviousInstanceL(CalCommon::TCalViewFilter aCalViewFilter, const TCalTime& aStartDate) const;
	
private:
	CCalInstanceView();
	void ConstructL(CCalSession& aSession, MCalProgressCallBack& aProgressCallBack);
	
private: 
	CCalInstanceViewImpl* iImpl;
	};
	
// __CALINSTANCEVIEW_H__
#endif
