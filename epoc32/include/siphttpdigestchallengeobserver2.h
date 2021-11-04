/*
* ==============================================================================
*  Name        : siphttpdigestchallengeobserver2.h
*  Part of     : SIP Client
*  Interface   : SDK API, SIP Client API
*  Description : 
*  Version     : 1.0
*
*  Copyright (c) 2006 Nokia Corporation.
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

#ifndef MSIPHTTPDIGESTCHALLENGEOBSERVER2_H
#define MSIPHTTPDIGESTCHALLENGEOBSERVER2_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class CSIPClientTransaction;
class CSIPRefresh;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* The user should implement this interface if it intends to
* provide HTTP Digest credentials upon received challenges
* from the SIP servers on the signaling path.
* The user should provide credentials or ignore the challenge
* using functions defined in CSIPHttpDigest class.
*
*  
*/
class MSIPHttpDigestChallengeObserver2
	{
    public: // New functions
		/**
		* A SIP request resulted in 401/407 response that contains
		* 1..n challenges. 
		* The challenges can be obtained from Proxy-Authenticate- and/or
		* WWW-Authenticate-headers in the CSIPResponseElements
		* attached to the CSIPClientTransaction.
		* The user must call CSIPHttpDigest::SetCredentialsL or
		* CSIPHttpDigest::IgnoreChallenge for each challenge.
		*
		* @param aTransaction transaction which was completed with 
		*        a response containing HTTP Digest challenge.
		*/
		virtual void ChallengeReceived(
		    const CSIPClientTransaction& aTransaction) = 0;

		/**
		* A refreshed SIP request resulted in 401/407 response that contains
		* 1..n challenges.
		* The challenges can be obtained from Proxy-Authenticate- and/or
		* WWW-Authenticate-headers in the CSIPResponseElements
		* attached to the CSIPClientTransaction attached to the CSIPRefresh.
		* The user must call CSIPHttpDigest::SetCredentialsL or
		* CSIPHttpDigest::IgnoreChallenge for each challenge.		 
		*
		* @param aRefresh the refresh for which a transaction completed with 
		*        a response containing HTTP Digest challenge.
		*/		    
		virtual void ChallengeReceived(
		    const CSIPRefresh& aRefresh) = 0;		    
	};

// MSIPHTTPDIGESTCHALLENGEOBSERVER2_H
#endif
