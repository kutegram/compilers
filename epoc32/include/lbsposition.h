/*
* ==============================================================================
*  Name        : LbsPosition.h
*  Part of     : Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Position classes
*  Version     : %version: 4 %
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

#ifndef __LBSPOSITION_H__
#define __LBSPOSITION_H__

#include <e32std.h>

/**
 * @file LbsPosition.h
 * This header file defines the data classes that hold the various attributes
 * for a location
 */
 
/**
 * Defines the identifier for various positioning standard datums
 */
typedef TUid TPositionDatumId;

/**
 * Defines the identifier for the WGS-84 Positioning Datum Standard
 */
const TPositionDatumId KPositionDatumWgs84 = {0x101FAA29};


/**
 * TCoordinate is used to hold the basic coordinates of a location (latitude,
 * longitude and altitude).
 */
class TCoordinate
	{
public:

    /**
     * Default constructor for TCoordinate. Sets the member data to
     * default values (NaN).
     */
	IMPORT_C TCoordinate();

    /**
     * Constructor for TCoordinate. Allows the client to set just latitude and
     * longitude, and sets the altitude to its default value (NaN).
     *
     * @param[in] aLatitude specifies an initial value for latitude.
     * @param[in] aLongitude specifies an initial value for longitude.
     */
	IMPORT_C TCoordinate(const TReal64& aLatitude,
	                     const TReal64& aLongitude);

    /**
     * Constructor for TCoordinate. Allows the client to set the latitude,
     * longitude and altitude.
     *
     * @param[in] aLatitude specifies an initial value for latitude.
     * @param[in] aLongitude specifies an initial value for longitude.
     * @param[in] aAltitude specifies an initial value for altitude.
     */
	IMPORT_C TCoordinate(const TReal64& aLatitude,
	                     const TReal64& aLongitude,
	                     TReal32 aAltitude);

    /**
     * This method assigns a new latitude and longitude to the object. The
     * altitude is set to its default value (NaN).
     * @param[in] aLatitude specifies a new latitude.
     * @param[in] aLongitude specifies a new longitude.
     */
	IMPORT_C void SetCoordinate(const TReal64& aLatitude,
	                            const TReal64& aLongitude);

    /**
     * This method assigns a new latitude, longitude and altitude to the object.
     * @param[in] aLatitude specifies a new latitude.
     * @param[in] aLongitude specifies a new longitude.
     * @param aAltitude specifies a new altitude.
     */
	IMPORT_C void SetCoordinate(const TReal64& aLatitude,
	                            const TReal64& aLongitude,
	                            TReal32 aAltitude);

    /**
     * This method assigns a new datum to the object.
     * @param aDatum specifies a new datum.
     */
	IMPORT_C void SetDatum(TPositionDatumId aDatum);

    /**
     * Accessor for latitude.
     * @return the latitude component of this coordinate.
     */
	IMPORT_C TReal64 Latitude() const;

    /**
     * Accessor for longitude.
     * @return the longitude component of this coordinate.
     */
	IMPORT_C TReal64 Longitude() const;

    /**
     * Accessor for altitude.
     * @return the altitude component of this coordinate, in metres.
     */
	IMPORT_C TReal32 Altitude() const;

    /**
     * Accessor for the datum.
     * @return the datum of this coordinate.
     */
	IMPORT_C TPositionDatumId Datum() const;


    /**
     * This method calculates the distance between this coordinate and the
     * supplied coordinate.
     *
     * @param[in] aCoordinate is another point to use in the calculation.
     * @param[out] aDistance upon successful completion, this is set to the distance
     * between this coordinate and aCoordinate, in metres.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLatitude, iLongitude, aCoordinate.iLatitude
     * or aCoordinate.iLongitude are set to NaN.
     */
	IMPORT_C TInt Distance(const TCoordinate& aCoordinate,
	                       TReal32& aDistance) const;

    /**
     * This method calculates the bearing from this coordinate to the
     * supplied coordinate.
     *
     * @param[in] aTargetCoordinate is the supplied target coordinate.
     * @param[out] aBearing upon successful completion, this is set to the bearing
     * from this coordinate to aTargetCoordinate, in degrees counting clockwise  
     * relative to true north.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLatitude, iLongitude,
     * aTargetCoordinate.iLatitude or aTargetCoordinate.iLongitude are set to NaN.
     * @return KErrPositionIncalculable if this coordinate is at a pole or if the 
     * two coordinates are the same or antipodal.
     */
	IMPORT_C TInt BearingTo(const TCoordinate& aTargetCoordinate,
	                        TReal32& aBearing) const;

    /**
     * This method moves this coordinate aDistance in the direction specified
     * by aBearing
     *
     * @param aBearing is the direction to move this coordinate, in degrees 
     * counting clockwise relative to true north.
     * @param aDistance is the distance to move this coordinate, in metres.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLongitude or iLatitude are set to NaN.
     * @return KErrPositionIncalculable if this coordinate is at a pole.
     */
	IMPORT_C TInt Move(TReal32 aBearing, TReal32 aDistance);

private:
    /**
     * Helper method. Not for client usage.
     */
	void NormalizeCoordinate();

protected:
	/** Latitude, defaults to WGS-84 format. */
	TReal64 iLatitude;
	/** Longitude, defaults to WGS-84 format. */
	TReal64 iLongitude;
	/** Altitude, defaults to WGS-84 format. */
	TReal32 iAltitude;
	/** The ID of the datum the coordinate is in, defaults to WGS-84 format. */
	TPositionDatumId iDatum;
	/** Unused variable for future expansion. */
	TUint8 iReserved[4];
	};


