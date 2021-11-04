/*
* ==============================================================================
*  Name        : DclCRKeys.h
*  Part of     : DataConnectionLogger
*  Description : Contains Central Repository keys needed in logging GPRS/WLAN counters.
*
*  Copyright © 2004-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/

#ifndef DCLCRKEYS_H
#define DCLCRKEYS_H

const TUid KCRUidDCLLogs = {0x101F4CD5}; 

// Amount of total sent bytes using GPRS.
const TUint32 KLogsGPRSSentCounter     = 0x0000000C;

// Amount of total received bytes using GPRS.
const TUint32 KLogsGPRSReceivedCounter = 0x0000000D;

// Amount of total sent bytes using WLAN.
const TUint32 KLogsWLANSentCounter     = 0x00000014;

// Amount of total received bytes using WLAN.
const TUint32 KLogsWLANReceivedCounter = 0x00000015;

#endif      // DCLCRKEYS_H

// End of File
