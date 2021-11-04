// e32\include\e32msgqueue.h
//
// Copyright (c) 2002 - 2003 Symbian Ltd. All rights reserved.
//

#ifndef __E32MSGQUEUE_H__
#define __E32MSGQUEUE_H__

#include <e32std.h>




class RMsgQueueBase : public RHandleBase
/**
@publishedAll


Provides implementation for managing an asynchronous message queue,
and is a base class for the RMsgQueue templated class.

@see RMsgQueue
*/
	{
public:
	/**
	The limit for the size of an individual message.
	*/
	enum {KMaxLength = 256};

public:

	IMPORT_C TInt CreateLocal(TInt aSize, TInt aMsgLength, TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateGlobal(const TDesC& aName, TInt aSize, TInt aMsgLength, TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt OpenGlobal(const TDesC& aName, TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Open(RMessagePtr2 aMessage, TInt aParam, TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Open(TInt aArgumentIndex, TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Send(const TAny* aPtr, TInt aLength);
	IMPORT_C void SendBlocking(const TAny* aPtr, TInt aLength);
	IMPORT_C TInt Receive(TAny* aPtr, TInt aLength);
	IMPORT_C void ReceiveBlocking(TAny* aPtr, TInt aLength);
	IMPORT_C void NotifySpaceAvailable(TRequestStatus& aStatus);
	IMPORT_C void CancelSpaceAvailable();
	IMPORT_C void NotifyDataAvailable(TRequestStatus& aStatus);
	IMPORT_C void CancelDataAvailable();
	IMPORT_C TInt MessageSize();
	};




/**
@publishedAll


A handle to a message queue.

The templated class provides the behaviour for managing an
asynchronous queue of messages, where the template parameter defines the
message type.

The class adds a type-checking interface to the basic message queue
functionality provided by RMsgQueueBase.
*/
template <typename T>
class RMsgQueue : public RMsgQueueBase
	{
public:
	TInt CreateLocal(TInt aSize, TOwnerType aType=EOwnerProcess);
	TInt CreateGlobal(const TDesC& aName, TInt aSize, TOwnerType aType=EOwnerProcess);
	TInt Send(const T& aMsg);
	void SendBlocking(const T& aMsg);
	TInt Receive(T& aMsg);
	void ReceiveBlocking(T& aMsg);
	};

#include <e32msgqueue.inl>

#endif
