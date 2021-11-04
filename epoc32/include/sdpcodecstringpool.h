/*
* =============================================================================
*  Name          : SdpCodecStringPool.h
*  Part of       : SDP Codec
*  Interface     : SDK API, SDP Codec API
*  Description   : 
*  Version       : 1.0
*
*  Copyright (c) 2003 Nokia Corporation. 
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation. 
* =============================================================================
*/

#ifndef SDPCODECSTRINGPOOL_H
#define SDPCODECSTRINGPOOL_H

//  INCLUDES
#include <e32base.h>
#include "_sdpdefs.h"
#include <stringpool.h>

class CSdpCodecStringPool;

// CLASS DECLARATION
/**
 * @publishedAll
 * 
 *
 * This class defines string pool for SDP Codec.
 * The client of SDP Codec must call OpenL() before 
 * invoking any function of SDP Codec classes.
 * The client must close the string pool when finnished using
 * SDP Codec classes.
 *
 * Note: the client must not close the string pool while
 *       using SDP Codec classes.
 * 
 *  
 */

class SdpCodecStringPool
	{
public: // Constructors and destructor
 		
	/**
	* Opens SDP Codec string pool.
	*
    * @leave KErrAlreadyExists if pool already exists in TLS.
	*/
	IMPORT_C static void OpenL();

	/**
	* Closes SDP Codec string pool.
	*
	*/
	IMPORT_C static void Close(); 

public: 
	
	/**
	* Gets the string pool used by SDP Codec.
	*
	* @return RStringPool: A handle to a string pool
	* @leave KErrSdpCodecStringPool if the pool is not opened.
	*
	*/
	IMPORT_C static RStringPool StringPoolL();

	/**
	* Gets the string table used by SDP Codec.
	*
	* @return TStringTable&: The string pool table
	* @leave KErrSdpCodecStringPool if the pool is not opened.
	*
	*/
	IMPORT_C static const TStringTable& StringTableL();
	};

#endif
