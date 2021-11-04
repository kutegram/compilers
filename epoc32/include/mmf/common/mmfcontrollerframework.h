// MmfControllerFramework.h
//
// Copyright (c) Symbian Software Ltd 2002-2007.  All rights reserved.
//


#ifndef __MMFCONTROLLERFRAMEWORK_H__
#define __MMFCONTROLLERFRAMEWORK_H__

#include <e32base.h>
#include <e32std.h>
#include <f32file.h>
#include <mmf/common/mmfutilities.h>
#include <mmf/common/mmfcontrollerframeworkbase.h>
#include <mmf/common/mmfipc.h>

// fwd ref
class CMMFControllerImplementationInformation;
class CLogonMonitor;

_LIT(KMMFControllerProxyServerName, "MMFControllerProxyServer-");

/**
@internalComponent
*/
#define KMMFControllerProxyVersion TVersion(7,1,1)

/**
@internalComponent
*/
const TInt KMMFControllerProxyMaxHeapSize = 0x1000000;//16MB

/**
@internalComponent
*/
const TInt KMMFControllerProxyMaxCachedMessages = 10;

/**
@internalComponent

Signals that the message is destined for the controller proxy
*/
const TInt KMMFObjectHandleControllerProxy = -1;

/**
@publishedAll


Signals that the message is destined for the controller
*/
const TInt KMMFObjectHandleController = -2;

/**
@publishedAll


Null, or invalid, object handle
*/
const TInt KMMFObjectHandleNull = 0;
/**
@internalComponent

The first valid object handle.  The MMF Object container will
begin iterating from here when generating object handles.
*/
const TInt KMMFObjectHandleFirstValid = 1;

/**
@internalComponent
*/
const TInt KMmfControllerThreadShutdownTimeout = 20000000;	// 20 seconds

/**
@internalComponent

The UID and messages associated with the controller proxy interface.
*/
const TUid KUidInterfaceMMFControllerProxy = {0x101F77E7};

/**
@internalComponent
*/
enum TMMFControllerProxyMessages
	{
	EMMFControllerProxyLoadControllerPluginByUid,
	EMMFControllerProxyReceiveEvents,
	EMMFControllerProxyCancelReceiveEvents
	};


/**
@publishedAll


Describes the destination of a message in the controller framework.

The destination is defined by a UID describing the interface and an integer object handle.
The controller framework uses this information when it receives a message to decide where
to send the message.

The controller plugin and controller proxy use the special constant handles
KMMFObjectHandleControllerProxy and KMMFObjectHandleController for
efficiency.


*/
class TMMFMessageDestination
	{
public:

	/**
	Default constructor.
	
	Assigns a null UID to the interface, and a null handle to the handle.

	
	*/
	IMPORT_C TMMFMessageDestination();

	/**
	Constructor for sending messages to the controller plugin.

	Assigns KMMFObjectHandleController to the destination handle.

	@param  aInterfaceId
	        The UID of the interface of this message destination.

	
	*/
	IMPORT_C TMMFMessageDestination(TUid aInterfaceId);

	/**
	Full constructor.
	
	@param  aInterfaceId
	        The UID of the interface of this message destination.
	@param  aDestinationHandle
	        The handle of the destination object in the controller framework.

	
	*/
	IMPORT_C TMMFMessageDestination(TUid aInterfaceId, TInt aDestinationHandle);

	/**
	Copy constructor.

	@param  aOther
	        The TMMFMessageDestination object to be copied.

	
	*/
	IMPORT_C TMMFMessageDestination(const TMMFMessageDestination& aOther);

	/**
	Returns the UID of the interface of the message destination.

	@return	The interface UID.

	
	*/
	IMPORT_C TUid InterfaceId() const;

	/**
	Returns the handle of the destination object in the controller framework.

	@return	The destination handle.

	
	*/
	IMPORT_C TInt DestinationHandle() const;

	/**
	Compares two destinations.

	@param  aOther
	        The object to be compared with this object.

	@return A boolean indicating if the objects are the same. ETrue if the objects are the same, 
	        EFalse if the objects are different.

	
	*/
	IMPORT_C TBool operator==(const TMMFMessageDestination& aOther) const;

private:
	TUid iInterfaceId;
	TInt iDestinationHandle;
	/**
	This member is internal and not intended for use.
	*/
	TInt iReserved1;
	TInt iReserved2;
	TInt iReserved3;
	};

