/*
* ============================================================================
*  Name        : CAknMemorySelectionSettingPage.h
*  Part of     : Common File Dialogs / CommonDialogs.dll
*  Description : Setting page used to selection target memory.
*  Version     : %version: e003sa02#4 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright 2002-2007 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.1
*/


#ifndef C_AKNMEMORYSELECTIONSETTINGPAGE_H
#define C_AKNMEMORYSELECTIONSETTINGPAGE_H


#include <CAknMemorySelectionDialog.h>

class MAknMemorySelectionObserver;

/**
 *  A class that launches a popup setting page for memory selection.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 1.2
 */
NONSHARABLE_CLASS(CAknMemorySelectionSettingPage)
    : public CAknMemorySelectionDialog
    {

public:

// Constructors and destructors

    /**
     * Static constructor. Loads default settings.
     * @return Returns a pointer to an instance of itself.
     */
    IMPORT_C static CAknMemorySelectionSettingPage* NewL();

    /**
     * Static constructor.
     * @param aResourceId A resource id (MEMORYSELECTIONDIALOG).
     * @return Returns a pointer to an instance of itself.
     */
    IMPORT_C static CAknMemorySelectionSettingPage* NewL( TInt aResourceId );

    IMPORT_C ~CAknMemorySelectionSettingPage();

// New functions

    /**
     * Executes the memory selection setting page. Virtual to allow derivation.
     *
     * @param aSelectedMemory A reference to a memory (TMemory).
     *        If one of the memories is selected, the selected memory is
     *        stored to the parameter.
     * @return Returns true if user has selected an item and false
     *         if user hits cancel.
     */
    IMPORT_C TReturnKey ExecuteL( TMemory& aSelectedMemory );


    /**
     * Executes the memory selection setting page. Virtual to allow derivation.
     *
     * @param aSelectedMemory A reference to a memory (TMemory).
     *        If one of the memories is selected, the selected memory is
     *        stored to the parameter.
     * @param aRootPath A pointer to a descriptor where the root path
     *        of the selected memory is stored.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected memory is stored.
     * @return Returns true if user has selected an item and false
     *         if user hits cancel.
     */
    IMPORT_C TReturnKey ExecuteL(
        TMemory& aSelectedMemory, TDes* aRootPath, TDes* aDefaultFolder );

    /**
     * Static methods for launching memory selection dialog
     * Parameters & return value are descibed in method RunL
     */

    IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
        MAknMemorySelectionObserver* aObserver = NULL );

    IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
        const TDesC& aTitle,
        MAknMemorySelectionObserver* aObserver = NULL );

    IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
        TInt aResourceId,
        TDes* aRootPath = NULL, TDes* aDefaultFolder = NULL,
        MAknMemorySelectionObserver* aObserver = NULL );

private:    

// Constructors and destructors

    CAknMemorySelectionSettingPage();

// New functions

    /**
     * A static method for launching a memory selection setting page.
     * Creates, constructs, runs and deletes a memory selection dialog with
     * different parameters.
     *
     * @param aResourceId An id of a resource.
     * @param aSelectedMemory A reference to a memory described in ExecuteL.
     * @param aTitle A title for memory selection dialog.
     * @param aRootPath A pointer to a descriptor where the root path
     *        of the selected memory is stored.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected memory is stored.
     * @param aObserver An observer which is asked if the selected item
     *        can be selected. Implemented in application.
     */
    static TBool RunL(
        TInt aResourceId,
        TMemory& aSelectedMemory,
        const TDesC& aTitle,
        TDes* aRootPath,
        TDes* aDefaultFolder,
        MAknMemorySelectionObserver* aObserver );

    };

#endif // C_AKNMEMORYSELECTIONSETTINGPAGE_H
