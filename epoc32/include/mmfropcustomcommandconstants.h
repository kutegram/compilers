/*
* ==============================================================================
*  Name        : MMFROPCustomCommandConstants.h
*  Part of     : Helix Plugin
*
*  Description :
*  Version:
*
*  Copyright © 2006 Nokia Corporation.
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
#ifndef __MMFROPCUSTOMCOMMANDCONSTANTS_H
#define __MMFROPCUSTOMCOMMANDCONSTANTS_H
#include <e32std.h>
/**
 * @publishedAll
 *
 * Interface UID and messages for the ROP Controller API.
 */
const TUid KUidInterfaceMMFROPController = {0x101F855D};
/**
 *  Function constants
 */
enum TMMFROPControllerMessage
{
    EMMFROPControllerGetApplicationConfig,
    EMMFROPControllerSetApplicationConfig,
    EMMFROPControllerGetErrorLog,
    EMMFROPControllerClearErrorLog,

    EMMFROPControllerSetDownloadID,

    EMMFROPControllerSetDownloadComplete,
    EMMFROPControllerSetDownloadSize
};
/**
 *  Constants describing the config version to query
 */
enum TMMFROPControllerConfigVersion
{
    KMMFAudioVideoConfigDefault,   // Configuration created on installation
    KMMFAudioVideoConfigOperator,  // Configuration created on operator setup
    KMMFAudioVideoConfigUser       // Last Configuration saved by the application
};
/**
 *  Constants describing ErrorLog error classes.
 *  XXX  This enumeration must match the EErrorLogClass enumeration located
 *  XXX  in errorlog_sink.h.
 */
enum TMMFROPErrorLogClass
{
    KMMFROPErrorLogRTSP,           // RTSP error (must be first enum)
    KMMFROPErrorLogSendEvents,     // Error Send Events
    KMMFROPErrorLogECXlat,         // Error code translation.
    KMMFROPErrorLogNumClasses      // Number of error log classes (not a class)
};
#endif __MMFROPCUSTOMCOMMANDCONSTANTS_H
