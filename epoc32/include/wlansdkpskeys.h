/*
* ==============================================================================
*  Name        : wlansdkpskeys.h
*  Part of     : WLAN Engine / Adaptation
*  Interface   : 
*  Description : WLAN event enumerations and uid:s for Publish And Subscribe.
*                PubSub clients can include this file and listen to these events.
*                These events will be routed through Publish And Subscribe.
*  Version     : %version: 1 %
*
*  Copyright © 2002-2007 Nokia. All rights reserved.
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

#ifndef WLANSDKPSKEYS_H
#define WLANSDKPSKEYS_H

#include <e32property.h>


/**
* P&S category WLAN information
*/
const TUid KPSUidWlan = { 0x101f8ec5 };


/**
* WLAN MAC address
* The MAC address array consists of 6 consecutive bytes which can be used 
* to produce the address in format XX:XX:XX:XX:XX:XX  
*/
const TUint KPSWlanMacAddress = 0x00000001;
const RProperty::TType KPSWlanMacAddressType = RProperty::EByteArray;

/**
* Length of the MAC address array
*/
const TUint KPSWlanMacAddressLength = 6;

#endif // WLANSDKPSKEYS_H
           
//  End of File
