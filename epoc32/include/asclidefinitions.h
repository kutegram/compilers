// ASCLIDEFINITIONS.H
//
// Copyright (c) Symbian Software Ltd 1999-2005. All rights reserved.
//
#ifndef __ASCLIDEFINITIONS_H__
#define __ASCLIDEFINITIONS_H__

// System includes
#include <e32base.h>

// User includes

// Type definitions

// Constants

// Enumerations


///////////////////////////////////////////////////////////////////////////////////////
// ----> ASCliDefinitions (header)
///////////////////////////////////////////////////////////////////////////////////////
class ASCliDefinitions
/** This is a utility class that retrieves the name and version number of the alarm 
server. 
@publishedAll

*/
	{
///////////////////////////////////////////////////////////////////////////////////////
public:										// STATIC ACCESS METHODS
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C static const TDesC&			ServerAndThreadName();

	static const TDesC&						ServerImageName();

	static TUidType							ServerUidType();

	static TVersion							Version();

	};

#endif
