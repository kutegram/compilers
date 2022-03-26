// Copyright (c) Symbian Software Ltd 2006. All rights reserved.

/**
@file
@publishedPartner
*/

#ifndef HCTLCHANNELOBSERVER_H
#define HCTLCHANNELOBSERVER_H

/** Definition of the HCI transport channel type */
typedef TUint16 THCITransportChannel;	

/** No HCI transport channels available for sending */
static const THCITransportChannel KHCITransportNoChannels		= 0x0000;

/** Command HCI transport channel available for sending */
static const THCITransportChannel KHCITransportCommandChannel	= 0x0001;

/** ACL data HCI transport channel available for sending */
static const THCITransportChannel KHCITransportACLDataChannel	= 0x0002;

/** SCO data HCI transport channel available for sending */
static const THCITransportChannel KHCITransportSCODataChannel	= 0x0004;

/** All HCI transport channels available for sending */
static const THCITransportChannel KHCITransportAllChannels = static_cast<THCITransportChannel>(KHCITransportCommandChannel | 
																							   KHCITransportACLDataChannel | 
																							   KHCITransportSCODataChannel);

/** The UID associated with the MHCTLChannelObserver interface. */
const TInt KHCTLChannelObserverUid = 0x102736EF;

/**
API for observing information regarding the status of a HCTL channel.

This should be implemented by the stack so it can control the multiplexing
of the command and data sent over the HCTL.
*/
class MHCTLChannelObserver
	{
public:
	/**
	Indication that a HCTL channel has been opened.

	@param aChannel A bitmask containing the channels which are now open.
	*/
	virtual void MhcoChannelOpen(THCITransportChannel aChannels) =0;

	/**
	Indication that a HCTL channel has been closed.

	@param aChannel A bitmask containing the channels which are now closed.
	*/
	virtual void MhcoChannelClosed(THCITransportChannel aChannels) =0;
	};

// HCTLCHANNELOBSERVER_H
#endif
