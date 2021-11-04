// CSmsEmailFields.h
//
// Copyright (c) Symbian Software Ltd 2004. All rights reserved.
//

#ifndef __CSMSEMAILFIELDS_H__
#define __CSMSEMAILFIELDS_H__

#include <e32base.h>
#include <s32file.h>
#include <badesca.h>

class CMsvStore;

/**
Encapsulates the address and subject fields for Email sent over SMS.

@publishedAll

*/
class CSmsEmailFields : public CBase
	{
public:
	IMPORT_C static CSmsEmailFields* NewL();
	IMPORT_C static CSmsEmailFields* NewL(const CSmsEmailFields& aEmailFields);
	IMPORT_C virtual ~CSmsEmailFields();

	IMPORT_C void Reset();
	IMPORT_C TInt Length() const;
	IMPORT_C TBool HasAddress() const;
	IMPORT_C HBufC* ComposeLC() const;
	TInt ParseL(const TDesC& aBuffer);

	IMPORT_C void AddAddressL(const TDesC& aAddress);
	IMPORT_C void RemoveAddress(TInt aIndex);
	IMPORT_C const MDesCArray& Addresses() const;
	
	IMPORT_C void SetSubjectL(const TDesC& aSubject);
	IMPORT_C const TDesC& Subject() const;
	
	void RestoreL(CMsvStore& aStore);
	void StoreL(CMsvStore& aStore) const;
private:
	CSmsEmailFields();
	void ConstructL();
	void ConstructL(const CSmsEmailFields& aEmailFields);

	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:	
	CDesCArray*		iAddresses;
	HBufC*			iSubject;
	};

// __CSMSEMAILFIELDS_H__
#endif
