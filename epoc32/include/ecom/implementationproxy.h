//
// ImplementationProxy.h
// Copyright (c) Symbian Software Ltd 1997-2004. All rights reserved.
//

/** 
	Comments : This file contains the definition for the
				TImplementationProxy structure.
 */ 

#ifndef __IMPLEMENTATIONPROXY_H__
#define __IMPLEMENTATIONPROXY_H__

#include <e32std.h>

/**
Pre-defined function pointer type used in TImplementationProxy

@publishedAll

*/
typedef TAny* (*TFuncPtr)();

/**
Typedef used to cover the difference between EABI and older handling
of the instantiation method pointer.

@publishedAll

*/
#if  defined(__EABI__) || defined(__GCCXML__)
typedef TFuncPtr TProxyNewLPtr;
#else
typedef TAny* TProxyNewLPtr;
#endif

/**
The structure that defines the pairing required by the ECOM framework
to correctly identify the instantiation method pointer to provide
to a client's resolution request.

@publishedAll

*/
typedef struct
	{
	/** The unique UID for an Interface Implementation */
	TUid	iImplementationUid;
	/** The pointer to the instantiation method for the Interface Implementation identified by the UID.*/
	TProxyNewLPtr iNewLFuncPtr;
	} TImplementationProxy;

/**
Macro to initialise an element of a static array of TImplementationProxy objects.
This macro deals with casting the function pointer to the type used in the structure.

@publishedAll

*/
#define IMPLEMENTATION_PROXY_ENTRY(aUid, aFuncPtr)	{{aUid},(TProxyNewLPtr)(aFuncPtr)}

// __IMPLEMENTATIONPROXY_H__
#endif
