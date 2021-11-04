/*
 *  This file is part of Notifications API 
 *  Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *  Contact:  notifications.support@nokia.com
 *  This software, including documentation, is protected by copyright controlled by Nokia Corporation. 
 *  All rights reserved. You may use this file only in accordance with the Nokia Developer Software 
 *  Agreement version 2.0 and accompanying Ovi any additional terms. This material also contains 
 *  confidential information which may not be disclosed to others without the prior written consent of Nokia.
 */

#ifndef OVINOTIFICATIONPAYLOAD_H_
#define OVINOTIFICATIONPAYLOAD_H_

#include <QObject>
#include <QVariant>
#include <QString>

// Forward declarations
class OviNotificationPayloadPrivate;

class OviNotificationPayload : public QObject
{
    Q_OBJECT
    
public:
    
    OviNotificationPayload();
    ~OviNotificationPayload();
    
public slots:
    
    virtual QString dataString() const;
    virtual QString type() const;
    virtual QString encoding() const;
    virtual QByteArray data() const;
    
private:
    
    OviNotificationPayloadPrivate *impl;

    // Friend classes
    friend class OviNotificationResponseHandler;
};

#endif /* OVINOTIFICATIONMESSAGE_H_ */
