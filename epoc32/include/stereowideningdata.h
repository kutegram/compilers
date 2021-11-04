/*
* ==============================================================================
*  Name        : StereoWideningData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                stereo widening.
*  Version     : 0.3
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


#ifndef TEFSTEREOWIDENINGDATA_H
#define TEFSTEREOWIDENINGDATA_H

//  INCLUDES
#include <e32std.h>
#include <AudioEffectData.h>
// CLASS DECLARATION

/**
*  This class defines the effect data structure to be passed between client and
*  server.
*
*  @lib StereoWideningEffect.lib
*  @since 3.0
*/
class TEfStereoWidening : public TEfCommon
    {
    public:

        /**
        * Constructor.
        */
        TEfStereoWidening() {}

        /**
        * Constructor.
        */
        TEfStereoWidening( TUint8 aLevel, TBool aContinuousLevelSupported ) :
        	iLevel(aLevel), iContinuousLevelSupported(aContinuousLevelSupported) {}

    	// Data
        // Stereo widening level
		TUint8 iLevel;
        TBool iContinuousLevelSupported;
    };

typedef TPckgBuf<TEfStereoWidening> TEfStereoWideningDataPckg;

#endif      // TEFSTEREOWIDENINGDATA_H

// End of File
