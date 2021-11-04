// DelimitedQuery16.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

#ifndef __DELIMITEDQUERY16_H__
#define __DELIMITEDQUERY16_H__

/**
	@file DelimitedQuery16.h
	Comments :	This file contains the API definition for the classes TDelimitedQueryParser16
				and CDelimitedQuery16.
	@publishedAll
	
 */

// System includes
//
#include <e32base.h>
#include <delimitedparser16.h>


/**
Dependencies : TDelimitedParserBase16
Comments : Derived class from TDelimitedParserBase providing a class for parsing querys
delimited by '&' as defined in RFC2396.
@publishedAll


*/
class TDelimitedQueryParser16 : public TDelimitedParserBase16
	{
public:	// Methods

	IMPORT_C TDelimitedQueryParser16();

	IMPORT_C void Parse(const TDesC16& aQuery);

	IMPORT_C void ParseReverse(const TDesC16& aQuery);
	};

/**
Dependencies : CDelimitedStringBase16
Comments : Provides functionality to create a delimited query where components of the 
query delimited by '&' as defined in RFC2396.
@publishedAll


*/
class CDelimitedQuery16 : public CDelimitedDataBase16
	{
public:	// Methods

	IMPORT_C static CDelimitedQuery16* NewL(const TDesC16& aQuery);

	IMPORT_C static CDelimitedQuery16* NewLC(const TDesC16& aQuery);

	IMPORT_C ~CDelimitedQuery16();

	IMPORT_C void InsertAndEscapeCurrentL(const TDesC16& aSegment);

	IMPORT_C void PushAndEscapeFrontL(const TDesC16& aSegment);

	IMPORT_C void PushAndEscapeBackL(const TDesC16& aSegment);

private:	// Methods

	CDelimitedQuery16();

	void ConstructL(const TDesC16& aQuery);

	};

/**
typedef 
@publishedAll

*/
typedef TDelimitedQueryParser16	TDelimitedQueryParser;

/**
typedef 
@publishedAll

*/
typedef CDelimitedQuery16		CDelimitedQuery;

// __DELIMITEDQUERY16_H__
#endif