/**
@publishedAll


Package buffer for TMMFMessageDestination
*/
typedef TPckgBuf<TMMFMessageDestination> TMMFMessageDestinationPckg;


/**
@publishedAll


Encapsulation of an RMessage or an RMessage2 to provide protection to controller plugins
from the changes occurring with secure APIs.

Adds required destination information to the message so the controller framework
can determine which object the message is for.

Adds capability to check whether the message has been completed.

Allows two descriptors to be read from the client, and one descriptor to be copied to the client.

@see RMMFControllerProxy::SendSync
@see RMMFControllerProxy::SendAsync


*/
class TMMFMessage
	{
friend class CMMFControllerProxySession;
friend class CMMFDevSoundSession;
public:

	/**
	Copy constructor.
	
	A controller plugin should use this to take a copy of the message when it must wait for some
	other event before completing it.

	@param  aMessage
	        The message object to copy.

	
	*/
	IMPORT_C TMMFMessage(const TMMFMessage& aMessage);

	/**
	Returns the destination of the message.

	@return	The destination of the message, consisting of a UID defining the interface and the
			handle of the destination object.

	
	*/
	IMPORT_C const TMMFMessageDestination& Destination();

	/**
	Returns an integer describing the function being called. Equivalent to 
	RMessage::Function().

	@return The function being called over IPC.

	@see    RMessage::Function()

	
	*/
	IMPORT_C TInt Function();

	/**
	Returns the size of the first descriptor that can be copied over from the client.
	
	Use this to create a descriptor of appropriate size before reading the data from the client.

	@return	The size of data 1.
	
	*/
	IMPORT_C TInt SizeOfData1FromClient();

	/**
	Copy the first descriptor from the client.
	
	@param  aDes
	        A descriptor defining the area of memory into which the data from the client
	        will be copied. Note, the descriptor must be of sufficient size.

	@return	One of the system-wide error codes. In particular, KErrBadDescriptor will be returned
	        if the client did not provide a valid descriptor.

	
	*/
	IMPORT_C TInt ReadData1FromClient(TDes8& aDes);

	/**
	Copy the first descriptor from the client.

	This functino can leave with one of the system-wide error codes. In particular, the leave code 
	KErrBadDescriptor will be used if the client did not provide a valid descriptor.

	@param  aDes
	        A descriptor defining the area of memory into which the data from the client
	        will be copied. Note, the descriptor must be of sufficient size.

	
	*/
	IMPORT_C void ReadData1FromClientL(TDes8& aDes);


	/**
	Returns the size of the second descriptor that can be copied over from the client.
	
	Use this to create a descriptor of appropriate size before reading the data from the client.

	@return The size of data 2.

	
	*/
	IMPORT_C TInt SizeOfData2FromClient();

	/**
	Copies the second descriptor from the client.

	@param  aDes
	        A descriptor defining the area of memory into which the data from the client
	        will be copied. Note, the descriptor must be of sufficient size.

	@return One of the system-wide error codes. In particular, KErrBadDescriptor will be returned
	        if the client did not provide a valid descriptor.

	
	*/
	IMPORT_C TInt ReadData2FromClient(TDes8& aDes);

	/**
	Copies the second descriptor from the client.

	This function can leave with one of the system-wide error codes. In particular, the leave code
	KErrBadDescriptor will be used if the client did not provide a valid descriptor.

	@param  aDes
	        A descriptor defining the area of memory into which the data from the client
	        will be copied. Note, the descriptor must be of sufficient size.

	
	*/
	IMPORT_C void ReadData2FromClientL(TDes8& aDes);

	/**
	Copies data back to the client.

	@param  aDes
	        The data to be copied back to the client.  Note that the client must
	        have already created a descriptor of sufficient size for the data to be
	        copied into.

	@return One of the system-wide error codes. In particular, the error code KErrBadDescriptor will 
	        be returned if the client did not provide a valid descriptor.

	
	*/
	IMPORT_C TInt WriteDataToClient(const TDesC8& aDes);

	/**
	Copies the data back to the client.

	This function can leave with one of the system-wide error codes. In particular, the leave code
	KErrBadDescriptor will be used if the client did not provide a valid descriptor.

	@param  aDes
	        The data to be copied back to the client. Note that the client must have already
	        created a descriptor of sufficient size for the data to be copied into.

	
	*/
	IMPORT_C void WriteDataToClientL(const TDesC8& aDes);

	/**
	Signals to the client that its request has been completed.

	Equivalent to RMessage::Complete.

	@param  aReason
	        The result code to be given back to the client.

	
	*/
	IMPORT_C void Complete(TInt aReason);
	
	IMPORT_C void AdoptFileHandleFromClientL(TInt aFsHandleIndex, TInt aFileHandleIndex, RFile& aFile);

	/**
	Checks whether this message has already been completed.

	@return A boolean indicating if the message has been completed. ETrue if the message has been 
	        completed, EFalse if not.

	
	*/
	IMPORT_C TBool IsCompleted();

	/**
	Constructs a TMMFMessage from an RMmfIpcMessage.

	@param	aMessage
			The handle to the remote message.

	
	*/
	IMPORT_C TMMFMessage(const RMmfIpcMessage& aMessage);

	/**
	Gets the destination info from the client.

	
	*/
	IMPORT_C void FetchDestinationL();
private:
#ifdef __MMF_USE_IPC_V2__
	/**
	The encapsulated message
	*/
	RMessagePtr2 iMessage;
	/**
	The encapsulated function
	*/
	TInt iFunction;
	/**
	Private padding to preserve BC with earlier versions
	*/
	TInt iDummyPadding[6];
#else
	/**
	The RMessage encapsulated by this object.
	*/
	RMessage iMessage;
// __MMF_USE_IPC_V2__
#endif

	/**
	The destination of this message.
	*/
	TMMFMessageDestination iDestination;

	/**
	Defines whether this object has yet to be completed.
	*/
	TBool iAmCompleted;
	};

