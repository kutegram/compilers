// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll

*/

#ifndef REMCONTRACKINFOTARGETOBSERVER_H
#define REMCONTRACKINFOTARGETOBSERVER_H

#include <e32base.h>

/**
Client-implemented mixin- notifies the client of incoming TrackInfo commands.
*/
class MRemConTrackInfoTargetObserver
	{
public:
	/**
	A 'get track name' command has been received.
	*/
	virtual void MrctitoGetTrackName();

	/**
	A 'get artist' command has been received.
	*/
	virtual void MrctitoGetArtist();

	/**
	A 'get track duration' command has been received. 
	*/
	virtual void MrctitoGetTrackDuration();
	
/**
The following section of code is included to allow internal back to back 
testing of this component within Symbian Software Ltd. It will only be 
compiled in specially configured test builds. It will never be available 
in any release and so should never be used outside of Symbian owned test 
code.
*/
#ifdef SYMBIAN_ENABLE_TRACKINFO_BACKTOBACK_TEST_FUNCT
	/**
	This method is only available in specially configured test builds and will 
	not be found in any released code. 
	@internalTechnology 
	*/
	virtual void MrctitoSetTrackName(const TDesC& aTrackName);	
//SYMBIAN_ENABLE_TRACKINFO_BACKTOBACK_TEST_FUNCT
#endif
	};

// REMCONTRACKINFOTARGETOBSERVER_H
#endif
