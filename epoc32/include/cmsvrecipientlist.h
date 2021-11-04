// CMsvRecipientList.h
//
// Copyright (c) 2004-2005 Symbian Software Ltd.  All rights reserved.
//

#ifndef __CMSVRECIPIENTLIST_H__
#define __CMSVRECIPIENTLIST_H__

#include <e32base.h>
#include <badesca.h>



// must be 4 bytes so that RArray works.
typedef TUint32 TMsvRecipientType;

/**
@publishedAll

*/
enum TMsvRecipientTypeValues
	{
	EMsvRecipientTo = 0,
	EMsvRecipientCc,
	EMsvRecipientBcc,
	};

/**
@publishedAll

*/
class CMsvRecipientList : public CBase
	{
public:
	static CMsvRecipientList* NewL();
	static CMsvRecipientList* NewLC();
	virtual ~CMsvRecipientList();
	//
	IMPORT_C void Reset();
	IMPORT_C TInt Count() const;
	//
	IMPORT_C void AppendL(const TDesC& aPtr);
	IMPORT_C void AppendL(TMsvRecipientType aValue, const TDesC& aPtr);
	//
	IMPORT_C void Delete(TInt aPos);
	IMPORT_C void Delete(TInt aPos, TInt aCount);
	//
	IMPORT_C TMsvRecipientType Type(TInt aPos) const;
	IMPORT_C const TDesC& operator[](TInt aIndex) const;
	//
	IMPORT_C const MDesCArray& RecipientList() const;
private:
	CMsvRecipientList();
	void ConstructL();
private:
	RArray<TMsvRecipientType> iRecipientType;
	CDesCArrayFlat*	iRecipients;
	};

//__CMSVRECIPIENTLIST_H__
#endif
