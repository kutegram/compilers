// MTURUTILS.H
//
// Copyright (C) Symbian Ltd 2000
//

#ifndef __MTURUTILS_H__
#define __MTURUTILS_H__

#include <msvstd.h>

class MturUtils
/** Utility class that is used to start an application to 
edit a specified message.

@publishedAll

*/
{
public:
	IMPORT_C static void LaunchEditorL(TMsvId aId);
	IMPORT_C static void LaunchEditorAndWaitL(TMsvId aId);
	IMPORT_C static void LaunchEditorL(TMsvId aId, RThread& aThread, TRequestStatus& aStatus);
};

#endif
