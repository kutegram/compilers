/*
* ============================================================================
*  Name        : aknhlistpanic.h
*  Part of     : UI Framework Core / Avkon
*  Description : Panic codes for aknhlist library.
*  Version     : %version: 1 %
*
*  Copyright © 2006 Nokia.  All rights reserved.
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

#ifndef AKNHLISTPANIC_H
#define AKNHLISTPANIC_H


/** Panic codes used throughout the code in aknhlist library.
    These panics have a category of AKNHLIST. */
enum TAknHListPanic
    {
    /** Invalid item ID. The client has used an item ID to refer to some
        non-existing item. This panic is raised, for example, when client
        uses an ID of item that has already been removed from the list. */
    EAknHListPanicInvalidItemID      = 0,
    /** Invalid item type. The client has referred to item an item of wrong
        type. This is raised, for example, when client tries to add an item
        into a leaf item. */
    EAknHListPanicInvalidItemType    = 1
    };


#endif // AKNHLISTPANIC_H
