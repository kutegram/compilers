// stringdictionarycollection.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//

#ifndef __STRINGDICTIONARYCOLLECTION_H__
#define __STRINGDICTIONARYCOLLECTION_H__

#include <e32base.h>

class RStringPool;
class RString;
class TDesC8;

namespace Xml
{

class MStringDictionary;
class RStringDictionaryCollectionImpl;


class RStringDictionaryCollection
/**
The RStringDictionaryCollection class holds a collection of Dictionaries requested by the user.

@publishedAll

*/
	{
public:
	IMPORT_C void OpenL();
	IMPORT_C void Close();

	IMPORT_C RStringDictionaryCollection();

	IMPORT_C void OpenDictionaryL(const TDesC8& aDictionaryDescription);

	IMPORT_C RStringPool& StringPool();

	IMPORT_C MStringDictionary& CurrentDictionaryL() const;
		
private:

	RStringDictionaryCollection(const RStringDictionaryCollection& aOriginal);
	RStringDictionaryCollection& operator=(const RStringDictionaryCollection& aRhs);
	void CreateImplL();

private:

/**
Hide the implementation details.
*/
	RStringDictionaryCollectionImpl*	iImpl;
	};

}

//__STRINGDICTIONARYCOLLECTION_H__
#endif
