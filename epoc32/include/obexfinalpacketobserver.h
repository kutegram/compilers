// ObexFinalPacketObserver.h
//
// Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.

#ifndef OBEXFINALPACKETOBSERVER_H
#define OBEXFINALPACKETOBSERVER_H

#include <e32std.h>

/**
This mixin class must be inherited by any class interested in final packet notifications. 

@publishedAll

*/

class MObexFinalPacketObserver
	{
public:

	/** Indicates start of final packet.
	@publishedAll
	
	*/
	virtual void MofpoFinalPacketStarted() {};

	/** Indicates end of final packet.
	@publishedAll
	
	*/
	virtual void MofpoFinalPacketFinished() {};
	};

// OBEXFINALPACKETOBSERVER_H
#endif

