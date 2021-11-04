/*
* ==============================================================================
*  Name        : sensrvilluminationsensor.h
*  Part of     : Sensor Definitions API
*  Description : Channel data types definitions
*  Version     : %version: 2 %
*
*  Copyright © 2008 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.1
*/


#ifndef SENSRVILLUMINATIONSENSOR_H
#define SENSRVILLUMINATIONSENSOR_H

//  INCLUDES
#include <e32base.h>
#include <sensrvtypes.h> 


// ILLUMINATION RELATED CHANNELS

/**
* - Name:          Ambient light event channel type
* - Type:          Event
* - Datatype:      TSensrvAmbientLightData
* - Description:   Ambient light events
*/
const TSensrvChannelTypeId KSensrvChannelTypeIdAmbientLightData = 0x2000BF16;


// ILLUMINATION RELATED DATATYPES

class TSensrvAmbientLightData
    {
public:

    /**
    * Brighness constants for ambien light sensor data channel.
    */
    static const TUint8 KAmbientLightVeryDark 	= 0;
    static const TUint8 KAmbientLightDark 	    = 20;
    static const TUint8 KAmbientLightTwilight 	= 40;
    static const TUint8 KAmbientLightLight      = 60;
    static const TUint8 KAmbientLightBright     = 80;
    static const TUint8 KAmbientLightSunny      = 100;

    /**
    * Channel data type Id number
    */
    static const TSensrvChannelDataTypeId KDataTypeId = 0x2000BF16;

	/**
    * Channel data type index numbers
    */
	enum TSensrvAmbientLightDataIndexes
        {
        ETimeStamp = 0,
        EAmbientLight
        };

public:

    /**
    * - Item name:   Sampling time
    * - Item Index:  0
    * - Description: Timestamp for a sample
    */
    TTime iTimeStamp;

    /**
    * - Item name:   Ambient light
    * - Item Index:  1
    * - Description: Percentage value (0..100) of Ambient light sensor's brightness.
    */
    TUint8 iAmbientLight;
    };


//SENSRVILLUMINATIONSENSOR_H
#endif

// End of File
