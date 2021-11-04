// TNONOPERATIONMTMDATA.H
//
// Copyright (c) Symbian Software Ltd 2007.  All rights reserved. 
//

#ifndef __TNONOPERATIONMTMDATATYPE_H__
#define __TNONOPERATIONMTMDATATYPE_H__

#include <e32std.h>

/**
UID used by the Extension_ method for CBaseServerMtm to identify that the
non operation MTM data has been requested.

@internalComponent
@published
*/
const TUint KUidMsgNonOperationMtmData = 0x1028368e;

/**
Defines the types of non operation MTM data that can be requested from a
server MTM.

@internalComponent
@published
*/
enum TNonOperationMtmDataType
	{
	EMtmDataAccessPointId = 0
	};

/**
Structure to store IAP value for non operation MTM data IAP request

@internalComponent
@published
*/
struct TNonOperationMtmDataAccessPointId
	{
	TUint32 iAccessPointId;
	};

/**
Package to store result for non operation MTM data IAP request

@internalComponent
@published
*/
typedef TPckgBuf<TNonOperationMtmDataAccessPointId> TNonOperationMtmDataAccessPointIdBuffer;

// #define __TNONOPERATIONMTMDATATYPE_H__
#endif
