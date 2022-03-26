// EIKDEF.H
//
// Copyright (c) Symbian Software Ltd 1997-2006.  All rights reserved.
// 

#ifndef __EIKDEF_H__
#define __EIKDEF_H__

#include <e32std.h>
#include <coedef.h>

/** This is used in combination with a specified position to place a popout on 
the display. 

The TPopupTargetPosType enum identifies which corner of the popout 
will be placed in the given target position. The default is the top left corner. 

@publishedAll
*/
enum TPopupTargetPosType
	{
	/** Places the popout with the top left corner in the specified position. */
	EPopupTargetTopLeft,
	/** Places the popout with the top right corner in the specified position. */
	EPopupTargetTopRight,
	/** Places the popout with the bottom left corner in the specified position. */
	EPopupTargetBottomLeft,
	/** Places the popout with the bottom right corner in the specified position. */
	EPopupTargetBottomRight
	};


/** Defines the printer port settings. This is used by GUI print dialogs.*/
enum TEikPortFlag
	{
	/** Printing is via a serial port.*/
	ESerialPort = 0x01,
	/** Printing is via a parallel port.*/
	EParallelPort = 0x02,
	/** Printing is via infra red.*/
	EIrdaPort = 0x04,
	/** Printing is to a file. */
	EFilePort = 0x08,
	/** Printing is via a PC.*/
	EViaPCPort = 0x10
	};

/** Macro to allow easy access to the CEikonEnv instance.

@publishedAll

*/
#define iEikonEnv (STATIC_CAST(CEikonEnv*,iCoeEnv))

/** Defines the border style for an editable control.

@publishedPartner

*/
#define KEikEditableControlBorder TGulBorder::EShallowSunken

/** Name of the default bitmap store.

@publishedPartner

*/
_LIT(KEikDefaultAppBitmapStore,"*");

/** Uid of the KEikMessageColorSchemeChange message.

@publishedPartner

*/
const TInt KUidValueEikColorSchemeChangeEvent	=0x10006956;

/**
@internalComponent
*/
const TInt KEikCustomColorsArrayValue			=0x100057C2;

/** Indicates that all windows should appear faded.

@publishedAll

*/
const TInt KEikMessageFadeAllWindows			=0x100056C2;

/** Indicates that all windows should appear unfaded.

@publishedAll

*/
const TInt KEikMessageUnfadeWindows				=0x100056C3;

/** Indicates that the colour scheme has changed.

@publishedAll

*/
const TInt KEikMessageColorSchemeChange			=KUidValueCoeColorSchemeChangeEvent;

/** Indicates that the color scheme has changed.

@publishedAll

*/
#define KEikColorResourceChange KEikMessageColorSchemeChange // for source compatibility

/** Indicates that the zoom level has changed.

@publishedAll

*/
const TInt KEikMessageZoomChange				=KUidValueCoeZoomChangeEvent;

/** Indicates that a font has changed. Controls should ensure they are using 
the right font after receiving this message.

@publishedAll

*/
const TInt KEikMessageFontChange     = KUidValueCoeFontChangeEvent;  

/** Indicates that the state of the virtual cursor has changed.

@publishedAll

*/
const TInt KEikMessageVirtualCursorStateChange	=0x10005D0A;

/** Indicates that caps lock key has been pressed.

@publishedAll

*/
const TInt KEikMessageCapsLock					=0x100048F9;

/** Indicates that the application should be ready to save any data that needs saving.

@publishedAll

*/
const TInt KEikMessagePrepareForSave			=0x100069FD;

/** Indicates that the level of embedding of the application has changed.

@publishedAll

*/
const TInt KEikMessageEmbedLevelChange			=0x1000A4AA;

/** Passed immediately after completion of the call to CCoeEnv::SetAppUi() 
when aNewAppUi has become current AppUi. This happens during the destruction of the embedded
AppUi.

@publishedAll 

*/
const TInt KEikHasBecomeCurrentAppUiWhileEmbeddedAppUiDeletes = 0x10207F75;

/** Passed immediately before CEikAppUiFactory::CreateEmbeddedL()

@publishedAll 

*/
const TInt KEikNotifyPreCreateEmbeddedL = 0x10207F67;

/** Passed immediately after CEikAppUiFactory::CreateEmbeddedL()

@publishedAll 

*/
const TInt KEikNotifyPostCreateEmbeddedL = 0x10207F65;

/** Passed immediately after CCoeAppUi::ConstructL()

@publishedAll 

*/
const TInt KEikPostCoeAppUiConstructL = 0x10207F66;

/**
@publishedAll

*/
_LIT8(KDebugStart, "-DebugMemFail:");

/**
@publishedPartner 

*/
const TInt KEikDefaultCursorWidth=2;

/**
@publishedPartner 

*/
const TInt KTimeBetweenClicks=1000000;	 // in Microseconds	

/**
@publishedPartner 

*/		 
const TInt KDoubleClickDistance=10;

/**
@publishedPartner 

*/	
const TInt KKeyboardRepeatRate=50000;

/**
@publishedPartner 

*/	
const TInt KKeyboardRepeatInitialDelay=800000;

/** Resource id of the query dialog.
@publishedPartner

*/
const TInt KEikResIdQueryDialog	=0;

/** Resource id of the info dialog.
@publishedPartner

*/
const TInt KEikResIdInfoDialog	=1;

/**
@publishedPartner 

*/	
const TInt KEikErrorResolverMaxTextLength = 256;

/**
@internalTechnology
*/
#define COMPARE_BOOLS(a,b) (((a) && (b)) || (!(a) && !(b)))

/**
@internalComponent
*/
#if defined(_DEBUG)
#define __UHEAP_CHECK_INTEGRITY User::Heap().Check()
#else
#define __UHEAP_CHECK_INTEGRITY
#endif

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_FIRST		32

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_LAST		39

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_SIMPLE		32

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_DIALOG_LOAD	33

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_APP_LAUNCH	34

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_CLOCK		35

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_CALENDER	35

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_LIBS_LOAD	36

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_ADD_RES		37

/**
@internalComponent
*/
#define KEikEikonBitmapStore		KNullDesC

/**
@internalComponent
*/
const TUid KSystemIniFileUid = {0x1000010C};

/**
@internalComponent
*/	
const TInt KLastSystemWideErrCode = KErrCommsBreak;


// __EIKDEF_H__
#endif
