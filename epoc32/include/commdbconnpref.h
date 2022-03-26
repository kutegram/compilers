// Copyright (c) Symbian Software Ltd. 2006-2007.  All rights reserved.
//
// commdbconnpref.h
//

/**
@file
@deprecated since v9.1. Functionality is replaced with commsdat.
*/

#if !(defined COMMDBCONNPREF_H)
#define COMMDBCONNPREF_H

#include <connpref.h>
#include <cdbcols.h>

/**
Constant for storing Major Version Number
@internalTechnology
*/
const TInt8 KMajorVersionNumber = 8;

/**
Constant for storing Minor Version Number
*/
const TInt8 KMinorVersionNumber = 0;

/**
Constant for storing Build Version Number
*/
const TInt16 KBuildVersionNumber = 1;


/**
@internalTechnology
*/
struct SCommDbConnPref
	{
	TUint32 iIapId;
	TUint32 iNetId;
	TCommDbDialogPref iDialogPref;
	TCommDbConnectionDirection iDirection;
	TUint32 iBearerSet;
	};

class TCommDbConnPref : public TConnPref
/**
@publishedAll

*/
	{
	friend class TCommDbMultiConnPref;
public:
	IMPORT_C TCommDbConnPref();
	IMPORT_C static TVersion Version();

	IMPORT_C void SetIapId(TUint32 aIapId);
	IMPORT_C TUint32 IapId() const;

	IMPORT_C void SetNetId(TUint32 aNetId);
	IMPORT_C TUint32 NetId() const;

	IMPORT_C void SetDialogPreference(TCommDbDialogPref aDialogPref);
	IMPORT_C TCommDbDialogPref DialogPreference() const;

	IMPORT_C void SetDirection(TCommDbConnectionDirection aDirection);
	IMPORT_C TCommDbConnectionDirection Direction() const;

	IMPORT_C void SetBearerSet(TUint32 aBearerSet);
	IMPORT_C TUint32 BearerSet() const;

	IMPORT_C virtual TInt Compare(const TCommDbConnPref& aPref) const;
	inline TBool operator==(const TCommDbConnPref& aPref) const;
	inline TBool operator!=(const TCommDbConnPref& aPref) const;

	inline static TCommDbConnPref& Cast(const TConnPref& aPref);

protected:
	inline SCommDbConnPref* PrefPtr() const;
	};

/**
@internalTechnology
*/
const TInt KMaxMultiConnPrefCount = 2;

/**
@internalTechnology
*/
struct SCommDbMultiConnPref
	{
	TInt iNumAttempts;
	struct SCommDbConnPref iPrefs[KMaxMultiConnPrefCount];
	};

class TCommDbMultiConnPref : public TConnPref
/**
@publishedAll

*/
	{
public:
	IMPORT_C TCommDbMultiConnPref();
	IMPORT_C static TVersion Version();

	IMPORT_C TInt SetPreference(TInt aIndex, const TCommDbConnPref& aPref);
	IMPORT_C TInt GetPreference(TInt aIndex, TCommDbConnPref& aPref);

	IMPORT_C void SetConnectionAttempts(TInt aNumAttempts);
	IMPORT_C TInt ConnectionAttempts();

	inline static TCommDbMultiConnPref& Cast(const TConnPref& aPref);

protected:
	inline struct SCommDbMultiConnPref* PrefPtr() const;
	};

#include <commdbconnpref.inl>

#endif
// COMMDBCONNPREF_H
