// EscapeUtils.h
//
// Copyright (c) Symbian Software Ltd 2001-2008. All rights reserved.
//

/**
	@file EscapeUtils.h
	Comments :	This file contains the API definition for escape enoding functionality
				and UNICODE/UTF8 conversion. Escape encoding is performed as specified
				by RFC2396.
	@publishedAll
	
*/

#ifndef __ESCAPEUTILS_H__
#define __ESCAPEUTILS_H__

// System includes
//
#include <e32base.h>
#include <uriutilscommon.h>


/**
Comments : Provides an API to allow data to be escape encoded and decoded. 
Also provide an API for converting a UNICODE data (16-bit descriptor) into 
UTF8 data (8-bit descriptor) and vice-verse.
@publishedAll


*/
class EscapeUtils
	{
public:	// Enums

/**
	enum	TEscapeMode
	Enum defining escaping modes. Each mode has a different set of reserved characters.
	These are based on various uri components, as decribed in RFC2396.
 */
	enum TEscapeMode
		{
		/** Default mode, which has no reserved characters 	*/
		EEscapeNormal	= 0,
		/** Mode specifying reserved characters in a uri query - ;/?:@&=+$,[] 	*/ 
		EEscapeQuery,
		/** Mode specifying reserved characters in a uri path - /;=?[]  */
		EEscapePath,
		/** Mode specifying reserved characters in a uri authority - /;:@?[]  */
		EEscapeAuth,
		/** Mode specifying reserved characters in a URL ;/?:@&=+$[]!\'()~  */
		EEscapeUrlEncoded
		};

public:	// Methods

	IMPORT_C static HBufC8* EscapeEncodeL(const TDesC8& aData, TEscapeMode aMode);

	IMPORT_C static HBufC16* EscapeEncodeL(const TDesC16& aData, TEscapeMode aMode);

	IMPORT_C static HBufC8* EscapeEncodeL(const TDesC8& aData, const TDesC8& aReservedChars);

	IMPORT_C static HBufC16* EscapeEncodeL(const TDesC16& aData, const TDesC16& aReservedChars);

	IMPORT_C static HBufC8* EscapeDecodeL(const TDesC8& aData);

	IMPORT_C static HBufC16* EscapeDecodeL(const TDesC16& aData);

	IMPORT_C static HBufC8* ConvertFromUnicodeToUtf8L(const TDesC& aData);

	IMPORT_C static HBufC* ConvertToUnicodeFromUtf8L(const TDesC8& aData);

	IMPORT_C static TBool IsExcludedChar(TChar aChar);

	IMPORT_C static TBool IsEscapeTriple(const TDesC8& aData, TInt& aHexValue);

	IMPORT_C static TBool IsEscapeTriple(const TDesC16& aData, TInt& aHexValue);

	IMPORT_C static HBufC8* SpecificEscapeEncodeL ( const TDesC8& aData, const TDesC8& aCharsToEscape );

	static HBufC8*  ReEscapeEncodeL(const TDesC8& aData);

private: // Dummy Method

	IMPORT_C static HBufC8* DummyForwardingFunctionForCompatibility( const TDesC8& aData, const TDesC8& aCharsToEscape );

	};

// __ESCAPEUTILS_H__
#endif
