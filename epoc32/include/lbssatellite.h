/*
* ==============================================================================
*  Name        : LbsSatellite.h
*  Part of     : Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : GPS Satellite Data classes
*  Version     : %version: 3 %
*
*  Copyright (c) 2002-2006 Nokia Corporation.
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

#ifndef __LBSSATELLITE_H__
#define __LBSSATELLITE_H__

#include <LbsPosition.h>
#include <LbsPositionInfo.h>

const TUint KPositionMaxSatellitesInView = 20;


/**
 * This class is used to transfer data about a satellite
 */
class TSatelliteData
	{
public:
    /**
     * Default constructor for a TSatelliteData.
     * Note the azimuth and elevation are both initially NaN.
     */
	IMPORT_C TSatelliteData();

    /**
     * @return The Satellite ID
     */
	IMPORT_C TInt SatelliteId() const;

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the Id of 
     * this satellite.
     * @param aSatelliteId The satellite ID to be set
     */
	IMPORT_C void SetSatelliteId(TInt aSatelliteId);

    /**
     * Get the azimuth value of the satellite.
     * @note The azimuth can be NaN. The client should check
     * if this field is NaN using Math::IsNaN() before doing any
     * calculations based on this field.
     * @return The satellite azimuth
     */
	IMPORT_C TReal32 Azimuth() const;

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the azimuth of 
     * this satellite.
     * @param aAzimuth The satellite azimuth to be set
     */
	IMPORT_C void SetAzimuth(TReal32 aAzimuth);

    /**
     * @note The elevation can be NaN. The client should check
     * if this field is NaN using Math::IsNaN() before doing any
     * calculations based on this field.
     * @return The satellite elevation
     */
	IMPORT_C TReal32 Elevation() const;

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the elevation of 
     * this satellite.
     * @param aElevation The satellite elevation to be set
     */
	IMPORT_C void SetElevation(TReal32 aElevation);

    /**
     * Find if this satellite is being used to obtain position information
     * @return Whether this satellite is used
     */
	IMPORT_C TBool IsUsed() const;

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set if this satellite is 
     * being used for position determination.
     * @param aIsUsed Whether this satellite will be used
     */
	IMPORT_C void SetIsUsed(TBool aIsUsed);

    /**
     * Get the strength of the satellite signal.
     * @return The signal strength
     */
	IMPORT_C TInt SignalStrength() const;

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the strength of the 
     * signal from this satellite.
     * @param aSignalStrength The signal strength to set
     */
	IMPORT_C void SetSignalStrength(TInt aSignalStrength);

protected:
	/** The ID (in GPS, the PRN) */
	TInt    iSatelliteId;
	/** The azimuth, in degrees */
	TReal32 iAzimuth;
	/** The elevation, in degrees */
	TReal32 iElevation;
	/** Whether the satellite is used */
	TBool   iIsUsed;
	/** The signal strength, in decibels */
	TInt    iSignalStrength;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};

/**
 * This class is used to store information about positions obtained by satellites.
 */
class TPositionSatelliteInfo : public TPositionCourseInfo
	{
public:
    /**
     * TPositionSatelliteInfo constructor.
     */
	IMPORT_C TPositionSatelliteInfo();

    /**
     * Get the data of a particular satellite used for positioning.
     * @param aIndex The index of the satellite whose data is requested
     * @param[out] aSatelliteData The TSatelliteData structure where the data will be placed
     * @return a symbian OS error code
     * @return KErrNone if successful
     * @return KErrNotFound otherwise
     */
	IMPORT_C TInt GetSatelliteData(TUint aIndex, TSatelliteData& aSatelliteData) const;

    /**
     * This method is not intended for the client's usage.
     * Append the data of a particular satellite used for positioning.
     * This method is usually used by the positioning module to set
     * the satellite information.
     * @param[in] aSatelliteData The data to append
     * @return a symbian OS error code
     * @return KErrNone if successful
     * @return KErrOverflow otherwise
     */
	IMPORT_C TInt AppendSatelliteData(const TSatelliteData& aSatelliteData);

    /**
     * Get the information about the number of satellites that are
     * available for position determination.
     * @return The number of satellites in view
     */
	IMPORT_C TInt NumSatellitesInView() const;

    /**
     * Reset the number of satellites in view
     */
	IMPORT_C void ClearSatellitesInView();

    /**
     * Get the information about the number of satellites that are
     * being used for position determination.
     * @return The number of satellites used in the calculation
     */
	IMPORT_C TInt NumSatellitesUsed() const;

    /**
     * Get the time as per the satellite
     * @return The time according to the satellite
     */
	IMPORT_C TTime SatelliteTime() const;

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the time of 
     * the satellite.
     * @param aTime The satellite time to be set
     */
	IMPORT_C void SetSatelliteTime(TTime aTime);

    /**
     * Get the horizontal dilution of precision. Dilution of precision
     * indicates the accuracy of the measured value.
     * @return The horizontal dilution of precision
     * @note the horizontal dilution of precision value is initially NaN.
     */
	IMPORT_C TReal32 HorizontalDoP() const;

    /**
     * Get the vertical dilution of precision. Dilution of precision
     * indicates the accuracy of the measured value.
     * @return The vertical dilution of precision
     * @note the vertical dilution of precision value is initially NaN.
     */
	IMPORT_C TReal32 VerticalDoP() const;

    /**
     * Get the time dilution of precision. Dilution of precision
     * indicates the accuracy of the measured value.
     * @return The time dilution of precision
     * @note the time dilution of precision value is initially NaN.
     */
	IMPORT_C TReal32 TimeDoP() const;

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the horizontal  
     * dilution of precision.
     * @param aDoPValue The horizontal dilution of precision to be set
     */
	IMPORT_C void SetHorizontalDoP(TReal32 aDoPValue);

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the vertical  
     * dilution of precision.
     * @param aDoPValue The vertical dilution of precision to be set
     */
	IMPORT_C void SetVerticalDoP(TReal32 aDoPValue);

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the time  
     * dilution of precision.
     * @param aDoPValue The time dilution of precision to be set
     */
	IMPORT_C void SetTimeDoP(TReal32 aDoPValue);

protected:
	/** The number of satellites in view */
	TUint iNumSatellitesInView;
	/** The number of satellites used */
	TUint iNumSatellitesUsed;
	/** The time according to the satellite */
	TTime iSatelliteTime;
	/** The horizontal dilution of precision */
	TReal32 iHorizontalDoPValue;
	/** The vertical dilution of precision */
	TReal32 iVerticalDoPValue;
	/** The time dilution of precision */
	TReal32 iTimeDoPValue;
	/** The satellites in view */
	TFixedArray<TSatelliteData, KPositionMaxSatellitesInView> iSatellitesInView;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[24];
	};

#endif //__LBSSATELLITE_H__
