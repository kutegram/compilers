/*
* ==============================================================================
*  Name        : sipconcreteprofileobserver.h
*  Part of     : SIP Profile Client
*  Interface   : private
*  Description : The observer class that must be implemented by users of 
*                 CSIPConcreteProfile
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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

#ifndef MSIPCONCRETEPROFILEOBSERVER_H
#define MSIPCONCRETEPROFILEOBSERVER_H

//  INCLUDES

#include <e32base.h>

// FORWARD DECLARATIONS


// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Observer class to be implemented by users of CSIPConcreteProfile
* It provides event notifications related to profiles.
*/
class MSIPConcreteProfileObserver
    {
    public:

        /**
        * SIP profile registration status changed event
        * Event is send to those observers, who have the
        * corresponding profile instantiated.
        * @param aProfileId id of profile which registration 
        *        status has been changed.
        * @param aStatus new status of the profile
        * @param aStatusId id related to registration
        */
        virtual void RegistrationStatusChangedL(
            TUint32 aProfileId, 
            TInt aStatus,
            TUint32 aStatusId) = 0;

        /** 
        * SIP profile creation event.
        * Event is send to all observers.
        * @param aProfileId id of new SIP Profile
        */
        virtual void AddedL(TUint32 aProfileId) = 0;

        /**
        * SIP profile destruction event.
        * Event is send to those observers, who have the
        * corresponding profile instantiated.
        * @param aProfileId id of profile which was destroyed
        */        
        virtual void RemovedL(TUint32 aProfileId) = 0;

        /** 
        * SIP profile information update event
        * Event is send to those observers, who have the
        * corresponding profile instantiated.
        * @param aProfileId id of updated SIP Profile
        * @param aSize size of updated SIP Profile
        */
        virtual void UpdatedL(TUint32 aProfileId, TUint aSize) = 0;

        /**
        * An asynchronous error has occurred related to SIP profile
        * Event is send to those observers, who have the
        * corresponding profile instantiated.
        * @param aProfileId the id of failed profile 
        * @param aStatus status indicating if error occurred
        *          during registering (ERegistrationInProgress)
        *          or deregistering (EUnregistrationInProgress)
        * @param aError a error code
        */
        virtual void ErrorOccurredL(
            TUint32 aProfileId,
            TInt aStatus,
            TInt aError) = 0;
    };

// MSIPCONCRETEPROFILEOBSERVER_H
#endif
