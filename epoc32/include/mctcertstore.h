// MCTCertStore.h
//
// Copyright (c) 2001 Symbian Software Ltd.  All rights reserved.
//
/**
 * @file 
 * 
 * @publishedPartner
 * 
 */

#ifndef __MCTCERTSTORE_H__
#define __MCTCERTSTORE_H__

#include <cctcertinfo.h>
#include <ccertattributefilter.h>
#include <mcertstore.h>

/** The UID of read-only certificate store interfaces. */
const TInt KInterfaceCertStore = 0x101F501B;

/** The UID of filecertstore tokentype */
const TInt KTokenTypeFileCertstore = 0x101F501A;

/**
 * Defines the interface for a read-only certificate store token.
 * 
 * All the details are defined in MCertStore as they are shared by the unified
 * certificate store.
 * 
 * The class adds no extra member functions or data. 
 * 
 * @see MCertStore
 */
class MCTCertStore : public MCertStore, public MCTTokenInterface
	{
	};


#endif
