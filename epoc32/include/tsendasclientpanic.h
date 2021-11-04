// TSendAsClientPanic.h
//
// Copyright (c) 2004-2005 Symbian Software Ltd. All rights reserved.
//

#ifndef __TSENDASCLIENTPANIC_H__
#define __TSENDASCLIENTPANIC_H__

/**
Defines the SendAs client panic codes.

@publishedAll

*/
enum TSendAsClientPanic
	{
	/**
	Indicates an invalid request was made.
	*/
	ESendAsClientPanicBadRequest				= 0,

	/**
	Indicates a request was made on a session with an invalid handle.
	*/
	ESendAsClientPanicBadSubSessionHandle		= 1,
	
	/**
	Indicates a request was made with invalid an argument.
	*/
	ESendAsClientPanicBadRequestArgument		= 2,
	
	/**
	Indicates a request while the session is already in use.
	*/
	ESendAsClientPanicSubsessionInUse			= 3,
	
	/**
	Indicates a request relating to a message was made where no message exists.
	*/
	ESendAsClientPanicNoCurrentMessage			= 4,

	/**
	Indicates a request deleting a non-existent message was made.
	*/
	ESendAsClientPanicMessageAlreadyDeleted		= 5,
	
	/**
	Indicates a request to send a message encountered a problem.
	*/
	ESendAsClientPanicSendingMessage			= 6,

	/**
	Indicates a request to add or create an attachment encountered a problem.
	*/
	ESendAsClientPanicAddingCreatingAttachment  = 7

	};

//  __TSENDASCLIENTPANIC_H__
#endif
