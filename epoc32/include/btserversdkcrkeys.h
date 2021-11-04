/*
* ============================================================================
*  Name        : btserversdkcrkeys.h
*  Part of     : Bluetooth Engine / Bluetooth Engine
*  Description : Bluetooth Engine SDK central repository key definitions.
*                The file name is kept as before for compatibility reasons.
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
* Template version: 4.1
*/

#ifndef BTSERVER_SDK_CR_KEYS_H
#define BTSERVER_SDK_CR_KEYS_H


/** 
* @file btserversdkcrkeys.h
* 
* The API provides the BT power state central repository key that is updated by
* the S60 BT Server. The key provides up-to-date information on the BT
* HW power state. Any application may monitor to the cenrep key that is
* updated to receive notifications of any change in state.
*
* The key UID is #KCRUidBluetoothPowerState and following key is provided:
* - #KBTPowerState
*/

/**  Bluetooth Power Mode UID */
const TUid KCRUidBluetoothPowerState = { 0x10204DA9 };

/**
 * The cenrep key for storing the Bluetooth power mode.
 *
 * Valid values are defined by the enum #TBTPowerStateValue
 *
 * Possible values are:
 * 0 Bluetooth chip is not powered/in sleep mode
 * 1 Bluetooth chip is powered up and fully functional
 *
 * Default value: 0
 *
 * @see TBTPowerStateValue
 */
const TUint32 KBTPowerState = 0x00000001;


/**  Enumeration for Bluetooth power mode values */
enum TBTPowerStateValue
    {
    EBTPowerOff,
    EBTPowerOn
    };
#endif // BTSERVER_SDK_CR_KEYS_H
