// DelimitedPathSegment8.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

#ifndef __DELIMITEDPATHSEGMENT8_H__
#define __DELIMITEDPATHSEGMENT8_H__

/**
	@file DelimitedPathSegment8.h
	Comments :	This file contains the API definition for the classes TDelimitedPathSegmentParser8
				and CDelimitedPathSegment8. 
	@publishedAll
	
 */

// System includes
//
#include <e32base.h>
#include <delimitedparser8.h>


/**
Dependencies : TDelimitedParserBase8
Comments : Derived class from TDelimitedParserBase providing a class for parsing 
path segments delimited by a ';' as defined in RFC2396.
@publishedAll


*/
class TDelimitedPathSegmentParser8 : public TDelimitedParserBase8
	{
public:	// Methods


	IMPORT_C TDelimitedPathSegmentParser8();

	IMPORT_C void Parse(const TDesC8& aPathSegment);

	IMPORT_C void ParseReverse(const TDesC8& aPathSegment);
	};

/**
Dependencies : CDelimitedStringBase8
Comments : Provides functionality to create a delimited path segment where components of the 
path segment delimited by '/' as defined in RFC2396.
@publishedAll


*/
class CDelimitedPathSegment8 : public CDelimitedDataBase8
	{
public:	// Methods

	IMPORT_C static CDelimitedPathSegment8* NewL(const TDesC8& aPathSegment);

	IMPORT_C static CDelimitedPathSegment8* NewLC(const TDesC8& aPathSegment);

	IMPORT_C ~CDelimitedPathSegment8();

	IMPORT_C void InsertAndEscapeCurrentL(const TDesC8& aParam);

	IMPORT_C void PushAndEscapeFrontL(const TDesC8& aParam);

	IMPORT_C void PushAndEscapeBackL(const TDesC8& aParam);

private:	// Methods

	CDelimitedPathSegment8();

	void ConstructL(const TDesC8& aPathSegment);

	};

// __DELIMITEDPATHSEGMENT8_H__
#endif
