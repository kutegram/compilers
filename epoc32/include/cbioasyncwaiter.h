// CBIOASYNCWAITER.H
// 
// Copyright (c) Symbian Software Ltd 2004. All rights reserved.
//

#ifndef __CBIOASYNCWAITER_H__
#define __CBIOASYNCWAITER_H__

#include <e32base.h>

/**
Utility class for waiting for asychronous requests.

This class allows asynchronous requests to be made from synchronous
objects. This object is used by passing its iStatus to an asynchronous
request and then calling Start(). The result of the request can be 
obtained by calling the Result() method.

@publishedAll

*/
class CBioAsyncWaiter : public CActive
	{
public:
	IMPORT_C static CBioAsyncWaiter* NewLC();
	IMPORT_C ~CBioAsyncWaiter();
	
	IMPORT_C void StartAndWait();
	IMPORT_C TInt Result() const;
	
private:
	CBioAsyncWaiter();
	
	// from CActive
	virtual void RunL();
	virtual void DoCancel();
	
private:
	TInt iError;
	};

// __CBIOASYNCWAITER_H__
#endif
