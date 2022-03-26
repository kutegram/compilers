// MmfController.h
//
// Copyright (c) 2002-2007 Symbian Software Ltd.  All rights reserved.
//


#ifndef __MMFCONTROLLER_H__
#define __MMFCONTROLLER_H__

#include <mmf/server/mmfdatasource.h>
#include <mmf/server/mmfdatasink.h>
#include <mmf/common/mmfcontrollerframework.h>
#include <mmf/common/mmfcontrollerpluginresolver.h>
#include <mmfplugininterfaceuids.hrh>

#include <caf/caf.h>


/**
@publishedAll


Error category denoting a general controller error.

@see TMMFEvent

*/
const TUid KMMFErrorCategoryControllerGeneralError = {0x101F76D3};

/**
@publishedAll


Error category denoting playback complete i.e. due to EOF or error condition

@see TMMFEvent

*/
const TUid KMMFEventCategoryPlaybackComplete = {0x101f7ea0};

/**
@internalComponent
*/
const TUid KUidInterfaceMMFDataSinkHolder = {0x101F76D4};
/**
@internalComponent
*/
const TUid KUidInterfaceMMFDataSourceHolder = {0x101F76D5};

/**
@internalComponent

Create a const TUid with the same values as the controller
ECOM plugin interface UID
*/
const TUid KUidInterfaceMMFController = {KMmfUidPluginInterfaceController};

/**
@internalComponent

IPC messages for interface KUidInterfaceMMFController in the controller framework.
*/
enum TMMFControllerMessages
	{
	EMMFControllerAddDataSource,
	EMMFControllerAddDataSink,
	EMMFControllerRemoveDataSource,
	EMMFControllerRemoveDataSink,
	EMMFControllerReset,
	EMMFControllerPrime,
	EMMFControllerPlay,
	EMMFControllerPause,
	EMMFControllerStop,
	EMMFControllerGetPosition,
	EMMFControllerSetPosition,
	EMMFControllerGetDuration,
	EMMFControllerGetNumberOfMetaDataEntries,
	EMMFControllerGetSizeOfMetaDataEntry,//use internally
	EMMFControllerGetMetaDataEntry,
	EMMFControllerSetPrioritySettings,
	EMMFControllerCancelAddDataSource,
	EMMFControllerCancelAddDataSink,
	EMMFControllerAddFileHandleDataSource,
	EMMFControllerAddFileHandleDataSink
	};



/**
@publishedAll


Client representation of a controller plugin for the Multimedia Framework.

This class allows a client to load a controller plugin into a new thread and access the
functionality provided by that plugin.


*/
class RMMFController
	{
public:

	IMPORT_C RMMFController();

	IMPORT_C TInt Open(TUid aControllerUid, const TMMFPrioritySettings& aPrioritySettings);

	IMPORT_C TInt Open(const CMMFControllerImplementationInformation& aControllerInfo, const TMMFPrioritySettings& aPrioritySettings);

	IMPORT_C TInt Open(TUid aControllerUid, const TMMFPrioritySettings& aPrioritySettings, TBool aUseSharedHeap );

	IMPORT_C TInt Open(const CMMFControllerImplementationInformation& aControllerInfo, const TMMFPrioritySettings& aPrioritySettings, TBool aUseSharedHeap );
	
	IMPORT_C void Close();

	IMPORT_C TInt SetPrioritySettings(const TMMFPrioritySettings& aPrioritySettings) const;

	IMPORT_C TInt AddDataSource(TUid aSourceUid, const TDesC8& aSourceInitData);

	IMPORT_C TInt AddDataSink(TUid aSinkUid, const TDesC8& aSinkInitData);

	IMPORT_C TInt AddDataSource(TUid aSourceUid, const TDesC8& aSourceInitData, TMMFMessageDestination& aHandleInfo);

	IMPORT_C TInt AddDataSink(TUid aSinkUid, const TDesC8& aSinkInitData, TMMFMessageDestination& aHandleInfo);

	IMPORT_C void AddDataSource(const TMMFUidPckg& aSourceUid, const TDesC8& aSourceInitData, TMMFMessageDestinationPckg& aHandleInfoPckg, TRequestStatus& aStatus);
	IMPORT_C void AddFileHandleDataSource(const RFile& aFile, TMMFMessageDestinationPckg& aHandleInfoPckg, TRequestStatus& aStatus);

	IMPORT_C void CancelAddDataSource();
	
	IMPORT_C void AddDataSink(const TMMFUidPckg& aSinkUid, const TDesC8& aSinkInitData, TMMFMessageDestinationPckg& aHandleInfoPckg, TRequestStatus& aStatus);
	IMPORT_C void AddFileHandleDataSink(const RFile& aFile, TMMFMessageDestinationPckg& aHandleInfoPckg, TRequestStatus& aStatus);
	
	IMPORT_C void CancelAddDataSink();

	IMPORT_C TInt RemoveDataSource(const TMMFMessageDestination& aSourceHandleInfo);

	IMPORT_C TInt RemoveDataSink(const TMMFMessageDestination& aSinkHandleInfo);

	IMPORT_C TInt Reset();

	IMPORT_C TInt Prime();

	IMPORT_C TInt Play();

	IMPORT_C TInt Pause();

	IMPORT_C TInt Stop();

	IMPORT_C TInt GetPosition(TTimeIntervalMicroSeconds& aPosition) const;

	IMPORT_C TInt SetPosition(const TTimeIntervalMicroSeconds& aPosition) const;

	IMPORT_C TInt GetDuration(TTimeIntervalMicroSeconds& aDuration) const;

	IMPORT_C TInt GetNumberOfMetaDataEntries(TInt& aNumberOfEntries) const;

	IMPORT_C CMMFMetaDataEntry* GetMetaDataEntryL(TInt aIndex) const;

	IMPORT_C TInt CustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom);

	IMPORT_C TInt CustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2);

	IMPORT_C void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom, TRequestStatus& aStatus);

	IMPORT_C void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TRequestStatus& aStatus);

	IMPORT_C void ReceiveEvents(TMMFEventPckg& aEventPckg, TRequestStatus& aStatus);

	IMPORT_C TInt CancelReceiveEvents();
	
	IMPORT_C TInt SetThreadPriority(const TThreadPriority& aPriority) const;

