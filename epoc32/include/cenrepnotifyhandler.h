/*
* ==============================================================================
*  Name        : CenRepNotifyHandler.h
*  Part of     : Common Services / Common Engine
*  Interface   : SDK, Central Repository Notification Handler API
*  Description : Active object wrapper for Central Repository one-shot 
*                Notification handling.
*  Version     : %version: ou1s60rt#14 %
*
*  Copyright © 2004-2007 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef CCENREPNOTIFYHANDLER_H
#define CCENREPNOTIFYHANDLER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// FORWARD DECLARATIONS
class MCenRepNotifyHandlerCallback;
class CRepository;

/**
* Active object wrapper for Central Repository one-shot notification handling.
* Central Repository Notification Handler API provides an easy-to-use 
* implementation of a CActive-based wrapper for Central Repository single-shot
* notifications. In most cases Central Repository Notification Handler can 
* automatically resubscribe to notifications and fetch the modified value from
* Central Repository. 
* The API consists of the classes CCenRepNotifyHandler and 
* MCenRepNotifyHandlerCallback. The user of this class needs to implement relevant
* MCenRepNotifyHandlerCallback interface methods to receive notifications. 
* The user of Central Repository Notification Handler API needs access to 
* Central Repository (centralrepository.h).
*
* Usage:
*  
* Initialization example (from a class that implements MCenRepNotifyHandlerCallback interface):
* @code
* iSession = CRepository::NewL(KTestUid);
* iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession, CCenRepNotifyHandler::EStringKey, KKey1);
* iNotifyHandler->StartListeningL();
* @endcode
*
* Uninitialization example:
* @code
* iNotifyHandler->StopListening(); 
* delete iNotifyHandler;
* @endcode
*
* Handler method implementation example:
* @code
* void CMyCenRepNotifyTest::HandleNotifyString(TUint32 aId, const TDesC16&  aNewValue)
*    {
*    // Print out the notified value
*    RDebug::Print(_L("Key %d changed, new value: %S"), aId, &aNewValue);
*    }
* @endcode
*
* @lib cenrepnotifhandler.lib
* @since S60 3.0
*/
class CCenRepNotifyHandler : public CActive
    {
    public:
        /**
        * Defines different key types. Enumeration is used to indicate the 
        * key type that is listened to. 
        */
        enum TCenRepKeyType
        {
            EIntKey,    ///< Key holds a TInt value.
            ERealKey,   ///< Key holds a TReal value.
            EStringKey, ///< Key holds a TDesC16 value.
            EBinaryKey  ///< Key holds a TDesC8 value.
        };

        /**
        * This is a two-phase constructor method that is used to
        * create a new instance for listening to the changes in a single key.
        *
        * @param aCallback Reference to a callback instance.
        * @param aSession  Reference to an existing repository session.
        *                  Do not close this session until all CCenRepNotifyHandler
        *                  instances referring to it have been deleted.
        * @param aKeyType  Type of the key identified by aId parameter. 
        * @param aId       Id of the key that change notifications are needed for.
        * @return          A pointer to a new instance of the CCenRepNotifyHandler class.
        *
        * @leave  KErrArgument if invalid key type is passed as a parameter.
        */
        IMPORT_C static CCenRepNotifyHandler* NewL( MCenRepNotifyHandlerCallback& aCallback, 
                                                    CRepository& aSession, 
                                                    TCenRepKeyType aKeyType, 
                                                    TUint32 aId );

        /**
        * This is a two-phase constructor method that is used to create a new
        * instance for listening to the changes in all keys in the repository. 
        *
        * Type specific callback methods of MCenRepNotifyHandlerCallback will not
        * be used when notifying about changes in this case,
        * only HandleNotifyGeneric() is used.
        *
        * @param aCallback Reference to a callback instance.
        * @param aSession  Reference to an existing repository session.
        *                  Do not close this session until all CCenRepNotifyHandler
        *                  instances referring to it have been deleted.
        * @return          A pointer to a new instance of the CCenRepNotifyHandler class.
        */
        IMPORT_C static CCenRepNotifyHandler* NewL( MCenRepNotifyHandlerCallback& aCallback, 
                                                    CRepository& aSession );

        /**
        * This is a two-phase constructor method that is used to create a new
        * instance for listening to the changes in a single key.
        * Leaves the constructed instance to cleanup stack.
        *
        * @param aCallback Reference to a callback instance.
        * @param aSession  Reference to an existing repository session.
        *                  Do not close this session until all CCenRepNotifyHandler
        *                  instances referring to it have been deleted.
        * @param aKeyType  Type of the key identified by aId parameter.
        * @param aId       Id of the key that change notifications are needed for.
        * @return          A pointer to a new instance of the CCenRepNotifyHandler class.
        *
        * @leave  KErrArgument if invalid key type is passed as a parameter.
        */
        IMPORT_C static CCenRepNotifyHandler* NewLC( MCenRepNotifyHandlerCallback& aCallback, 
                                                     CRepository& aSession, 
                                                     TCenRepKeyType aKeyType, 
                                                     TUint32 aId );
        /**
        * This is a two-phase constructor method that is used to create a new
        * instance for listening to the changes in all keys in the repository.
        * Leaves the constructed instance to cleanup stack. 
        *
        * Type specific callback methods of MCenRepNotifyHandlerCallback will
        * not be used when notifying about changes in this case,
        * only HandleNotifyGeneric() is used.
        *
        * @param aCallback Reference to a callback instance.
        * @param aSession  Reference to an existing repository session.
        *                  Do not close this session until all CCenRepNotifyHandler
        *                  instances referring to it have been deleted.
        * @return          A pointer to a new instance of the CCenRepNotifyHandler class.
        */
        IMPORT_C static CCenRepNotifyHandler* NewLC( MCenRepNotifyHandlerCallback& aCallback, 
                                                     CRepository& aSession );
        /**
        * When this method is called, the CCenRepNotifyHandler starts
        * listening for notifications. If it is already listening, nothing happens.
        *
        * @leave  KErrAlreadyExists if there is already a notification on same
        *         CRepository for this setting, or an error from IPC or server
        *         side resource allocation failure.
        */
        IMPORT_C void StartListeningL();

        /**
        * When this method is called, the CCenRepNotifyHandler stops
        * listening for notifications. If it is already stopped, nothing happens.
        */
        IMPORT_C void StopListening();


        /**
        * Destructor.
        */
        IMPORT_C virtual ~CCenRepNotifyHandler();

    protected:

        /**
        * Implements CActive
        * @param none
        * @return none
        */    
        void RunL();
    
        /**
        * Implements CActive
        * @param aError the error returned
        * @return error
        */
        TInt RunError( TInt aError );

        /**
        * Implements CActive
        * @param none
        * @return none
        */    
        void DoCancel();

    private:

        /**
        * Constructor used for single key listening.
        *
        * @param aCallback Reference to a callback instance.
        * @param aSession Reference to an existing repository session.
        * @param aKeyType  Type of the key identified by aId parameter.
        * @param aId       Id of the key that change notifications are needed for.
        */
        CCenRepNotifyHandler( MCenRepNotifyHandlerCallback& aCallback, 
                              CRepository& aSession, 
                              TCenRepKeyType aKeyType, 
                              TUint32 aId );
                                                   
        /**
        * Constructor used for whole repository listening.
        *
        * @param aCallback Reference to a callback instance.
        * @param aSession Reference to an existing repository session.
        */
        CCenRepNotifyHandler( MCenRepNotifyHandlerCallback& aCallback, 
                              CRepository& aSession );
        /* 
        * Order notification
        * @return error code from CenRep
        */
        TInt OrderNotification();
       
    private:
        
        CRepository& iSession;  // not owned by this class
        MCenRepNotifyHandlerCallback& iCallback; // not owned by this class
        TCenRepKeyType iKeyType;
        TUint32 iId;        
        TBool iWholeRepository;  // The flag to indicate if listening is for whole repository
    };


