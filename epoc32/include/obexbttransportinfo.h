//
// obexbttransportinfo.h
//
// Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
//

#ifndef __OBEXBTTRANSPORTINFO_H__
#define __OBEXBTTRANSPORTINFO_H__

#include <bt_sock.h>
#include <obextransportinfo.h>

/**
Concrete transport info type for use when using RFCOMM transport controller.
@publishedAll

*/
NONSHARABLE_CLASS(TObexBtTransportInfo) : public TObexTransportInfo
	{
public:
	/**
	The BT device address of the remote party.
	*/
	TBTSockAddr iAddr;
	};

// __OBEXBTTRANSPORTINFO_H__
#endif