private:
	/**
	The controller proxy.  Used to pass messages to the controller thread.
	*/
	RMMFControllerProxy iControllerProxy;

	/**
	Used to hold the destination information for messages for the standard controller plugin interface.
	*/
	TMMFMessageDestinationPckg iDestinationPckg;
	};


/**
@publishedAll


Defines an object to which a client may have a direct handle.

This class provides a way of identifying objects within the controller framework, and a means
of passing commands to those objects.


*/
class CMMFObject : public CBase
	{
friend class CMMFObjectContainer;//to set the handle
public:
	IMPORT_C ~CMMFObject();

	IMPORT_C CMMFObject(TUid aInterfaceId);

	IMPORT_C const TMMFMessageDestination& Handle();

	IMPORT_C TBool operator==(const CMMFObject& aOther);

	/**
	Passes a message to the object to handle.

	This is a pure virtual method to be implemented by concrete classes derived from this class.

	The message passed in MUST be completed by the object; however, it can be copied to be
	completed at a later time, should some other asynchronous action need to occur first.

	@param  aMessage
	        The message to be handled.  This MUST be completed by the object.

	
	*/
	virtual void HandleRequest(TMMFMessage& aMessage) = 0;
private:
	void SetHandle(const TMMFMessageDestination& aNewHandle);
private:
	TMMFMessageDestination iHandle;
	};


/**
@publishedAll


Container class to hold the CMMFObject-derived objects in the controller framework.


*/
class CMMFObjectContainer : public CBase
	{
public:

	IMPORT_C CMMFObjectContainer();

	IMPORT_C ~CMMFObjectContainer();

	IMPORT_C TInt AddMMFObject(CMMFObject& aObject);

	IMPORT_C void RemoveAndDestroyMMFObject(CMMFObject& aObject);

	IMPORT_C TInt FindMMFObject(const TMMFMessageDestination& aObjectHandle, CMMFObject*& aObjectFound);

	IMPORT_C void DeleteAllObjects();
private:
	/**
	Internal method to find an object in the array.
	*/
	TInt FindMMFObject(const CMMFObject& aObject, TInt& aPositionInArray);

	/**
	Internal method used to generate the object handle for a newly added object.
	*/
	TInt GenerateObjectHandle();
private:
	/**
	The array of objects.
	*/
	RPointerArray<CMMFObject> iObjects;

	/**
	The next available object handle.
	*/
	TInt iNextObjectHandle;
	};


