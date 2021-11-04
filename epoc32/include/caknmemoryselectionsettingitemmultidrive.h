/*
* ============================================================================
*  Name        : CAknMemorySelectionSettingItemMultiDrive.h
*  Part of     : Common File Dialogs / CommonDialogs.dll
*  Description : New memory selection setting item to support multiple drives.
*  Version     : %version: be1s60pr#2 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright 2007 Nokia.  All rights reserved.
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


#ifndef C_AKNMEMORYSELECTIONSETTINGITEMMULTIDRIVE_H
#define C_AKNMEMORYSELECTIONSETTINGITEMMULTIDRIVE_H

#include <AknSettingItemList.h>

class CAknMemorySelectionSettingItemExtension;
class CAknCFDFileSystemEvent;

/**
 *  CAknMemorySelectionSettingItemMultiDrive is a setting item class that
 *  launches a CAknMemorySelectionDialogMultiDrive. It is used to replace
 *  old CAknMemorySelectionSettingItem for multiple drive support.
 *
 *  
 *  
 */
class CAknMemorySelectionSettingItemMultiDrive : public CAknSettingItem
    {
        
public:
    
// Constructors and destructor

    /**
     * Constructor
     *
     * 
     */
    IMPORT_C CAknMemorySelectionSettingItemMultiDrive(
        TInt aIdentifier,
        TDriveNumber& aSelectedDrive
        );            
            
    IMPORT_C virtual ~CAknMemorySelectionSettingItemMultiDrive();
    
    /**
     * The 2nd phase constructor. It is called internally when extension
     * object is needed. User also could call it after creating a object of
     * CAknMemorySelectionSettingItemMultiDrive.
     *
     * 
     */
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
    
    /**
     * Update contents of setting item
     */
    void UpdateSettingItemContentL();
    
protected: // Data

    // Ref: External data
    TDriveNumber& iExternalData;

    // Own: Internal data
    TDriveNumber iInternalData;
    
    // Own: Pointer to extension object
    CAknMemorySelectionSettingItemExtension* iExtension;

    // Own: The length is enough for memory name.
    HBufC* iSettingText;
    
    };

// C_AKNMEMORYSELECTIONSETTINGITEMMULTIDRIVE_H
#endif
