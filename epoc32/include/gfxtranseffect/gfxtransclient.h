// GFXTRANSCLIENT.H
//
// Copyright (c) Symbian Software Ltd 2006.  All rights reserved.
//

#ifndef _GFXTRANSCLIENT_H_
#define _GFXTRANSCLIENT_H_

#include <gfxtransdatatype.h>

/**
 this interface is given to the transition engine on contruction.
 It is then to be used to retrieve information about transitions the client has gathered.
 It is also used to signal the client.
 
 @publishedPartner
*/
class MGfxTransClient
	{
public:
	/**
	 Callback called by adapter when a new policy arrives.
	 @param aPolicy the newly arrived policy. The client takes ownership of the pointer passed.
	 */
	virtual void TransitionPolicyUpdate(TControlPolicy* aPolicy) = 0;

	/**
	 resets policies all to its default, ENotSupported.
	 */
	virtual void ClearAllPolicies() = 0;

	/**
	 Callback, called by adapter when a transition has stopped animating.
	 @param aHandle handle for the transition that finished.
	 */
	virtual void TransitionFinished(TInt aHandle) = 0;

	/**
	 Used by adapter to get transition data from the client.
	 @param aHandle handle for the transition to get the data for.
	 @param aTransData on return contains a pointer to the transition data. Does not transfer ownership.
	 */
	virtual TInt GetTransitionData(TInt aHandle, const CTransitionData*& aTransData) = 0;
	};
	
#endif