/**
@publishedAll


CMMFObject-derived class to wrap a Data Source.

Allows a handle to be attributed to a data source, so it can be removed from the controller and
the client can send messages directly to it.


*/
class CMMFDataSourceHolder : public CMMFObject
	{
public:

	IMPORT_C CMMFDataSourceHolder(MDataSource& aDataSource);

	IMPORT_C ~CMMFDataSourceHolder();

	IMPORT_C MDataSource& DataSource();

	//from CMMFObject
	IMPORT_C void HandleRequest(TMMFMessage& aMessage);
private:
	/**
	Pointer to the data source owned by this object.
	*/
	MDataSource* iDataSource;
	};

/**
@publishedAll


CMMFObject-derived class to wrap a Data Sink.

Allows a handle to be attributed to a data sink, so it can be removed from the controller and
the client can send messages directly to it.


*/
class CMMFDataSinkHolder : public CMMFObject
	{
public:
	IMPORT_C CMMFDataSinkHolder(MDataSink& aDataSink);

	IMPORT_C ~CMMFDataSinkHolder();

	IMPORT_C MDataSink& DataSink();

	//from CMMFObject
	IMPORT_C void HandleRequest(TMMFMessage& aMessage);

private:
	/**
	Pointer to the data sink owned by this object.
	*/
	MDataSink* iDataSink;
	};


/**
@publishedAll


Base class for client-side custom command classes.

In order facilitate the use of the more common custom commands, it is desirable to write
a concrete API class for the client to use.  This API class can then be use to wrap all the code
involved to formulate the custom command messages.


*/
class RMMFCustomCommandsBase
	{
public:

	IMPORT_C RMMFCustomCommandsBase(RMMFController& aController, TUid aInterfaceId);
protected:
	/**
	The controller.

	Derived classes should use iController.CustomCommandSync() and
	iController.CustomCommandAsync() to send the custom commands to the controller
	plugin.
	*/
	RMMFController& iController;

	/**
	The destination package.

	Derived classes must pass this into iController.CustomCommandSync() and
	iController.CustomCommandAsync() as the destination argument.
	*/
	TMMFMessageDestinationPckg iDestinationPckg;
	};

/**
@publishedAll


Base class to define the interface of a custom command parser.

In order to facilitate the support of common custom commands by controller plugins, a
custom command parser object can be used.  A set of custom command parsers are created
by the controller plugin (one for each interface supported), and added to the custom command
parser manager in the controller framework.  The controller plugin must also derive from a set of
concrete interfaces (provided in the form of mixin classes). Then, a custom command supported by
one of the custom command parsers will appear to the controller as a concrete API call, rather than
a call to its own custom command API.


*/
class CMMFCustomCommandParserBase : public CBase
	{
public:

	/**
	Pure virtual method to be implemented by derived classes.

	Derived classes must implement the code to decode the message from the client.

	@param  aMessage
	        The message to be serviced. This message must be completed by the derived class.

	
	*/
	virtual void HandleRequest(TMMFMessage& aMessage) = 0;

	/**
	Returns the UID of the custom command interface provided by this parser.

	@return The interface UID.

	
	*/
	IMPORT_C TUid InterfaceId();

	/**
	Destructor.

	
	*/
	IMPORT_C ~CMMFCustomCommandParserBase();
protected:

	/**
	Constructor.

	@param  aInterfaceId
	        The uid of the custom command interface provided by this parser.
	        This must be the same as the interface id of the corresponding client
	        API class. See RMMFCustomCommandsBase.

	
	*/
	IMPORT_C CMMFCustomCommandParserBase(TUid aInterfaceId);

private:

	/**
	The uid of the custom command interface provided by this parser.
	*/
	TUid iInterfaceId;
	};

