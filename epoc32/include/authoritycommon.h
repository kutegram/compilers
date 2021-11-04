// AuthorityCommon.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

/**
	@file AuthorityCommon.h
	Comments :	Internal header file with common information used by the authority
				classes TAuthorityC??, CAuthority?? and TAuthorityParser??.

	@publishedAll
	
	@see Authority8.h, Authority16.h
 */

#ifndef __AUTHORITYCOMMON_H__
#define __AUTHORITYCOMMON_H__

// System includes
//
#include <e32base.h>

/**
enum TAuthorityComponent
Enum defining the authority components.
@publishedAll

@warning		The enum value EAuthorityMaxComponents should not be used as it will 
cause a panic.

*/
enum TAuthorityComponent
	{
	/** 
		The userinfo component specifier 
	*/
	EAuthorityUserinfo = 0,
	/** 
		The host component specifier 
	*/
	EAuthorityHost,
	/** 
		The port component specifier 
	*/
	EAuthorityPort,
	/** 
		Do not use as a field specifier - will cause panic 
	*/
	EAuthorityMaxComponents,
	/** 
		The complete Authority. Only use with DisplayFormL, otherwise will cause panic 
	*/
	EAuthorityComplete = -1
	};
		
// __AUTHORITYCOMMON_H__
#endif
