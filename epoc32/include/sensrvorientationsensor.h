/*
* ==============================================================================
*  Name        : sensrvorientationsensor.h
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


#ifndef SENSRVORIENTATIONSENSOR_H
#define SENSRVORIENTATIONSENSOR_H

//  INCLUDES
#include <e32base.h>
#include <sensrvtypes.h> 

// ORIENTATION RELATED CHANNELS

/**
* - Name:          Orientation event channel type
* - Type:          Event
* - Datatype:      TSensrvOrientationData
* - Description:   Orientation events
*/
const TSensrvChannelTypeId KSensrvChannelTypeIdOrientationData = 0x10205088; 

/**
* - Name:          Rotation event channel type
* - Type:          Event
* - Datatype:      TSensrvRotationData
* - Description:   Rotation events
*/
const TSensrvChannelTypeId KSensrvChannelTypeIdRotationData = 0x10205089; 

// ORIENTATION RELATED DATATYPES

class TSensrvOrientationData
    {
public:
    /**
    * Channel data type Id number
    */      
    static const TSensrvChannelDataTypeId KDataTypeId = 0x10205088;

    /**
    * Channel data type index numbers
    */
    enum TSensrvOrientationEventIndexes
        {
        ETimeStamp = 0,
        EDeviceOrientation
        }; 

    /**
    * Possible device orientations
    */
    enum TSensrvDeviceOrientation
        {
	    EOrientationUndefined = 0,
	    EOrientationDisplayUp,
	    EOrientationDisplayDown,
	    EOrientationDisplayLeftUp,
	    EOrientationDisplayRightUp,
	    EOrientationDisplayUpwards,
	    EOrientationDisplayDownwards	
        };
        
public:
        
    /**
    * - Item name:   Sampling time
    * - Item Index:  0
    * - Description: Timestamp for a sample
    */   
    TTime iTimeStamp;

    /**
    * - Item name:   Device orientation
    * - Item Index:  1
    * - Description: Contains one of the six basic orientations of the device
    */   
    TSensrvDeviceOrientation iDeviceOrientation;    
    };


class TSensrvRotationData
    {
public:
    /**
    * Channel data type Id number
    */      
    static const TSensrvChannelDataTypeId KDataTypeId = 0x10205089;
    
    /**
    * Rotation axis value equals -1 when it cannot be defined. 
    * The undefined situation varies depending on the sensor type. 
    * In the case of an accelerometer, the rotation value cannot be defined 
    * when the corresponding axis is parallel to the gravitational force or
    * the device is in motion. In the case of a magnetometer, there are
    * difficulties in measuring values, when the axis is parallel to the
    * magnetic field.
    */
    static const TInt KSensrvRotationUndefined = -1; 

    /**
    * Channel data type index numbers
    */ 
    enum TSensrvRotationDataIndexes
        {
        ETimeStamp = 0,          
        EDeviceRotationAboutXAxis,
        EDeviceRotationAboutYAxis,
        EDeviceRotationAboutZAxis,
        };

public:
    /**
    * - Item name:   Sampling time.
    * - Item Index:  0
    * - Description: Timestamp for a sample
    */   
    TTime iTimeStamp;
  
    /**
    * - Item name:   Rotation about x-axis
    * - Item Index:  1 
    * - Description: Positive rotation in Cartesian coordinate system about the x-axis.
    *                If the value cannot be defined it is set to KSensrvRotationUndefined.
    */   
    TInt iDeviceRotationAboutXAxis;  

    /**
    * - Item name:   Rotation about y-axis
    * - Item Index:  2
    * - Description: Positive rotation in Cartesian coordinate system about the y-axis.
    *                If the value cannot be defined it is set to KSensrvRotationUndefined.
    */   
    TInt iDeviceRotationAboutYAxis;  
      

    /**
    * - Item name:   Rotation about z-axis
    * - Item Index:  3 
    * - Description: Positive rotation in Cartesian coordinate system about the z-axis.
    *                If the value cannot be defined it is set to KSensrvRotationUndefined.
    */   
    TInt iDeviceRotationAboutZAxis;  
    };

//SENSRVORIENTATIONSENSOR_H
#endif

// End of File
