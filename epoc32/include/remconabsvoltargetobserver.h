// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll

*/

#ifndef REMCONABSVOLTARGETOBSERVER_H
#define REMCONABSVOLTARGETOBSERVER_H

#include <e32base.h>

/**
Client-implemented mixin- notifies the client of incoming AbsVol commands.
*/
class MRemConAbsVolTargetObserver
	{
public:
	/** 
	A 'get absolute volume' command has been received.
	*/
	virtual void MrcavtoGetAbsoluteVolume();

	/**
	A 'set absolute volume' command has been received.
	@param aAbsVol The volume on a scale of 0 to aMaxVol.
	@param aMaxVol The volume aAbsVol is relative to.
	*/
	virtual void MrcavtoSetAbsoluteVolume(TUint aAbsVol, TUint aMaxVol);
	};

// REMCONABSVOLTARGETOBSERVER_H
#endif
