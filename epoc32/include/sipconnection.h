/*
* ==============================================================================
*  Name        : sipconnection.h
*  Part of     : SIP Client
*  Interface   : SDK API, SIP API
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

#ifndef CSIPCONNECTION_H
#define CSIPCONNECTION_H

// INCLUDES
#include <e32base.h>
#include <in_sock.h>
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIP;
class MSIPConnectionObserver;
class CSIPClientTransaction;
class MSIPRegistrationContext;
class CSIPRefresh;
class CSIPRequestElements;
class CSIPConnectionImplementation;

// CONSTANTS

// CLASS DECLARATION

/**
* @publishedAll
* 
*
* Class for monitoring connection's state and sending SIP requests outside
* the dialog associations. Class must not be used
* - for sending requests to which received non-failure response creates a dialog
* - for sending requests that must be sent within SIP dialog
*  
* Note that the user can have only one instance of the class per same IAP-id.
*/
class CSIPConnection : public CBase
	{
    public:
        /** Connection states */
        enum TState 
            {
            /** Connection initializing */
			EInit=1,
			/** Connection active */
			EActive,
			/** Connection suspended */
			ESuspended,
			/** Connection is inactive */
			EInactive,
			/** Connection is permanently unavailable */
			EUnavailable
            };

    public:  // Constructors and destructor

	    /**
        * Two-phased constructor.
		* @param aSip a handle to the SIP server
		* @param aIapId IAP-id
		* @param aObserver a observer for receiving asynchonous events on this
        *   connection
        * @return New object, ownership is transferred
        * @capability NetworkServices
        */
		IMPORT_C static CSIPConnection*
            NewL(CSIP& aSIP,
				 TUint32 aIapId,
				 MSIPConnectionObserver& aObserver);

	    /**
        * Two-phased constructor.
		* Constructs an object and adds the pointer to the cleanup stack;
		* @param aSip a handle to the SIP server
		* @param aIapId IAP-id
		* @param aObserver a observer for receiving asynchonous events on this
        *   connection
        * @return New object, ownership is transferred
        * @capability NetworkServices
        */
		IMPORT_C static CSIPConnection*
            NewLC(CSIP& aSIP,
				  TUint32 aIapId,
				  MSIPConnectionObserver& aObserver);

		/**
		* Destructor
        * @capability NetworkServices
		*/
		IMPORT_C ~CSIPConnection();

    public: // New functions

        /**
		* Gets current state of the connection        
        * @return current state of the connection
        */
		IMPORT_C TState State() const;

        /**
		* Creates SIP request and sends it to the given destination.
		* The function must not be used with SIP requests that creates
		* SIP dialog associations or must be sent within SIP dialog
		* association.
		* This provokes the Non-invite state machine.
		* This function must be used if the user has created the
		* registration binding.
		* @pre State() == EActive.
		* @pre aContext.IsContextActive() == ETrue
		* @param aElements contains local and remote addresses,
		*		 optional SIP message headers and body.
		*        The ownership is transferred.
		* @param aContext defines outbound proxy to be used. If the user
		*        does not provide from-address it will be constucted using
		*        user's AOR used during the registration.
        * @return SIP client transaction, ownership is transferred
        * @leave KErrArgument if aElements == 0
        * @leave KErrSIPInvalidRegistrationState if aContext.IsContextActive()
        *	== EFalse
		* @capability NetworkServices
        */
		IMPORT_C CSIPClientTransaction*
            SendRequestL(CSIPRequestElements* aElements,
                         const MSIPRegistrationContext& aContext);

        /**
		* Creates SIP request and sends it to the given destination.
		* The function must not be used with SIP requests that creates
		* SIP dialog associations or must be sent within SIP dialog
		* association.
		* This provokes the Non-invite state machine.
		* This function must be used if the user has created the
		* registration binding.
		* @pre State() == EActive.
		* @pre aContext.IsContextActive() == ETrue
		* @param aElements contains local and remote addresses,
		*		 optional SIP message headers and body.
		*        The ownership is transferred.
		* @param aContext defines outbound proxy to be used. If the user
		*        does not provide from-address it will 
		*        be constucted using user's AOR used during the registration.
		* @param aRefresh defines the refresh interval for this transaction.
        * @return SIP client transaction, ownership is transferred
        * @leave KErrArgument if aElements == 0
        * @leave KErrSIPInvalidRegistrationState if aContext.IsContextActive()
        *	== EFalse
        * @capability NetworkServices
        */
		IMPORT_C CSIPClientTransaction*
            SendRequestL(CSIPRequestElements* aElements,                                        
                         const MSIPRegistrationContext& aContext,
						 CSIPRefresh& aRefresh); 

        /**
		* Creates SIP request and sends it to the given destination.
		* The function must not be used with SIP requests that creates SIP
		* dialog associations or must be sent within SIP dialog association.
		* This invokes the Non-invite state machine.
		* @pre State() == EActive.
		* @pre aElements.FromHeader() != 0
		* @param aElements contains local and remote addresses,
		*		 optional SIP message headers and body.
		*        The ownership is transferred.
        * @return SIP client transaction, ownership is transferred
        * @leave KErrArgument if aElements == 0 or if From-header is not
        *	present in aElements
        * @capability NetworkServices
        */
		IMPORT_C CSIPClientTransaction*
            SendRequestL(CSIPRequestElements* aElements);

        /**
		* Creates SIP request and sends it to the given destination.
		* The function must not be used with SIP requests that creates SIP
		* dialog associations or must be sent within SIP dialog association.
		* This invokes the Non-invite state machine.
		* @pre State() == EActive.
		* @pre aElements.FromHeader() != 0
		* @param aElements contains local and remote addresses,
		*		 optional SIP message headers and body.
		*        The ownership is transferred.
		* @param aRefresh indicates that transaction will be refreshed
        * @return SIP client transaction, ownership is transferred
        * @leave KErrArgument if aElements == 0 or if From-header is not
        *	present in aElements
        * @capability NetworkServices
        */
		IMPORT_C CSIPClientTransaction*
            SendRequestL(CSIPRequestElements* aElements,
						 CSIPRefresh& aRefresh);

		/**
		* Creates SIP REGISTER request and sends it to the given destination.
		* User must no define any Contact or Expires-headers
		* in the provided elements.
		* @pre State() == EActive
        * @pre aElements != 0
        * @pre aElements->Method().DesC().Length()==0
		* @param aElements contains local and remote addresses, optional SIP
        *        message headers and body. User must not set any expires values
        *        to aElements. The ownership is transferred.
        * @return SIP REGISTER client transaction, ownership is transferred
        * @leave KErrArgument if aElements == 0 or if the request method has
        *	been defined in aElements
        * @capability NetworkServices
        */
		IMPORT_C CSIPClientTransaction*
            FetchRegistrationsL(CSIPRequestElements* aElements);

		/**
		* Gets Iap-id used for this connection
		* @return Iap-id
		*/
        IMPORT_C TUint32 IapId() const;

		/**
        * Gets SIP server handle
        * @return handle to SIP server, or 0-pointer if SIP server does not
        *	exist any more
        */        
        IMPORT_C CSIP* SIP();

        /**
        * Gets SIP server handle
        * @return handle to SIP server, or 0-pointer if SIP server does not
        *	exist any more
        */        
        IMPORT_C const CSIP* SIP() const;
      
		/**
		* Sets a RSocket option used for all the sockets used for sending 
		* SIP requests and responses in this CSIPConnection.
		* @pre State() == EActive
		* @param aOptionName An integer constant which identifies an option.
        * @param aOptionLevel An integer constant which identifies 
        *        level of an option.
        * @param aOption Option value packaged in a descriptor.
        * @leave A system-wide error code
        * @capability NetworkControl
        * @capability NetworkServices
        * @capability Location
        * @capability ReadDeviceData
        * @capability WriteDeviceData        
        */        
	    IMPORT_C void SetOptL(TUint aOptionName,
	                      	  TUint aOptionLevel,
	                      	  const TDesC8& aOption=KNullDesC8);

		/**
		* Sets a RSocket option used for all the sockets used for sending 
		* SIP requests and responses in this CSIPConnection.
		* @pre State() == EActive
		* @param aOptionName An integer constant which identifies an option.
        * @param aOptionLevel An integer constant which identifies 
        *        level of an option.
        * @param aOption Option value as an integer.
        * @leave A system-wide error codes
        * @capability NetworkControl
        * @capability NetworkServices
        * @capability Location
        * @capability ReadDeviceData
        * @capability WriteDeviceData
        */ 	                         
	    IMPORT_C void SetOptL(TUint aOptionName,
	                          TUint aOptionLevel,
	                          TInt aOption);

        /**
        * Gets the local IP address of this CSIPConnection 
        * that is used by the SIP implementation.
        * The user should re-new the call whenever the connection state changes
        * to the CSIPConnection::EActive in order to verify the correctness of
        * the previously retrieved local IP address. The local IP address might
        * be different as a result of the connection state change.
        * @pre State() == CSIPConnection::EActive
        * @param aAddr on return filled with local IP address
        * @leave a system-wide error code
        */ 	                         
	    IMPORT_C void GetLocalAddrL(TInetAddr& aAddr) const;

	public: // New functions, for internal use
	
		/**
		* Returns the implementation instance.
		*
 		* @return CSIPConnectionImplementation
		*/
		CSIPConnectionImplementation& Implementation();

    private: // Constructors
    
        CSIPConnection();

        void ConstructL(CSIP& aSIP,
                        TUint32 aIapId,
                        MSIPConnectionObserver& aObserver);

	private: // Data
	
		CSIPConnectionImplementation* iImplementation;
		        
	private: // For testing purposes
	
	    UNIT_TEST(CSIP_Test)
        UNIT_TEST(CSIPConnection_Test)
        UNIT_TEST(CSIPSubscribeDialogAssoc_Test)
        UNIT_TEST(CSIPInviteDialogAssoc_Test)
        UNIT_TEST(CSIPReferDialogAssoc_Test)
        UNIT_TEST(CSIPNotifyDialogAssoc_Test)
        UNIT_TEST(CSIPDialogTrying_Test)
        UNIT_TEST(CSIPRegistrationBinding_Test)
        
        __DECLARE_TEST;
	};

#endif
