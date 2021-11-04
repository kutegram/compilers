/*
* ==============================================================================
*  Name        : MLocationObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Location effect observer class.
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

#ifndef MLOCATIONOBSERVER_H
#define MLOCATIONOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <LocationBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the location effect observer class. Object interested in receiving notification
*  when the CLocation object changes state should derive from this class and implement
*  its interface.
*
*  @since 3.0
*/

class MLocationObserver : public MAudioEffectObserver
	{
	public:
		static const TUint KLocationCartesianChanged = KSpecificEffectBase + 1;
		static const TUint KLocationSphericalChanged = KSpecificEffectBase + 2;
	};

#endif	// of MLOCATIONOBSERVER_H

// End of File