/**
@internalComponent

Mixin class used by CLogonMonitor to inform about its state


*/
class MLogonMonitorObserver
	{
public:
	/**
	The monitored thread has been terminated.
	*/
	virtual void ThreadTerminated() = 0;
	};
	
/**
@internalComponent

RSessionBase-based client class to handle the creation of the controller thread and
message sending over IPC.

The controller proxy is responsible for sending and recieving messages over IPC; it does not
care exactly what those messages are.

Note the fact that, although this is an internal component, its size cannot be changed because 
it's embedded in a publishedAll class (RMMFController) and the size of the latter would also be
changed raising a binary compatibility problem.


*/
NONSHARABLE_CLASS(RMMFControllerProxy) : public RMmfSessionBase, public MLogonMonitorObserver
	{
public:

	/**
	Constructor.
	
	*/
	IMPORT_C RMMFControllerProxy();

	/**
	Create a new thread and load a controller plugin into that thread.
	
	@param  aControllerUid
	        The UID of the controller plugin to be loaded.
	@param	aUseSharedHeap
			If this value is EFalse each controller is created with its own heap. The alternative,
			if the value is ETrue, is that controllers share a special heap with other controllers
			created the same way. Each heap uses a chunk, so this avoids situations where the
			number of chunks per process is limited. The default behaviour is generally to be
			preferred, and should give lower overall memory usage. However, if many controllers are
			to be created for a particular thread, then ETrue should be provided to prevent running
			out of heaps or chunks.

	@return One of the system-wide error codes.
	
	*/
	IMPORT_C TInt LoadController(TUid aControllerUid, TBool aUseSharedHeap);

	/**
	Create a new thread and load a controller plugin into that thread.
	
	@param  aControllerInfo
	        A reference to a CMMFControllerImplementationInformation object
	        used for determining the controller UID and heap size
	@param	aUseSharedHeap
			If this value is EFalse each controller is created with its own heap. The alternative,
			if the value is ETrue, is that controllers share a special heap with other controllers
			created the same way. Each heap uses a chunk, so this avoids situations where the
			number of chunks per process is limited. The default behaviour is generally to be
			preferred, and should give lower overall memory usage. However, if many controllers are
			to be created for a particular thread, then ETrue should be provided to prevent running
			out of heaps or chunks.

	@return	One of the system-wide error codes.
	
	*/
	IMPORT_C TInt LoadController(const CMMFControllerImplementationInformation& aControllerInfo, TBool aUseSharedHeap);

	/**
	Delete the controller plugin and close its thread.
	
	Clients must call Close() on the controller proxy, otherwise leaks will occur.

	
	*/
	IMPORT_C void Close();

	/**
	Send a message synchronously to the controller thread.

	The controller framework will analyze the message to determine its correct destination.

	Note: This method will not return until the controller framework has serviced the command.

	@param  aDestination
	        The destination of the message, consisting of the uid of
	        the interface of this message.
	@param  aFunction
	        The function number to indicate which function is to be called
	        on the interface defined in the aDestination parameter.
	@param  aDataTo1
	        A reference to the first chunk of data to be copied to the controller
	        framework. The exact contents of the data are dependent on the
	        interface being called.  Can be NULL.
	@param  aDataTo2
	        A reference to the second chunk of data to be copied to the controller
	        framework. The exact contents of the data are dependent on the
	        interface being called.  Can be NULL.
	@param  aDataFrom
	        A reference to an area of memory to which the controller framework will
	        write any data to be passed back to the client.  Can't be NULL.

	@return The result of the request.  Exact range of values is dependent on the interface.
	
	*/
	IMPORT_C TInt SendSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom) const;

	/**
	Send a message synchronously to the controller thread.

	The controller framework will analyze the message to determine its correct destination.

	Note: This method will not return until the controller framework has serviced the command.

	@param  aDestination
	        The destination of the message, consisting of the uid of
	        the interface of this message.
	@param  aFunction
	        The function number to indicate which function is to be called
	        on the interface defined in the aDestination parameter.
	@param  aDataTo1
	        A reference to the first chunk of data to be copied to the controller
	        framework. The exact contents of the data are dependent on the
	        interface being called.  Can be NULL.
	@param  aDataTo2
	        A reference to the second chunk of data to be copied to the controller
	        framework. The exact contents of the data are dependent on the
	        interface being called.  Can be NULL.

	@return The result of the request.  Exact range of values is dependent on the interface.
	
	*/
	IMPORT_C TInt SendSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2) const;

	/**
	Send a message asynchronously to the controller thread.
	
	The controller framework will analyze the message to determine its correct destination.

	Note: This method will return immediately.  The RunL of the active object owning the
	aStatus parameter will be called when the command is completed by the
	controller framework.

	@param  aDestination
	        The destination of the message, consisting of the uid of
	        the interface of this message.
	@param  aFunction
	        The function number to indicate which function is to be called
	        on the interface defined in the aDestination parameter.
	@param  aDataTo1
	        A reference to the first chunk of data to be copied to the controller
	        framework. The exact contents of the data are dependent on the
	        interface being called.  Can be NULL.
	@param  aDataTo2
	        A reference to the second chunk of data to be copied to the controller
	        framework. The exact contents of the data are dependent on the
	        interface being called.  Can be NULL.
	@param  aDataFrom
	        A reference to an area of memory to which the controller framework will
	        write any data to be passed back to the client.  Can't be NULL.
	@param  aStatus
	        The TRequestStatus of an active object.  This will contain the
	        result of the request on completion.  The exact range of
	        result values is dependent on the interface.

	
	*/
	IMPORT_C void SendAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction,  const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom, TRequestStatus& aStatus) const;

	/**
	Send a message asynchronously to the controller thread.
	
	The controller framework will analyze the message to determine its correct destination.
	
	Note: This method will return immediately.  The RunL of the active object owning the 
	aStatus parameter will be called when the command is completed by the
	controller framework.

	@param  aDestination
	        The destination of the message, consisting of the uid of
	        the interface of this message.
	@param  aFunction
	        The function number to indicate which function is to be called
	        on the interface defined in the aDestination parameter.
	@param  aDataTo1
	        A reference to the first chunk of data to be copied to the controller
	        framework. The exact contents of the data are dependent on the
	        interface being called.  Can be NULL.
	@param  aDataTo2
	        A reference to the second chunk of data to be copied to the controller
	        framework. The exact contents of the data are dependent on the
	        interface being called.  Can be NULL.
	@param  aStatus
	        The TRequestStatus of an active object.  This will contain the
	        result of the request on completion.  The exact range of
	        result values is dependent on the interface.

	
	*/
	IMPORT_C void SendAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction,  const TDesC8& aDataTo1, const TDesC8& aDataTo2, TRequestStatus& aStatus) const;

	IMPORT_C TInt SendSync(TInt aFunction, const TIpcArgs& aIpcArgs) const;
	IMPORT_C void SendAsync(TInt aFunction, const TIpcArgs& aIpcArgs, TRequestStatus& aStatus) const;
	/**
	Register to receive events from the controller framework.
	
	Events can be generated at any time, and are generally associated with things that occur
	due to something happening internally within the controller. For example, an event will
	be generated if the controller stops playing due to reaching the end of a file.

	@param  aEvent
	        A reference to a TMMFEventPckg object that must be member data
	        of the active object calling this method.  The details of the event
	        will be copied into this object when an event occurs.
	@param  aStatus
	        The TRequestStatus of the active object calling this method.

	@see	TMMFEvent
	@see	CMMFControllerEventMonitor
	
	*/
	IMPORT_C void ReceiveEvents(TMMFEventPckg& aEvent, TRequestStatus& aStatus);

	/**
	Cancel a previous registration to receive events from the controller framework.

	This must be called from the DoCancel() method of the active object using the
	ReceiveEvents() API.

	@return One of the standard system-wide error codes.

	@see	TMMFEvent
	
	*/
	IMPORT_C TInt CancelReceiveEvents();
	
	/**
	Set the priority of the controller's sub thread.
	
	This can be used to increase the responsiveness of the audio plugin to minimise
	any lag in processing. This function should be used with care as it may have knock-on
	effects elsewhere in the system.
	
	@param	aPriority
			The TThreadPriority that the thread should run under.  The default is EPriorityNormal.
	@return	TInt
			A standard error code: KErrNone if successful, KErrNotReady if the thread does not have a
			valid handle.
	*/
	IMPORT_C TInt SetThreadPriority(const TThreadPriority& aPriority) const;
	
	/**
	The controller subthread has been terminated.
	
	This is called by CLogonMonitor when the the thread terminates
	*/
	void ThreadTerminated();
