/*
* ==============================================================================
*  Name        : sensrvtappingsensor.h
*  Part of     : Sensor Definitions API
*  Description : Channel data types definitions
*  Version     : %version:  4 %
*
*  Copyright � 2008 Nokia.  All rights reserved.
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


#ifndef SENSRVTAPPINGSENSOR_H
#define SENSRVTAPPINGSENSOR_H

//  INCLUDES
#include <e32base.h>
#include <sensrvtypes.h> 
#include <sensrvaccelerometersensor.h>

// TAPPING RELATED CHANNELS 

/**
* - Name:          Double tapping event channel type
* - Type:          Event
* - Datatype:      TSensrvTappingData
* - Description:   Double tapping events 
*/
const TSensrvChannelTypeId KSensrvChannelTypeIdAccelerometerDoubleTappingData = 0x10205081;

// TAPPING RELATED PROPERTIES

/**
* - Name:         Double tapping axis active
* - Type:         TInt 
* - Scope:        Channel item property
* - Mandatory:    No
* - Capability:   None
* - Description:  Indicates is sensor axis activated.
*                 Value is one if the axis is activated, zero otherwise.
*/
const TSensrvPropertyId KSensrvPropIdDblTapAxisActive = KSensrvPropIdAxisActive;

/**
* - Name:         Double tap duration threshold
* - Type:         TInt
* - Scope:        Channel property
* - Mandatory:    No
* - Capability:   ReadDeviceData, WriteDeviceData
* - Description:  Threshold as an offset of the selected range.
*/
const TSensrvPropertyId KSensrvPropIdDblTapThreshold = 0x00001002;

/**
* - Name:         Double tap duration in milliseconds
* - Type:         TInt
* - Scope:        Channel property
* - Mandatory:    No
* - Capability:   None
* - Description:  Scalar Integer representing the duration of the tap value.
*                 Not dependent upon ODR.
*/
const TSensrvPropertyId KSensrvPropIdDblTapDuration = 0x00001003;

/**
* - Name:         Double tap latency 
* - Type:         TInt
* - Scope:        Channel property
* - Mandatory:    No
* - Capability:   None
* - Description:  Double tap latency in milliseconds
*/
const TSensrvPropertyId KSensrvPropIdDblTapLatency = 0x00001004;

/**
* - Name:         Double tap interval
* - Type:         TInt
* - Scope:        Channel property
* - Mandatory:    No
* - Capability:   None
* - Description:  Double tap interval in milliseconds
*/
const TSensrvPropertyId KSensrvPropIdDblTapInterval = 0x00001005;

// TAPPING RELATED DATATYPES

/**
* Direction of the tapping data. If direction (plus or minus) is not known, 
* direction is, for example in x-axis case 
* KSensrvAccelerometerDirectionXplus | KSensrvAccelerometerDirectionXminus
*/
const TUint8 KSensrvAccelerometerDirectionXplus 	= 0x01;
const TUint8 KSensrvAccelerometerDirectionXminus 	= 0x02;
const TUint8 KSensrvAccelerometerDirectionYplus 	= 0x04;
const TUint8 KSensrvAccelerometerDirectionYminus 	= 0x08;
const TUint8 KSensrvAccelerometerDirectionZplus 	= 0x10;
const TUint8 KSensrvAccelerometerDirectionZminus 	= 0x20;

/**
* Tapping data type
*/
class TSensrvTappingData 
    {
public:
    /**
    * Channel data type Id number
    */      
    static const TSensrvChannelDataTypeId KDataTypeId = 0x1020507F;

	/**
    * Channel data type index numbers
    */
	enum TSensrvAccelerometerAxisDataIndexes
          {
          ETimeStamp = 0,
          EDirection
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
    * - Item name:   Tapping direction bitmask
    * - Item Index:  1
    * - Conditions:  Binary
    * - Description: Direction bitmask of the tapping event. 
    *                See constant definitions above.
    */
    TUint32 iDirection;  
    };

//SENSRVTAPPINGSENSOR_H
#endif

// End of File
