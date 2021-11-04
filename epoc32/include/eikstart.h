// EIKSTART.H
//
// Copyright (c) Symbian Software Ltd 1997-2004.  All rights reserved.
//

#ifndef __EIKSTART_H__
#define __EIKSTART_H__

#include <e32std.h>
#include <apparc.h>

class CApaCommandLine;

/**
This is the API to initialise and run the application architecture for applications built as exes.
It is not intended to be used for generally running applications from other code. Use RApaLsSession for that.

@publishedAll

*/
NONSHARABLE_CLASS(EikStart)
	{
public:
	IMPORT_C static TInt RunApplication(TApaApplicationFactory aApplicationFactory);
private:
	EikStart();
	};

// __EIKSTART_H__
#endif
