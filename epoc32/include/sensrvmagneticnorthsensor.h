/*
* ==============================================================================
*  Name        : sensrvmagneticnorthsensor.h
*  Part of     : Sensor Definitions API
*  Description : Channel data types definitions
*  Version     : %version:  2 %
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


#ifndef MAGNETICNORTHSENSOR_H
#define MAGNETICNORTHSENSOR_H

//  INCLUDES
#include <e32base.h>
#include <sensrvtypes.h> 

// TILT RELATED CHANNELS

/**
* - Name:          Magnetic north channel data
* - Type:          Event
* - Datatype:      TSensrvMagneticNorthData
* - Description:   The magnetic north data describes the angle between the
*                  device and magnetic north.
*/
const TSensrvChannelTypeId KSensrvChannelTypeIdMagneticNorthData = 0x2000BEDF;


// TILT RELATED DATATYPES

/**
* Tilt angel data type
*/
class TSensrvMagneticNorthData
    {
public:
    /**
    * Channel data type Id number
    */      
    static const TSensrvChannelDataTypeId KDataTypeId = 0x2000BEDF;

    /**
    * Channel data type index numbers
    */
    enum TSensrvMagneticNorthDataIndexes
        {
        ETimeStamp = 0,
        EAngleFromMagneticNorth
        };

public:

    /**
    * - Item name:   Sampling time.
    * - Item Index:  0
    * - Conditions:  None
    * - Description: Timestamp for a sample.
    */   
    TTime iTimeStamp;    

    /**
    * - Item name:   Tilt angle
    * - Item Index:  1
    * - Conditions:  Single limit and range 
    * - Description: The angle between the magnetic north and the device heading.
    */
    TInt iAngleFromMagneticNorth;  
    };

#endif //MAGNETICNORTHSENSOR_H

// End of File
