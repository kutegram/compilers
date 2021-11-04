// caluser.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//
#ifndef __CALUSER_H__
#define __CALUSER_H__

#include <e32base.h>

class CCalUserImpl;

/** Class representing a calendar user.

A calendar user is the base class representation of a meeting participant.
It contains attributes common to all calendar users.

Contains methods to store and retrieve a user's ADDRESS, SENT-BY and CN
fields.

@publishedAll

*/
NONSHARABLE_CLASS(CCalUser) : public CBase
	{
public:
	IMPORT_C static CCalUser* NewL(const TDesC& aAddress);
	IMPORT_C static CCalUser* NewL(const TDesC& aAddress, const TDesC& aSentBy);
	IMPORT_C ~CCalUser();

	IMPORT_C void SetCommonNameL(const TDesC& aCommonName);
	IMPORT_C const TDesC& Address() const;
	IMPORT_C const TDesC& CommonName() const;
	IMPORT_C const TDesC& SentBy() const;
public:
	static CCalUser* NewL(CCalUserImpl* aImpl);

	CCalUserImpl* Impl() const;
protected:
	CCalUser();
	CCalUser(CCalUserImpl* aImpl);
	void ConstructL(const TDesC& aAddress);
	void ConstructL(const TDesC& aAddress, const TDesC& aSentBy);
protected:
/** Handle to CCalUser implementation */
	CCalUserImpl*	iImpl;
	};


/** Class representing an attendee of an event.

CCalAttendee is a specialization of the CCalUser class.

This class contains extra methods to store and retrieve an Attendee's
ROLE, PART-STAT, and RSVP fields.

@publishedAll

*/
NONSHARABLE_CLASS(CCalAttendee) : public CCalUser
	{
public:
	/** Attendee's role
	@publishedAll
	
	*/
	enum TCalRole
		{
		/** A required participant of the event. */
		EReqParticipant=0,
		/** An optional participant of the event. */
		EOptParticipant,
		/** A non-participant of the event. */
		ENonParticipant,
		/** This participant will chair the event. */
		EChair
		};

	/** Attendee's status
	@publishedAll
	
	*/
	enum TCalStatus
		{
		/** Action is required by attendee. */
		ENeedsAction=0,
		/** Attendee has accepted request. */
		EAccepted,
		/** Attendee has tentatively accepted the request. */
		ETentative,
		/** Attendee's presence is confirmed. */
		EConfirmed,
		/** Attendee has declined request. */
		EDeclined,
		/** The required action has been completed by attendee. */
		ECompleted,
		/** Attendee has delegated the request to another person. */
		EDelegated,
		/**	A to-do action in the process of being completed. */
		EInProcess
		};

public:
	IMPORT_C static CCalAttendee* NewL(const TDesC& aAddress);
	IMPORT_C static CCalAttendee* NewL(const TDesC& aAddress, const TDesC& aSentBy);

	IMPORT_C void SetRoleL(TCalRole aRole);
	IMPORT_C void SetStatusL(TCalStatus aStatus);
	IMPORT_C void SetResponseRequested(TBool aRsvp);

	IMPORT_C TCalRole RoleL() const;
	IMPORT_C TCalStatus StatusL() const;
	IMPORT_C TBool ResponseRequested() const;
public:
	static CCalAttendee* NewL(CCalUserImpl* aImpl);
private:
	CCalAttendee();
	CCalAttendee(CCalUserImpl* aImpl);
	};


// __CALUSER_H__
#endif

