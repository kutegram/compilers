/*
* ==============================================================================
*  Name        : MSourceOrientationObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Source orientation effect
*                observer class.
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

#ifndef MSOURCEORIENTATIONOBSERVER_H
#define MSOURCEORIENTATIONOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <SourceOrientationBase.h>
#include <MOrientationObserver.h>


// CLASS DECLARATION

/**
*  This is the Source Orientation effect observer class. Object interested in receiving notification
*  when the CSourceOrientation object changes state should derive from this class and implement its
*  interface.
*
*  @since 3.0
*/

class MSourceOrientationObserver : public MOrientationObserver
	{

	};

#endif	// of MSOURCEORIENTATIONOBSERVER_H

// End of File