/**
* Class provides a callback interface for handling the notifification
* events from the Central Repository. The Client derives a class 
* from this interface and implements the HandleNotify-methods that 
* interest it.
* An empty default implementation is provided for all of the methods.
* In debug build the default implementations print out a debug trace.
*
* @lib commonengine.lib
* @since Series S60 3.0
*/
class MCenRepNotifyHandlerCallback
    {

    public:

    /** 
    * This callback method is used to notify the client about
    * changes for integer value keys, i.e. key type is EIntKey.
    *
    * @param aId Id of the key that has changed.
    * @param aNewValue The new value of the key.
    */
    IMPORT_C virtual void HandleNotifyInt( TUint32 aId, TInt aNewValue );

    /** 
    * This callback method is used to notify the client about
    * changes for real value keys, i.e. key type is ERealKey.
    *
    * @param aId Id of the key that has changed.
    * @param aNewValue The new value of the key.
    */
    IMPORT_C virtual void HandleNotifyReal( TUint32 aId, TReal aNewValue );

    /** 
    * This callback method is used to notify the client about
    * changes for string value keys, i.e. key type is EStringKey.
    *
    * @param aId Id of the key that has changed.
    * @param aNewValue The new value of the key.
    */
    IMPORT_C virtual void HandleNotifyString( TUint32 aId, const TDesC16& aNewValue );

    /** 
    * This callback method is used to notify the client about
    * changes for binary value keys, i.e. key type is EBinaryKey.
    *
    * @param aId Id of the key that has changed.
    * @param aNewValue The new value of the key.
    */
    IMPORT_C virtual void HandleNotifyBinary( TUint32 aId, const TDesC8& aNewValue );

    /** 
    * This callback method is used to notify the client about
    * changes in keys when the whole repository is listened for.
    *
    * Note: It is not guaranteed that a notification will be received
    *       for all keys, if multiple keys are changed in rapid succession
    *       by multiple threads or when the whole repository is reset,
    *       therefore only listen for whole repository if this is not an issue.
    *
    * @param aId Id of the key that has changed. If multiple keys were changed by
    *            whole repository reset, value will be KInvalidNotificationId.
    */
    IMPORT_C virtual void HandleNotifyGeneric( TUint32 aId );

    /** 
    * This callback method is used to notify the client about errors
    * in the handler. Any error in handling causes the handler to stop
    * handling any more notifications. Handling can be restarted with
    * a call to aHandler->StartListeningL(), if the error is non-fatal.
    * However, be careful to trap any errors from this call if this is done.
    *
    * @param aId Id of the key this instance listens to or if notifications for
    *            whole repository are listened, could also be KInvalidNotificationId.
    * @param aError Error code.
    * @param aHandler Pointer to the handler instance. 
    *                 This pointer can be used to identify the handler or restart the listening.
    */
    IMPORT_C virtual void HandleNotifyError( TUint32 aId, TInt aError, 
                                            CCenRepNotifyHandler* aHandler );
    };

#endif      // CCENREPNOTIFYHANDLER_H

// End of File
