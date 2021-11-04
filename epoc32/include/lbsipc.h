/*
* ==============================================================================
*  Name        : LbsIpc.h
*  Part of     : Mobile Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Client-Server Request codes
*  Version     :
*
*  Copyright (c) 2002-2005 Nokia Corporation.
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

#ifndef __LBSIPC_H__
#define __LBSIPC_H__

// 0x00000000 to 0x00000FFF not used
#define EPositioningIpcOffset           0x1000

// 0x00001000 to 0x00001FFF reserved for RPositionServer requests
#define EPositionServerIpcOffset        (EPositioningIpcOffset)

// 0x00002000 to 0x00002FFF reserved for RPositioner requests
#define EPositionerIpcOffset            (EPositionServerIpcOffset + 0x1000)

// 0x40000000 to 0x7FFFFFFF reserved for 3rd party extensions to the LBS API.
// All extensions implemented by 3rd parties should be implemented in this range.
#define EPositionerCustomIpcOffset      0x40000000


enum TPositionIpcId
    {
    //
    // Request IDs

    EPositionServerCancelAsyncRequest       = EPositionServerIpcOffset,
    EPositionServerConnect,
    EPositionServerGetDefaultModuleId,
    EPositionServerGetNumModules,
    EPositionServerGetModuleInfoByIndex,
    EPositionServerGetModuleInfoById,
    EPositionServerGetModuleStatus,
    EPositionServerNotifyModuleStatusEvent,

    EPositionerCancelAsyncRequest           = EPositionerIpcOffset,
    EPositionerOpen,
    EPositionerOpenModuleId,
    EPositionerOpenCriteria,
    EPositionerClose,
    EPositionerSetSingleRequestor,
    EPositionerSetMultipleRequestors,
    EPositionerSetUpdateOptions,
    EPositionerGetUpdateOptions,
    EPositionerGetLastKnownPosition,
    EPositionerNotifyPositionUpdate,

    EPositionerCustomCodesBegin             = EPositionerCustomIpcOffset,
    };

#endif // __LBSIPC_H__
