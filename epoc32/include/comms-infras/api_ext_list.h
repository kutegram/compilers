// API_EXT_LIST.H
//
// Copyright (c) 2006-2007 Symbian Software Ltd. All rights reserved.
//
/** @file
@publishedPartner
@prototype
*/

#ifndef API_EXT_LIST_H
#define API_EXT_LIST_H

#include <es_sock.h>

#define API_ZONE(n) (10000*n)

enum TSupportedCommsApiExt
/**
List of all currently supported API extensions.

@publishedPartner
@prototype
*/
	{
	// Client/Server extension APIs
	EApiExtBegin = API_ZONE(0),
	EMobilityApiExt,
	EAvailabilityApiExt,
	EDataMonitoringApiExt,
	EApiExtEnd,

	// Internal cross-thread APIs
	EApiITCBegin = API_ZONE(1),
    EQueryConnSettingsApiExt = API_ZONE(1) + 1, // Forward BC compatible
	EAccessPointConfigApiExt = API_ZONE(1) + 2, // Forward BC compatible
	EApiITCEnd,

	// 3rd party internal cross-thread APIs
	EApi3rdPartyBegin = API_ZONE(2),
	EApi3rdPartyEnd = API_ZONE(3) - 1
	};


// API_EXT_LIST_H
#endif

