//
// obextransportinfo.h
//
// Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
//

#ifndef __OBEXTRANSPORTINFO_H__
#define __OBEXTRANSPORTINFO_H__

#include <e32std.h>

/**
This class is a combination of the TObexProtocolInfo and TObexProtocolPolicy 
classes.
This class is designed for licensee derivation, to support novel transport 
controllers. Existing superclasses include @c TObexUsbTransportInfo, @c 
TObexUsbV2TransportInfo, @c TObexBtTransportInfo and @c TObexIrTransportInfo. 
It is also designed for 3rd party instantiation, for use when creation a 
CObexServer or a CObexClient.

Note that, being a T-type, this type and all derived types must hold data by 
value, to support bitwise copying.

@publishedAll

*/
class TObexTransportInfo
	{
public:
	/**
	The type of the transport over which obex will run.
	The size of the buffer is chosen for historical reasons. This is the size 
	originally used by TObexProtocolInfo.
	@publishedAll
	
	*/
	TBuf<60> iTransportName; 
	
	/**
	The version of the protocol policy format that this class supports
	@publishedAll
	
	*/
	TUint16 iVersion;
	
	/**
	The maximum size of the receive packet buffer for the policy
	@publishedAll
	
	*/
	TUint16 iReceiveMtu;
	
	/**
	The maximum size of the transmit packet buffer for the policy
	@publishedAll
	
	*/
	TUint16 iTransmitMtu;
	
	/**	*/
	TUint16 iFuture1;
	
	/**	*/
	TUint32 iFuture2;
	
	/**	*/
	TInt iFuture3;
	
	/**	*/
	TInt iFuture4;
	};

// __OBEXTRANSPORTINFO_H__
#endif