/**
@publishedPartner


Class to manage custom command parsers.

An object of this type is owned by the controller framework to contain all the custom command
parsers for the controller plugin.


*/
class CMMFCustomCommandParserManager : public CBase
	{
public:
	/**
	Factory constructor.

	@return A pointer to the newly created object.

	
	*/
	IMPORT_C static CMMFCustomCommandParserManager* NewL();

	/**
	Destructor.

	Deletes all custom command parsers added to the manager.

	
	*/
	IMPORT_C ~CMMFCustomCommandParserManager();

	/**
	Attempts to find a custom command parser capable of handling the message.

	@param  aMessage
            The message to be handled.

	@return A boolean indicating in the message has been handled. ETrue if the message has been handled, EFalse
	        if it has not.

	
	*/
	IMPORT_C TBool HandleRequest(TMMFMessage& aMessage);

	/**
	Adds a custom command parser to the manager.  The manager takes ownership of the parser.

	Note:
	This method will leave if it fails to add the parser. If it does leave, ownership
	of the parser will remain with the caller.

	@param  aParser
	        A reference to the parser to be added to the manager.

	
	*/
	IMPORT_C void AddCustomCommandParserL(CMMFCustomCommandParserBase& aParser);
private:
	CMMFCustomCommandParserManager();
private:
	/**
	The array of custom command parsers.
	*/
	RPointerArray<CMMFCustomCommandParserBase> iParsers;
	};



