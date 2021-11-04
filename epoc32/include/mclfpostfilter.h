/*
* ==============================================================================
*  Name        : MCLFPostFilter.h
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


#ifndef MCLFPOSTFILTER_H
#define MCLFPOSTFILTER_H

//  INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class MCLFPostFilterExt;
class MCLFItem;

// CLASS DECLARATION

/**
*  Post filter interface for Content Listing Framework.
*  With this interface client you can add own post filter to
*  exclude items from list model.<br><br>
*  Example:
*  @code
*  // This example filters items by drive letter:
*  // Items that are in phone memory are included to the list model.
*  // All other items will be filtered.
*  void CMyFilter::FilterItemsL( const TArray<MCLFItem*>& aItemList,
*                                RPointerArray<MCLFItem>& aFilteredItemList )
*      {
*      TCharF phoneMemory( PathInfo::PhoneMemoryRootPath()[0] );
*      TInt count( aItemList.Count() );
*      for( TInt i = 0 ; i < count ; ++i )
*          {
*          TPtrC ptr;
*          MCLFItem* item = aItemList[i];
*          TInt error( item->GetField( ECLFFieldIdDrive, ptr ) );
*          if( error == KErrNone )
*              {
*              TCharF memory( ptr[0] );
*              if( memory == phoneMemory )
*                  {
*                  aFilteredItemList.AppendL( item );
*                  }
*              }
*          }
*      }
*  @endcode
*  @lib ContentListingFramework.lib
*  @since S60 3.1
*/
class MCLFPostFilter
    {
    public: // New functions

        /**
        * Abstract method to filter source list. This method is called when
        * the filtering process is executed by list model refresh.
        * @since S60 3.1
        * @param aItemList Source list, contains all items that are in
        *        the list model
        * @param aFilteredItemList Filtered/destination list, contains all items
                 that will be in the list model after filtering.
        */
        virtual void FilterItemsL( const TArray<MCLFItem*>& aItemList,
                                   RPointerArray<MCLFItem>& aFilteredItemList ) = 0;

    protected:

        /**
        * Destructor.
        */
        virtual ~MCLFPostFilter() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MCLFPostFilterExt* Extension() { return NULL; }


    };

#endif      // MCLFPOSTFILTER_H

// End of File
