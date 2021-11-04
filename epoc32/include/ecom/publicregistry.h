//
// PublicRegistry.h
// Copyright © 1997-2005 Symbian Software Ltd. All rights reserved.
//

/** 
Comments : The interface definition for the MPublicRegistry class
 */ 

#ifndef __PUBLICREGISTRY_H__
#define __PUBLICREGISTRY_H__

#include <ecom/implementationinformation.h>

/**
Provides access to the public functions of CRegistryData for CResolver 
implementations.

@publishedAll

*/

class MPublicRegistry
	{
public:
	/**
	Intended Usage	: Provides a list of the implementations which satisfy the 
					interface uid specified.
	@leave  		Depends on implementation.
	
	@return			None.
	@pre 			This object is fully constructed.
 	*/
	
	virtual RImplInfoArray& ListImplementationsL(TUid aInterfaceUid) const = 0 ;

	};

// __PUBLICREGISTRY_H__
#endif