/**
@publishedAll


Base class for controller plugins.

A controller plugin for the multimedia framework must derive from this class and implement
all the pure virtual functions.

Controller plugins control the flow of multimedia data from one or more sources to one or
more sinks. For example, an audio controller plugin might take data from a file source and
output it to a speaker sink, or take data from a microphone source and save it to a file
sink. A controller plugin typically supports one or more multimedia formats, for example
WAV or MPEG4.


*/
class CMMFController : public CBase
	{
public:

	/**
	Allocates and constructs a new controller plugin.

	Uses ECOM to instantiate a new controller plugin. Can leave with any of the system-wide error codes.

	@param  aControllerUid
	        The unique ID of the controller to be instantiated from ECOM.
	@param  aEventHandler
	        A reference to an event handling object that can be used by the
	        controller to send events back to the client.

	@return A pointer to the new controller plugin.

	
	*/
	static CMMFController* NewL(TUid aControllerUid, MAsyncEventHandler& aEventHandler);

	/**
	Handles a message from the client.

	Decodes the message and calls one of the private DoXxx methods to unpackaged the parameters.

	@param  aMessage
	        The message to be handled.

	
	*/
	IMPORT_C virtual void HandleRequestL(TMMFMessage& aMessage);

	/**
	Default destructor.
	*/
	IMPORT_C virtual ~CMMFController();
protected:

	/**
	Constructor.
	*/
	CMMFController(){};

	// virtual functions to be implemented by controller plugin

	/**
	Add a data source to the controller plugin.

	NOTE: The data source is owned by the controller framework, NOT by the controller plugin.
	Under no circumstances should the controller plugin delete the data source.

	@param  aDataSource
	        A reference to the data source to be added.  The controller plugin
	        may call aDataSource.DataSourceType() to find out
	        exactly what type of source it is.

	@leave  KErrNotSupported
	        If the controller plugin does not support the data source, it should leave with this.

	
	*/
	virtual void AddDataSourceL(MDataSource& aDataSource) = 0;

	/**
	Adds a data sink to the controller plugin.

	NOTE: The data sink is owned by the controller framework, NOT by the controller plugin.
	Under no circumstances should the controller plugin delete the data sink.

	@param  aDataSink
	        A reference to the data sink to be added.  The controller plugin
	        may call aDatasink.DatasinkType() to find out
            exactly what type of sink it is.

	@leave  KErrNotSupported
	        If the controller plugin does not support the data sink, it should leave with this.

	
	*/
	virtual void AddDataSinkL(MDataSink& aDataSink) = 0;

	/**
	Removes a data source from the controller plugin.

	Note:
	The data source is owned by the controller framework, NOT by the controller plugin.
	Under no circumstances should the controller plugin delete the data source.

	@param  aDataSource
	        A reference to the data source to be removed.

	@leave  KErrNotSupported
	        The controller plugin may leave during this method.  If the controller plugin does
	        not support the removal of data sources, it should leave with
	        KErrNotSupported. If the controller plugin leaves, the data source will
	        not be destroyed by the controller framework.  If it does not leave, the data source
	        will be destroyed.

	
	*/
	virtual void RemoveDataSourceL(MDataSource& aDataSource) = 0;

	/**
	Removes a data sink from the controller plugin.

	Note:
	The data sink is owned by the controller framework, NOT by the controller plugin.
	Under no circumstances should the controller plugin delete the data sink.

	@param  aDataSink
	        A reference to the data sink to be removed.

	@leave  KErrNotSupported
	        The controller plugin may leave during this method.  If the controller plugin does
	        not support the removal of data sinks, it should leave with
	        KErrNotSupported. If the controller plugin leaves, the data sink will
	        not be destroyed by the controller framework.  If it does not leave, the data sink
	        will be destroyed.

	
	*/
	virtual void RemoveDataSinkL(MDataSink& aDataSink) = 0;

	/**
	Resets the controller plugin.

	The controller should revert back to its newly constructed state. If the Reset is successful
	(i.e. it doesn't leave), the controller framework will delete all objects added to the
	MMFObjectManager including any sources and sinks.

	@leave  KErrNotSupported
	        If the controller plugin does not support being reset, it should leave with KErrNotSupported.

	
	*/
	virtual void ResetL() = 0;

	/**
	Primes the controller plugin.

	The controller must prepare to start playing, by initialising its sources, sinks and buffers.
	This moves the controller from the STOPPED to the PRIMED state.

	
	*/
	virtual void PrimeL() = 0;

	/**
	A partner to the PrimeL() method that is overridable to allow Asynchronous
	completion in the controller whilst maintaining a Synchronous client API.

	The default implementation of this is to call PrimeL() and complete the message with KErrNone.

	
	*/
	IMPORT_C virtual void PrimeL(TMMFMessage& aMessage);

	/**
	Commences playback.

	The controller must now begin transferring data from its source(s) to its sink(s).
	This moves the controller from the PRIMED to the PLAYING state.

	Note:
	This method must return once playing has commenced, and not wait until playing is complete.

	
	*/
	virtual void PlayL()= 0;

	/**
	A partner to the PlayL() method that is overridable to allow Asynchronous
	completion in the controller whilst maintaining a Synchronous client API.

	The default implementation of this is to call PlayL() and complete the message with KErrNone.

	
	*/
	IMPORT_C virtual void PlayL(TMMFMessage& aMessage);


	/**
	Pauses the controller plugin.

	The controller must now cease transferring data from its source(s) to its sink(s).
	This moves the controller from the PLAYING back to the PRIMED state.

	A subsequent call to Play() will cause the controller plugin to resume playback
	from the point it was paused (unless there has been a call to SetPosition() in
	the meantime.

	
	*/
	virtual void PauseL()= 0;

	/**
	A partner to the PauseL() method that is overridable to allow Asynchronous
	completion in the controller whilst maintaining a Synchronous client API.

	The default implementation of this is to call PauseL() and complete the message with KErrNone.

	
	*/
	IMPORT_C virtual void PauseL(TMMFMessage& aMessage);

	/**
	Stops the controller plugin.

	The controller must now undo anything that occurred during the call to Prime().
	This moves the controller from the PRIMED back to the STOPPED state.

	
	*/
	virtual void StopL()= 0;

	/**
	A partner to the StopL() method that is overridable to allow Asynchronous
	completion in the controller whilst maintaining a Synchronous client API.

	The default implementation of this is to call StopL() and complete the message with KErrNone.

	
	*/
	IMPORT_C virtual void StopL(TMMFMessage& aMessage);

	/**
	Gets the current position.

	The controller plugin should calculate the current position in microseconds.

	@return The current position in microseconds.

	
	*/
	virtual TTimeIntervalMicroSeconds PositionL() const = 0;

	/**
	Sets the current position.

	The controller plugin should reposition itself to the position provided.

	@param  aPosition
	        The desired position in microseconds.

	
	*/
	virtual void SetPositionL(const TTimeIntervalMicroSeconds& aPosition) = 0;

	/**
	Gets the duration of the clip.

	The controller plugin should calculate the clip duration in microseconds.

	@return The clips duration in microseconds.

	
	*/
	virtual TTimeIntervalMicroSeconds DurationL() const = 0;

	/**
	Sets the priority settings.

	The new priority settings must be applied to any resource being used by the controller
	plugin that requires priority settings (for example the sound device).

	@param  aPrioritySettings
	        The new priority settings

	

	@capability MultimediaDD
	            A process requesting or using this method that has MultimediaDD capability will
				always have precedence over a process that does not have MultimediaDD.
	*/
	virtual void SetPrioritySettings(const TMMFPrioritySettings& aPrioritySettings) = 0;

	/**
	Handles a custom command.

	Custom commands allow a controller plugin to define its own API.  If the controller framework
	does not understand a message from the client, it is assumed this is a custom command for the
	plugin and passed into this interface.

	The more common custom commands can be handled by Custom Command Parsers on behalf of the
	controller plugin.  This allows the controller plugin to implement a concrete interface
	(defined by mixin classes) rather than having to decode the command itself.  For more
	information, see CMMFCustomCommandParserBase.

	The controller plugin must always complete the message passed into this method,
	even if it does not support the interface required by the message.

	@param  aMessage
	        The message to be handled by the controller plugin.

    @see    CMMFCustomCommandParserBase.
	
	*/
	virtual void CustomCommand(TMMFMessage& aMessage)
		{aMessage.Complete(KErrNotSupported);};//default implementation

	/**
	RetrieveS the number of meta data entries in the clip.

	@param  aNumberOfEntries
	        The controller plugin must set this to the number of meta data entries
	        in the clip.

	
	*/
	virtual void GetNumberOfMetaDataEntriesL(TInt& aNumberOfEntries) = 0;

	/**
	Retrieves a meta data entry from the clip.

	@param  aIndex
	        The index of the meta data entry to retrieve.

	@return A pointer to a newly created CMMFMetaDataEntry object containing the meta information.
	        The controller framework will take ownership of the object when this method returns.

	
	*/
	virtual CMMFMetaDataEntry* GetMetaDataEntryL(TInt aIndex) = 0;

	// Utility functions to be used by controller plugins

	/**
	Sends an event to the client.

	The controller plugin can use this method to send an event to the client.

	@param  aEvent
	        The event to be sent to the client.
	@return One of the system-wide error codes.

	
	*/
	IMPORT_C TInt DoSendEventToClient(const TMMFEvent& aEvent);

	/**
	Gets a reference to the multimedia framework object container.

	The controller plugin may add CMMFObject-derived objects to the container to allow them
	to receive messages directly from the client.

	@return A reference to the MMFObjectContainer.

	
	*/
	IMPORT_C CMMFObjectContainer& MMFObjectContainerL();

	/**
	Adds a custom command parser to the controller framework.

	If the controller framework receives a request it does not understand, it will
	search through its list of custom command parsers before passing the request
	on to the controller plugin as a custom command.

	By using the custom command parsers, the controller plugin can implement a concrete
	API rather than having to decode the common custom commands itself.

	@param  aParser
	        The parser to be added to the controller framework. The controller framework
	        takes ownership of the parser if the call does not leave.

	
	*/
	IMPORT_C void AddCustomCommandParserL(CMMFCustomCommandParserBase& aParser);

private:
	/**
	This is internal and not intended for use.
	*/
	void ConstructL(MAsyncEventHandler& aEventHandler);
	// IPC decode functions
	TBool DoAddDataSourceL(TMMFMessage& aMessage);
	TBool DoAddDataSinkL(TMMFMessage& aMessage);
	TBool DoAddFileHandleDataSourceL(TMMFMessage& aMessage);
	TBool DoAddFileHandleDataSinkL(TMMFMessage& aMessage);
	TBool DoRemoveDataSourceL(TMMFMessage& aMessage);
	TBool DoRemoveDataSinkL(TMMFMessage& aMessage);
	TBool DoResetL(TMMFMessage& aMessage);
	TBool DoPrimeL(TMMFMessage& aMessage);
	TBool DoPlayL(TMMFMessage& aMessage);
	TBool DoPauseL(TMMFMessage& aMessage);
	TBool DoStopL(TMMFMessage& aMessage);
	TBool DoGetPositionL(TMMFMessage& aMessage);
	TBool DoSetPositionL(TMMFMessage& aMessage);
	TBool DoGetDurationL(TMMFMessage& aMessage);
	TBool DoSetPrioritySettingsL(TMMFMessage& aMessage);
	void DoCustomCommand(TMMFMessage& aMessage);
	TBool DoGetNumberOfMetaDataEntriesL(TMMFMessage& aMessage);
	TBool DoGetSizeOfMetaDataEntryL(TMMFMessage& aMessage);
	TBool DoGetMetaDataEntryL(TMMFMessage& aMessage);
private:
	/**
	Buffer to assist copy of meta data over the thread boundary.
	*/
	CBufFlat* iMetaDataBuffer;

	/**
	Required by ECOM.
	*/
	TUid iDtor_ID_Key;

	/**
	The event handler for the controller plugin.
	*/
	MAsyncEventHandler* iAsyncEventHandler;

	/**
	The MMF object container.
	*/
	CMMFObjectContainer* iMMFObjectContainer;

	/**
	The custom command parser manager.
	*/
	CMMFCustomCommandParserManager* iCustomCommandParserManager;
	};



