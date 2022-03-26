//
// obextransportconstants.h
//
// Copyright (c) 2005 - 2006 Symbian Software Ltd.  All rights reserved.
//

#ifndef __OBEXTRANSPORTCONSTANTS_H__
#define __OBEXTRANSPORTCONSTANTS_H__

/**
@file
@internalTechnology
*/

#include <e32base.h>

const TUint8 KObexConnectionIDLength = 4;

typedef TUint16 TObexHeaderMask;
typedef TUint8 TObexOpcode;
typedef TBuf8<KObexConnectionIDLength> TConnId;
typedef TBuf8<16> TNonce;
typedef TBuf8<16> TRequestDigest;

/**
This enum is for INTERNAL USE ONLY.

The enum values are signals sent between layers in OBEX. Some of them result 
in user-visible notifications and some don't.

Their numerical values are not significant, with the exception of the fact 
that EObexFinalPacketStarted must have a lower numerical value than 
EObexFinalPacketFinished. If both of these signals are outstanding on a packet 
at once, the user will be notified in numerical-value order. The 'final packet 
observer' API requires that the signals are given to the user in the order 
'final packet started' then 'final packet finished'. 

These are to be used as fields in a bitmask, so a value must always bit set.
*/
enum TObexPacketProcessEvent
	{
	/** The transport layer has started to write a final packet. */
	EObexFinalPacketStarted = 0x1,

	/** The transport layer has finished writing a final packet. */
	EObexFinalPacketFinished = 0x2,

	/** A packet has finished being written. */
	EObexWriteCompleted = 0x4,
	
	/** A packet has finished being written. This is signalled upwards by the 
	transport layer last of all	because it signals the completion of the 
	sending of an ACK to a disconnect command. The OBEX server uses this 
	signal to progress the disconnection. */
	EObexWriteCompletedFinal = 0x8,
	
	/** Read activity has been detected. This is signalled upwards by the 
	transport layer AT LEAST when the first read of a new Obex operation 
	is detected.	*/
	EObexReadActivityDetected = 0x10,
	};

typedef TUint TObexPacketProcessEvents;

//__OBEXTRANSPORTCONSTANTS_H
#endif
