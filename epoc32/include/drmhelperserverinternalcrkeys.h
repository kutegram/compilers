/*
* ==============================================================================
*  Name        : DRMHelperServerInternalCRKeys.h
*  Part of     : DRM Helper Server
*  Description : 
*  Version     :
*
*  Copyright (c) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef DRMHELPERSERVERINTERNALCRKEYS_H
#define DRMHELPERSERVERINTERNALCRKEYS_H

//#include <DRMHelperServerSDKCRKeys.h>

const TUid KCRUidDRMHelperServer = {0x10205CA7};

/* Key format for both KDRMHelperServerNotification and KDRMHelperServerNotificationPassive

To inform the expiration event of automated usage to active clients. 
The first Tuint8 is the times the content has been informed, the second
 Tuint8 could either be 'E' or 'V', 'E' means expired and 'V' means 
 valid but about to expire. The third is permission type (which is 
 defined in caf.h, including EPlay, EExcute, EView, EPrint, EPeek). 
 The rest of data is the content ID. So, the whole format of the 
 values would be "<TUint8 aTimes><TUint8 aExpirationMark><TUint8
  aPermissionType><TDesC8 aContentID>".
  
*/ 

const TUint32 KDRMHelperServerNotification = 0x00000001;
const TUint32 KDRMHelperServerNotificationPassive = 0x00000002;

#endif      // DRMHELPERSERVERINTERNALCRKEYS_H

