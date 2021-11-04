// calnotification.h
//
// Copyright (c) Symbian Software Ltd 2005. All rights reserved.
//

#ifndef __CALNOTIFICATION_H__
#define __CALNOTIFICATION_H__

/** The calendar publish and subscribe category
@publishedAll


*/
const TUid KCalPubSubCategory = { 0x10003a5b };

/** Used for subcribing to either todos or event changes
@publishedAll

*/
enum TCalPubSubValues
	{
	/** subscribe to todo notifications */
	ECalPubSubTodoNotification,
	/** subscribe to event notifications */
	ECalPubSubEventNotification,
	};
	
/** The publish and subscribe data 
@publishedAll

*/
struct TCalPubSubData
	{
	/** The time that the calendar change took place, in universal (UTC) time */
	TTime iTimeOfChangeUtc;
	/** The filename hashed into a 4-byte integer. CalInterimAPI provides a method to find the filename from this value. */
	TUint32 iFileNameHash;
	};

// __CALNOTIFICATION_H__
#endif

