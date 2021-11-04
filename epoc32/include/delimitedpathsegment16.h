// DelimitedPathSegment16.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

#ifndef __DELIMITEDPATHSEGMENT16_H__
#define __DELIMITEDPATHSEGMENT16_H__

/**
	@file DelimitedPathSegment16.h
	Comments :	This file contains the API definition for the classes TDelimitedPathSegmentParser16
				and CDelimitedPathSegment16.
	@publishedAll
	
 */

// System includes
//
#include <e32base.h>
#include <delimitedparser16.h>


/**
Dependencies : TDelimitedParserBase16
Comments : Derived class from TDelimitedParserBase providing a class for parsing path segments
delimited by '/' as defined in RFC2396.
@publishedAll


*/
class TDelimitedPathSegmentParser16 : public TDelimitedParserBase16
	{
public:	// Methods

	IMPORT_C TDelimitedPathSegmentParser16();

	IMPORT_C void Parse(const TDesC16& aPathSegment);

	IMPORT_C void ParseReverse(const TDesC16& aPathSegment);
	};

/**
Dependencies : CDelimitedStringBase16
Comments : Provides functionality to create a delimited path segment where components of the 
path segment delimited by '/' as defined in RFC2396.
@publishedAll


*/
class CDelimitedPathSegment16 : public CDelimitedDataBase16
	{
public:	// Methods

	IMPORT_C static CDelimitedPathSegment16* NewL(const TDesC16& aPathSegment);

	IMPORT_C static CDelimitedPathSegment16* NewLC(const TDesC16& aPathSegment);

	IMPORT_C ~CDelimitedPathSegment16();

	IMPORT_C void InsertAndEscapeCurrentL(const TDesC16& aParam);

	IMPORT_C void PushAndEscapeBackL(const TDesC16& aParam);
	
	IMPORT_C void PushAndEscapeFrontL(const TDesC16& aParam);

private:	// Methods

	CDelimitedPathSegment16();

	void ConstructL(const TDesC16& aPathSegment);

	};

/**
typedef 
@publishedAll

*/
typedef TDelimitedPathSegmentParser16	TDelimitedPathSegmentParser;

/**
typedef 
@publishedAll

*/
typedef CDelimitedPathSegment16			CDelimitedPathSegment;

// __DELIMITEDPATHSEGMENT16_H__
#endif
