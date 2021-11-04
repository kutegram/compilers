// btsecmanclient.h
// 
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

#ifndef BTSECMANCLIENT_H
#define BTSECMANCLIENT_H

#include <btmanclient.h>

/**
@internalAll

Struct used to transfer BT address to host resolver to indicate notification of event
**/
NONSHARABLE_CLASS(TBTHostResolverNotification)
	{
public:
	TBTDevAddr iBDAddr;
	TInt iNotification;
	};

/**
@internalAll

Struct used to transfer device information to host resolver.
**/
NONSHARABLE_CLASS(TBTHostResolverDeviceInfo)
	{
public:
	TBTDevAddr iBDAddr;
	TUint8 iPageScanRepMode;				/*!< Page Scan repetition mode of remote device*/
	TUint8 iPageScanMode;					/*!< Page scan mode of remote device*/
	TUint16 iClockOffSet;					/*!< clock off set of remote device*/
	};

/**
@internalAll

Struct used to transfer new Juice information from host resolver client to server.
Juice information contains data pertaining to 
**/
NONSHARABLE_CLASS(TBTHostResolverNewJuice)
	{
public:
	TBTDevAddr iBDAddr;
	TUint32 iPageScanRepMode;				///< Page Scan repetition mode of remote device
	TUint32 iPageScanMode;					///< Page scan mode of remote device
	TUint32 iClockOffSet;					///< clock off set of remote device
	};


/**
@internalAll

Struct used to transfer new link key event params from client to server.
**/
NONSHARABLE_CLASS(TBTSecManNewLinkKeyParams)
	{
public:
	TBTDevAddr iBDAddr;
	TBTLinkKey iLinkKey;
	};

/**
@internalAll

Typedef'ed pckgbuf to send a TBTSecManNewLinkKeyParams object over IPC.
*/
typedef TPckgBuf<TBTSecManNewLinkKeyParams> TBTSecManNewLinkKeyParamsPckg;

/**
@internalAll

Typedef'ed pckgbuf to send a TBTHostResolverNotification object over IPC.
*/
typedef TPckgBuf<TBTHostResolverNotification> TBTHostResolverNotificationPckg;


#endif
