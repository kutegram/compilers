// mhttpdataoptimiser.h
//
// Copyright (c) Symbian Software Ltd 2007. All rights reserved.
//

/**
	@file mhttpoptimisercallback.h
	@warning : This file contains Rose Model ID comments - please do not delete
 */

#ifndef	__MHTTPDATAOPTIMISER_H__
#define	__MHTTPDATAOPTIMISER_H__


//@publishedPartner
//@released
class MHttpDataOptimiser
{
	public:
	/**
	This method converts the HTTP message data to the proprietary protocol format. 
	It is the responsibility of the implementation to allocate the required buffer for the encoded data. 
	It is the responsibility of the caller to free the allocated memory.
	@param	aHTTPData Contains the message data in HTTP format.
	@param	aEncodedData On return it contains the encoded message data.
	@leave		KErrNoMemory On insuffcient memory conditions.
	*/
	virtual void EncodeL (const TDesC8& aHttpData, HBufC8*& aEncodedData) = 0;

	/**
	This method converts the data from the proprietary protocol format to the HTTP format. 
	It is the responsibility of the implementation to allocate the required buffer for the encoded data. 
	It is the responsibility of the caller to free the allocated memory.
	@param	aData Is the raw data received over the TCP connection.
	@param	aHTTPData On return contains the data in HTTP format.
	@param	aTransFail If set to ETrue, sends the KErrHTTPOptimiserFailsTrans event to the client. 
	@leave		KErrNoMemory On insuffcient memory conditions.
	*/
	virtual void DecodeL (const TDesC8& aData, HBufC8*& aHttpData, TBool& aTransFail) = 0;
};


//	__MHTTPDATAOPTIMISER_H__
#endif
