/*
* ==============================================================================
*  Name        : StereoWideningUtilityData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                StereoWidening.
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


#ifndef STEREOWIDENINGUTILITYDATA_H
#define STEREOWIDENINGUTILITYDATA_H

//  INCLUDES
#include <e32std.h>

// CLASS DECLARATION

/**
*  This class defines the StereoWidening Effect Utility data structure.
*
*  @lib StereoWideningUtility.lib
*  @since 3.0
*/
class TEfStereoWideningUtilityPreset
    {
    public:

        /**
        * Constructor.
        */
        TEfStereoWideningUtilityPreset() : iPresetNameKey(0),iPresetDescriptionKey(0),iPresetName(NULL)
        {}

		TUint32 iPresetNameKey;
		TUint32 iPresetDescriptionKey;
		TBuf16<32>  iPresetName;

    };

#endif      // STEREOWIDENINGUTILITYDATA_H

// End of File
