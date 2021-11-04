// GSMUNMSPACEMOBSTORE.h
//
// Copyright (c) Symbian Software Ltd. 2004-2006.  All rights reserved.
//

/**
 *  @file
 *  Multimode SMS common API header file.
 *  
 *  Describes common Telephony interface types for SMS stores.
 *  The types are duplicated from ETELMM.h in an effort to separate SMS from ETEL.
 *  Correspondent ETEL types could be found in ETELMM.h, class RMobileSmsStore.
 *  
 *  @publishedAll
 *  
 */

#ifndef __GSMUNMSPACEMOBSTORE_H__
#define __GSMUNMSPACEMOBSTORE_H__


/**
 *  Defines contents of a fixed-size, stored SMS entry.
 *  
 *  Modes: Common
 *  
 *  These types are duplicated from ETELMM.h.
 *  
 *  @see class RMobileSmsStore
 */
namespace NMobileSmsStore
	{
	enum TMobileSmsStoreStatus
		{
		/** The status of the SMS is unknown.*/
		EStoredMessageUnknownStatus,
		/**
		 *  The SMS is stored phone-side. It is an incoming message
		 *  		that has not been read yet.
		 */
		EStoredMessageUnread,
		/**
		 *  The SMS is stored phone-side. It is an incoming message
		 *  		that has already been read.
		 */
		EStoredMessageRead,
		/**
		 *  The SMS is stored phone-side. It is an outgoing message
		 *  		that has not been sent yet.
		 */
		EStoredMessageUnsent,
		/**
		 *  The SMS is stored phone-side. It is an outgoing message
		 *  that has already been sent but a delivery/status report has
		 *  either not been received yet or was not requested in the first
		 *  		place.
		 */
		EStoredMessageSent,
		/**
		 *  The SMS is stored phone-side. It is an outgoing message
		 *  that has already been sent and a delivery/status report has
		 *  		been received 
		 */
		EStoredMessageDelivered
		};
	}

// __GSMUNMSPACEMOBSTORE_H__
#endif
