/*
* ==============================================================================
*  Name        : MCLFModifiableItem.h
*  Part of     : Content Listing Framework
*  Interface   : SDK, Content Listing Framework API
*  Description :
*  Version     :
*
*  Copyright � 2002-2004 Nokia. All rights reserved.
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


#ifndef MCLFMODIFIABLEITEM_H
#define MCLFMODIFIABLEITEM_H

//  INCLUDES
#include <MCLFItem.h>

// FORWARD DECLARATIONS
class MCLFModifiableItemExt;

// CLASS DECLARATION

/**
*  Modifiable item for Content Listing Framework.
*  Use ContentListingFactory to create modifiable items. These new items are
*  used as groups in the custom grouper (see MCLFCustomGrouper). Modifiable
*  item is like MCLFItem but you can add new fields to the modifiable item.
*  One item can contain multiple fields, but normally it is not needed in
*  a custom grouper. The field consists of a Field ID and field data. Type
*  of the field is defined with Field ID. See TCLFDefaultFieldId in
*  CLFContentListing.hrh.<br><br>
*  Example:
*  @code
*  // Create a modifiable item and add one string field to it.
*  // Field id is ECLFFieldIdArtist and field value is "test".
*  _LIT( KTest, "test" );
*  MCLFModifiableItem* item = ContentListingFactory::NewModifiableItemLC();
*  item->AddFieldL( ECLFFieldIdArtist, KTest );
*  CleanupStack::Pop(); // item
*  @endcode
*
*  @lib ContentListingFramework.lib
*  @since S60 3.1
*/
class MCLFModifiableItem : public MCLFItem
    {
    public:  // Destructor
        /**
        * Destructor.
        */
        virtual ~MCLFModifiableItem() {}

    public: // New functions

        /**
        * Add new string field to the item.
        * @since S60 3.1
        * @param aFieldId Field ID
        * @param aValue Field value
        */
        virtual void AddFieldL( TCLFFieldId aFieldId,
                                const TDesC& aValue ) = 0;

        /**
        * Add new integer field to the item.
        * @since S60 3.1
        * @param aFieldId Field ID
        * @param aValue Field value
        */
        virtual void AddFieldL( TCLFFieldId aFieldId,
                                TInt32 aValue ) = 0;

        /**
        * Add new time field to the item.
        * @since S60 3.1
        * @param aFieldId Field ID
        * @param aValue Field value
        */
        virtual void AddFieldL( TCLFFieldId aFieldId,
                                const TTime& aValue ) = 0;

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MCLFModifiableItemExt* ModifiableItemExtension() { return NULL; }

    };

#endif      // MCLFMODIFIABLEITEM_H

// End of File
