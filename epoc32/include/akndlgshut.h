/*
* ============================================================================
*  Name     : AknDlgShut.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#if !defined(__AKNDLGSHUT_H__)
#define __AKNDLGSHUT_H__

#include <e32std.h>


// FORWARD DECLARATIONS
class CEikonEnv;

/**
* Utility class for shutting dialogs
*/
class AknDialogShutter
	{
public:
    /**
    * Shut all open dialogs.
    * This stops either when all open dialogs and menus are closed
    * or when another dialog, such as a confirmation dialog is launched.
    * @param aEikEnv the CEikonEnv instance for this app.
    */
	IMPORT_C static void ShutDialogsL(CEikonEnv& aEikEnv);

private:
	static TInt StartLevel();
	};

#endif
