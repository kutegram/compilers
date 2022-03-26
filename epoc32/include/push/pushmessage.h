// PushMessage.h
//
// Copyright (c) 2000-2007 Symbian Ltd.  All rights reserved.
//

/** @file
@publishedPartner

*/

#ifndef __PUSHMESSAGE_H__
#define __PUSHMESSAGE_H__

#include <e32base.h>
#include <thttpfields.h>

class RWriteStream;
class CHTTPResponse;


/** 
Encapsulates a WAP Push Message.

It provides functions to access the headers and body information. There are 
specific functions to find Application ID, and the Content Type headers as 
these fields are frequently required. 

The class also has a function to give Read-Only access to the body of the message. 

@publishedPartner

*/
class CPushMessage : public CBase
	{
public:
	IMPORT_C static CPushMessage* NewL(HBufC8* aHeader, HBufC8* aBody);
	IMPORT_C static CPushMessage* NewL(HBufC8* aHeader, HBufC8* aBody, 
								TUint8 aPushID, HBufC8* aRemoteAddress);	

	IMPORT_C virtual ~CPushMessage();  
	IMPORT_C TBool GetAppID(TPtrC8& aAppURI, TInt& aAppID, TBool& aIsAnInt);
	IMPORT_C TBool GetAppIdL(TPtrC8& aAppURI, TInt& aAppID, TBool& aIsInt);	
	IMPORT_C void  GetContentType(TPtrC& aContentType) const;
	IMPORT_C TBool GetHeaderField(THttpHeaderField aField, TPtrC8& aFieldValue) const;
	IMPORT_C TBool GetBinaryHeaderField(THttpHeaderField aField, TPtrC8& aFieldValue) const;
	IMPORT_C TBool GetHeaderField(THttpHeaderField aField, TTime& aTime) const;
	IMPORT_C TBool GetMessageBody(TPtrC8& aMessageBodyPtr) const;
	IMPORT_C TBool GetHeader(TPtrC8& aMessageHeaderPtr) const;

	IMPORT_C TBool GetServerAddress(TPtrC8& aServerAddress) const;
	IMPORT_C TBool GetPushId(TUint8& aPushID) const;
	
	IMPORT_C void SetMessageAllowed(TBool aAllowed);
	IMPORT_C TBool MessageAllowed() const;

private:
	CPushMessage(HBufC8* aHeader, TUint8 aPushID = 0);
	void ConstructL(HBufC8* aHeader, HBufC8* aBody, HBufC8* aRemoteAddress);

private:
	CHTTPResponse* iHttpResponse;
	TPtrC8 iPushHeader;
	HBufC8* iPushBody;
	// Buffer containing the a unicode version of the content-type from CHTTPResponse
	mutable HBufC* iContentType;

	TUint8 iPushID;

	// Passed in constructor. Takes ownership.
	HBufC8* iServerAddress;
	
	TBool iAllowed;
	};

#endif
