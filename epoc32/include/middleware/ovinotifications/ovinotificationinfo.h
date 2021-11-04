/*
 *  This file is part of Notifications API 
 *  Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *  Contact:  notifications.support@nokia.com
 *  This software, including documentation, is protected by copyright controlled by Nokia Corporation. 
 *  All rights reserved. You may use this file only in accordance with the Nokia Developer Software 
 *  Agreement version 2.0 and accompanying Ovi any additional terms. This material also contains 
 *  confidential information which may not be disclosed to others without the prior written consent of Nokia.
 */

#ifndef OVINOTIFICATIONINFO_H_
#define OVINOTIFICATIONINFO_H_

#include <QObject>

// Forward declarations
class OviNotificationInfoPrivate;

class OviNotificationInfo : public QObject
{
    Q_OBJECT
    
public:
    
    OviNotificationInfo();
    ~OviNotificationInfo();
    
public slots:

    virtual QString notificationId() const;

private:
    
    OviNotificationInfoPrivate *impl;
    
    // Friend classes
    friend class OviNotificationResponseHandler;
};

#endif /* OVINOTIFICATIONINFO_H_ */
