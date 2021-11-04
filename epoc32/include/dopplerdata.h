/*
* ==============================================================================
*  Name        : DopplerData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                doppler.
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


#ifndef DOPPLERDATA_H
#define DOPPLERDATA_H

//  INCLUDES
#include <e32std.h>
#include <AudioEffectData.h>

// CLASS DECLARATION

/**
*  This class defines the effect data structure to be passed between client and
*  server.
*
*  @lib DopplerUtility.lib
*  @since 3.0
*/



class TEfDoppler : public TEfCommon
    {
    public:

        /**
        * Constructor.
        */
        TEfDoppler() {}

        /**
        * Constructor.
        */
        TEfDoppler( TInt32 aVelocityX, TInt32 aVelocityY, TInt32 aVelocityZ, TInt32 aAzimuth,
                    TInt32 aElevation, TInt32 aRadius, TUint32 aFactor, TUint32 aMaxFactor ) :
        			iVelocityX(aVelocityX), iVelocityY(aVelocityY), iVelocityZ(aVelocityZ),
        			iAzimuth(aAzimuth), iElevation(aElevation), iRadius(aRadius), iFactor(aFactor),
        			iMaxFactor(aMaxFactor) {}

		TInt32 iVelocityX;
		TInt32 iVelocityY;
		TInt32 iVelocityZ;
		TInt32 iAzimuth;
		TInt32 iElevation;
		TInt32 iRadius;
		TUint32 iFactor;
		TUint32 iMaxFactor;

    };

typedef TPckgBuf<TEfDoppler> TEfDopplerDataPckg;

#endif      // DOPPLERDATA_H

// End of File
