/*
* ==============================================================================
*  Name        : LoudnessData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                Echo Cancellation Data.
*  Version     : 1
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


#ifndef TEFLOUDNESSDATA_H
#define TEFLOUDNESSDATA_H

//  INCLUDES
#include <e32std.h>
#include <AudioEffectData.h>

// CLASS DECLARATION

/**
*  This class defines the effect data structure to be passed between client and
*  server.
*
*  @lib LoudnessEffect.lib
*  @since 3.0
*/
class TEfLoudnessData : public TEfCommon
    {
    public:

        /**
        * Constructor.
        */
        TEfLoudnessData() {}

		// No specific data
    };

typedef TPckgBuf<TEfLoudnessData> TEfLoudnessDataPckg;

#endif      // TEFLOUDNESSDATA_H

// End of File
