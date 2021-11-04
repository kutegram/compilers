/*
 *  This file is part of Notifications API 
 *  Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *  Contact:  notifications.support@nokia.com
 *  This software, including documentation, is protected by copyright controlled by Nokia Corporation. 
 *  All rights reserved. You may use this file only in accordance with the Nokia Developer Software 
 *  Agreement version 2.0 and accompanying Ovi any additional terms. This material also contains 
 *  confidential information which may not be disclosed to others without the prior written consent of Nokia.
 */

#ifndef OVINOTIFICATIONS_INTERFACE_H
#define OVINOTIFICATIONS_INTERFACE_H

// System includes
#include <QtCore>
#include <QString>
#include <qglobal.h>


// Forward Declarations
class MbModuleInterface;

// Constants
static const char* KOviNotificationInterfaceId = "com.nokia.OviNotificationSession/1.0";

class OviNotificationInterface
{
public:

    virtual void registerApplication(const QString& aApplicationId) = 0;
    virtual void setWakeUp(bool aWakeUp) = 0;
    virtual bool setNotificationUi(bool aUseNotificationUi, const QString& aIcon = "") = 0;
    virtual bool isWakeUp() = 0;
    virtual bool isNotificationUi() = 0;
    virtual void unregisterApplication() = 0;
    virtual void getNotificationInformation(const QString& aServiceId = "") = 0;
    virtual void getVersion() = 0;
};

Q_DECLARE_INTERFACE(OviNotificationInterface, KOviNotificationInterfaceId);

#endif // OVINOTIFICATIONS_INTERFACE_H

// End of file
