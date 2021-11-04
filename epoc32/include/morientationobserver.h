/*
* ==============================================================================
*  Name        : MOrientationObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Orientation effect observer class.
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

#ifndef MORIENTATIONOBSERVER_H
#define MORIENTATIONOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <OrientationBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the location effect observer class. Object interested in receiving notification
*  when the COrientation object changes state should derive from this class and implement
*  its interface.
*
*  @since 3.0
*/

class MOrientationObserver : public MAudioEffectObserver
	{
	public:
		static const TUint KOrientationChanged = KSpecificEffectBase + 1;
		static const TUint KOrientationVectorsChanged = KSpecificEffectBase + 2;
	};

#endif	// of MORIENTATIONOBSERVER_H

// End of File