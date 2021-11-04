/*
* ==============================================================================
*  Name        : MLoudnessObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the doppler effect observer class.
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

#ifndef LOUDNESSOBSERVER_H
#define LOUDNESSOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <LoudnessBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the noise reduction effect observer class. Object interested in receiving notification
*  when the CLoudness object changes state should derive from this class and implement its
*  interface.
*
*  @since 3.0
*/

class MLoudnessObserver : public MAudioEffectObserver
	{
		// No specific event ID other than the ones from the base observer class.
	};

#endif	// of LOUDNESSOBSERVER_H

// End of File