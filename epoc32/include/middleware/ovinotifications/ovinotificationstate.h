/*
 *  This file is part of Notifications API 
 *  Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *  Contact:  notifications.support@nokia.com
 *  This software, including documentation, is protected by copyright controlled by Nokia Corporation. 
 *  All rights reserved. You may use this file only in accordance with the Nokia Developer Software 
 *  Agreement version 2.0 and accompanying Ovi any additional terms. This material also contains 
 *  confidential information which may not be disclosed to others without the prior written consent of Nokia.
 */

#ifndef OVINOTIFICATIONSTATE_H
#define OVINOTIFICATIONSTATE_H

#include <QObject>
#include <ovinotificationinterface.h>

// forward declaration
class OviNotificationStatePrivate;
class OviNotificationResponseHandler;
class OviNotificationSessionPrivate;

class OviNotificationState : public QObject
{
    Q_OBJECT
    Q_ENUMS(State)
    Q_PROPERTY(State sessionState READ sessionState)
    Q_ENUMS(StateError)
    Q_PROPERTY(StateError sessionError READ sessionError)
    
    
public:
    OviNotificationState();
    ~OviNotificationState();
    
    enum State
    {
        EStateOffline                   = 0,
        EStateConnecting                = 1,
        EStateOnline                    = 2 
    };

    enum StateError
    {
        EErrorNone                  = 0,  
        EErrorEnablerNotFound       = 1,  
        EErrorApplicationIdConflict = 2,  
        EErrorMissingCredentials    = 3,  
        EErrorNoNetwork             = 4,  
        EErrorServiceUnavailable    = 5,  
        EErrorNotAllowed            = 6,  
        EErrorDisabledByUser        = 7,  
        EErrorNotificationIdInvalidated = 8, 
        EErrorWidgetIdMismatch      = 9,   
        EErrorInvalidApplicationId  = 10,  
        EErrorInvalidServiceId      = 11,  
        EErrorEnablerExpired        = 12,  
    };    

public slots:

    virtual State sessionState();
    virtual QString sessionStateString();
    virtual StateError sessionError();
    virtual int sessionErrorInteger();
    virtual QString sessionErrorString();

private:
    OviNotificationStatePrivate* impl;

    // Friend class
    friend class OviNotificationResponseHandler;
    friend class OviNotificationSessionPrivate;
};

#endif // OVINOTIFICATIONSTATE_H
