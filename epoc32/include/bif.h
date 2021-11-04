// BIF.H
//
// Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
//

#ifndef __BIF_H__
#define __BIF_H__

#include <apmrec.h>

class CBifEntry;

//
// Constants
/** 2nd UID of BIF file stores. */
const TUid KUidBioInfoFile={0x10005233};		// unicode Uid, used as 2nd Uid of file store
/** Indicates that when opening the message no application should be launched. */
const TUid KUidBioUseNoApp={0x00000000};			
/** Indicates that when opened the message is to be viewed by the default application. */
const TUid KUidBioUseDefaultApp={0x100052b2};		
/** Maximum length of BIO_INFO_FILE description field. */
const TInt KMaxBioDescription=128;
/** Maximum length of ID text field. */
const TInt KMaxBioIdText=128;
/** Unused from v7.0.

Previously, it specified the maximum length of a command line to BIFTOOL. */
const TInt KMaxBioCommandLine=256;
/** Maximum length of BIO_INFO_FILE file_extension field. */
const TInt KMaxBioFileExtension=10;

//
// Data types
/** Buffer to hold a BIF ID identifier text field. */
typedef TBuf<KMaxBioIdText> TBioMsgIdText;
/** Unused from v7.0.

Previously, it held a command line to BIFTOOL. */
typedef TBuf<KMaxBioCommandLine> TBioCommand;

/** Identifies bearers for the BIF ID type field.

It is the C++ equivalent of the resource enum ID_TYPE. */
enum TBioMsgIdType 
	{
	/** Unknown.
	
	Item will not be used in matching. */
	EBioMsgIdUnknown,

	/** MIME type.
	
	Specifies that a bearer that transports MIME messages (e.g. e-mail) should 
	match the MIME type against the ID text field. */
	EBioMsgIdIana,

	/** Narrow band (SMS).
	
	Specifies that the SMS bearer should match messages against the ID port field. */
	EBioMsgIdNbs,

	/** WAP WDP.
	
	Specifies that the WAP bearer should match messages against the ID port field. */
	EBioMsgIdWap,

	/** WAP secure WDP.
	
	Specifies that the WAP bearer should match messages against the ID port field. */
	EBioMsgIdWapSecure,

	/** WAP WSP.
	
	Specifies that the WAP bearer should match messages against the ID port field. */
	EBioMsgIdWsp,

	/** WAP secure WSP.
	
	Specifies that the WAP bearer should match messages against the ID port field. */
	EBioMsgIdWspSecure
	};

/** Encapsulates an ID from a BIF (BIO_INFO_FILE). 
@internalTechnology

*/
class TBioMsgId 
	{
public:
	/** Identifies the bearer that should use this resource to match messages. */
	TBioMsgIdType iType;
	/** Confidence level. */
	CApaDataRecognizerType::TRecognitionConfidence iConfidence;			// from APMREC.H
	/** Text field that can be used to match the message to this BIO type. */
	TBioMsgIdText iText;
	/** Receiving port number that can be used to match the message to this BIO type. */
	TUint16 iPort;
	/** Expected receiving character set of messages. */
	TUid iCharacterSet;
	/** This is available for 3rd party use for BIO message type identity specific 
	data. */
	TInt16 iGeneralIdData;
	};
	
// NOTE - this is included here cos the CBioInfoFile requires some of the enums 
// defined above.
#include "bifbase.h"			// for CBioInfoFile

/** BIO information file (BIF) reader. 

Allows reading (all but the icons) from an existing BIF file.

@publishedAll

*/
class CBioInfoFileReader : public CBioInfoFile
	{
public:
	//
	// Construction/destruction
	IMPORT_C static CBioInfoFileReader* NewLC(RFs& aFs,const TDesC& aFileName,TUid aMsgTypeUid=KNullUid);
	IMPORT_C static CBioInfoFileReader* NewL(RFs& aFs,const TDesC& aFileName,TUid aMsgTypeUid=KNullUid);
	IMPORT_C virtual ~CBioInfoFileReader();

	//
	// Data getters
	IMPORT_C TUid MessageTypeUid() const;
	IMPORT_C const TPtrC MessageParserName() const;
	IMPORT_C TUid MessageAppUid() const;
	IMPORT_C TUid MessageAppCtrlUid() const;
	IMPORT_C const TPtrC MessageAppCtrlName() const;
	IMPORT_C TInt16 GeneralData1() const;
	IMPORT_C TInt16 GeneralData2() const;
	IMPORT_C TInt16 GeneralData3() const;
	IMPORT_C const TPtrC Description() const;			
	IMPORT_C const TPtrC FileExtension() const;			

	IMPORT_C const TPtrC IconsFilename() const;			
	IMPORT_C const CArrayFixFlat<TInt16>* ZoomLevelsLC() const;
	IMPORT_C TInt ZoomLevelsCount() const;			

	IMPORT_C const CArrayFixFlat<TBioMsgId>* IdsLC() const;
	
	IMPORT_C const CBifEntry& BifEntry() const;

private:
	CBioInfoFileReader(RFs& aFs);
	void ConstructL(const TDesC& aFileName, TUid aMsgTypeUid);

private:
	void InternalizeL(RReadStream& aStream);
	void LoadResourceL(TUid aMsgTypeUid);
	void LoadDataL(TUid aMsgTypeUid);
	TBool IsResFileL() const;
	TBool IsDatFile(const TUidType& aUidType) const;
    //
    HBufC*		iFileName;
    CBifEntry*	iEntry;
	};

// __BIF_H__
#endif
