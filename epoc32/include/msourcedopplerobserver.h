/*
* ==============================================================================
*  Name        : MSourceDopplerObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Source Doppler Effect observer class.
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

#ifndef MSOURCEDOPPLEROBSERVER_H
#define MSOURCEDOPPLEROBSERVER_H

// INCLUDES

#include <e32base.h>
#include <SourceDopplerBase.h>
#include <MDopplerObserver.h>


// CLASS DECLARATION

/**
*  This is the doppler effect observer class. Object interested in receiving notification
*  when the CDoppler object changes state should derive from this class and implement its
*  interface.
*
*  @since 3.0
*/

class MSourceDopplerObserver : public MDopplerObserver
	{
	};

#endif	// of MSOURCEDOPPLEROBSERVER_H

// End of File