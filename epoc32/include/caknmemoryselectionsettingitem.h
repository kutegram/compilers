/*
* ============================================================================
*  Name        : CAknMemorySelectionSettingItem.h
*  Part of     : Common File Dialogs / CommonDialogs.dll
*  Description : The setting item to use CAknMemorySelectionSettingPage.
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
* Template version: 4.1
*/


#ifndef C_AKNMEMORYSELECTIONSETTINGITEM_H
#define C_AKNMEMORYSELECTIONSETTINGITEM_H

#include <AknSettingItemList.h>
#include <CAknMemorySelectionSettingPage.h>

/**
 *  CAknMemorySelectionSettingItem is a setting item class that
 *  launches a CAknMemorySelectionSettingPage.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 1.2
 */
class CAknMemorySelectionSettingItem : public CAknSettingItem
    {
public:

// Constructors and destructor

    /**
     * Constructor
     */
    IMPORT_C CAknMemorySelectionSettingItem(
        TInt aIdentifier,
        CAknMemorySelectionSettingPage::TMemory& aSelectedMemory );

    IMPORT_C virtual ~CAknMemorySelectionSettingItem();
    IMPORT_C void CompleteConstructionL();

// Functions from base class CAknSettingItem

    /**
    * From CAknSettingItem
    */
    IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

    /**
    * From CAknSettingItem
    */
    IMPORT_C virtual void LoadL();

    /**
    * From CAknSettingItem
    */
    IMPORT_C virtual void StoreL();

    /**
    * From CAknSettingItem
    */
    IMPORT_C virtual const TDesC& SettingTextL();

protected: // Data

    // Ref: External data
    CAknMemorySelectionSettingPage::TMemory& iExternalData;

    // Own: Internal data
    CAknMemorySelectionSettingPage::TMemory iInternalData;

    // Own: Setting page
    CAknMemorySelectionSettingPage* iSettingPage;

    // Own: The length is enough for memory name.
    TBuf<64> iSettingText;

    };

#endif      // C_AKNMEMORYSELECTIONSETTINGITEM_H
