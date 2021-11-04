/*
* ==============================================================================
*  Name        : Lbs.h
*  Part of     : Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Client-Server communication
*  Version     : %vesion: %
*
*  Copyright (c) 2002-2006 Nokia Corporation.
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

#ifndef __LBS_H__
#define __LBS_H__

#include <LbsPositionInfo.h>
#include <LbsIpc.h>
#include <LbsCommon.h>
#include <LbsRequestor.h>
#include <LbsCriteria.h>

// Forward declarations
class CPositioningPtrHolder;
class CServerPositioningPtrHolder;

/**
 * This is generally the first interface class used by all client applications.
 * It is used to make the primary connection to the location server. After the
 * primary connection has been established, its handle is passed as a parameter
 * of the Open methods of RPositioner to create a sub-session.
 *
 * The RPositionServer class can also be used to discover what position
 * technology modules are available. However, this is only required if a
 * client application actually needs to use a particular module.
 */
class RPositionServer : public RSessionBase
	{
public:
    /**
     * Constructor for RPositionServer
     */
	IMPORT_C RPositionServer();

    /**
     * Creates a session with the positioning server. If there are no other
     * sessions when this is called, the method will start the server.
     * This method must be called before an attempt to obtain module 
     * information or on opening a sub-session.
     *
     * @return a Symbian OS error code.
     * @panic "Lbs Client Fault" 5 If this method is called when a connection is
     * already present. 
     */
	IMPORT_C TInt Connect();

    /**
     * Closes a session with the positioning server.Before the connection to 
     * Location Server is closed, the client application must ensure that any 
     * outstanding notification requests have been cancelled. In particular, 
     * applications must issue all appropriate cancel requests and then wait 
     * for a confirmation that the notifications have been terminated. A 
     * failure to do so results in a client side panic.
     *
     * @panic "Lbs Client Fault" 16 If the outstanding notification requests 
     * are not cancelled before calling this method.
     */
	IMPORT_C void Close();

    /**
     * Obtains the current version number of the location server.
     *
     * @return the version of the client API.
     */
	IMPORT_C TVersion Version() const;

    /**
     * This method obtains the identifier of the systems' default positioning
     * module. This module will be used if no criteria is specified when an
     * RPositioner sub-session is created.
     *
     * @see RPositioner::Open()
     * @param[out] aModuleId will be set, upon successful completion, to the ID of the
     * module that the positioning server uses by default.
     * @return a Symbian OS error code.
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     * are not cancelled before calling close.
     *
     * @pre before calling this method RPositionServer::Connect() should be called.
     */
	IMPORT_C TInt GetDefaultModuleId(TPositionModuleId& aModuleId) const;

    /**
     * This method obtains the current number of available positioning modules.
     *
     * @param[out] aNumModules will be set, upon successful completion, to the number of
     * positioning modules (PSYs) that are currently available.
     * @return a Symbian OS error code.
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     *
     * @pre before calling this method RPositionServer::Connect() should be called.
     */
	IMPORT_C TInt GetNumModules(TUint& aNumModules) const;

    /**
     * Return details about a specified module.
     *
     * @param aModuleIndex a logical index (0...GetNumModules()-1) of a 
     * positioning module.
     * @param[out] aModuleInfo contains, on successful completion, the information
     * relating to the specified positioning module.
     * @return a Symbian OS error code.
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     *
     * @pre before calling this method RPositionServer::Connect() should be called.
     */
	IMPORT_C TInt GetModuleInfoByIndex(TInt aModuleIndex,
	                                   TPositionModuleInfoBase& aModuleInfo) const;
    /**
     * Return details about a specified module.
     *
     * @param aModuleId the unique identifier (UID) of a positioning module
     * @param[out] aModuleInfo contains, on successful completion, the information
     * relating to the specified positioning module.
     * @return a symbian OS error code.
     * @return KErrNotFound is returned if the specified moduleId is not valid.
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     *
     * @pre before calling this method RPositionServer::Connect() should be called.
     */
	IMPORT_C TInt GetModuleInfoById(TPositionModuleId aModuleId,
	                                TPositionModuleInfoBase& aModuleInfo) const;

    /**
     * Obtains information about the specified positioning module.
     *
     * @param[out] aPosModuleStatus contains, on successful completion, the status of
     * the specified positioning module
     * @param aModuleId the unique identifier (UID) of a positioning module
     * @return a symbian OS error code.
     * @return KErrNotFound is returned if the specified moduleId is not valid.
     */
	IMPORT_C TInt GetModuleStatus(TPositionModuleStatusBase& aPosModuleStatus,
	                              TPositionModuleId aModuleId) const;

    /**
     * This method reports status changes of either a single module or all
     * positioning modules. It is an asynchronous request and the client should
     * use it appropriately using active objects.
     *
     * After a notification has been received, the client application must re-issue
     * the status change request if it wishes to obtain further updates.
     *
     * To cancel this request use RPositionServer::CancelRequest() with 
     * EPositionServerNotifyModuleStatusEvent as parameter
     *
     * @param[out] aStatusEvent contains, on successful completion, information regarding
     * the status event and the new status of of the specified positioning module.
     * @param[out] aStatus contains the result code after the asynchronous call completes.
     * It returns
     * - KErrNotFound if the moduleId specified does not exist
     * - KErrArgument is the requested event mask is zero
     * - KErrCancel if the notification is cancelled.
     * @param aModuleId the unique identifier (UID) of a positioning module. If 
     * the parameter is zero, then a status update is provided for all positioning 
     * modules.
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     * @panic "Lbs Client Fault" 15 If there is already is a pending notification for
     * module status event.
     */
	IMPORT_C void NotifyModuleStatusEvent(TPositionModuleStatusEventBase& aStatusEvent,
	                                      TRequestStatus& aStatus,
	                                      const TPositionModuleId aModuleId = KPositionNullModuleId) const;

    /**
     * Cancels a previously issued asynchronous request. The TRequestStatus of the
     * original request will be set to KErrCancel if the cancellation request was
     * successful, or any other Symbian OS error code if CancelRequest was called
     * too late.
     *
     * @param aRequestId is a number that specifies the request to be cancelled.
     * It should be set to EPositionServerNotifyModuleStatusEvent to cancel a 
     * call to RPositionServer::NotifyModuleStatusEvent()
     * @return a symbian OS error code.
     * @return KErrNotFound if there is no outstanding request for the 
     * specified request ID.
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     */
	IMPORT_C TInt CancelRequest(TInt aRequestId);

private:
	void ConstructL();
	void Destruct();
	static TInt StartServer();

private:
	/** A pointer to a container that holds pointer descriptors, needed to point
	to the clients request data during asynchronous requests */
	CServerPositioningPtrHolder* iPtrHolder;
	/** Unused variable for future expansion. */
	TAny* iReserved;
	};


