/*
* ==============================================================================
*  Name        : MCLFCustomGrouper.h
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


#ifndef MCLFCUSTOMGROUPER_H
#define MCLFCUSTOMGROUPER_H

//  INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class MCLFCustomGrouperExt;
class MCLFItem;

// CLASS DECLARATION

/**
*  Custom grouper interface of Content Listing Framework.
*  With this interface, client can add own custom grouper
*  to its List Model. Custom grouper is used for grouping list model items.
*  For example, List Model of music files can be grouped by genre or artist
*  name by using this interface.
*  Use ContentListingFactory to create items for new groups (MCLFModifiableItem).
*  <br><br>
*  Example:
*  @code
*  // This grouper will overwrite the source list and add three items to model.
*  void CMyGrouper::GroupItemsL( const TArray<MCLFItem*>& aSourceList,
*                                RPointerArray<MCLFItem>& aGroupedList )
*      {
*      _LIT( KTest, "test" );
*      MCLFModifiableItem* item = ContentListingFactory::NewModifiableItemLC();
*      item->AddFieldL( ECLFFieldIdName, KTest );
*      aGroupedList.AppendL( item );
*      CleanupStack::Pop(); // item
*
*      _LIT( KTest1, "test1" );
*      item = ContentListingFactory::NewModifiableItemLC();
*      item->AddFieldL( ECLFFieldIdName, KTest1 );
*      aGroupedList.AppendL( item );
*      CleanupStack::Pop(); // item
*
*      _LIT( KTest2, "test2" );
*      item = ContentListingFactory::NewModifiableItemLC();
*      item->AddFieldL( ECLFFieldIdName, KTest2 );
*      aGroupedList.AppendL( item );
*      CleanupStack::Pop(); // item
*      }
*  @endcode
*
*  Custom grouper is activated and removed by calling method
*  MCLFItemListModel::SetCustomGrouper
*
*  @lib ContentListingFramework.lib
*  @since S60 3.1
*/
class MCLFCustomGrouper
    {
    public: // New functions

        /**
        * Abstract method for grouping Content Listing Framework items of
        * list models. This method is called when the grouping process is
        * executed by refreshing the model.
        * @since S60 3.1
        * @param aSourceList Source list. Contains all items that are in
        *        the list model when the grouping process starts.
        * @param aGroupedList Grouped/destination list. While grouping, each
        *        group should be added to this list. The list model will
        *        contain only these items when the grouping process is
        *        finished.
        */
        virtual void GroupItemsL( const TArray<MCLFItem*>& aSourceList,
                                  RPointerArray<MCLFItem>& aGroupedList ) = 0;

    protected:

        /**
        * Destructor.
        */
        virtual ~MCLFCustomGrouper() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MCLFCustomGrouperExt* Extension() { return NULL; }

    };

#endif      // MCLFCUSTOMGROUPER_H

// End of File
