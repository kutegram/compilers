/*
* ==============================================================================
*  Name        : AudioEffectData.h
*  Part of     : Audio Effects API
*  Interface   : Audio Effects
*  Description : This file contains definitions of common audio effects data structures.
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


#ifndef AUDIOEFFECTDATA_H
#define AUDIOEFFECTDATA_H

//  INCLUDES
#include <e32std.h>

// CLASS DECLARATION

/**
*  This class defines the common effect data
*
*  @lib EffectBase.lib
*  @since 3.0
*/
class TEfCommon
    {
    public: // Constructor and Destructor

        /**
        * Constructor.
        */
        TEfCommon() :
        	iEnabled(EFalse), iEnforced(EFalse), iHaveUpdateRights(ETrue) {}

    public:	// Data
		// Flag to indicate whether the effect is enabled or not
		TBool iEnabled;
		// Flag to indicate wheter the effect is enforced
		TInt8 iEnforced;
		// Flag to indicate wheter the effect current has update rights
		TBool iHaveUpdateRights;
    };

#endif      // AUDIOEFFECTDATA_H

// End of File
