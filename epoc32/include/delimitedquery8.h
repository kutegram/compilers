// DelimitedQuery8.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

#ifndef __DELIMITEDQUERY8_H__
#define __DELIMITEDQUERY8_H__

/**
	@file DelimitedQuery8.h
	Comments :	This file contains the API definition for the classes TDelimitedQueryParser8
				and CDelimitedQuery8. 
	@publishedAll
	
 */

// System includes
//
#include <e32base.h>
#include <delimitedparser8.h>


/**
Dependencies : TDelimitedParserBase8
Comments : Derived class from TDelimitedParserBase providing a class for parsing 
querys delimited by a '&' as defined in RFC2396.
@publishedAll


*/
class TDelimitedQueryParser8 : public TDelimitedParserBase8
	{
public:	// Methods

	IMPORT_C TDelimitedQueryParser8();

	IMPORT_C void Parse(const TDesC8& aQuery);

	IMPORT_C void ParseReverse(const TDesC8& aQuery);
	};

/**
Dependencies : CDelimitedStringBase8
Comments : Provides functionality to create a delimited query where components of the 
query delimited by '&' as defined in RFC2396.
@publishedAll


*/
class CDelimitedQuery8 : public CDelimitedDataBase8
	{
public:	// Methods

	IMPORT_C static CDelimitedQuery8* NewL(const TDesC8& aQuery);

	IMPORT_C static CDelimitedQuery8* NewLC(const TDesC8& aQuery);

	IMPORT_C ~CDelimitedQuery8();

	IMPORT_C void InsertAndEscapeCurrentL(const TDesC8& aSegment);

	IMPORT_C void PushAndEscapeFrontL(const TDesC8& aSegment);

	IMPORT_C void PushAndEscapeBackL(const TDesC8& aSegment);

private:	// Methods

	CDelimitedQuery8();

	void ConstructL(const TDesC8& aQuery);

	};

// __DELIMITEDQUERY8_H__
#endif
