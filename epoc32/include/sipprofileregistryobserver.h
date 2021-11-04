/*
* ==============================================================================
*  Name        : sipprofileregistryobserver.h
*  Part of     : SIP Profile Client
*  Interface   : SDK API, SIP Profile API
*  Description : The observer class for monitoring SIP profiles.
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

#ifndef MSIPPROFILEOREGISTRYBSERVER_H
#define MSIPPROFILEOREGISTRYBSERVER_H

//  INCLUDES
#include <e32base.h>
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
*  @publishedAll
*  
*
*  The observer class for monitoring SIP profiles.
*  Class must be implemented by the user in order to 
*  observe changes in the SIP profiles.
*/
class MSIPProfileRegistryObserver 
    {
    public: 
        /** Profile Registry events */
        enum TEvent
            {
            /** 
            * Signals the creation of a SIP profile, indicating that a new
            * profile is added into permanent store. This event is sent to
            * all observers.
            */
            EProfileCreated = 0,
            /** 
            * Signals the updating of a SIP profile, indicating that the data of 
            * an existing profile is updated into permanent store. This event is
            * sent to those observers who have the corresponding profile 
            * instantiated. 
            * Newly updated values of the profile are available for clients after
            * they receive this signal.If profile was registered while updated,
            * reregistration of the profile may occur. Updated values of the 
            * profile are uploaded into network when SIP registration process
            * is completed.It is possible (but not recommended) that profile is
            * updated even when it is being enabled by the client. If client 
            * receives this event for enabled profile, client should react as if
            * error was occurred in the exception that profile is disabled
            * or deleted first.
            */
            EProfileUpdated,
            /**
            * Signals the changing of the registration status of a SIP profile
            * to registered.
            * This event is sent to those observers who have the corresponding
            * profile instantiated.
            */
            EProfileRegistered,
            /**
            * Signals the changing of the registration status of a SIP profile
            * to deregistered.
            * This event is sent to those observers who have the corresponding
            * profile instantiated.
            */
            EProfileDeregistered,
            /**
            * Signals the destruction of a SIP profile, indicating that the 
            * profile has been removed from the permanent store and cannot 
            * be used anymore.This event is sent to those observers who have 
            * the corresponding profile instantiated.
            */
            EProfileDestroyed
            };

        /** 
        * An event related to SIP Profile has accorred
        * @param aProfileId a profile Id
        * @param aEvent an occurred event
        **/
        virtual void ProfileRegistryEventOccurred(TUint32 aProfileId,
                                                  TEvent aEvent)=0;

        /**
        * An asynchronous error has occurred related to SIP profile
        * Event is send to those observers, who have the
        * corresponding profile instantiated.
        * @param aProfileId the id of failed profile 
        * @param aError an occurred error
        */
        virtual void ProfileRegistryErrorOccurred(TUint32 aProfileId,
                                                  TInt aError)=0;
    };

// MSIPPROFILEOREGISTRYBSERVER_H
#endif
