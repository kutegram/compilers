// BifBase.h
//
// Copyright (c) 1997-2005 Symbian Software Ltd. All rights reserved.
//

#ifndef __BIFBASE_H__
#define __BIFBASE_H__

#include <e32base.h>
#include <s32std.h>				// for TSwizzle
#include <apmrec.h>				// for TRecognitionConfidence

/** Base classes for BIO-message Information File (BIF) Reader

@internalTechnology

*/
class CBioInfoFile : public CBase
	{
public:
	~CBioInfoFile();

protected:
	CBioInfoFile(RFs& aFs);
	void ConstructL();

protected:
	class CIdHeader : public CBase
		{
	public:
		CIdHeader();
		~CIdHeader();

		void InternalizeL(RReadStream& aStream);			
		void ExternalizeL(RWriteStream& aStream) const;		

	public:
		TBioMsgIdType iType;
		CApaDataRecognizerType::TRecognitionConfidence iConfidence;
		TSwizzle<HBufC> iText;
		TUint16 iPort;
		TUid iCharacterSet;
		TInt16 iGeneralIdData;
		};

	class TIconZoomLevel
		{
	public:
		void InternalizeL(RReadStream& aStream);			
		void ExternalizeL(RWriteStream& aStream) const;		

	public:
		TInt16 iZoomLevel;
		};

protected:
	RFs& iFs;

	//
	// Simple data to be read/write to/from BIF file
	TUid iMessageTypeUid;

	HBufC* iMessageParserName;
	
	TUid iMessageAppUid;
	HBufC* iMessageAppCtrlName;	
	HBufC* iDescription;
	TInt16 iGeneralData1;
	TInt16 iGeneralData2;
	TInt16 iGeneralData3;
	HBufC* iFileExtension;
	HBufC* iIconsFilename;
		
	//
	// Complex data to be read/write to/from BIF file
	CArrayPtrFlat<CIdHeader>* iIdHeaderArray;
	CArrayFix<TIconZoomLevel>* iIconZoomLevelArray;
	};

// __BIFBASE_H__
#endif
