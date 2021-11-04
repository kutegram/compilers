/*
* ==============================================================================
*  Name        : MDopplerObserver.h
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

#ifndef MDOPPLEROBSERVER_H
#define MDOPPLEROBSERVER_H

// INCLUDES

#include <e32base.h>
#include <DopplerBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the doppler effect observer class. Object interested in receiving notification
*  when the CDoppler object changes state should derive from this class and implement its
*  interface.
*
*  @since 3.0
*/

class MDopplerObserver : public MAudioEffectObserver
	{
	public:
		static const TUint KFactorChanged = KSpecificEffectBase + 1;
		static const TUint KCartesianVelocityChanged = KSpecificEffectBase + 2;
		static const TUint KSphericalVelocityChanged = KSpecificEffectBase + 3;
		static const TUint KMaxFactorChanged = KSpecificEffectBase + 4;
	};

#endif	// of MDOPPLEROBSERVER_H

// End of File