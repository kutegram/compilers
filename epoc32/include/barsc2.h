// BARSC2.H
//
// Copyright (c) 2003-2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __BARSC2_H__
#define __BARSC2_H__

#include <f32file.h>

//Forward declarations
class RResourceFileImpl;

/** Accesses a resource file or resource file buffer and reads the 
resource data into a buffer.

Interpretation of the data is achieved using the RResourceReader class.
CResourceFile methods behaviour when some problem occurs - it leaves
with an error code. Most of the time the error code will be KErrCorrupt.

@publishedAll 

@see RResourceReader */
class CResourceFile : public CBase
	{
public:
	IMPORT_C static CResourceFile* NewL(RFs& aFs, const TDesC& aName, 
										TUint aFileOffset, TInt aFileSize);
	IMPORT_C static CResourceFile* NewLC(RFs& aFs, const TDesC& aName, 
										TUint aFileOffset, TInt aFileSize);
	IMPORT_C static CResourceFile* NewL(const TDesC8& aRscFileBuffer);
	IMPORT_C virtual ~CResourceFile();
	IMPORT_C TUidType UidType() const;
	IMPORT_C void ReadL(TDes8 &aDes,TInt aResourceId) const;
	IMPORT_C HBufC8 *AllocReadL(TInt aResourceId) const;
	IMPORT_C HBufC8 *AllocReadLC(TInt aResourceId) const;
	IMPORT_C void ConfirmSignatureL(TInt aSignature);
	IMPORT_C void ConfirmSignatureL();
	IMPORT_C TInt SignatureL() const;
	IMPORT_C TBool OwnsResourceIdL(TInt aResourceId) const;
	IMPORT_C TInt Offset() const;
private:
	CResourceFile();
	CResourceFile(const CResourceFile&);//prevent default copy constructor
	CResourceFile& operator=(const CResourceFile&);//prevent default "=" operator
	void ConstructL(RFs& aFs, const TDesC& aName, TUint aFileOffset, TInt aFileSize);
	void ConstructL(const TDesC8& aRscFileBuffer);
	RResourceFileImpl* Impl();
	const RResourceFileImpl* Impl() const;
private:
	enum
		{
		KRscFileSize = 24
		};
	TUint8 iImpl[KRscFileSize];
	};

#endif//__BARSC2_H__
