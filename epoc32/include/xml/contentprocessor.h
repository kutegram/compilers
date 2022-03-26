// contentprocessor.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//
// Plugin interface

#ifndef __CONTENTPROCESSOR_H__
#define __CONTENTPROCESSOR_H__

#include <xml/contenthandler.h>
#include <xml/contentsource.h>

namespace Xml
{

class MContentProcessor : public MContentHandler, public MContentSource
/**
This interface class provides an interface to plugins of the xml framework wishing
to receive and pass on data as part of a chain of plugins.
This class is not used directly, but via a derived class the user provides.
This will allow it to receive data, and pass data onto
other MContentProcessor derivations. Examples of such classes include Validator's and 
AutoCorrector's.
@see MContentHandler
@see ECom


@publishedPartner

*/
	{
public:

/**
This method allows for the correct destrution of the plugin.

@post				the objects memory is cleaned up.

*/
	virtual void Release() = 0;

	};

}

//__CONTENTPROCESSOR_H__
#endif