/**
 * Abstract base class for all positioning sub-sessions, including RPositioner.
 *
 * @see RPositioner.
 */
class RPositionerSubSessionBase : public RSubSessionBase
	{
public:
    /**
     * Cancels a previously issued asynchronous request. The TRequestStatus of the
     * original request will be set to KErrCancel if the cancellation request was
     * successful, or any other Symbian OS error code if CancelRequest was called
     * too late.
     *
     * @param aRequestId is a number that specifies the request to be cancelled.
     * It should be set to 
     * - EPositionerNotifyPositionUpdate to cancel a call to
     * RPositioner::NotifyPositionUpdate().
     * - EPositionerGetLastKnownPosition to cancel a call to
     * RPositioner::GetLastKnownPosition()
     * @return KErrNotFound if there is no outstanding request for the 
     * specified request ID.
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     */
	IMPORT_C TInt CancelRequest(TInt aRequestId);
protected:
	IMPORT_C RPositionerSubSessionBase();
	IMPORT_C virtual TAny* ExtendedInterface(TInt aFunctionNumber, TAny* aPtr1, TAny* aPtr2);
private:
	/** Unused variable for future expansion. */
	TAny* iReserved;
	};


/**
 * This class is used to create a sub-session with the server for the
 * purpose of obtaining the current position. In addition to actually
 * obtaining position information, this class also provides mechanisms
 * for obtaining the last known position, the general status of the
 * positioning module, changing how often it wishes to receive position
 * updates, as well as identifying itself to the location framework. 
 *
 * Before using the class, a primary connection must have already been
 * established with the server.
 *
 * @see RPositionServer
 */
