/*
* ==============================================================================
*  Name        : MEnvironmentalReverbObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the reverb effect observer class.
*
*  Version     : 0.4
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

#ifndef MENVIRONMENTALREVERBOBSERVER_H
#define MENVIRONMENTALREVERBOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <EnvironmentalReverbBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the reverb effect observer class. Object interested in receiving notification
*  when the CEnvironmentalReverb object changes state should derive from this class and implement
*  its interface.
*
*  @since 3.0
*/

class MEnvironmentalReverbObserver : public MAudioEffectObserver
	{
	public:
		static const TUint KDecayTimeChanged = KSpecificEffectBase + 1;
		static const TUint KDecayHFRatioChanged = KSpecificEffectBase + 2;
		static const TUint KDensityChanged = KSpecificEffectBase + 3;
		static const TUint KDiffusionChanged = KSpecificEffectBase + 4;
		static const TUint KReflectionsDelayChanged = KSpecificEffectBase + 5;
		static const TUint KReflectionsLevelChanged = KSpecificEffectBase + 6;
		static const TUint KReverbDelayChanged = KSpecificEffectBase + 7;
		static const TUint KReverbLevelChanged = KSpecificEffectBase + 8;
		static const TUint KRoomLevelChanged = KSpecificEffectBase + 9;
		static const TUint KRoomHFLevelChanged = KSpecificEffectBase + 10;
	};

#endif	// of MENVIRONMENTALREVERBOBSERVER_H

// End of File