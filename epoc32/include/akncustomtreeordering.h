/*
* ============================================================================
*  Name        : akncustomtreeordering.h
*  Part of     : UI Framework / Avkon
*  Description : Interface for implementing custom ordering for tree list.
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
* Template version: 4.2
*/

#ifndef M_AKNCUSTOMTREEORDERING_H
#define M_AKNCUSTOMTREEORDERING_H


#include <akntreelistconstants.h>


/**
 *  Interface class for implementing custom ordering for hierarchical list.
 *
 *  Implementation of this interface class can be set to hierarchical
 *  list to define the ordering of items in the list. Hierarchical list
 *  then uses the implementation of @c MAknCustomTreeOrdering::Compare
 *  method in sorting the items within each node of the list.
 *
 *  @since S60 v3.2
 */
class MAknCustomTreeOrdering
    {

public:

    /**
     * Compares two tree list items.
     *
     * @param aFirst Item ID of the first compared hierarchical list item.
     *
     * @param aSecond Item ID of the second compared hierarchical list item.
     *
     * @return Positive, if the first item is greater than the second item;
     *      negative, if the first item is less than the second item;
     *      and zero, if the items are equal.
     */
    virtual TInt Compare( TAknTreeItemID aFirst, TAknTreeItemID aSecond ) = 0;

    };


#endif // M_AKNCUSTOMTREEORDERING_H
