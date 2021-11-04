// documentparameters.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//

#ifndef __DOCUMENTPARAMETERS_H__
#define __DOCUMENTPARAMETERS_H__


#include <stringpool.h>

namespace Xml
{

class RDocumentParameters
/**
The RDocumentParameters class contains information about the document to be passed to the client.

@publishedAll

*/
	{
public:

/**
@publishedPartner

*/
	IMPORT_C RDocumentParameters();

/**
@publishedPartner

*/
	IMPORT_C void Close();

/**
@publishedPartner

*/
	IMPORT_C void Open(const RString& aCharacterSetName);

	IMPORT_C const RString& CharacterSetName() const;

private:


/**
@publishedPartner

*/
	RDocumentParameters(const RDocumentParameters& aOriginal);

/**
@publishedPartner

*/
	RDocumentParameters &operator=(const RDocumentParameters& aRhs);

private:

/**
The character encoding of the document.
The Internet-standard name of a character set, which is identified in Symbian OS by its UID
*/
	RString	iCharacterSetName;

	};

}

#endif
