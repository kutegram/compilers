/*
* ============================================================================
*  Name         : btnotifierAPI.h
*  Part of      : BTNotif
*  Description  : Declares Bluetooth notifiers SDK API.
*  Version      :
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/


#ifndef BTNOTIFIERAPI_H
#define BTNOTIFIERAPI_H

// CONSTANTS

/**
* @file btnotifierapi.h 
* The UID of the Bluetooth Power Mode Notifier. This notifier checks the Bluetooth
* power status, If Bluetooth is off, a dialog is poped up asking user's 
* acceptance of switching on Bluetooth. The notifier is launched via 
* the notifier framework through RNotifier API. 
*
* Sample code of using RNotifier:
*
*  RNotifier notifier;
*  TRequestStatus status;
*  TPckgBuf <TBool> param, result;
*  notifier.StartNotifierAndGetResponse (status, KPowerModeSettingNotifierUid, param, result);
*/

const TUid KPowerModeSettingNotifierUid = {0x100059E2}; 

#endif // BTNOTIFIERAPI_H

// End of File
