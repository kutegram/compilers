// xmlframeworkconstants.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//

#ifndef __XMLFRAMEWORKCONSTANTS_H__
#define __XMLFRAMEWORKCONSTANTS_H__

#include <e32std.h>

namespace Xml
{
/**
Indicates the String Dictionary interface uid that ECom uses to locate the appropriate plugin.
@publishedPartner

*/
const TUid KStringDictionaryInterfaceUid	= {0x101FA94F};

/**
Indicates the Parser interface uid that ECom uses to locate the appropriate plugin.

@publishedPartner

*/
const TUid KParserInterfaceUid				= {0x101FAA0B};

/**
Indicates the Generator interface uid that ECom uses to locate the appropriate plugin.

@publishedPartner

*/
const TUid KGeneratorInterfaceUid			= {0x101FD284};

}

//__XMLFRAMEWORKCONSTANTS_H__
#endif
