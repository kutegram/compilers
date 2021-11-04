/*
* ==============================================================================
*  Name        : EnvironmentalReverbData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                Reverb.
*  Version     : 0.4
*
*  Copyright (c) 2004 Nokia Corporation.
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


#ifndef TEFENVIRONMENTALREVERB_H
#define TEFENVIRONMENTALREVERB_H

//  INCLUDES
#include <e32std.h>
#include <AudioEffectData.h>

// CLASS DECLARATION

/**
*  This class defines the effect data structure to be passed between client and
*  server.
*
*  @lib EnvironmentalReverbEffect.lib
*  @since 3.0
*/
class TEfEnvironmentalReverb : public TEfCommon
    {
    public:

        /**
        * Constructor.
        */
        TEfEnvironmentalReverb() {}

    	// Data
        // Reverb values of a Reverb object

		TUint32 iDecayHFRatio;
		TUint32 iDecayHFRatioMin;
		TUint32 iDecayHFRatioMax;
		TUint32 iDecayTime;
		TUint32 iDecayTimeMin;
		TUint32 iDecayTimeMax;
		TUint32 iDensity;
		TUint32 iDiffusion;
		TInt32 iReflectionsLevel;
		TInt32 iReflectionLevelMin;
		TInt32 iReflectionLevelMax;
		TUint32 iReflectionsDelay;
		TUint32 iReflectionsDelayMax;
		TUint32 iReverbDelay;
		TUint32 iReverbDelayMax;
		TInt32 iReverbLevel;
		TInt32 iReverbLevelMin;
		TInt32 iReverbLevelMax;
		TInt32 iRoomHFLevel;
		TInt32 iRoomHFLevelMin;
		TInt32 iRoomHFLevelMax;
		TInt32 iRoomLevel;
		TInt32 iRoomLevelMin;
		TInt32 iRoomLevelMax;
		TUint32 iDelayMax;
		TUint32 iEnvironmentalReverbId;

	};

typedef TPckgBuf<TEfEnvironmentalReverb> TEfEnvReverbDataPckg;

#endif      // TEFENVIRONMENTALREVERB_H

// End of File
