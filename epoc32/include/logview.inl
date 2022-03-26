// LOGVIEW.INL
// 
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

//**********************************
// CLogView
//**********************************

inline const CLogEvent& CLogView::Event() const
/** Returns details of the log event at the current position within the view.

@return A reference to the log event details object. If a view does not contain 
any events, then the content of this object is undefined. */
	{
	return *iEvent;
	}

inline TBool CLogView::IsValid() const
	{
	return iValid;
	}

//**********************************
// CLogViewRecent
//**********************************

inline TLogRecentList CLogViewRecent::RecentList() const
/** Gets the recent event list number that identifies the recent event list to 
which the current entry belongs. This is an asynchronous request.

Note that this function is only useful if KLogNullRecentList is passed to 
the SetRecentListL() functions.

@return The recent event list number. */
	{
	return iCurrentList;
	}

//**********************************
// CLogViewDuplicate
//**********************************

inline TLogId CLogViewDuplicate::Source() const
/** Returns the unique ID of the event for which all the events in this view are 
duplicates.

@return The unique event ID. */
	{
	return iSourceId;
	}
