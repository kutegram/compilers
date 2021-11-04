/*
* ============================================================================
*  Name     : MPbkEditorOkToExitCallback from MPbkEditorOkToExitCallback.h
*  Part of  : PbkView.dll
*
*  Description:
*     Phonebook contact editor exit callback abstract interface.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
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

#ifndef __MPbkEditorOkToExitCallback_H__
#define __MPbkEditorOkToExitCallback_H__

// CLASS DECLARATION

/**
 * Phonebook contact editor exit callback interface. This callback is used in
 * conjunction with the CPbkContactEditorDlg editing dialog. The user can set
 * a callback function that is called before the dialog exit happens.
 * @see CPbkContactEditorDlg
 */
class MPbkEditorOkToExitCallback
    {
    public: // Interface

        /**
         * Returns ETrue if it is ok to exit the contact editor and
         * EFalse if not.
         *
         * @param aCommandId    The exit command id.
         * @return  ETrue to exit the editor.
         */
        virtual TBool OkToExitL(
                TInt aCommandId ) = 0;
    };


#endif // __MPbkEditorOkToExitCallback_H__

// End of File
