// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedPartner

*/

#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

/**
Message type enumeration.
*/
enum TRemConMessageType
	{
	/** Undefined message type. */
	ERemConMessageTypeUndefined = 0,

	/** Command. */
	ERemConCommand,
	
	/** Response. */
	ERemConResponse,

	/** Errored Response or Reject. */
	/** Treated as a command completion by RemCon */
	ERemConReject,
	
	/** NotifyCommand */
	ERemConNotifyCommand,
	};

enum TRemConMessageSubType
	{
	/** Default command or response */
	ERemConMessageDefault = 0,
	
	/** Notify command requiring an interim response and (later) changed response */
	ERemConNotifyCommandAwaitingInterim,
	
	/** Notify command requiring only a changed response, after notify has been readdressed */
	ERemConNotifyCommandAwaitingChanged,
	
	/** Notify interim response */
	ERemConNotifyResponseInterim,
	
	/** Notify changed response */
	ERemConNotifyResponseChanged,
	};

// MESSAGETYPE_H
#endif
