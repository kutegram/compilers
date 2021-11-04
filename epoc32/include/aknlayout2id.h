/*
* ============================================================================
*  Name     : AknLayout2Id.h
*  Part of  : Avkon Layout 2
*
*  Copyright © 2002-2006 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef AKNLAYOUT2ID_H
#define AKNLAYOUT2ID_H

#include <e32std.h>

/**
* Enum for identifying regional variants
*/
enum TAknLayoutId
	{
	/**
	* Identifies left to right layouts
	*/
	EAknLayoutIdELAF = 0,
	/**
	* Identifies right to left layouts
	*/
	EAknLayoutIdABRW = 1,
	/**
	* Identifies Asian and Pacific layouts
	*/
	EAknLayoutIdAPAC = 2
	};

#endif
// End of File
