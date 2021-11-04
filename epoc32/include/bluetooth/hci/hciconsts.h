// Copyright (c) Symbian Software Ltd 2006. All rights reserved.

/**
@file
@publishedPartner
*/

#ifndef HCICONSTS_H
#define HCICONSTS_H

#include <e32def.h>
#include <bluetooth/hci/hcitypes.h>
#include <bluetooth/hci/hciframe.h>

static const TUint8 KSCODefaultTransmissionInterval = 4;
static const TUint8 KSCODefaultRetransmissionWindow = 0;
static const TUint16 KSCODefaultRxPacketLength = 20;
static const TUint16 KSCODefaultTxPacketLength = 20;

// For backwards compatibility with HCI v1
static const TUint16 KSCOTxDefaultPacketLength = KSCODefaultTxPacketLength;

static const TAirMode KSCODefaultAirMode = ECVSD;

static const THCIConnHandle KHCIMinimumHandle = 0x000; /*!< Minimum Handle. */
static const THCIConnHandle KHCIBroadcastHandle	= 0xbca; /*!< Broadcast Handle. */
static const THCIConnHandle KHCIMaximumHandle = 0xeff; /*!< Maximum Handle. */
static const THCIConnHandle KInvalidConnectionHandle = 0xBADC; /*!< Invalid Connection Handle.  */

static const TInt KHCILocalDeviceNameMaxLength = 248; /*!< Local Device Name Max Length. */
static const TInt KHCIRemoteDeviceNameMaxLength = KHCILocalDeviceNameMaxLength; /*!< Remote device name max length. */

static const TInt KHCIAFHChannelMapLength = 10; /*!< AFH Channel Map Length (in bytes, 1 bit per channel, 79 channels). */

// Inquiry stuff - see page 562 of BT Standard 1.1
static const TUint8  KHCIMaximumAmountOfInquiryTime = 0x30; /*!< Maximum amount of inquiry time. */

// Event stuff
static const TUint8  KHCIRemoteNameReqCompleteEventPacketLength = 255; /*!< Remote name request complete event packet length. */

static const TUint16 KHCIClockOffsetValidBit = 1<<15; /*!< Clock offset valid bit. */

// Constants Declaration
static const TUint KHCIMajorVersionNumber=2;
static const TUint KHCIMinorVersionNumber=0;
static const TUint KHCIBuildVersionNumber=1;
static const TUint16 KMaxConnectionAcceptTimeout=0xB540;
static const TUint16 KMinConnectionAcceptTimeout=0x0001;
static const TUint16 KMaxPageTimeout=0xFFFF;
static const TUint16 KMinPageTimeout=0x0001;

static const TUint16 KInvalidParameter=0xDEAD; 
static const THCIConnHandle KHCILargestSupportedConnectionHandle=0x3eff; 

static const TInt KHCIWriteLinkKeyNumKeysOffset = CHctlCommandFrame::KHCICommandPacketHeaderLength + 0;

// used by the HCTL Rx Framer (only in hci_v1, hci_v2 hctls has their own configuration
// of buffer size.
static const TUint KHCIRecvBufSize=2048;
static const TUint KHCISendBufSize=1024;	

// "juice" consts
enum TRemotePageScanRepetitionMode
	{
	EPageScanModeR0,
	EPageScanModeR1,
	EPageScanModeR2
	};

static const TInt KDefaultBluetoothPageScanRepMode = EPageScanModeR2; //R2 works better than R0: see DEF040531
static const TInt KDefaultBluetoothPageScanMode = 0;
static const TInt KDefaultBluetoothClockOffset = 0;
static const TInt KDefaultBluetoothClassOfDevice = 0;

// HCICONSTS_H 
#endif
