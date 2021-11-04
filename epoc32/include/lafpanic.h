/*
* ==============================================================================
*  Name        : lafpanic.h
*  Part of     : 
*  Description : 
*  Version     :  
*
*  Copyright © 2002-2007 Nokia. All rights reserved.
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

#ifndef __LAFPANIC_H__
#define __LAFPANIC_H__

/** Panic codes used throughout the code in Avkon library.
  * These panics have a category of EIKON or EikCoCtlLaf.
  */
enum TLafPanic
	{
	/** 00: Invalid pointer cursor index used. */
	ELafPanicPointerCursorIndexOutOfRange,
	/** 01: Invalid font index used in menu. */
	ELafPanicFontIndexOutOfRange,
	/** 02: Invalid constant used. */
	ELafPanicConstantNotKnown,
	/** 03: Invalid horizontal alignment constant used. */
	ELafPanicMsgWinBadHorizontalAlignment,
	/** 04: Invalid vertical alignment constant used. */
	ELafPanicMsgWinBadVerticalAlignment,
	/** 05: Bitmap index out of range. */
	ELafPanicBitmapIndexOutOfRange,
	/** 06: @deprecated */
	ELafPanicNotificationWithoutRequest,
	/** 07: Invalid logical font category used. */
    ELafPanicFontUidUnknownOrMissing,
	/** 08: APAC font requested in western variant. */
    ELafPanicUsingFontFromWrongVariant,
	/** 09: Font creation failure. */
    ELafPanicFontCreationFailure
	};

#endif //__LAFPANIC_H__

// End of file.
