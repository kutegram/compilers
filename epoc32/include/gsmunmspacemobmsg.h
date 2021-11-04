// GSMUNMSPACEMOBMSG.H
//
// Copyright (c) Symbian Software Ltd. 2004-2006.  All rights reserved.
//

/**
 *  @file
 *  Multimode SMS common API header file.
 *  
 *  Describes common Telephony interface types for SMS messaging.
 *  The types are duplicated from ETELMM.h in an effort to separate SMS from ETEL.
 *  Correspondent ETEL types could be found in ETELMM.h, class RMobileSmsMessaging.
 *  
 *  @publishedAll
 *  
 */


#ifndef __GSMUNMSPACEMOBMSG_H__
#define __GSMUNMSPACEMOBMSG_H__

/**
 *  PDU types.
 *  
 *  Modes: Common
 *  
 *  @see class class RMobileSmsMessaging
 */
namespace NMobileSmsMessaging
	{
	// Definitions for sizes of TPDU and User Data fields
	enum
		{
		KGsmTpduSize = 165,		// 140 bytes user data + 25 bytes TPDU header
		KCdmaTpduSize  = 256	// Max size of Bearer Data in Transport Layer message
		};

	/** A typedef'd buffer for GSM or WCDMA message data.*/
	typedef TBuf8<KGsmTpduSize>	TMobileSmsGsmTpdu;
	/** A typedef'd buffer for CDMA message data.*/
	typedef TBuf8<KCdmaTpduSize> TMobileSmsCdmaTpdu;
	}

// __GSMUNMSPACEMOBMSG_H__
#endif
