/*
* ==============================================================================
*  Name        : EPos_TPosLmDatabaseEvent.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK/S60, Landmarks Database Management API
*  Description : TPosLmDatabaseEvent
*  Version     : %version: 2 % 
*
*  Copyright © 2005-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.0
*/

#ifndef TPOSLMDATABASEEVENT_H
#define TPOSLMDATABASEEVENT_H

#include <e32def.h>

/**
*  Specifies what type of event has occured.
*
*  If there is no adequate event type to describe the event,
*  @p EPosLmDbUnknownEvent is specified.
*
*  @since S60 3.0
*/
enum TPosLmDatabaseEventType
    {
    EPosLmDbUnknownEvent= 0,
    /**< Something has happened, but what happened is not specified.
    This event is used if there are too many events in
    which case the events are bundled into a single unknown event. If
    the client is interested in some database management information,
    it should be reread from the database manager. */
    EPosLmDbDatabaseRegistered = 100,
    /**< A landmark database has been registered or created. This
    event is also generated if a database is copied. The URI of the
    new database can be retrieved by calling
    @ref CPosLmDatabaseManager::DatabaseUriFromEventLC. */
    EPosLmDbDatabaseUnregistered,
    /**< A landmark database has been unregistered or deleted. The
    URI of the deleted database can be retrieved by calling
    @ref CPosLmDatabaseManager::DatabaseUriFromEventLC. */
    EPosLmDbSettingsModified,
    /**< Information about a database, e.g. display name has been
    changed. The URI of the database can be retrieved by calling
    @ref CPosLmDatabaseManager::DatabaseUriFromEventLC. */
    EPosLmDbMediaRemoved = 200,
    /**< Media was removed, possibly containing landmark databases. Use
    @ref ListDatabasesL to list the available databases. */
    EPosLmDbMediaInserted,
    /**< Media was inserted, possibly containing landmark databases.
    Use @ref ListDatabasesL to list the available databases. */
    EPosLmDbNewDefaultDbLocation = 300
    /**< The location of the default database has changed. The URI of
    the default database can be retrieved by calling
    @ref CPosLmDatabaseManager::DefaultDatabaseUriLC. */
    };

/**
*  Struct for landmark database events.
*
*  @since S60 3.0
*/
struct TPosLmDatabaseEvent
    {
    TPosLmDatabaseEventType iEventType;  /**< Type of event. */
    TUint8 iUnused[8];                   /**< For future use. */
    };

#endif      // TPOSLMDATABASEEVENT_H