class RPositioner : public RPositionerSubSessionBase
	{
public:
    /**
     * Constructor for RPositioner
     */
	IMPORT_C RPositioner();

    /**
     * Creates a sub-session with the positioning server. The server uses the 
     * positioning module with the highest priority by default. 
     * If the highest priority positioning module is not available or if it 
     * returns an error for a position request then the 
     * positioning module with the next highest priority is used.
     *
     * @param[in] aPosServer is a connected session with the positioning server.
     * @return a Symbian OS error code.
     * @panic "Lbs Client Fault" 5 If open is called more than one time on the
     * same RPositioner instance. 
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     *
     * @pre a connection with the server should already have been created
     * by calling RPositionServer::Connect().
     */
	IMPORT_C TInt Open(RPositionServer& aPosServer);

    /**
     * Creates a sub-session with the positioning server. The client specifies
     * the module ID of the positioning module to be used for obtaining position 
     * information.
     *
     * @param[in] aPosServer is a connected session with the positioning server.
     * @param aModuleId is the module ID for this sub-session to use to
     * obtain location information. The module ID of different positioning modules can
     * be obtained by calling RPositionServer::GetNumModules() and 
     * RPositionServer::GetModuleInfoByIndex()
     *
     * @return a symbian OS error code.
     * @return KErrNotFound if the module ID is not valid.
     * @panic "Lbs Client Fault" 5 If open is called more than one time on the
     * same RPositioner instance. 
     * @panic "Lbs Client Fault" 6 If no connection has been established with 
     * Location Server ( by calling RPositionServer::Connect() ).  
     *
     * @pre a connection with the server should already have been created
     * by calling RPositionServer::Connect().
     */
	IMPORT_C TInt Open(RPositionServer& aPosServer,
	                   TPositionModuleId aModuleId);

    /**
     * Creates a sub-session with the positioning server. The client specifies
     * the criteria for choosing the positioning module. The server chooses the 
     * positioning module that satisfies the criteria parameter.
     *
     * @param[in] aPosServer is a connected session with the positioning server.
     * @param[in] aCriteria is the criteria that the server must use to choose an
     * appropriate PSY for this sub-session.
     * @return a Symbian OS error code.
     * @note This function is not supported and it returns KErrNotFound.
     */
	IMPORT_C TInt Open(RPositionServer& aPosServer,
	                   const TPositionCriteriaBase& aCriteria);

    /**
     * Closes a sub-session with the positioning server.
     * Before a sub-session is closed, the client application must ensure 
     * that all outstanding notification requests have been cancelled. In 
     * particular, the application must issue all the appropriate Cancel 
     * requests and then wait for a confirmation that the notifications 
     * have been terminated. A failure to do so results in a panic.
     *
     * @panic "Lbs Client Fault" 16 if the outstanding position request is not
     * cancelled before calling this method.
     */
	IMPORT_C void Close();

    /**
     * Set the requestor for this sub-session. This requestor will be used
     * to verify privacy whenever a location request is made through this sub-session.
     * This method is used when there is only one requestor involved in the
     * positioning request.
     *
     * @param aType identifies the type of requestor, a service or a contact.
     * @param aFormat identifies the format of the requestor.
     * @param[in] aData identifies the requestor string. The requestor string can 
     * be a telephone number, a URL etc.
     * @return a Symbian OS error code.
     * @return KErrArgument is returned if the format or type of the 
     * specified requestor parameter (aRequestor) is incorrect, or if the 
     * EFormatApplication format is used with an ERequestorContact type 
     * of requestor,or if the length of aData exceeds 255 characters.
     * @panic "Lbs Client Fault" 6 If no sub session has been created with 
     * this session ( by calling RPositioner::Open() ).  
     *
     * @pre RPositioner::Open() should have been called prior to this operation.
     * @post This sets the requestor for this session. Further location
     * information requests will result in a privacy check being done with this
     * requestor information.
     */
	IMPORT_C TInt SetRequestor(CRequestor::TRequestorType aType,
	                           CRequestor::TRequestorFormat aFormat,
	                           const TDesC& aData);

    /**
     * Sets the requestors for this sub-session. These requestors will be used
     * to verify privacy whenever a location request is made through this sub-session.
     * This method is used when a chain of requestors is involved in the
     * positioning request.
     *
     * @param[in] aRequestorStack is a collection of CRequestor objects.
     *
     * @return a Symbian OS error code.
     * @return KErrArgument if aRequestorStack contains no requestors, or
     * if the length of aData exceeds 255 characters.
     *
     * @panic "Lbs Client Fault" 6 If no sub session has been created with 
     * this session ( by calling RPositioner::Open() ).  
     *
     * @pre RPositioner::Open() should have been called prior to this operation.
     *
     * @post This sets the requestor for this session. Further location
     * information requests will result in a privacy check being done with this
     * requestor information.
     */
	IMPORT_C TInt SetRequestor(const RRequestorStack& aRequestorStack);

    /**
     * This method can be used to modify the current options set for this sub-session.
     * It enables the client to request an interval time for receiving
     * position updates.
     *
     * @param[in] aPosOption contains the clients requested options for receiving
     * location updates.
     *
     * @return a Symbian OS error code.
     * @return KErrArgument if the specified options conflict – for example, 
     * if the timeout period is less than the specified update interval.
     * @return KErrNotSupported if the positioning module is unable to support 
     * the required options – for example, if the update interval period is 
     * too short.
     *
     * @panic "Lbs Client Fault" 6 If no sub session has been created with 
     * this session ( by calling RPositioner::Open() ).  
     *
     * @pre RPositioner::Open() should have been called prior to this operation.
     */
	IMPORT_C TInt SetUpdateOptions(const TPositionUpdateOptionsBase& aPosOption);

    /**
     * This method retrieves the current options set for this sub-session.
     * These options are related to receiving the position update from the server.
     *
     * @param[out] aPosOption contains, upon successful completion, the set of update
     * options for NotifyPositionUpdate() that are currently in use.
     *
     * @return a Symbian OS error code.
     *
     * @panic "Lbs Client Fault" 6 If no sub session has been created with 
     * this session ( by calling RPositioner::Open() ).  
     */
	IMPORT_C TInt GetUpdateOptions(TPositionUpdateOptionsBase& aPosOption) const;

    /**
     * This method returns cached position information if it is available. This
     * method can be an efficient mechanism - in terms of speed, cost and power
     * consumption - of obtaining the devices' recent position.
     *
     * @param[out] aPosInfo will be set, upon successful completion, to the most recently
     * determined location data.
     * @param[out] aStatus returns the result code after the asynchronous call completes.
     * The parameter can contain the following values,
     * - KErrNone on successful completion.
     * - KErrUnknown if no cached position information is available. 
     * - KErrArgument if the parameter aPosInfo is of a non-supported type. The 
     * only parameter type that is guaranteed to be supported is TPositionInfo.
     * - KErrAccessDenied if no requestor information has been specified or if
     * privacy check fails.
     * - KErrPositionBufferOverflow if there is insufficient space to return 
     * the required information back to the client. This situation can occur when 
     * using HPositionGenericInfo if the application has not allocated a large enough buffer.
     *
     * @panic "Lbs Client Fault" 6 If no sub session has been created with 
     * this session ( by calling RPositioner::Open() ).  
     *
     * @note To cancel this request use RPositioner::CancelRequest() with 
     * EPositionerGetLastKnownPosition as parameter.
     *
     * @note The GetLastKnownPosition does not use any of the options specified
     * using SetUpdateOptions() (namely update interval, maximum age, timeout and 
     * partial updates).
     * 
     * @pre The application should have called RPositioner::SetRequestor() before
     * calling this method.
     */
	IMPORT_C void GetLastKnownPosition(TPositionInfoBase& aPosInfo,
	                                   TRequestStatus& aStatus) const;

    /**
     * This is an asynchronous method for obtaining position updates. It is possible
     * to pass any class that is derived from TPositionInfoBase. However, the
     * standard data retrieval class is TPositionInfo. The standard means of
     * retrieving extended information is to use HPositionGenericInfo.
     *
     * @param[out] aPosInfo will hold, on successful completion, information on the
     * devices' current position.
     * @param[out] aStatus returns the result code after the asynchronous call completes.
     * On completion, the parameter can contain the following values,
     * - KErrNone on successful completion.
     * - KPositionQualityLoss if the positioning module is unable to return 
     * any position information.
     * - KPositionPartialUpdate if position information has been retrieved but 
     * it is incomplete.
     * - KErrNotFound is returned if the currently used module is invalid. A 
     * previously correct module may become invalid if the positioning 
     * module has been uninstalled or disabled by user.
     * - KErrTimedOut if the requested location information could not be 
     * retrieved within the maximum period as specified in the current update 
     * options or time out happens in entities that are involved in retrieving 
     * the location fix.
     * - KErrArgument if the positioning module is unable to support the type 
     * of the class passed in aPosInfo. All positioning modules are required 
     * to support both TPositionInfo and HPositionGenericInfo.
     * - KErrAccessDenied if no requestor information has been specified or if
     * privacy check fails.
     * - KErrPositionBufferOverflow if there is insufficient space to return 
     * the required information back to the client. This situation can occur when 
     * using HPositionGenericInfo if the application has not allocated a large 
     * enough buffer.
     * - KErrCancel if the request was successfully cancelled.
     * @panic "Lbs Client Fault" 6 If no sub session has been created with 
     * this session ( by calling RPositioner::Open() ).  
     * @panic "Lbs Client Fault" 15 If there is already an outstanding request
     * pending for position information.
     *
     * @note To cancel this request use RPositioner::CancelRequest() with 
     * EPositionerNotifyPositionUpdate as parameter.
     *
     * @pre The application should have called RPositioner::SetRequestor() before
     * calling this method.
     */
	IMPORT_C void NotifyPositionUpdate(TPositionInfoBase& aPosInfo,
	                                   TRequestStatus& aStatus) const;

protected:
    /**
     * symbian 2nd phase constructor
     */
	IMPORT_C virtual void ConstructL();
    /**
     * destructs the data inside this class
     */
	IMPORT_C virtual void Destruct();

	/* Reserved for future expansion - derived classes should see documentation
	on how this is to be used. */
	IMPORT_C virtual TAny* ExtendedInterface(TInt aFunctionNumber, TAny* aPtr1, TAny* aPtr2);

private:
    /**
     * Private helper method. To be used only within this class.
     */
	void SetRequestorImplL(const RRequestorStack& aRequestorStack) const;

private:
	/** A pointer to a container that holds pointer descriptors, needed to point
	to the clients request data during asynchronous requests */
	CPositioningPtrHolder* iPtrHolder;
	/** Unused variable for future expansion. */
	TAny* iReserved;
	};

#endif // __LBS_H__