private:
	/**
	Creates the new thread
	*/
	TInt DoCreateSubThread(RServer2* aServer2, TUint aMaxHeapSize, TBool aUseSharedHeap);

	/**
	Determines the maximum heap size required by the selected controller
	*/
	TUint ControllersMaxHeapSizeL(TUid aControllerUid);

	/**
	Load a controller by UID
	aControllerInfo is used to determine the heap size; if this is NULL then
	a CMMFControllerImplementationInformation object is created internally.
	*/
	TInt LoadController(TUid aControllerUid, const CMMFControllerImplementationInformation* aControllerInfo, TBool aUseSharedHeap);
	
	/**
	Release heap - for use when a shared heap has been registered
	*/
	void ReleaseHeap();

private:
	enum
		{
		/**
		Shared heap has been opened for this object, and must be closed
		*/
		EFlagOpenedSharedHeap=0x01	
		};

private:
	/**
	The thread in which the controller plugin will run.
	*/
	RThread iSubThread;
	/**
	Used to hold destination for messages from the controller proxy
	(not from clients calling SendSync/SendAsync!!)
	*/
	TMMFMessageDestinationPckg iDestinationPckg;
	/**
	Used to determine the success of a logon.  If the status is not pending, the logon has failed
	and the thread should be closed.
	*/
	CLogonMonitor* iLogonAO;
	/**
	The priority at which the controller plugin thread runs.
	*/
	TThreadPriority iThreadPriority;
	/**
	Flags field
	*/
	TInt iFlags;	
	/**
	This member is internal and not intended for use.
	*/
	TInt iReserved1;
	};

