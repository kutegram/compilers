/*
* ==============================================================================
*  Name        : EnvironmentalReverbUtilityData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                EnvironmentalReverb.
*  Version     : 0.1
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


#ifndef ENVIRONMENTALREVERBUTILITYDATA_H
#define ENVIRONMENTALREVERBUTILITYDATA_H

//  INCLUDES
#include <e32std.h>

// CLASS DECLARATION

/**
*  This class defines the EnvironmentalReverb Effect Utility data structure.
*
*  @lib EnvironmentalReverbUtility.lib
*  @since 3.0
*/
class TEfEnvironmentalReverbUtilityPreset
    {
    public:

        /**
        * Constructor.
        */
        TEfEnvironmentalReverbUtilityPreset() : iPresetNameKey(0),iPresetDescriptionKey(0),iPresetName(NULL)
        {}

		TUint32 iPresetNameKey;
		TUint32 iPresetDescriptionKey;
		TBuf16<32>  iPresetName;

    };

#endif      // ENVIRONMENTALREVERBUTILITYDATA_H

// End of File
