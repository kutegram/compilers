// CALENTRY.H
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#ifndef __CALENTRY_H__
#define __CALENTRY_H__

#include <e32base.h>
#include <caltime.h>
#include <calcommon.h>

class CCalAlarm;
class CCalAttendee;
class CCalCategory;
class CCalEntryImpl;
class CCalUser;
class CTzRules;
class TCalRRule;
class CCalEntryIdImpl;

/** Class representing a calendar entry. This can be an appointment, to-do
item, reminder, event or anniversary.

CCalEntry contains information about a calendar entry, including
a repeat definition, synchronisation information, and group scheduling data.

A repeating calendar entry has more than one occurrence. Instances are
represented by the CCalInstance class.

Synchronisation information includes a record of the date/time the entry was
last modified. This can be found by calling the LastModifiedDateL() function.

@publishedAll

*/
NONSHARABLE_CLASS(CCalEntry) : public CBase
	{
public:
	/** Defines the type of the calendar entry.
	@publishedAll
	
	*/
	enum TType
		{
		/** An appointment, which has a start time and end time. */
		EAppt,
		/** A to-do, which can have a start time and end time (the end time is the due date), or can be undated. */
		ETodo,
		/** An event, which has a start time and end time. */
		EEvent,
		/** A reminder, which has a start time only. */
		EReminder,
		/** An anniversary, which has a start time and end time. */
		EAnniv
		};

	/** Defines the possible status values of the entry.
	@publishedAll
	
	*/
	enum TStatus
		{
		/** The entry is tentative. */
		ETentative,
		/** The entry has been confirmed. */
		EConfirmed,
		/** The entry has been cancelled. */
		ECancelled,
		/** The to-do entry needs action. */
		ETodoNeedsAction,
		/** The to-do entry has been completed. */
		ETodoCompleted,
		/** The to-do entry is in progress. */
		ETodoInProcess,
		/** No Status is Set */
		ENullStatus
		};

	/** Replication status.
	@publishedAll
	
	*/
	enum TReplicationStatus
		{
		/** No restriction on access. */
		EOpen,
		/** Data is private (no access). */
		EPrivate,
		/** Data is confidential (restricted access). */
		ERestricted
		};

	/** The method property of a Group Scheduling entry.
	@publishedAll
	
	*/
	enum TMethod
		{
		/** The RFC2445-defined method value 'None'. */
		EMethodNone,
		/** The RFC2445-defined method value 'Publish'. */
		EMethodPublish,
		/** The RFC2445-defined method value 'Request'. */
		EMethodRequest,
		/** The RFC2445-defined method value 'Reply'. */
		EMethodReply,
		/** The RFC2445-defined method value 'Add'. */
		EMethodAdd,
		/** The RFC2445-defined method value 'Cancel'. */
		EMethodCancel,
		/** The RFC2445-defined method value 'Refresh'. */
		EMethodRefresh,
		/** The RFC2445-defined method value 'Counter'. */
		EMethodCounter,
		/** The RFC2445-defined method value 'DeclineCounter'. */
		EMethodDeclineCounter
		};

	/** Specify which entry details are to be copied in CCalEntry::CopyFromL functions.
	@publishedAll
	
	*/
	enum TCopyType
		{
		/** Copy the ID of the entry */
		ECopyAll,
		/** Dont copy ID of the entry */
		EDontCopyId
		};

	// Construction / Destruction
	IMPORT_C static CCalEntry* NewL(TType aType, HBufC8* aUid, TMethod aMethod, TUint aSeqNum);
	IMPORT_C static CCalEntry* NewL(TType aType, HBufC8* aUid, TMethod aMethod, TUint aSeqNum,
					const TCalTime& aRecurrenceId, CalCommon::TRecurrenceRange aRange);

	IMPORT_C ~CCalEntry();

	// Date and Time
	IMPORT_C TCalTime StartTimeL() const;
	IMPORT_C TCalTime EndTimeL() const;
	IMPORT_C void SetStartAndEndTimeL(const TCalTime& aStartTime, const TCalTime& aEndTime);

	IMPORT_C void SetLastModifiedDateL();
	IMPORT_C TCalTime LastModifiedDateL() const;

	IMPORT_C void SetDTStampL(const TCalTime& aTime);
	IMPORT_C TCalTime DTStampL() const;

	IMPORT_C TCalTime CompletedTimeL() const;
	IMPORT_C void SetCompletedL(TBool aCompleted, const TCalTime& aTime);

	// Repeat rules / RDate / ExDate Methods
	IMPORT_C void SetRRuleL(const TCalRRule& aRule);
	IMPORT_C TBool GetRRuleL(TCalRRule& aRule) const;

	IMPORT_C void SetRDatesL(const RArray<TCalTime>& aRDateList);
	IMPORT_C void GetRDatesL(RArray<TCalTime>& aRDateList) const;

	IMPORT_C void SetExceptionDatesL(const RArray<TCalTime>& aExDateList);
	IMPORT_C void GetExceptionDatesL(RArray<TCalTime>& aExDateList) const;

	IMPORT_C void ClearRepeatingPropertiesL();

	// Entry alarm
	IMPORT_C void SetAlarmL(CCalAlarm* aAlarm);
	IMPORT_C CCalAlarm* AlarmL() const;

	// Comparison
	IMPORT_C TBool CompareL(const CCalEntry& aEntry) const;

 	// Copy
 	IMPORT_C void CopyFromL(const CCalEntry& aOther);
	IMPORT_C void CopyFromL(const CCalEntry& aOther, TCopyType aCopyType);

	// Text Fields
	IMPORT_C void SetSummaryL(const TDesC& aSummary);
	IMPORT_C const TDesC& SummaryL() const;
	IMPORT_C void SetDescriptionL(const TDesC& aDescription);
	IMPORT_C const TDesC& DescriptionL() const;
	IMPORT_C void SetLocationL(const TDesC& aLocation);
	IMPORT_C const TDesC& LocationL() const;

	// Category list
	IMPORT_C void AddCategoryL(CCalCategory* aCategory);
	IMPORT_C void DeleteCategoryL(TInt aIndex);
	IMPORT_C const RPointerArray<CCalCategory>& CategoryListL();

	//	Attendee Methods
	IMPORT_C void AddAttendeeL(CCalAttendee* aAttendee);
	IMPORT_C void DeleteAttendeeL(TInt aIndex);
	IMPORT_C RPointerArray<CCalAttendee>& AttendeesL() const;
	IMPORT_C void SetOrganizerL(CCalUser* aUser);
	IMPORT_C CCalUser* OrganizerL() const;
	IMPORT_C void SetPhoneOwnerL(const CCalUser* aOwner);
	IMPORT_C CCalUser* PhoneOwnerL() const;

	// Other Attributes
	IMPORT_C TType EntryTypeL() const;
	IMPORT_C void SetStatusL(TStatus aStatus);
	IMPORT_C TStatus StatusL() const;

	IMPORT_C void SetReplicationStatusL(TReplicationStatus aReplicationStatus);
	IMPORT_C TReplicationStatus ReplicationStatusL() const;

	IMPORT_C void SetPriorityL(TUint aPriority);
	IMPORT_C TUint PriorityL() const;

	IMPORT_C void SetMethodL(TMethod aMethod);
	IMPORT_C TMethod MethodL() const;
	IMPORT_C void SetSequenceNumberL(TInt aSeq);
	IMPORT_C TInt SequenceNumberL() const;
	IMPORT_C const TDesC8& UidL() const;
	IMPORT_C TCalTime RecurrenceIdL() const;
	IMPORT_C CalCommon::TRecurrenceRange RecurrenceRangeL() const;

	IMPORT_C CTzRules* TzRulesL() const;
	IMPORT_C void SetTzRulesL(const CTzRules& aTzRule);
	IMPORT_C void SetTzRulesL();

	IMPORT_C void SetLocalUidL(TCalLocalUid aLocalId);
	IMPORT_C TCalLocalUid LocalUidL() const;

public:
	// Internal APIs
	static CCalEntry* NewL(CCalEntryImpl* aImpl);
	CCalEntryImpl* Impl() const;

private:
	void ConstructL(TType aType, HBufC8* aUid, TMethod aMethod, TUint aSeqNum,
					const TTime& aRecurrenceId, CalCommon::TRecurrenceRange aRange);
	void ConstructL(CCalEntryImpl* aImpl);

private: // member data
	CCalEntryImpl* iImpl;
	};


/** Class representing a uniquely identifiable calendar entry in a calendar file.

@publishedAll

*/
NONSHARABLE_CLASS(CCalEntryId) : public CBase
	{
public:
	IMPORT_C static CCalEntryId* NewL(TDesC8* aFlatData);
	IMPORT_C ~CCalEntryId();
	IMPORT_C TPtrC8 IdL();
	IMPORT_C TPtrC StoreFileNameL();
	IMPORT_C TCalTime RecurrenceIdL();
	IMPORT_C TCalTime InstanceTimeL() const;
	IMPORT_C TCalLocalUid LocalUidL() const;
private:
	CCalEntryId();
private:
	CCalEntryIdImpl* iImpl;
	};

// __CALENTRY_H__
#endif

