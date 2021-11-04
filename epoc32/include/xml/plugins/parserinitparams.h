// parserinitparams.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//

#ifndef __PARSERINITPARAMS_H__
#define __PARSERINITPARAMS_H__

#include <xml/plugins/elementstack.h> // needed for the typedef

namespace Xml
{

class CCharSetConverter;
class MContentHandler;
class RStringDictionaryCollection;


struct TParserInitParams
/**
A structure for passing initialisation parameters to the derived class being instantiated.

@publishedPartner

*/
	{

/**
The helper class for character conversions and encoding resolution.
We do not own this.
*/	
	CCharSetConverter*				iCharSetConverter;

/**
The client callback to pass the data to.
We do not own this.
*/
	MContentHandler*				iContentHandler;

/**
The collection of string dictionaries that can be loaded by the user or by the framework at runtime.
We do not own this.
*/
	RStringDictionaryCollection*	iStringDictionaryCollection;

/**
The Element stack that allows checking on tag ordering.
An object may want to check this in associating with validation.
We do not own this.
*/
	RElementStack*					iElementStack;

	};

}

//__PARSERINITPARAMS_H__
#endif
