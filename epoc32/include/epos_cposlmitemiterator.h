/*
* ==============================================================================
*  Name        : EPos_CPosLmItemIterator.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK/S60, Landmarks API
*  Description : CPosLmItemIterator class
*  Version     : %version: 2 % 
*
*  Copyright © 2005-2006 Nokia.  All rights reserved.
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

#ifndef CPOSLMITEMITERATOR_H
#define CPOSLMITEMITERATOR_H

#include <e32base.h>
#include "EPos_Landmarks.h"

/**
*  Landmark item iterator.
*
*  This is an abstract base class for objects which iterates a set of database
*  items in a single database.
*
*  A database item is an item which is stored in a landmark database, i.e. a
*  landmark or a landmark category.
*
*  Note that an iterator either iterates categories or landmarks. The items are
*  never mixed.
*
*  This class does not export a constructor. The instance is created by the
*  operation which generates the item set to be iterated. The iterator may
*  implement a caching scheme, but that scheme depends on what is iterated.
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*/
class CPosLmItemIterator : public CBase
    {
    public:

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLmItemIterator();

    public:

        /**
        * Returns the next database item ID in the iterated set.
        *
        * The first call will return the first database item ID in the set.
        *
        * @return The next database item ID, or @p KPosLmNullItemId if there
        *   are no more database items in the iterated set.
        */
        virtual TPosLmItemId NextL() = 0;

        /**
        * Resets the database item iterator.
        *
        * The next call to @ref NextL will return the first database item ID in
        * the iterated set.
        */
        virtual void Reset() = 0;

        /**
        * Returns the number of database items which are iterated.
        *
        * @return Number of items in the iterated database item set.
        */
        virtual TUint NumOfItemsL() = 0;

        /**
        * Fetches a sequence of database items from the iterated set.
        *
        * The client supplies an ID array which will be filled by this
        * operation. The array will be reset before any items are added.
        *
        * The client specifies which database item sequence to fetch by
        * supplying a start index (0 is the first item) and the number of items
        * to fetch.
        *
        * @param[out] aIdArray On return contains the requested items.
        * @param[in] aStartIndex The index of the first item to fetch.
        * @param[in] aNumOfItems The number of items to fetch
        *
        * @panic "Landmarks Client"-EPosSpecifiedIntervalLiesOutsideIteratedSet 
        *   specified interval lies [partially] outside the iterated set.
        */
        virtual void GetItemIdsL(
            RArray<TPosLmItemId>& aIdArray,
            TInt aStartIndex,
            TInt aNumOfItems
        ) = 0;

    protected:

        // C++ constructor.
        IMPORT_C CPosLmItemIterator();

    private:

        // Prohibit copy constructor
        CPosLmItemIterator( const CPosLmItemIterator& );
        // Prohibit assigment operator
        CPosLmItemIterator& operator= ( const CPosLmItemIterator& );

    };

#endif      // CPOSLMITEMITERATOR_H


