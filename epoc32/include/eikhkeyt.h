/*
* ============================================================================
*  Name        : eikhkeyt.h
*  Part of     : S60 UI Framework / EikCoCtl
*  Description : Class declaration for EIKON hotkey table.
*  Version     : %version: 1 %
*
*  Copyright © 2002-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/

#ifndef __EIKHKEYT_H__
#define __EIKHKEYT_H__

#include <e32base.h>
#include <e32keys.h>

/**
 * Hotkey parameters. This can be added to a hotkey table using
 * the functions provided by the @c CEikHotKeyTable class.
 */
struct SEikHotKey
	{
	TInt iCommandId; ///< The command ID associated with the hotkey.
	TInt iKeycode;   ///< The key code associated with the hotkey.
	};

/**
 * An array for hotkey commands and their associated key codes and modifiers.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9
 */
class CEikHotKeyTable : public CArrayFixFlat<SEikHotKey>
	{
public:

    /**
     * Default C++ constructor.
     */
	IMPORT_C CEikHotKeyTable();
	
	/**
     * Destructor
     */
	IMPORT_C ~CEikHotKeyTable();
	
	/**
     * Gets the hotkey code and modifier for the specified command ID.
     *
     * @param      aCommandId  The ID of the hotkey for which the key code and
     *                         modifiers are obtained.
     * @param[out] aKeycode    On return, the key code for the
     *                         specified command ID.
     * @param[out] aModifiers  On return, the modifier for the
     *                         specified command ID.
     *
     * @return     @c ETrue if the hotkey exists, @c EFalse otherwise
     */
	IMPORT_C TBool HotKeyFromCommandId( TInt aCommandId,
	                                    TInt& aKeycode,
	                                    TInt& aModifiers) const;
	
	/**
     * Gets the command ID associated with the specified key code and modifier.
     *
     * @param aKeycode   The key code for which the command ID is obtained.
     * @param aModifiers The key modifier for which the command ID is obtained.
     *
     * @return The command ID for the specified key code and modifier.
     */
	IMPORT_C TInt CommandIdFromHotKey(TInt aKeycode,TInt aModifiers) const;
	
	/**
     * Adds the specified hotkey to the hotkey array.
     *
     * @param aCommandId  The command associated with the hotkey.
     * @param aKeycode    The key code used to invoke the command.
     * @param aModifiers  Any modifiers used to invoke the command,
     *                    shift or control for example.
     *
     * @leave KErrNotSupported If the specified modifier is not supported
     */
	IMPORT_C void AddItemL(TInt aCommandId,TInt aKeycode,TInt aModifiers);
	
	/**
     * Removes the item specified by command ID from the array.
     *
     * @param aCommandId The ID of the item to remove.
     * @panic EIKCOCTL-7 If the array contains no hotkeys.
     */
	IMPORT_C void RemoveItem(TInt aCommandId);
	
	/**
     * Constructs an empty array from resource.
     *
     * @param aResourceId  The ID if the resource reader to use to
     *                     construct the array.
     */
	IMPORT_C void ConstructFromResourceL(TInt aResourceId);
	
	/**
     * Resets the hotkey array.
     */
	IMPORT_C void Reset();
	
private:
	TInt iNumberPlain;
	TInt iNumberCtrl;
	TInt iNumberShiftCtrl;
	TInt iSpare;
	};

#endif // __EIKHKEYT_H__
