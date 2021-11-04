// MMFrameworkSP.h
//
//  Copyright (c) Symbian Software Ltd 1997-2007.  All rights reserved.
//

#ifndef __MFRAMEWORKSP_H__
#define __MFRAMEWORKSP_H__

// System includes
//
#include <e32def.h>

// Forward class declarations
//
class MWAPEngineObserver;
class CXmlTaskCoordinator;
class CLocalContext;
class CWapGCtxClient;
class CAttributeLookupTable;
class MWtaiPublicObserver;

//##ModelId=3B666FA40394
class MFrameworkSP
/**
@publishedAll
@deprecated
*/
	{
public:

/**
	Intended Usage	:	Return a pointer to the engine observer (pointer 
	because it could be NULL).
	
	@return			A pointer to the MWAPEngineObsever object.
 */
	//##ModelId=3B666FA403C7
	virtual MWAPEngineObserver* Observer() =0;

/**
	Intended Usage	:	Gets the Task Coordinator.
	
	@return			A reference to the Task Coordinater.
 */
	//##ModelId=3B666FA403C6
	virtual CXmlTaskCoordinator& TaskCoordinator() =0;
	
/**
	Intended Usage	:	Gets WAP Local Context.
	
	@return			A reference to the WAP Local Context. 
 */
	//##ModelId=3B666FA403BE
	virtual CLocalContext& LocalContext() =0;

/**
	Intended Usage	:	Gets WAP Global Context.
	
	@return			A reference to the WAP Global Context. 
 */
	//##ModelId=3B666FA403BD
	virtual CWapGCtxClient& GlobalContext() =0;

/**
	Intended Usage	:	Gets the Attribute Look Up Table.
	
	@return			A reference to the Attribute Look Up Table.
 */
	//##ModelId=3B666FA403BC
	virtual CAttributeLookupTable& AttributeLookup() =0;

/**
	Intended Usage	:	
	
	@return			A reference to the WtaiPublic observer 
 */
	//##ModelId=3B666FA403B2
	virtual MWtaiPublicObserver& WtaiPublicObserver() =0;

	};

// __MFRAMEWORKSP_H__
#endif
