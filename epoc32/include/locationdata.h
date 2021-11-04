/*
* ==============================================================================
*  Name        : LocationData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                location.
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


#ifndef TEFLOCATION_H
#define TEFLOCATION_H

//  INCLUDES
#include <e32std.h>
#include <AudioEffectData.h>

// CLASS DECLARATION

/**
*  This class defines the effect data structure to be passed between client and
*  server.
*
*  @lib LocationEffect.lib
*  @since 3.0
*/



class TEfLocation : public TEfCommon
    {
    public:

        /**
        * Constructor.
        */
        TEfLocation() {}

        /**
        * Constructor.
        */
        TEfLocation( TInt32 aXCoordinate, TInt32 aYCoordinate, TInt32 aZCoordinate,
        			 TInt32 aAzimuth, TInt32 aElevation, TInt32 aRadius ):
        	iXCoordinate(aXCoordinate), iYCoordinate(aYCoordinate), iZCoordinate(aZCoordinate),
        	iAzimuth(aAzimuth), iElevation(aElevation), iRadius(aRadius) {}

    	// Data
        // Location values of a location object
		TInt32 iXCoordinate;
		TInt32 iYCoordinate;
		TInt32 iZCoordinate;
		TInt32 iAzimuth;
		TInt32 iElevation;
		TInt32 iRadius;

    };

typedef TPckgBuf<TEfLocation> TEfLocationDataPckg;

#endif      // TEFLOCATION_H

// End of File
