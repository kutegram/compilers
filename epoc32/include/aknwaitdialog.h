/*
* ============================================================================
*  Name     : AknWaitDialog.h
*  Part of  : Avkon
*
*  Description:
*       CAknWaitDialog should be used when the progress of the process cannot be
*       traced and the length of the process is unknown. If that's not the case
*       please use CAknProgressDialog.
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
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

#ifndef __AKN_WAIT_DIALOG__
#define __AKN_WAIT_DIALOG__

#include <aknprogressdialog.h>

/**
*  This class is exactly like CAknProgressDialog except it should be used 
*  when the progress of the process cannot be
*  traced and the length of the process is unknown. If that's not the case
*  please use CAknProgressDialog.
*
*  @see CAknProgressDialog
*
* Usage:
*        iWaitDialog = new(ELeave)CAknWaitDialog(
*                                (REINTERPRET_CAST(CEikDialog**,&iWaitDialog)));
*        iWaitDialog->SetTone( CAknNoteDialog::EConfirmationTone );
*        iWaitDialog->ExecuteLD(R_WAIT_NOTE);
* 
*        // Process finished
*        iWaitDialog->ProcessFinishedL(); // deletes the dialog
*
* Callback:
*       To get a callback when/if the dialog has been dismissed
*       use SetCallBack API (for more info see aknprogressdialog.h) or
*       make your dialog modal. If the dialog is used as a modal, RunDlgLD
*       returns 0 if the dialog is dismissed and EAknSoftkeyDone if not.
*
* Resource flags:
*        -   Always set EEikDialogFlagNotifyEsc. (or use preset avkon
*                   dialog resource flag, i.e. EAknWaitNoteFlags).
*        -   To make a dialog modal use EEikDialogFlagWait
*
* Note!  Dialog should be dismissed only by using ProcessFinishedL() method,
*        it should not be deleted directly (i.e. delete iWaitDialog)!!!
*
*/

class CAknWaitDialog : public CAknProgressDialog  
{
public:
    /**
     * A class constructor
     *
     * @param    aSelfPtr        Pointer to itself. The pointer needs to be
     *                           valid when the dialog is dismissed and must not
	 *                           be on the stack.
     */
	IMPORT_C CAknWaitDialog(CEikDialog** aSelfPtr);

    /**
     * A class constructor
     *
     * @param    aSelfPtr        Pointer to itself. The pointer needs to be
     *                           valid when the dialog is dismissed and must not
	 *                           be on the stack.
     * @param    aVisibilityDelayOff If set ETrue the dialog will be visible
     *                               immediality. Use only when the length of
     *                               the process is ALWAYS over 1.5 seconds.
     */
    IMPORT_C CAknWaitDialog(CEikDialog** aSelfPtr,TBool aVisibilityDelayOff);

    /** 
     * From CCoeControl
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
private: 
	IMPORT_C virtual void CAknNoteDialog_Reserved();
public:

    /**
     * CAknWaitDialog does not support this and hence this method will PANIC.
	 * Therefore do not use it.
     */
    IMPORT_C CEikProgressInfo* GetProgressInfo();

private:
    TInt iSpare;

};

#endif