/**
@publishedAll


Mixin class that the user of the class CMMFControllerEventMonitor must derive from.


*/
class MMMFControllerEventMonitorObserver
	{
public:

	/**
	Handles an event that has been generated.

	@param  aEvent
	        The event to be handled.

	
	*/
	virtual void HandleEvent(const TMMFEvent& aEvent) = 0;
	};

/**
@publishedAll


Active object utility class that can be used to monitor a controller plugin for events.
If an event occurs, the client will be notified via the MMMFControllerEventMonitorObserver interface.


*/
class CMMFControllerEventMonitor : public CActive
	{
public:

	/**
	Constructs a controller event monitor object.

	@param  aObserver
	        A reference to the observer of the active object.  The observer will be
	        notified when an event occurs.
	@param  aMMFController
	        A reference to the client controller interface class.

	@return A pointer to the new event monitor.

	
	*/
	IMPORT_C static CMMFControllerEventMonitor* NewL(MMMFControllerEventMonitorObserver& aObserver,
		RMMFController& aMMFController);
	/**
	Destructor.
	*/
	~CMMFControllerEventMonitor();

	/**
	Tells the controller event monitor to start listening for events.

	The controller plugin must have been opened before this method is called.

	
	*/
	IMPORT_C void Start();

private:
	/**
	Calls HandleEvent on iObserver.

	This will not leave.

	
	*/
	void RunL();

	/**
	Cancels the outstanding request on iMMFController.

	
	*/
	void DoCancel();

	/**
	Constructs a controller event monitor object.
	
	@param  aObserver
	        A reference to the observer of the active object.  The observer will be
	        notified when an event occurs.
	@param  aMMFController
	        A reference to the client controller interface class.

	
	*/
	CMMFControllerEventMonitor(MMMFControllerEventMonitorObserver& aObserver,
		RMMFController& aMMFController);
private:
	MMMFControllerEventMonitorObserver& iObserver;
	RMMFController& iMMFController;
	TMMFEventPckg iEventPckg;
	};

