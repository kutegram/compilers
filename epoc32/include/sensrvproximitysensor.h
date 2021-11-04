/*
* ==============================================================================
*  Name        : sensrvproximitysensor.h
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


#ifndef SENSRVPROXIMITYSENSOR_H
#define SENSRVPROXIMITYSENSOR_H

//  INCLUDES
#include <e32base.h>
#include <sensrvtypes.h> 

// PROXIMITY RELATED CHANNELS

/**
* - Name: Proximity data channel
* - Type: Event
* - Datatype: TSensrvProximityMonitorData
* - Description: Proximity status 
*/
const TSensrvChannelTypeId KSensrvChannelTypeIdProximityMonitor = 0x2000E585;

// PROXIMITY RELATED DATATYPES

/**
* Proximity monitoring data type
*/
class TSensrvProximityData
	{
public:
	/**
	* Channel data type Id number
	*/ 
	static const TSensrvChannelDataTypeId KDataTypeId = 0x2000E585;

    /**
    * Channel data type index numbers
    */ 
    enum TSensrvProximityDataIndexes
        {
        ETimeStamp = 0,
        EState
        };

    /**
    * Possible values for proximito state
    */ 
    enum TProximityState
        {
        EProximityUndefined = 0,
        EProximityIndiscernible,
        EProximityDiscernible
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
    * - Item name: Proximity state
    * - Item Index: 0
    * - Conditions: None
    * - Description: -
    */ 
    TProximityState iProximityState;

};

//SENSRVPROXIMITYSENSOR_H
#endif

// End of File
