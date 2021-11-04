/*
* ==============================================================================
*  Name        : MAknFileSelectionObserver.h
*  Part of     : Common File Dialogs / CommonDialogs.dll
*  Interface   : ?Interface_category, ?Interface_name
*  Description : ?Description
*  Version     : ?Version
*
*  Copyright (c) 2002-2006 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef MAKNFILESELECTIONOBSERVER_H
#define MAKNFILESELECTIONOBSERVER_H

// INCLUDES
#include <E32STD.H>

// FORWARD DECLARATIONS
class TEntry;

//  CLASS DEFINITION
/**
*  Observer class that can be set to observe if selected item
*  e.g. has correct size or date before letting dialog exit.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class MAknFileSelectionObserver
    {
    public:     // Constructors and destructor

        /**
        * A virtual destructor to ensure that correct destructor gets called.
        * Must have an empty implementation.
        */
        virtual ~MAknFileSelectionObserver() { };

    public:     // New functions

        /**
        * Get's called when user selects an file.
        * @param aDriveAndPath Drive and full path of the file.
        * @param aEntry An entry containing all information of selected item.
        * @return Returns ETrue if it is ok to exit from dialog.
        */
        virtual TBool OkToExitL( const TDesC& aDriveAndPath, const TEntry& aEntry ) = 0;
    };

#endif // MAKNFILESELECTIONOBSERVER_H

// End of File
