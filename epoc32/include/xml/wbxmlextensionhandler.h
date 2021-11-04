// wbxmlextensionhandler.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//
// Plugin interface
//

#ifndef __WBXMLEXTENSIONHANDLER_H__
#define __WBXMLEXTENSIONHANDLER_H__

#include <e32std.h>


class RString;

namespace Xml
{

class MWbxmlExtensionHandler
/**
The Wbxml api extension class.
Inherited by classes wishing to cater for this interface, e.g. WbxmlParser.

@publishedAll

*/
	{
public:

/**
The uid identifying this extension interface.
*/
	enum TExtInterfaceUid {EExtInterfaceUid = 0x101FE212};
	
/**
This method is a receive notification of an extension instruction.
The type of extension is specified in aToken and is based on the global tokens
specified in WBXML documents.
@see http://www.w3.org/TR/wbxml/
@param				aData is the extension data.
@param				aToken is the global unambiguous token value.
@param				aErrorCode is the error code.
					If this is not KErrNone then special action may be required.
*/
	virtual void OnExtensionL(const RString& aData, TInt aToken, TInt aErrorCode) = 0;

	};

}

//__WBXMLEXTENSIONHANDLER_H__
#endif