/**
@internalComponent

Used to Kill the controller thread either immediately or after a timeout.
Used by the controller thread on startup to prevent orphaning if no sessions are created to it.
*/
class CMMFControllerProxyShutdown : public CTimer
	{
	enum {EMMFControllerProxyShutdownDelay=1000000};	// 1s
public:

	/**
	Create a new shutdown timer.

	This method can leave with one of the system-wide error codes.

	
	*/
	static CMMFControllerProxyShutdown* NewL();

	/**
	Start the shutdown timer.  The RunL of this active object will be called after
	EMMFControllerProxyShutdownDelay microseconds.

	
	*/
	void Start();

	/**
	Shut down the controller thread immediately.
	
	Calls CActiveScheduler::Stop().

	
	*/
	void ShutdownNow();
private:
	CMMFControllerProxyShutdown();
	void ConstructL();

	/**
	Calls ShutdownNow().

	
	*/
	void RunL();
	};


/**
@publishedAll


Mixin class to define an object capable of handling an event within the controller framework.
*/
class MAsyncEventHandler
	{
public:

	/**
	Sends an event to the client.

	@param  aEvent
	        The event.

	
	*/
	virtual TInt SendEventToClient(const TMMFEvent& aEvent) = 0;
	};

/**
@internalComponent

Used to hold on to an TMMFMessage so we can complete it asynchronously to 
send an event to the client.


*/
class CMMFEventReceiver : public CBase
	{
public:

	/**
	Constructs a new event receiver.
	
	This method may leave with one of the system-wide error codes.

	@param  aMessage
	        The message to be completed when an event occurs.

	@return A pointer to the newly created event receiver.

	
	*/
	static CMMFEventReceiver* NewL(const TMMFMessage& aMessage);

	/**
	Destructor.

	Completes the message with KErrCancel if the message hasn't already been completed.

	
	*/
	~CMMFEventReceiver();

	/**
	Sends an event to the client.

	@param  aEvent
	        The event.

	
	*/
	void SendEvent(const TMMFEvent& aEvent);
private:

	/**
	Constructor.

	@param  aMessage
	        The message to be completed when an event occurs.

	
	*/
	CMMFEventReceiver(const TMMFMessage& aMessage);
private:
	/** 
	The message to be completed when an event occurs.
	*/
	TMMFMessage iMessage;
	};



