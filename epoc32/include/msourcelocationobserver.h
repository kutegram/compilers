/*
* ==============================================================================
*  Name        : MSourceLocationObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Source location effect observer class.
*
*  Version     : 2
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

#ifndef MSOURCELOCATIONOBSERVER_H
#define MSOURCELOCATIONOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <SourceLocationBase.h>
#include <MLocationObserver.h>


// CLASS DECLARATION

/**
*  This is the Source Location effect observer class. Object interested in receiving notification
*  when the CSourceLocation object changes state should derive from this class and implement its
*  interface.
*
*  @since 3.0
*/

class MSourceLocationObserver : public MLocationObserver
	{
		// No specific event ID other than the ones from the base observer class.
	};

#endif	// of MSOURCELOCATIONOBSERVER_H

// End of File