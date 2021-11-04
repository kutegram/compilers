// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll

*/

#ifndef REMCONCOREAPICONTROLLEROBSERVER_H
#define REMCONCOREAPICONTROLLEROBSERVER_H

#include <e32base.h>
#include <remconcoreapi.h>

/**
Clients must implement this interface in order to instantiate objects of type 
CRemConCoreApiController. This interface passes incoming responses from RemCon 
to the client. 
In order to minimise the number of virtual functions the client has to 
implement, there's just one non-pure function which delivers all responses.
*/
class MRemConCoreApiControllerObserver
	{
public:
	/** 
	A response has been received. 
	@param aOperationId The operation ID. The response is to a previous 
	command of this type.
	@param The response error.
	*/
	virtual void MrccacoResponse(TRemConCoreApiOperationId aOperationId, TInt aError);
	};

// REMCONCOREAPICONTROLLEROBSERVER_H
#endif
