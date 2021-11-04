// e32\include\e32notif.h
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

/**
	@file
	@internalTechnology
*/

#ifndef __E32NOTIF_H__
#define __E32NOTIF_H__
#include <e32std.h>

#define __NOTIFIER_NAME _L("!Notifier")
enum TNotifierMessage 
	{
	ENotifierNotify,
	ENotifierInfoPrint,
	EStartNotifier,
	ECancelNotifier,
	EUpdateNotifier,
	EStartNotifierAndGetResponse,
	EStartNotifierFromSpecifiedDll,
	EStartNotifierFromSpecifiedDllAndGetResponse,
	ENotifierNotifyCancel,
	EUpdateNotifierAndGetResponse,
	};

#endif

