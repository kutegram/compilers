/*
* ==============================================================================
*  Name        : DistanceAttenuationData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                Distance Attenuation.
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


#ifndef DISTANCEATTENUATIONDATA_H
#define DISTANCEATTENUATIONDATA_H

//  INCLUDES
#include <e32std.h>
#include <AudioEffectData.h>

// CLASS DECLARATION

/**
*  This class defines the effect data structure to be passed between client and
*  server.
*
*  @lib DistanceAttenuationEffect.lib
*  @since 3.0
*/
class TEfDistanceAttenuation : public TEfCommon
    {
    public:

        /**
        * Constructor.
        */
        TEfDistanceAttenuation() {}

        /**
        * Constructor.
        */
        TEfDistanceAttenuation( TInt32 aRMin, TInt32 aRMax, TBool aMuteAfterMax,
        						TUint32 aRollOffFactor, TUint32 aRoomRollOffFactor) :
        			 			iRMax(aRMax), iRMin(aRMin), iMuteAfterMax(aMuteAfterMax),
        			 			iRollOffFactor(aRollOffFactor), iRoomRollOffFactor(aRoomRollOffFactor) {}

    	// Data
		TInt32 iRMin;
		TInt32 iRMax;
		TBool iMuteAfterMax;
		TUint32 iRollOffFactor;
		TUint32 iRoomRollOffFactor;
		TUint32 iRollOffFactorMax;
		TUint32 iRoomRollOffFactorMax;

    };

typedef TPckgBuf<TEfDistanceAttenuation> TEfDistanceAttenuationDataPckg;

#endif      // DISTANCEATTENUATIONDATA_H

// End of File
