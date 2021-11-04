/*
* ============================================================================
*  Name        : MAknMemorySelectionObserver.h
*  Part of     : Common File Dialogs / CommonDialogs.dll
*  Description : Observer interface for memory selection.
*  Version     : %version: e003sa02#3 % << Don't touch! Updated by Synergy at check-out.
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
* Template version: 4.2
*/


#ifndef M_AKNMEMORYSELECTIONOBSERVER_H
#define M_AKNMEMORYSELECTIONOBSERVER_H

#include <CAknMemorySelectionDialog.h>

/**
*  Observer class that can be set to observe if selected memory
*  e.g. has enoung free space before letting dialog exit.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class MAknMemorySelectionObserver
    {

public:

// Constructors and destructor

    /**
     * A virtual destructor to ensure that correct destructor gets called.
     * Must have an empty implementation.
     */
    virtual ~MAknMemorySelectionObserver() { };

// New functions

    /**
     * Get's called when user selects a memory.
     * @param aMemory Currently selected memory.
     * @return Returns ETrue if it is ok to exit from dialog.
     */
    virtual TBool OkToExitL( CAknMemorySelectionDialog::TMemory aMemory ) = 0;

    };

#endif // M_AKNMEMORYSELECTIONOBSERVER_H
