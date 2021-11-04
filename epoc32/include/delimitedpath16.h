// DelimitedPath16.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

#ifndef __DELIMITEDPATH16_H__
#define __DELIMITEDPATH16_H__

/**
	@file DelimitedPath16.h
	Comments :	This file contains the API definition for the classes 
				TDelimitedPathParser16 and CDelimitedPath16. 
	@publishedAll
	
 */

// System includes
//
#include <e32base.h>
#include <delimitedparser16.h>


/**
Dependencies : TDelimitedParserBase16
Comments : Derived class from TDelimitedParserBase providing a class for parsing paths
delimited by '/' as defined in RFC2396.
@publishedAll


*/
class TDelimitedPathParser16 : public TDelimitedParserBase16
	{
public:	// Methods

	IMPORT_C TDelimitedPathParser16();

	IMPORT_C void Parse(const TDesC16& aPath);

	IMPORT_C void ParseReverse(const TDesC16& aPath);
	};

/**
Dependencies : CDelimitedStringBase16
Comments : Provides functionality to create a delimited path where components of the 
path delimited by '/' as defined in RFC2396.
@publishedAll


*/
class CDelimitedPath16 : public CDelimitedDataBase16
	{
public:	// Methods

	IMPORT_C static CDelimitedPath16* NewL(const TDesC16& aPath);

	IMPORT_C static CDelimitedPath16* NewLC(const TDesC16& aPath);

	IMPORT_C ~CDelimitedPath16();

	IMPORT_C void InsertAndEscapeCurrentL(const TDesC16& aSegment);

	IMPORT_C void PushAndEscapeBackL(const TDesC16& aSegment);
	
	IMPORT_C void PushAndEscapeFrontL(const TDesC16& aSegment);

private:	// Methods

	CDelimitedPath16();

	void ConstructL(const TDesC16& aPath);

	};

/**
typedef 
@publishedAll

*/
typedef TDelimitedPathParser16 TDelimitedPathParser;

/**
typedef 
@publishedAll

*/
typedef CDelimitedPath16 CDelimitedPath;

// __DELIMITEDPATH16_H__
#endif


