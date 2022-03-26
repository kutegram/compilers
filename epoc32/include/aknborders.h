/*
* ==============================================================================
*  Name        : aknborders.h
*  Part of     : 
*  Description : 
*  Version     : 
*
*  Copyright � 2002-2006 Nokia. All rights reserved.
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

#ifndef __AKNBORDERS_H__
#define __AKNBORDERS_H__

#include <e32std.h>

/** 
 * Border ids for Avkon extended TGulBorder.
 * Contains hard coded border definitions for different
 * dialogs.
 */
class AknBorderId
	{
public:
	enum TAknBorderId
		{
		/** Border id for notes and queries. */
		EAknBorderNotePopup = 0x800110,
		/** Border id for options menu. */
		EAknBorderMenuPopup,
		/** Border id for sub-menu of options menu. */
		EAknBorderMenuSubmenuPopup,
		/** Border id for notification popup. */
		EAknBorderNotificationPopup,
		/** Border id for grouped notification popup. */
		EAknBorderGroupedNotificationsPopup,
		/** Border id for character selection popup. */
		EAknBorderCharacterSelectionPopup,
		/** Border id for list query dialog. */		
		EAknBorderPopups,
		/** Border id for list query dialog with heading. */		
		EAknBorderPopupsWithHeading,
		/** End marker for Avkon borders. Not a real border type. */		
		EAknBorderMax
		};
	};


#endif //__AKNBORDERS_H__
