/*
* ==============================================================================
*  Name        : siphttpdigestchallengeobserver.h
*  Part of     : SIP Client
*  Interface   : SDK API, SIP Client API
*  Description : 
*  Version     : 1.0
*
*  Copyright (c) 2005 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef MSIPHTTPDIGESTCHALLENGEOBSERVER_H
#define MSIPHTTPDIGESTCHALLENGEOBSERVER_H

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* @publishedAll
* 
*
* The user must implement this interface if it intends to
* provide HTTP Digest credentials upon received challenges
* from the SIP servers on the signaling path.
* The user should provide credentials or ignore the challenge
* using functions defined in TSIPHttpDigest class.
*
*  
*/
class MSIPHttpDigestChallengeObserver
	{
    public: // New functions
		/**
		* SIP request resulted in 401/407 response that contains
		* a challenge.
		*
		* @param aRealm a realm for which the challenge was received
		*/
		virtual void ChallengeReceived(const TDesC8& aRealm) = 0;
	};

#endif
