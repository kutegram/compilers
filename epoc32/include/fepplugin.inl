// FEPPLUGIN.INL
//
// Copyright (c) 1997-2004 Symbian Ltd.  All rights reserved.
//
#ifndef __FEPPLUGIN_INL__
#define __FEPPLUGIN_INL__

#include <ecom/ecom.h>

/**
Factory function to create and return a FEP plug-in with the specified UID.

@return				A FEP plug-in object instance corresponding to the UID provided 
@param				aFepUid The UID of the FEP plug-in implementation to be loaded 
*/
inline CCoeFepPlugIn* CCoeFepPlugIn::NewL(TUid aFepUid)
	{ // static
	TAny* any = REComSession::CreateImplementationL(aFepUid, _FOFF(CCoeFepPlugIn, iDtorTag));
	CCoeFepPlugIn* feppi = reinterpret_cast<CCoeFepPlugIn*>(any);
	return feppi;
	}

/**
Destructor that destroys the FEP plug-in.
*/
inline CCoeFepPlugIn::~CCoeFepPlugIn()
	{
	REComSession::DestroyedImplementation(iDtorTag);
	}


// __FEPPLUGIN_INL__
#endif
