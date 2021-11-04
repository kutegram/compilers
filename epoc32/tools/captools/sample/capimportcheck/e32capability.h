// e32\include\e32capability.h
//
// Copyright (c) 2001-2004 Symbian Ltd. All rights reserved.
//

//
// Platform security capability definitions
// Used by both source code and tools
// This file can be directly included into C++ tools such as ROMBUILD to allow
// capabilities to be specified by name. To do the same for MAKMAKE (in MMP
// files) some perl code will be needed to parse this file and extract the
// capability names and values.
//

#ifndef __E32CAPABILITY_H__
#define __E32CAPABILITY_H__

/** List of all supported capabilities

@publishedAll
@released
*/
enum TCapability
	{
	ECapabilityTCB				= 0,
	ECapabilityCommDD			= 1,
	ECapabilityPowerMgmt		= 2,
	ECapabilityMultimediaDD		= 3,
	ECapabilityReadDeviceData	= 4,
	ECapabilityWriteDeviceData	= 5,
	ECapabilityDRM				= 6,
	ECapabilityTrustedUI		= 7,
	ECapabilityProtServ			= 8,
	ECapabilityDiskAdmin		= 9,
	ECapabilityNetworkControl	= 10,
	ECapabilityAllFiles			= 11,
	ECapabilitySwEvent			= 12,
	ECapabilityNetworkServices	= 13,
	ECapabilityLocalServices	= 14,
	ECapabilityReadUserData		= 15,
	ECapabilityWriteUserData	= 16,
	ECapabilityLocation			= 17,

	ECapability_Limit,					/**< @internalTechnology */

	ECapability_HardLimit		= 255,	/**< @internalTechnology */

	ECapability_None			= -1	
	};


/** Define this macro to reference the names of the capabilities. This is here so
	that ROMBUILD can accept capability names.
*/
#ifdef __REFERENCE_CAPABILITY_NAMES__

extern const char* CapabilityNames[ECapability_Limit];

#endif	// __REFERENCE_CAPABILITY_NAMES__

/** Define this macro to include the names of the capabilities. This is here so
	that ROMBUILD can accept capability names.
*/
#ifdef __INCLUDE_CAPABILITY_NAMES__

/** List of names of all supported capabilities
	Must be in the same order as the enumerators in TCapability

@publishedAll
@released
*/
extern const char* CapabilityNames[ECapability_Limit] =
	{
	"TCB",
	"CommDD",
	"PowerMgmt",
	"MultimediaDD",
	"ReadDeviceData",
	"WriteDeviceData",
	"DRM",
	"TrustedUI",
	"ProtServ",
	"DiskAdmin",
	"NetworkControl",
	"AllFiles",
	"SwEvent",
	"NetworkServices",
	"LocalServices",
	"ReadUserData",
	"WriteUserData",
	"Location"
	};

#endif	// __INCLUDE_CAPABILITY_NAMES__

#endif	// __E32CAPABILITY_H__
