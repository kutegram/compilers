// agent.h
// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** 
@file

@publishedPartner

*/

#ifndef __CAF_AGENT_H__
#define __CAF_AGENT_H__

#include <e32base.h>

/** Maximum length of an Agent name, a longer name will be truncated */
const TInt KMaxAgentNameLength = KMaxFileName;
const TInt KMaxSIDLength = 8;

namespace ContentAccess
	{

	/** Represents the name of a single CAF agent. This allows 
	applications to reference a particular agent within the 
	Content Access Framework.

	@publishedPartner
	
	*/
	class TAgent 
		{
	public:
		/** The name of the agent 
		@return The name of the agent
		*/
		IMPORT_C const TDesC& Name() const;

		/** The UID of the agent DLL
		@return The UID of the agent ECOM implementation DLL 

		@internalComponent
		
		*/
		TUid ImplementationUid() const;

		/** Set the value of this TAgent
		@param aName The name of the agent
		@param aUid The agent implementation Uid
		
		@internalComponent
		
		*/
		void SetValue(const TDesC& aName, TUid aUid);

	private:

		TBuf <KMaxAgentNameLength> iName;
		TUid iImplementationUid;
		};
	}

#endif
