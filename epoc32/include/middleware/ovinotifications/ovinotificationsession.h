/*
 *  This file is part of Notifications API 
 *  Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *  Contact:  notifications.support@nokia.com
 *  This software, including documentation, is protected by copyright controlled by Nokia Corporation. 
 *  All rights reserved. You may use this file only in accordance with the Nokia Developer Software 
 *  Agreement version 2.0 and accompanying Ovi any additional terms. This material also contains 
 *  confidential information which may not be disclosed to others without the prior written consent of Nokia.
 */

#ifndef OVINOTIFICATIONSESSION_H
#define OVINOTIFICATIONSESSION_H

// System includes
#include <QObject>
#include <qglobal.h>

// User includes
#include "ovinotificationinterface.h"

#define str_(x) #x
#define str(x) str_(x)
#define ONE_PLUGIN_ABSOLUTE_PATH str(ONE_PLUGIN_PATH)

// Forward Declarations
class OviNotificationSessionPrivate;

class OviNotificationSession : public QObject,
                   public OviNotificationInterface
{
    Q_OBJECT
    Q_INTERFACES(OviNotificationInterface)

public:
    OviNotificationSession();
    ~OviNotificationSession();

public slots:

    void registerApplication(const QString& aApplicationId);
    void setWakeUp(bool aWakeUp);
    bool setNotificationUi(bool aUseNotificationUi, const QString& aIcon = "");
    bool isWakeUp();
    bool isNotificationUi();
    void unregisterApplication();
    void getNotificationInformation(const QString& aServiceId = "");
    void getVersion();

signals:

    void received(QObject *aNotification) const;
    void stateChanged(QObject* aState);
    void notificationInformation(QObject* aData);
    void version(QString aVersion);

private:

    OviNotificationSessionPrivate   *impl;
};

#endif // OVINOTIFICATIONSESSION_H

// End of file
