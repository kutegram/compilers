/*
* ==============================================================================
*  Name        : cmpluginembdestinationdef.h
*  Part of     : Networking Utilities / Connection Method Manager
*  Description : Embedded destination attribute descriptor header.
*  Version     : %version: %
*
*  Copyright © 2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ==============================================================================
*/
#ifndef CMEMBEDDEDDESTINATION_H
#define CMEMBEDDEDDESTINATION_H

// Bearer type of the embedded destination
/**  ECOM interface UID */
const TUint KUidEmbeddedDestination  = 0x10207379;

// Embedded destination plugin has no special attribute. Call ::Destination()
// function of interface class to get destination object.
// The following common attribute are supported:
// - ECmBearerType  (read-only)
// - ECmName,       (read/write)
// - ECmIapId       (returns destination Id! read-only)
// - ECmCoverage    (always return EFalse. read-only)
// - ECmProtected   (read/write)
// - ECmDestination (always return ETrue. read-only)
// - ECmHidden      (read/write)
// - ECmDefaultPriority (read-only)

#endif // CMEMBEDDEDDESTINATION_H