/**
@internalComponent

The controller proxy server.

The main server inside the controller thread, responsible for creating and destroying the single
session used to transmit messages from the client to the server.

Every controller plugin runs in its own thread, and has its own controller proxy server.


*/
class CMMFControllerProxyServer : public CMmfIpcServer
	{
public:
	/**
	Construct the server.

	This method may leave with one of the system-wide error codes.

	@return The newly created server.

	
	*/
	static CMMFControllerProxyServer* NewL(RServer2* aServer2 );

	/**
	Destructor.

	
	*/
	~CMMFControllerProxyServer();

	/**
	Static thread function.

	The address of this function is passed into RThread::Create.

	Unpackages the startup parameters and calls DoStartThreadL().

	@param  aAny
	        A pointer to the packaged startup parameters.

	@return One of the system-wide error codes.

	
	*/
	static TInt StartThread(TAny* aParam);

	/**
	Called by the active scheduler when the ServiceL of the session leaves.
	Completes the message with the error and restarts the server.

	@param  aError
	        The error that the session ServiceL left with.

	@return  KErrNone
	
	*/
	TInt RunError(TInt aError);

	/**
	Signals that the session has been created.

	Stops the shutdown timer.

	
	*/
	void SessionCreated();

	/**
	Signals that the session has been destroyed.
	Causes the server to shut down immediately.

	
	*/
	void SessionDestroyed();
private:

	/**
	Thread startup code.

	Creates the cleanup stack, installs the active scheduler and creates the server.
	Once all this is completed successfully, it signals the success back to the client.

	This function may leave with one of the system-wide error codes.

	@param  aParams
	        Used to signal startup success back to the client.

	
	*/
	static void DoStartThreadL(TAny* aParam);

	/**
	Creates a new session.  Only one session may be created with the ControllerProxyServer.

	This function may leave with one of the system-wide error codes.

	@param  aVersion
	        The version number of the session.

	@return A pointer to the new session.

	
	*/
	CMmfIpcSession* NewSessionL(const TVersion& aVersion) const;

	/** 
	Constructor.

	
	*/
	CMMFControllerProxyServer();

	/**
	Second phase constructor.

	
	*/
	void ConstructL(RServer2* aServer2);
	
	/**
	Renaming Controller Proxy Server name
	
	
	*/
	static void RenameControllerProxyThread();

private:
	/** 
	The timer used to shut down the server in case the client fails to connect a session.
	*/
	CMMFControllerProxyShutdown* iShutdownTimer;
	/** 
	Indicates whether we have a session connected.  Only one session is allowed to connect to the server.
	*/
	TBool iHaveSession;
	};

