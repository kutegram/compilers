/*
* ============================================================================
*  Name        : akntreelistconstants.h
*  Part of     : UI Framework Core / Avkon
*  Description : Constants for hierarchical list.
*  Version     : %version: 2 %
*
*  Copyright � 2006, 2007 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.0
*/

#ifndef AKNTREELISTCONSTANTS_H
#define AKNTREELISTCONSTANTS_H


#include <e32def.h>


/** Item ID for hierarchical list items. */
typedef TInt TAknTreeItemID;

/** Constant Item ID for non-existent hierarchical list item. */
const TAknTreeItemID KAknTreeIIDNone = 0;

/** Constant Item ID for the hierarchical list root node. */
const TAknTreeItemID KAknTreeIIDRoot = 1;


/** Namespace for pre-defined tree list icon IDs. */
namespace AknTreeListIconID
    {
    /** Constant indicating that default icon is to be used. */
    const TInt KDefault = -1;

    /** No icon. */
    const TInt KNone = 0;

    /** Tree structure line with branch. */
    const TInt KLineBranchIndication = 1;

    /** Tree structure end line. */
    const TInt KLineEndIndication = 2;

    /** Tree structure straight line indication. */
    const TInt KLineStraightIndication = 3;

    /** Default file indication. */
    const TInt KDefaultFileIndication = 4;

    /** Closed folder indication. */
    const TInt KClosedFolderIndication = 5;

    /** Open folder indication. */
    const TInt KOpenFolderIndication = 6;

    /** Collapse function indication, superimposed. */
    const TInt KCollapseFunctionIndication = 7;

    /** Expand function indication, superimposed. */
    const TInt KExpandFunctionIndication = 8;

    /** Item marked indication. */
    const TInt KMarkedIndication = 9;

    /** Highlighted item marked indication. */
    const TInt KHighlightedMarkedIndication = 10;
    }


#endif // AKNTREELISTCONSTANTS_H
