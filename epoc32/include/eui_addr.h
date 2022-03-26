//
//    eui_addr.h - modified EUI-xx for IPv6 interface identifiers
//
//    Portions Copyright (c) Symbian Software Ltd. 2007.
//    Portions Copyright (C) 1999-2004 Nokia. * Nokia Core OS *
//    Save as expressly licensed to you by Symbian Software Ltd, all rights reserved.
//
////////////////////////////////////////////////////////////////

/** @file eui_addr.h
 * Modified EUI-xx address structure for IPv6 interface identifiers
 *
 * @publishedAll
 * 
 */

#ifndef __EUI_ADDR_H__
#define __EUI_ADDR_H__

#include <e32def.h>		// TUint*
#include "es_sock.h"	// TSockAddr

/**  Address family ID */
const TUint KAfEui64	= 0x0F64;	///< TODO

/**  Panic codes.
@publishedAll

*/
enum TEuiPanic
{
	EEuiPanicFamilyMismatch,
	EEuiPanicBitIsNotBit,
	EEuiPanicSourceTooLong
};


//
// Lots of these functions should be inlined -tom
//

/**
 * The raw 64 bits of Modified EUI-64 address stored in network byte order.
 * @publishedAll
 * 
 */
class TE64Addr
{
 public:
	IMPORT_C TE64Addr();					///< Constructs an address with zero value
	IMPORT_C TE64Addr(const TE64Addr& aAddr);		///< Constructs an address with given value
	IMPORT_C TE64Addr(const TInt64& aAddr);			///< Constructs an address with given value
	IMPORT_C TE64Addr(const TUint8* aPtr, TUint aLength);	///< Constructs an address with given value

	IMPORT_C void SetAddr(const TE64Addr& aAddr);			///< Sets the address value
	IMPORT_C void SetAddr(const TInt64& aAddr);			///< Sets the address value
	IMPORT_C void SetAddr(const TUint8* aPtr, TUint aLength);	///< Sets the address value


	IMPORT_C void SetAddrZero();	///< Creates a zero address

	/**
	 * Creates a random address.
	 * The Group bit is set to 0.
	 * The Universal bit is set to 0.
	 */
	IMPORT_C void SetAddrRandom();

	/**
	 * Creates a random non-zero address.
	 * The Group bit is set to 0.
	 * The Universal bit is set to 0.
	 */
	IMPORT_C void SetAddrRandomNZ();

	/**
	 * Creates a random non-zero address that does not match the parameter address.
	 * The Group bit is set to 0.
	 * The Universal bit is set to 0.
	 */
	IMPORT_C void SetAddrRandomNZButNot(const TE64Addr& aAddr);

	// Really should define TE48Addr for this... -tom
	IMPORT_C void SetAddrFromEUI48(const TUint8* aPtr);	///< Reads and converts a value from EUI-48 (6 bytes)

	IMPORT_C void SetGroupBit(TBool aBit = 1);		///< Sets the Group bit to 1 by default
	IMPORT_C void SetUniversalBit(TBool aBit = 1);		///< Sets the Universal bit to 1 by default

	IMPORT_C TBool Match(const TE64Addr& aAddr) const;	///< TRUE if the address matches given address
	IMPORT_C TBool IsZero() const;				///< TRUE if the address is a zero address
	IMPORT_C TBool IsGroup() const;				///< TRUE if the Group bit is set in the address
	IMPORT_C TBool IsUniversal() const;			///< TRUE if the Universal bit is set in the address

//	IMPORT_C TInt Input(const TDesC& aBuf);			///< Reads a value for the address from a string
	IMPORT_C void Output(TDes& aBuf) const;			///< Writes the address into a string
	
	IMPORT_C static TUint AddrLen();			///< Returns the size of raw KAfEui64 content format
	IMPORT_C TUint8* AddrPtr();				///< Returns a pointer to raw KAfEui64 content format
	IMPORT_C const TUint8* AddrPtrC() const;		///< Returns a const pointer to raw KAfEui64 content format

 private:
	union
	{
		TUint8 iAddr8[64 / 8];
		TUint16 iAddr16[64 / 16];
		TUint32 iAddr32[64 / 32];
	} u;
};

struct SE64Addr {
	TE64Addr iAddr;		///< 8 bytes of Modified EUI-64 address (64 bits)
};

/**
 * This class specializes the generic socket server address class
 * TSockAddr for the IPv6 Interface Identifier; the Modified EUI-64
 * address. Value KAfEui64 is used for the protocol family field
 * of the TSockAddr base class.
 *
 * @publishedAll
 * 
 */
class TEui64Addr : public TSockAddr
{
 public:
	/**
	 * Constructs a basic IPv6 Interface Identifier.
	 * The family is initialized to KafEui64.
	 * The port (unused) is initialized to 0.
	 * The address is set to zero address.
	 */
	IMPORT_C TEui64Addr();

	/**
	 * Constructs an IPv6 Interface Identifier from TSockAddr.
	 * The family of the parameter must be KAfEui64 or 0.
	 * The family of the resulting address is KAfEui64.
	 * The port (unused) is initialized to 0.
	 * The address bytes are copied from the parameter.
	 *
	 * @param anAddr TSockAddr to be used as initial content.
	 */
	IMPORT_C TEui64Addr(const TSockAddr& aAddr);

	/**
	 * Constructs an IPv6 Interface Identifier from TE64Addr.
	 * The family is initialized to KAfEui64.
	 * The port (unused) is initialized to 0.
	 * The address bytes are copied from the parameter.
	 *
	 * @param aAddr TE64Addr to be used as initial content.
	 */
	inline TEui64Addr(const TE64Addr& aAddr);

	/**
	 * Initializes the TSockAddr parts of an IPv6 Interface Identifier.
	 * The family is set to KAfEui64.
	 * The port (unused) is initialized to 0.
	 * The address bytes are not touched.
	 */
	IMPORT_C void Init();

	/**
	 * Sets the address bytes to given value.
	 * The other TSockAddr fields are not touched.
	 */
	IMPORT_C void SetAddress(const TE64Addr& aAddr);
	IMPORT_C TE64Addr& Address() const;	///< Accesses the address bytes

	IMPORT_C TBool Match(const TEui64Addr& aAddr) const;	///< TRUE if the address bytes match the parameter's
	IMPORT_C TBool IsZero() const;				///< TRUE if the address bytes are all zeros

	IMPORT_C static TEui64Addr& Cast(const TSockAddr& aAddr);	///< Unsafely casts a TSockAddr to TEui64Addr
	IMPORT_C static TEui64Addr& Cast(const TSockAddr* aAddr);	///< Unsafely casts a TSockAddr to TEui64Addr

 protected:
	IMPORT_C SE64Addr* AddrPtr() const;	///< Returns a pointer to KAfEui64 content format
	IMPORT_C static TUint AddrLen();	///< Returns the size of the KAfEui64 content format
};

inline TEui64Addr::TEui64Addr(const TE64Addr& aAddr) : TSockAddr()
{
	Init();
	SetAddress(aAddr);
};

#endif
