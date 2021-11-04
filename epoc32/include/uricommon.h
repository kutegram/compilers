// UriCommon.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

/**
	@file UriCommon.h
	Comments :	Internal header file with common constants used by the implementations
				of the uri classes TUriC??, CUri?? and TUriParser??.
	@publishedAll
	
 */

#ifndef __URICOMMON_H__
#define __URICOMMON_H__

// System includes
//
#include <e32base.h>

/** 
	Enum defining a flag used to indicate file storage type (fixed drive or removable media).
	@publishedAll
	
	
 */
enum TFileUriFlags
	 {
	 /** 
	 	Indiacte the drive letter in the URI is to be replaced by the term "ext-media" 
	  */
	 EExtMedia   = 1
	 };
 
/** 
	Enum used by GetFileNameL to specify what data is returned. 
	@publishedAll
	
	
 */
enum TUriFileName
	 {
	 /**
	 	Indicate a File URI is to be converted into a fully qualified file name. Will Leave if not used on a file URI 
	  */
	 EUriFileNameFull   = 0,
	 /**
	 	Indicate a the path component is to be converted into a file name with directories, but no drive. Behaviour is undefined for non-hierarchical  schemes 
	  */
	 EUriFileNamePath,
	 /** 
	 	Indicate just the name is to be converted into a file name, with no directories. Behaviour is undefined for non-hierarchical  schemes 
	  */
	 EUriFileNameTail 
	 };

/**
	Enum defining the uri components.
	@warning		The enum value EUriMaxComponents should not be used as it will
	cause a panic.
	@publishedAll
	
	
*/
enum TUriComponent
	{
	/**
		The scheme component specifier 
	 */
	EUriScheme,
	/**
		The userinfo component specifier 
	 */
	EUriUserinfo,
	/**
		The host component specifier 
	 */
	EUriHost,
	/**
		The port component specifier 
	 */
	EUriPort,
	/**
		 The path component specifier 
	 */
	EUriPath,
	/**
		 The query component specifier 
	 */
	EUriQuery,
	/** 
		The fragment component specifier 
	 */
	EUriFragment,
	/** 
		Do not use as a field specifier - will cause panic 
	 */
	EUriMaxComponents, 
	/** 
		The complete URI. Only use with DisplayFormL, otherwise will cause panic 
	 */
	EUriComplete = -1
	};

// __URICOMMON_H__
#endif