/**
 * Adds an error estimate for the horizontal and vertical accuracy of the point
 * to TCoordinate. Accuracy information is held in a TReal32 and is measure in
 * metres. The class also provides its own methods for determining the distance
 * and bearing to a target point. These methods also provide an error estimate.
 */
class TLocality : public TCoordinate
	{
public:
    /**
     * Default constructor for TLocality. Sets the member data to
     * default values (NaN).
     */
	IMPORT_C TLocality();

    /**
     * Constructor for TLocality. Allows the client to set a coordinate and a
     * 'surface' accuracy.
     *
     * @param[in] aCoordinate specifies an initial value for the coordinate.
     * @param aHorizontalAccuracy specifies an initial value for the
     * horizontal accuracy.
     * @panic "Lbs Client Fault" 13 if aHorizontalAccuracy is
     * negative and not set to NaN.
     */
	IMPORT_C TLocality(const TCoordinate& aCoordinate,
	                   TReal32 aHorizontalAccuracy);

    /**
     * Constructor for TLocality. Allows the client to set a coordinate and both a
     * horizontal and vertical accuracy.
     *
     * @param[in] aCoordinate specifies an initial value for the coordinate.
     * @param aHorizontalAccuracy specifies an initial value for the
     * horizontal (earth-surface) accuracy.
     * @param aVerticalAccuracy specifies an initial value for the
     * vertical (altitudinal) accuracy.
     * @panic "Lbs Client Fault" 13 if aHorizontalAccuracy or aVerticalAccuracy is
     * negative and not set to NaN.
     */
	IMPORT_C TLocality(const TCoordinate& aCoordinate,
	                   TReal32 aHorizontalAccuracy,
	                   TReal32 aVerticalAccuracy);

    /**
     * Sets the horizontal accuracy of this coordinate.
     *
     * @param aHorizontalAccuracy is the new horizontal accuracy, in metres.
     * @panic "Lbs Client Fault" 13 if aHorizontalAccuracy is negative
     * and not set to NaN.
     */
	IMPORT_C void SetHorizontalAccuracy(TReal32 aHorizontalAccuracy);
    
    /**
     * Sets the vertical accuracy of this coordinate.
     *
     * @param aVerticalAccuracy is the new vertical accuracy, in metres.
     * @panic "Lbs Client Fault" 13 if aVerticalAccuracy is negative
     * and not set to NaN.
     */
	IMPORT_C void SetVerticalAccuracy(TReal32 aVerticalAccuracy);

    /**
     * Sets both the horizontal and vertical accuracy of this coordinate.
     *
     * @param aHorizontalAccuracy is the new horizontal accuracy, in metres.
     * @param aVerticalAccuracy is the new vertical accuracy, in metres.
     * @panic "Lbs Client Fault" 13 if aHorizontalAccuracyor aVerticalAccuracy
     * is negative and not set to NaN.
     */
	IMPORT_C void SetAccuracy(TReal32 aHorizontalAccuracy,
	                          TReal32 aVerticalAccuracy);

    /**
     * Retrieves the horizontal accuracy of this coordinate.
     * @return the horizontal accuracy, in metres.
     */
	IMPORT_C TReal32 HorizontalAccuracy() const;

    /**
     * Retrieves the vertical accuracy of this coordinate.
     * @return the vertical accuracy, in metres.
     */
	IMPORT_C TReal32 VerticalAccuracy() const;

    /**
     * This method calculates the distance between this coordinate and the
     * supplied coordinate.
     *
     * @param[in] aCoordinate is another point to use in the calculation.
     * @param[out] aDistance upon successful completion, this is set to the distance
     * between this coordinate and aCoordinate, in metres.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLatitude, iLongitude, aCoordinate.iLatitude
     * or aCoordinate.iLongitude are set to NaN.
     */
	IMPORT_C TInt Distance(const TCoordinate& aCoordinate,
	                       TReal32& aDistance) const;

    /**
     * This method calculates the distance between this locality and the
     * supplied locality. An estimate of the accuracy of the result is also
     * provided.
     *
     * @param[in] aLocality is another point to use in the calculation.
     * @param[out] aDistance upon successful completion, this is set to the distance
     * between this locality and aLocality, in metres.
     * @param[out] aDelta upon successful completion, this is set to the estimated
     * accuracy of the distance calculation, in metres.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLatitude, iLongitude, aLocality.iLatitude
     * or aLocality.iLongitude are set to NaN.
     * @return KErrArgument if any of iHorizontalAccuracy or
     * aLocality.iHorizontalAccuracy are set to NaN.
     */
	IMPORT_C TInt Distance(const TLocality& aLocality,
	                       TReal32& aDistance,
	                       TReal32& aDelta) const;

    /**
     * This method calculates the bearing from this coordinate to the
     * supplied coordinate.
     *
     * @param[in] aTargetCoordinate is the supplied target coordinate.
     * @param[out] aBearing upon successful completion, this is set to the bearing
     * from this coordinate to aTargetCoordinate, in degrees counting clockwise  
     * relative to true north.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLatitude, iLongitude,
     * aTargetCoordinate.iLatitude or aTargetCoordinate.iLongitude are set to NaN.
     * @return KErrPositionIncalculable if this coordinate is at a pole or if the 
     * two coordinates are the same or antipodal.
     */
	IMPORT_C TInt BearingTo(const TCoordinate& aTargetCoordinate,
	                        TReal32& aBearing) const;

    /**
     * This method calculates the bearing from this locality to the
     * supplied locality.
     *
     * @param[in] aTargetLocality is the supplied target locality.
     * @param[out] aBearing upon successful completion, this is set to the bearing
     * from this locality to aTargetLocality, in degrees  counting clockwise
     * relative to true north.
     * @param[out] aDelta upon successful completion, this is set to an estimate of the
     * accuracy of the calculation, in degrees relative to aBearing.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLatitude, iLongitude,
     * aTargetLocality.iLatitude or aTargetLocality.iLongitude are set to NaN.
     * @return KErrArgument if any of iHorizontalAccuracy
     * or aTargetLocality.iHorizontalAccuracy are set to NaN.
     * @return KErrPositionIncalculable if the error circle (horizontal accuracy)
     * of this locality includes a pole.
     * @return KErrPositionIncalculable if the two localities has overlapping 
     * error circles.
     * @return KErrPositionIncalculable if the error circle of this locality 
     * overlaps with the error circle of aTargetLocality when projected antipodal.
     */
	IMPORT_C TInt BearingTo(const TLocality& aTargetLocality,
	                        TReal32& aBearing,
	                        TReal32& aDelta) const;

protected:
	/** Horizontal (earths-surface) accuracy, in metres. */
	TReal32 iHorizontalAccuracy;
	/** Altitudinal accuracy, in metres. */
	TReal32 iVerticalAccuracy;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


/**
 * This class is the standard data structure for retrieving location
 * information. It adds a time dimension to the inherited TLocality information.
 * This enables the speed to be calculated from two TPosition instances.
 *
 * The time reflects the system time (that is, the mobile terminal) of when the
 * location fix was obtained. It does not indicate the time as obtained from the
 * position technology (for example network or satellite time).
 *
 * The time is contained in a TTime data structure that provides microsecond
 * resolution. However, it should be noted that system clocks only provide a
 * resolution of milliseconds or indeed hundredths of a second.
 */
class TPosition : public TLocality
	{
public:
    /**
     * Default constructor for TCoordinate. Sets the member data to
     * default values (NaN for coordinates, 0 for time).
     */
	IMPORT_C TPosition();

    /**
     * Constructor for TPosition. Allows the client to set a locality and an
     * associated time.
     *
     * @param[in] aLocality specifies an initial value for the locality of the position.
     * @param aTime specifies an initial value for the time of the position.
     */
	IMPORT_C TPosition(const TLocality& aLocality,
	                   TTime aTime);

    /**
     * Sets the time of this position data.
     * @param aTime is the new timing information.
     */
	IMPORT_C void SetTime(TTime aTime);

    /**
     * Sets the time of this position data to the current universal time as indicated
     * by the systems clock.
     */
	IMPORT_C void SetCurrentTime();

    /**
     * Retrieves the time of this position data.
     *
     * @return the timing component of this position information.
     */
	IMPORT_C TTime Time() const;

    /**
     * This method calculates the horizontal speed between the current position
     * and the supplied instance aPosition. The speed is calculated based on the
     * coordinates and time associated with each instance.
     *
     * @param[in] aPosition is another position to use in the calculation.
     * @param[out] aSpeed upon successful completion, this is set to the speed 
     * indicated by being at this position at its recorded time, and at aPosition
     * at its recorded time. Always positive, in metres per second.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLatitude, iLongitude, aPosition.iLatitude
     * or aPosition.iLongitude are set to NaN.
     * @return KErrArgument if either of iTime or aPosition.iTime are set to zero.
     * @return KErrArgument if iTime and aPosition.iTime are the same.
     */
	IMPORT_C TInt Speed(const TPosition& aPosition,
	                    TReal32& aSpeed) const;
    /**
     * This method calculates the horizontal speed between the current position
     * and the supplied instance aPosition. The speed is calculated based on the
     * coordinates and time associated with each instance. An estimate of the
     * accuracy of the result is also provided.
     *
     * @param[in] aPosition is another position to use in the calculation.
     * @param[out] aSpeed upon successful completion, this is set to the speed 
     * indicated by being at this position at its recorded time, and at aPosition
     * at its recorded time. Always positive, in metres per second.
     * @param[out] aDelta upon successful completion, this is set to an estimate of the
     * accuracy of the calculation, in metres per second.
     * @return a Symbian OS error code.
     * @return KErrArgument if any of iLatitude, iLongitude, aPosition.iLatitude
     * or aPosition.iLongitude are set to NaN.
     * @return KErrArgument if any of iHorizontalAccuracy
     * or aPosition.iHorizontalAccuracy are set to NaN.
     * @return KErrArgument if either of iTime or aPosition.iTime are set to zero.
     * @return KErrArgument if iTime and aPosition.iTime are the same.
     */
	IMPORT_C TInt Speed(const TPosition& aPosition,
	                    TReal32& aSpeed,
	                    TReal32& aDelta) const;

protected:
	/** This is the system time when the position related member data was
	obtained. */
	TTime iTime;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


/**
 * This is used to hold information about the current speed and direction
 * of the device. It is generally used in conjunction with TPositionCourseInfo
 * when a positioning technology is able to supply these details as part of
 * its positioning information.
 */
class TCourse
	{
public:
    /**
     * Default constructor for TCourse. Sets the member data to
     * default values (NaN).
     */
	IMPORT_C TCourse();

    /**
     * Retrieves the speed.
     * @return the speed, in metres per second.
     */
	IMPORT_C TReal32 Speed() const;

    /**
     * Retrieves the heading.
     * @return the heading, in degrees.
     */
	IMPORT_C TReal32 Heading() const;

    /**
     * Retrieves the course over ground.
     * @return the course over ground, in degrees.
     */
    IMPORT_C TReal32 Course() const;

    /**
     * Retrieves the accuracy of the speed component.
     * @return the accuracy of the speed, in metres per second.
     */
	IMPORT_C TReal32 SpeedAccuracy() const;

    /**
     * Retrieves the accuracy of the heading component.
     * @return the accuracy of the heading, in degrees.
     */
	IMPORT_C TReal32 HeadingAccuracy() const;

    /**
     * Retrieves the accuracy of the course over ground.
     * @return the accuracy of the course over ground, in degrees.
     */
    IMPORT_C TReal32 CourseAccuracy() const;

    /**
     * Changes the speed of this course.
     * @param aSpeed is the new speed, in metres per second.
     */
	IMPORT_C void SetSpeed(TReal32 aSpeed);

    /**
     * Changes the heading of this course.
     * @param aHeading is the new heading, in degrees.
     */
	IMPORT_C void SetHeading(TReal32 aHeading);

    /**
     * Changes the accuracy of the speed component of this course.
     * @param aSpeedAccuracy is the new accuracy of the speed, in metres per second.
     * @panic "Lbs Client Fault" 13 if aSpeedAccuracy is negative.
     */
	IMPORT_C void SetSpeedAccuracy(TReal32 aSpeedAccuracy);

    /**
     * Changes the accuracy of the heading component of this course.
     * @param aHeadingAccuracy is the new accuracy of the heading, in degrees.
     * @panic "Lbs Client Fault" 13 if aHeadingAccuracy is negative.
     */
	IMPORT_C void SetHeadingAccuracy(TReal32 aHeadingAccuracy);

    /**
     * Changes the course over ground.
     * @param aCourse is the new course, in degrees.
     */
	IMPORT_C void SetCourse(TReal32 aCourse);

    /**
     * Changes the accuracy of the course component of this course.
     * @param aCourseAccuracy is the new accuracy of the course, in degrees.
     * @panic "Lbs Client Fault" 13 if aCourseAccuracy is negative.
     */
	IMPORT_C void SetCourseAccuracy(TReal32 aCourseAccuracy);

protected:
	/** Speed, in metres per second. */
	TReal32 iSpeed;
	/** Heading, in degrees. */
	TReal32 iHeading;
	/** Speed accuracy, in metres per second. */
	TReal32 iSpeedAccuracy;
	/** Heading accuracy, in degrees. */
	TReal32 iHeadingAccuracy;
	/** Course, in degrees. */
	TReal32 iCourse;
	/** Course accuracy, in degrees. */
	TReal32 iCourseAccuracy;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};

#endif //__LBSPOSITION_H__
