// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll

*/

#ifndef REMCONABSVOLCONTROLLEROBSERVER_H
#define REMCONABSVOLCONTROLLEROBSERVER_H

#include <e32base.h>

/**
Client-implemented mixin- notifies the client of incoming AbsVol commands.
*/
class MRemConAbsVolControllerObserver
	{
public:
	/** 
	A response to a 'get absolute volume' command has been received.
	@param aAbsVol The relative volume.
	@param aMaxVol The maximum against which aAbsVol is relative.
	@param aError The response error.
	*/
	virtual void MrcavcoGetAbsoluteVolumeResponse(TUint aAbsVol, TUint aMaxVol, TInt aError);

	/** 
	A response to a 'set absolute volume' command has been received.
	@param aError The response error.
	*/
	virtual void MrcavcoSetAbsoluteVolumeResponse(TInt aError);
	};

// REMCONABSVOLCONTROLLEROBSERVER_H
#endif
