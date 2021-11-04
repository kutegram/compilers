/*
* ==============================================================================
*  Name        : MCLFCustomSorter.h
*  Part of     : Content Listing Framework
*  Interface   : SDK, Content Listing Framework API
*  Description :
*  Version     :
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia. All rights are reserved. Copying, including
*  reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef MCLFCUSTOMSORTER_H
#define MCLFCUSTOMSORTER_H

//  INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class MCLFItem;
class MCLFCustomSorterExt;

// CLASS DECLARATION

/**
*  Custom sorter interface for Content Listing Framework.
*  With this interface, client can create a customized sorter for
*  sorting items in list model. For example, items in the List Model
*  can be sorted by Item IDs or it can be randomized.<br><br>
*  Example:
*  @code
*  // Example sorter that sorts items by Item IDs
*  void CMySorter::SortItemsL( RPointerArray<MCLFItem>& aItemArray )
*      {
*      TLinearOrder<MCLFItem> sorter( CMySorter::Compare );
*      aItemArray.Sort( sorter );
*      }
*
*  TInt CMySorter::Compare( const MCLFItem& aFirst, const MCLFItem& aSecond )
*      {
*      return aFirst.ItemId() - aSecond.ItemId();
*      }
*  @endcode
*
*  Custom sorter is activated and removed by calling method
*  MCLFItemListModel::SetCustomSorter
*
*  @lib ContentListingFramework.lib
*  @since S60 3.1
*/
class MCLFCustomSorter
    {
    public: // New functions

        /**
        * Abstract method for sorting Content Listing Framework items in a list
        * model. This method is called when the sorting process is executed
        * by calling refresh to the List Model.
        * @since S60 3.1
        * @param aItemArray The array to sort. Contains all items of
        *        the List Model.
        */
        virtual void SortItemsL( RPointerArray<MCLFItem>& aItemArray ) = 0;

    protected:

        /**
        * Destructor.
        */
        virtual ~MCLFCustomSorter() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MCLFCustomSorterExt* Extension() { return NULL; }

    };

#endif      // MCLFCUSTOMSORTER_H

// End of File
