/*
* ==============================================================================
*  Name        : MAudioEqualizerObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Audio Equalizer effect observer class.
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

#ifndef MAUDIOEQUALIZEROBSERVER_H
#define MAUDIOEQUALIZEROBSERVER_H

// INCLUDES

#include <e32base.h>
#include <AudioEqualizerBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the equalizer effect observer class. Object interested in receiving notification
*  when the CAudioEqualizer object changes state should derive from this class and implement
*  its interface.
*
*  @since 3.0
*/

class MAudioEqualizerObserver : public MAudioEffectObserver
	{
	public:
		static const TUint KBand1Changed = KSpecificEffectBase + 1;
		static const TUint KBand2Changed = KSpecificEffectBase + 2;
		static const TUint KBand3Changed = KSpecificEffectBase + 3;
		static const TUint KBand4Changed = KSpecificEffectBase + 4;
		static const TUint KBand5Changed = KSpecificEffectBase + 5;
		static const TUint KBand6Changed = KSpecificEffectBase + 6;
		static const TUint KBand7Changed = KSpecificEffectBase + 7;
		static const TUint KBand8Changed = KSpecificEffectBase + 8;
		static const TUint KBand9Changed = KSpecificEffectBase + 9;
		static const TUint KBand10Changed = KSpecificEffectBase + 10;
		static const TUint KBand11Changed = KSpecificEffectBase + 11;
		static const TUint KBand12Changed = KSpecificEffectBase + 12;
	};

#endif	// of MAUDIOEQUALIZEROBSERVER_H

// End of File