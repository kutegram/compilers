// Copyright (c) Symbian Software Ltd 2005. All rights reserved.

#ifndef REMCONERROROBSERVER_H
#define REMCONERROROBSERVER_H

/** 
@file
@publishedAll

*/

#include <e32base.h>

/**
This class defines an error notification interface.  This is
intended for use in the situation where a client application
needs to know about an error that has occurred passively.  
This is not used in situations where a client application 
makes a call that returns an error.

The main use is where a target application is sitting waiting
to receive commands and the server dies.  It needs to know if
this has happened so that it can restart the server if it
wishes.
*/
class MRemConErrorObserver
	{
public:
	/**
	This is called in the case of a session error that has
	occurred passively and cannot be notified via completion
	of an outstanding call made by the client application.
	
	@param aError The error that has occurred.  If this is 
		   KErrServerTerminated, the error is fatal and the 
		   server must be restarted before any new 
		   messages can be received.
	*/
	virtual void MrceoError(TInt aError) = 0;
	};

// REMCONERROROBSERVER_H
#endif
