// taginfo.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//

#ifndef __TAGINFO_H__
#define __TAGINFO_H__

#include <stringpool.h>


namespace Xml
{

class RTagInfo
/**
The RTagInfo class holds information that describes an element or attribute.
@see MContentHandler
@see RAttribute

@publishedAll

*/
	{
public:

/**
@publishedPartner

*/
	IMPORT_C RTagInfo();

/**
@publishedPartner

*/
	IMPORT_C RTagInfo Copy();

/**
@publishedPartner

*/
	IMPORT_C void Close();

/**
@publishedPartner

*/
	IMPORT_C void Open(const RString& aUri, const RString& aPrefix, const RString& aLocalName);
	
	IMPORT_C const RString& Uri() const;
	IMPORT_C const RString& LocalName() const;
	IMPORT_C const RString& Prefix() const;

private:

/**
Holds the namespace uri of the object it represents.
*/
	RString iUri;

/**
Holds the namespace prefix of the object it represents.
*/
	RString iPrefix;

/**
Holds the local name of the object it represents.
*/
	RString iLocalName;

	};

}

//__TAGINFO_H__
#endif
