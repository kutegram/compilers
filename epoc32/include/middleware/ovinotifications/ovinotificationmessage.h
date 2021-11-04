/*
 *  This file is part of Notifications API 
 *  Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *  Contact:  notifications.support@nokia.com
 *  This software, including documentation, is protected by copyright controlled by Nokia Corporation. 
 *  All rights reserved. You may use this file only in accordance with the Nokia Developer Software 
 *  Agreement version 2.0 and accompanying Ovi any additional terms. This material also contains 
 *  confidential information which may not be disclosed to others without the prior written consent of Nokia.
 */

#ifndef OVINOTIFICATIONMESSAGE_H_
#define OVINOTIFICATIONMESSAGE_H_

#include <QObject>
#include <QVariant>
#include <QString>

// Forward declarations
class OviNotificationResponseHandler;
class OviNotificationMessagePrivate;
class OviNotificationPayload;

class OviNotificationMessage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString from READ from)
    Q_PROPERTY(QString senderInformation READ senderInformation)
    Q_PROPERTY(QString timestamp READ timestamp)
    Q_PROPERTY(QObject* payload READ payload)
    
public:
    
    OviNotificationMessage();
    ~OviNotificationMessage();
    
public slots:
    
    virtual QString from() const;
    virtual QString senderInformation() const;
    virtual QString timestamp() const;
    virtual QObject* payload() const;
   
private:
    
    OviNotificationMessagePrivate *impl;

    // Friend classes
    friend class OviNotificationResponseHandler;
};

#endif /* OVINOTIFICATIONMESSAGE_H_ */
