// CNTSYNC.H
//
// Copyright (c) Symbian Software Ltd 2001-2005.  All rights reserved.
//

#ifndef __CNTSYNC_H__
#define __CNTSYNC_H__


#include <e32base.h>
#include <cntdef.h>

class CContactICCEntry;
class MContactSynchroniser
/** 
Abstract interface for a contacts phonebook synchroniser.

It should be inherited by classes which implement the phonebook 
synchroniser API. The plug-in should have a second UID of 
0x101F4A6E (KUidContactSynchroniserDll).

@internalAll
*/
	{
public:
	/**
	@internalAll
	*/
	enum TValidateOperation
		{
		ERead,		/** Check a cached ICC contact can be read */
		ESearch,	/** Check a cached ICC contact can be searched */
		EEdit		/** Check a cached ICC contact can be edited */
		};
public:
	/*
	A CContactICCEntry is wanted for read/search or edit.
	*/
	virtual TInt ValidateContact(TValidateOperation aOp, TContactItemId aId) = 0;
	/*
	A CContactICCEntry has being added/edited.
	*/
	virtual TInt ValidateWriteContact(CContactICCEntry& aContactItem) = 0;
	/*
	A CContactICCEntry is being deleted from the database.
	*/
	virtual TInt DeleteContact(TContactItemId aId) = 0;
	/*
	Release resources used by Phonebook Synchroniser. Called prior to unloading plug-in.
	*/
	virtual void Release() = 0;
	/*
	A new CContactICCEntry has been added to the database. 
	(Called after ValidateWriteContact() and database write has completed.)
	*/
	virtual void UpdatePostWriteL(const CContactICCEntry& aContactItem) = 0;

	/*
	Id of template contact for specified phonebook
	*/
	virtual TContactItemId ICCTemplateIdL(TUid aPhonebookUid) = 0;

	/*
	Id of contact group for specified phonebook
	*/
	virtual TContactItemId GroupIdL(TUid aPhonebookUid) = 0;

	/*
	Request notifiction of Synchronisation state changes for specified phonebook
	*/
	virtual void NotifySyncStateChange(TRequestStatus& aStatus, TUid aPhonebookUid) = 0;
	/*
	Cancel notification of Synchronisation state changes for specified phonebook
	*/
	virtual void CancelNotifyRequest(TUid aPhonebookUid) = 0;
	/*
	Test Synchronisation state changes for specified phonebook
	*/
	virtual TBool IsSynchronisedL(TUid aPhonebookUid) = 0;

	/*
	List of Phonebooks supported by Phonebook Synchroniser that may be present on the ICC.
	*/
	virtual TInt PhonebookList(RArray<TUid>& aPhonebookList) = 0;

private:
	IMPORT_C virtual void MContactSynchroniser_Reserved_1();
	};
	

/** The UID for the default phone book synchroniser ECom plugin interface
*/
const TUid KUidEcomCntPhBkSyncInterface = {0x102035FD};
	
class CContactSynchroniser : public CBase, public MContactSynchroniser
/** 
Abstract interface for a ECom contacts phonebook synchroniser plugin

It should be inherited by classes which implement the phonebook 
synchroniser API in a platform secured environment. The ECom plug-in interface uid is 
KUidEcomCntPhBkSyncInterface
@internalAll
*/
	{
public:
	// From MContactSynchroniser
	virtual TInt ValidateContact(TValidateOperation aOp, TContactItemId aId) = 0;
	virtual TInt ValidateWriteContact(CContactICCEntry& aContactItem) = 0;
	virtual TInt DeleteContact(TContactItemId aId) = 0;
	virtual void Release() = 0;
	virtual void UpdatePostWriteL(const CContactICCEntry& aContactItem) = 0;
	virtual TContactItemId ICCTemplateIdL(TUid aPhonebookUid) = 0;
	virtual TContactItemId GroupIdL(TUid aPhonebookUid) = 0;
	virtual void NotifySyncStateChange(TRequestStatus& aStatus, TUid aPhonebookUid) = 0;
	virtual void CancelNotifyRequest(TUid aPhonebookUid) = 0;
	virtual TBool IsSynchronisedL(TUid aPhonebookUid) = 0;
	virtual TInt PhonebookList(RArray<TUid>& aPhonebookList) = 0;
public:
	static CContactSynchroniser* NewL();
	IMPORT_C virtual ~CContactSynchroniser();
private:
	TUid iDtor_ID_Key;
	};

#endif
