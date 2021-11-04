/*
* =============================================================================
*  Name          : sipcrkeys.h
*  Part of       : SIP API
*  Description   :
*  Version       : SIP/4.0
*
*  Copyright (c) 2005 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* =============================================================================
*/
#ifndef SIPCRKEYS_H
#define SIPCRKEYS_H

// INCLUDES
#include <e32def.h>

/*
* @file
* @publishedAll
* 
*/


/**
* Defines configuration parameters used by the SIP stack.
*/
const TUid KCRUidSIP = { 0x101FED88 };

/**
* Defines SIP transaction timer T1 in milliseconds as per RFC3261.
*/
const TUint32 KSIPTransactionTimerT1 = 0x01;

/**
* Defines SIP transaction timer T2 in milliseconds as per RFC3261.
*/
const TUint32 KSIPTransactionTimerT2 = 0x02;

/**
* Defines SIP transaction timer T4 in milliseconds as per RFC3261.
*/
const TUint32 KSIPTransactionTimerT4 = 0x03;	


// SIPCRKEYS_H
#endif

// End of File
