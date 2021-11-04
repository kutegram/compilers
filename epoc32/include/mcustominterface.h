/*
* ============================================================================
*  Name        : MCustomInterface.h
*  Part of     : AudioEnhancements/CustomInterfaceUtility/CustomInterfaceUtility
*  Interface   : 
*  Description : 
*  Version     : %version: 3 %
*
*  Copyright © 2005-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/
#ifndef __MCUSTOMINTERFACE_H
#define __MCUSTOMINTERFACE_H

#include <e32std.h>

class MCustomInterface 
	{
public:
	virtual TAny* CustomInterface(TUid aInterfaceId) = 0;

	};

#endif
