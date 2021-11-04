/*
* ==============================================================================
*  Name        : MListenerLocationObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the listener location effect observer class.
*
*  Version     : 1
*
*  Copyright © 2004 Nokia Corporation.
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

#ifndef MLISTENERLOCATIONOBSERVER_H
#define MLISTENERLOCATIONOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <ListenerLocationBase.h>
#include <MLocationObserver.h>


// CLASS DECLARATION

/**
*  This is the Listener Location effect observer class. Object interested in receiving notification
*  when the CListenerLocation object changes state should derive from this class and implement its
*  interface.
*
*  @since 3.0
*/

class MListenerLocationObserver : public MLocationObserver
	{
		// No specific event ID other than the ones from the base observer class.
	};

#endif	// of MLISTENERLOCATIONOBSERVER_H

// End of File