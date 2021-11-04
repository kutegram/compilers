//
// Copyright  2004-2007 Symbian Ltd. All rights reserved.
//
// ** IMPORTANT ** PublishedPartner API's in this file are published to 3rd party developers via the 
// Symbian website. Changes to these API's should be treated as PublishedAll API changes and the Security TA should be consulted.
//
#ifndef __CRYPTOPANIC_H__
#define __CRYPTOPANIC_H__

/**
 * @file
 * Cryptography Panic Codes
 *
 * @publishedAll
 * 
 */

/** 
 * @publishedAll
 * 
 *
 * Panic codes for cryptography related libraries
 */
_LIT(KCryptoPanic, "CRYPTO-LIB");

/** 
 * @publishedAll
 * 
 *
 * Panic codes for "CRYPTO-LIB" */
enum TCryptoPanicCode
	{
	/**
	 * The supplied descriptor is not large enough to store the output
	 * of the cryptographic operation
	 */	
	ECryptoPanicOutputDescriptorOverflow= 1,
	/**
	 * The supplied input descriptor is too large to pad
	 */	
	ECryptoPanicPadInputTooLarge= 2,
	/**
	* The input data is too long
	*/
	ECryptoPanicInputTooLarge= 3
	};

#endif