class CMMFController;

/**
@internalComponent

The controller proxy session.

Only one session can be connected to a controller proxy server.


*/
class CMMFControllerProxySession : public CMmfIpcSession, public MAsyncEventHandler
	{
public:

	/**
	Construct the session.

	This method may leave with one of the system-wide error codes.

	@return The newly created server.

	
	*/
	static CMMFControllerProxySession* NewL();

	/**
	Second phase constructor called by the CServer base class.

	This function may leave with one of the system-wide error codes.

	@param  aServer
	        A reference to the server to which this session is attached.

	
	*/
	void CreateL(const CMmfIpcServer& aServer);

	/**
	Destructor.
	*/
	~CMMFControllerProxySession();

	/**
	Called by the CServer baseclass when a request has been made by the client.

	This function may leave with on of the system-wide error codes. If
	a leave occurs, the message will be automatically completed by the
	RunError() of the Controller Proxy Server.

	@param  aMessage
	        The request to be handled.  The controller proxy session will create
	        a TMMFMessage from this, and pass on the request to the controller
	        base class to handle.

	
	*/
	void ServiceL(const RMmfIpcMessage& aMessage);

	/**
	Derived from MAsyncEventHandler.

	@see MAsyncEventHandler

	
	*/
	TInt SendEventToClient(const TMMFEvent& aEvent);
private:
	/**
	Constructor
	*/
	CMMFControllerProxySession();

	/**
	Handle a request from the client to register to receive events from the controller framework.

	This function may leave with one of the system-wide error codes.

	@param  aMessage
	        The request to be handled.

	@return ETrue if the message is to be completed now, EFalse if the message will be completed 
	        later.
	*/
	TBool ReceiveEventsL(TMMFMessage& aMessage);

	/**
	Handle a request from the client to stop receiving events from the controller framework.

	This function may leave with one of the system-wide error codes.

	@param  aMessage
	        The request to be handled.

	@return ETrue if the message is to be completed now, EFalse if the message will be completed later.
	*/
	TBool CancelReceiveEvents(TMMFMessage& aMessage);

	/**
	Handle a request from the client to load a controller plugin.

	This function may leave with one of the system-wide error codes.

	@param  aMessage
	        The request to be handled.

	@return ETrue if the message is to be completed now, EFalse if the message will be completed later.
	*/
	TBool LoadControllerL(TMMFMessage& aMessage);
private:
	/** 
	The controller plugin. 
	*/
	CMMFController* iController;
	/** 
	A pointer to the server. 
	*/
	CMMFControllerProxyServer* iServer;
	/** 
	The event receiver.  Used to send events to the client.
	*/
	CMMFEventReceiver* iEventReceiver;
	/** 
	The events waiting to be sent to the client.
	*/
	RArray<TMMFEvent> iEvents;
	};


#endif
