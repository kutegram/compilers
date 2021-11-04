// MWbxmlConverterObserver.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __MWBXMLCONVERTEROBSERVER_H__
#define __MWBXMLCONVERTEROBSERVER_H__

// System includes
//
#include <e32std.h>

//##ModelId=3B6678E0000E
class MWbxmlConverterObserver
/**
@publishedAll
@deprecated
*/
	{
public:	// Methods

	//##ModelId=3B6678E00024
	virtual TInt HandleWbxmlOutputL(const HBufC8& aBuffer) = 0;

	//##ModelId=3B6678E00026
	virtual TInt HandleWbxmlOutputL(HBufC8& aBuffer) = 0;

	//##ModelId=3B6678E0002D
	virtual TInt HandleWbxmlOutputL(HBufC8* aBuffer) = 0;

	//##ModelId=3B6678E0002F
	virtual TInt HandleWbxmlOutputL(TUint32 aSource) = 0;

	//##ModelId=3B6678E00022
	virtual void HandleWbxmlEncodingUpdateL(HBufC8* aCharacterEncoding) = 0;

private:	// Methods

	//##ModelId=3B6678E00018
	IMPORT_C virtual void MWbxmlConverterObserver_Reserved1();

	};

// #define __MWBXMLCONVERTEROBSERVER_H__
#endif
