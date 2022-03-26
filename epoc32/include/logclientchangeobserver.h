// LOGCLIENTCHANGEOBSERVER.H
//
// Copyright (c) 2002-2007 Symbian Ltd.  All rights reserved.
//
#ifndef __LOGCLIENTCHANGEOBSERVER_H__
#define __LOGCLIENTCHANGEOBSERVER_H__

// System includes
#include <logwrap.h>

/**
Constants
@internalComponent
*/
const TUid KLogClientChangeEventLogCleared = { 0x101F8C4F };
const TUid KLogClientChangeEventRefreshView = { 0x1020601B }; 

/** 
This class allows a client of the log engine to observe specific change 
events within a given view.
@publishedAll 

*/
class MLogClientChangeObserver
	{
public:
	/** Handle a global change within the logs database
	
	This method is called when a generic event occurs within the log database. 
	Such events are	not specific to a view (see MLogViewChangeObserver for view 
	specific events).
	
	@param aChangeType The uid corresponding to the type of event which 
	occurred.
	@param aChangeParam1 A context-specific change paramater which can be 
	interpreted	based on the change type.
	@param aChangeParam2 A context-specific change paramater which can be 
	interpreted based on the change type.
	@param aChangeParam3 A context-specific change paramater which can be 
	interpreted	based on the change type.
	
	A list of change types and their associated parameters follows:
	
	KLogClientChangeEventLogCleared - no parameters. This event occurs when 
	the log database is cleared.	 
	KLogClientChangeEventRefreshView - no parameters. This event occurs when 
	the client needs to refresh their view. For example, this occurs after the
	log database has been restored from a backup. */
	virtual void HandleLogClientChangeEventL(TUid aChangeType, TInt aChangeParam1, TInt aChangeParam2, TInt aChangeParam3) = 0;

private:
	IMPORT_C virtual void MLogClientChangeObserver_Reserved1();
	IMPORT_C virtual void MLogClientChangeObserver_Reserved2();
	};


#endif