/**
Mixin class that the user of the class CMMFAddDataSourceSinkAsync must derive from.

@publishedAll

*/
class MMMFAddDataSourceSinkAsyncObserver
	{
public:
/**
The request to add a data source or sink has completed.
@param	"aError"		"The error resulting from adding the source/sink."
@param  "aHandleInfo"	"This object identifies	the data source/sink inside the controller 
						framework.  This allows the client to send custom commands directly to 
						the data source/sink, and to also remove the data sink from the controller.
						Note that not all data sinks support custom commands, and not all
						controller plugins support the removal of a data sink."
*/
	virtual void MadssaoAddDataSourceSinkAsyncComplete(TInt aError, const TMMFMessageDestination& aHandle) = 0;
	};


/**
Active object utility class that can be used to add a data source or data sink to a controller
plugin asynchronously.  Once the command has been completed, the caller will be notified via the
MMMFAddDataSourceSinkAsyncObserver interface.

@publishedAll


*/
class CMMFAddDataSourceSinkAsync : public CActive
	{
public:

	IMPORT_C static CMMFAddDataSourceSinkAsync* NewL(MMMFAddDataSourceSinkAsyncObserver& aObs);
    IMPORT_C void AddDataSource(RMMFController& aController, TUid aSourceUid, const TDesC8& aSourceInitData);
	IMPORT_C void AddFileHandleDataSource(RMMFController& aController, const RFile& aFile);
    IMPORT_C void AddDataSink(RMMFController& aController, TUid aSinkUid, const TDesC8& aSinkInitData);
	IMPORT_C void AddFileHandleDataSink(RMMFController& aController, const RFile& aFile);

	~CMMFAddDataSourceSinkAsync();

private:
	void RunL();
	void DoCancel();
	CMMFAddDataSourceSinkAsync(MMMFAddDataSourceSinkAsyncObserver& aObserver);
private:
	enum TCurrentAction {EIdle, EAddingDataSource, EAddingDataSink};
private:
	MMMFAddDataSourceSinkAsyncObserver& iObserver;
	TMMFMessageDestinationPckg iHandleInfoPckg;
	TCurrentAction iCurrentAction;
	RMMFController* iMMFController;
	HBufC8* iSourceSinkInitData;
	TMMFUidPckg iSourceSinkUidPckg;
	};

#endif
