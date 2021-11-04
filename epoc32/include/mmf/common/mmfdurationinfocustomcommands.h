// MmfDurationInfoCustomCommands.h
//
// Copyright (c) Symbian Software Ltd 2004-2006.  All rights reserved.
//

#ifndef __MMF_DURATION_INFO_CUSTOM_COMMANDS_H__
#define __MMF_DURATION_INFO_CUSTOM_COMMANDS_H__

#ifdef SYMBIAN_CAF_V2

#include <e32base.h>
#include <mmf/common/mmcaf.h>
#include <mmf/common/mmfstandardcustomcommands.h>


/**
@publishedAll
@deprecated 9.2- Replaced by KUidInterfaceMMFDurationInfoControl2
*/

const TUid KUidInterfaceMMFDurationInfoControl = {0x102737C8};

/**
@publishedPartner

*/

const TUid KUidInterfaceMMFDurationInfoControl2 = {0x10273812};

/**
@internalComponent
*/
enum TMMFDurationInfoMessages
	{
	EMMFGetDurationInfo
	};
	
	
/**
@publishedPartner


The duration state of the controller.
*/
enum TMMFDurationInfo
	{
	EMMFDurationInfoValid, 		// Duration is known
	EMMFDurationInfoUnknown,	// Invalid response from controller
	EMMFDurationInfoInfinite,	// Clip is of infinite length
	};

/**
@publishedAll
@deprecated 9.2 - Replaced by MMMFDurationInfoCustomCommandImplementor2

Mixin class to be derived from by controller plugins wishing to support the Duration information 
custom commands
*/
class MMMFDurationInfoCustomCommandImplementor
	{
public:

	/**
	Is the duration of the clip known? i.e. is the stream infinite?
	
	@param aDurationInfo
		   Controller duration information
		   
	@return TMMFDurationInfo Duration state.
	*/
	virtual TMMFDurationInfo GetDurationInfo(TMMFDurationInfo& aDurationInfo)=0;
	};

/**
@publishedAll
@deprecated 9.2 - Replaced by CMMFDurationInfoCustomCommandParser2
*/
class CMMFDurationInfoCustomCommandParser : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of processing duration information controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFDurationInfoCustomCommandParser* NewL(MMMFDurationInfoCustomCommandImplementor& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFDurationInfoCustomCommandParser();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.
	
	*/
	CMMFDurationInfoCustomCommandParser(MMMFDurationInfoCustomCommandImplementor& aImplementor);
	
	/**
	Request duration information from the implementor

	@param  aMessage
	        Message for writing results to the client.
	*/
	TInt GetDurationInfo(TMMFMessage& aMessage);

private:

	MMMFDurationInfoCustomCommandImplementor& iImplementor;
	
	};
	
/**
@publishedPartner


Mixin class to be derived from by controller plugins wishing to support the Duration information 
custom commands
*/
class MMMFDurationInfoCustomCommandImplementor2
	{
public:

	/**
	Is the duration of the clip known? i.e. is the stream infinite?
	
	@param aDurationInfo
		   Controller duration information
		   
	@return KErrNone or System wide error code
	*/
	virtual TInt GetDurationInfo(TMMFDurationInfo& aDurationInfo)=0;
	};
	
/**
@publishedPartner


Custom command parser capable of processing duration information controller commands
*/
class CMMFDurationInfoCustomCommandParser2 : public CMMFCustomCommandParserBase
	{
public:

	/**
	Creates a new custom command parser capable of processing duration information controller commands.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.

	@return A pointer to the object created.

	
	*/
	IMPORT_C static CMMFDurationInfoCustomCommandParser2* NewL(MMMFDurationInfoCustomCommandImplementor2& aImplementor);

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFDurationInfoCustomCommandParser2();

	/**
	Handles a request from the client. Called by the controller framework.

	@param  aMessage
	        The message to be handled.

	
	*/
	void HandleRequest(TMMFMessage& aMessage);

private:
	/**
	Constructor.

	@param  aImplementor
	        A reference to the controller plugin that owns this new object.
	
	*/
	CMMFDurationInfoCustomCommandParser2(MMMFDurationInfoCustomCommandImplementor2& aImplementor);
	
	/**
	Request duration information from the implementor

	@param  aMessage
	        Message for writing results to the client.
	*/
	TInt GetDurationInfo(TMMFMessage& aMessage);

private:
	MMMFDurationInfoCustomCommandImplementor2& iImplementor;
	};

// SYMBIAN_CAF_V2
#endif

// __MMF_DURATION_INFO_CUSTOM_COMMANDS_H__
#endif

