// POWER.H
//
// Copyright (c) 2001-2004 Symbian Software Ltd. All rights reserved.
//
#ifndef __POWER_H__
#define __POWER_H__

#include <e32std.h>


/**
Client power manager

This class gives applications and servers access to
UIKON's machine specific power management functionality
as defined in LafPowerMan
@internalComponent
*/
class PowerManager
	{
public:
	IMPORT_C static void SwitchOn();
	};

/**
@internalComponent
*/
enum TPowerManagerPanic { EPowerManagerCantGetDisplayState };

#endif


