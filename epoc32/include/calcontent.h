// calcontent.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#ifndef __CALCONTENT_H__
#define __CALCONTENT_H__

#include <e32base.h>

class RReadStream;
class RWriteStream;
class CAgnContent;

NONSHARABLE_CLASS(CCalContent) : public CBase
/**
This class holds in memory 8-bit data of any type, or a link to 8-bit
data such as a URI.  The MIME type of the data may also be held to help
callers determine the appropriate application to launch the content.

Because the data is held in memory, callers should only use this class
to store small amounts of data or a URI to some content elsewhere.

This class can be used to set an alarm action using
CCalAlarm::SetAlarmAction() (such as a link to an internet
radio station, or a small animated icon).

@see CCalAlarm
@capability None
@publishedAll

*/
	{
public:
	/** Disposition of the data which maybe used while setting an alarm. The data can be a link or inline.
	@publishedPartner
	
	*/
	enum TDisposition
		{
		/** URL disposition */
		EDispositionUrl = 0,
		/** Inline disposition */
		EDispositionInline = 1,
		/** Unknown disposition */
		EDispositionUnknown = 15
		};

	IMPORT_C static CCalContent* NewL();
	IMPORT_C ~CCalContent();
	IMPORT_C void SetContentL(TDesC8* aSmallContent, TDesC8* aContentMIMEType, CCalContent::TDisposition aContentDisposition);
	IMPORT_C const TDesC8& Content() const;
	IMPORT_C const TDesC8& MimeType() const;
	IMPORT_C TDisposition Disposition() const;
	CAgnContent* Impl() const;
	void SetImpl(CAgnContent* aImpl);

private:
	CCalContent();
	void ConstructL();

private:
	CAgnContent* iImpl;
	};


// __CALCONTENT_H__
#endif

