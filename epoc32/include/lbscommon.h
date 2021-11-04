/*
* ==============================================================================
*  Name        : LbsCommon.h
*  Part of     : Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Common classes
*  Version     : %version: 6 %
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

#ifndef __LBSCOMMON_H__
#define __LBSCOMMON_H__

#include <e32std.h>
#include <e32math.h>
#include <LbsRequestor.h>
#include <LbsClassTypes.h>
#include <LbsErrors.h>

/**
 * @file LbsCommon.h
 * This header file defines the constants used in Location Acquisition API and the
 * positioning related data classes.
 */

// A compile time assert macro. The aExpr parameter must evaluate to a
// positive integer value at compile time.
// eg. sizeof(TTime) == KSizeOfTInt64
// If aExpr is false, the compiler generates an error.
// If aExpr is true, the compilation continues, and use of this macro will not
// result in any extra object code.
#define POSITION_COMPILE_TIME_ASSERT(aExpr)   typedef char assert_type[(aExpr) ? 1 : -1]

/**
 * Defines the maximum length for a Positioning module name
 */
const TInt KPositionMaxModuleName = 64;

/**
 * Defines the maximum size of the value for position quality 
 * parameters like accuracy , speed etc.
 */
const TUint KPositionMaxSizeQualityItem = sizeof(TInt64);

/**
 * Defines the maximum number of quality fields like Accuracy , Speed
 * etc that can be there in a TPositionQuality class.
 */
const TUint KPositionMaxSectionFields = 10;

/**
 * @typedef TPositionModuleId
 * @brief The unique identifier for a Positioning module
 */
typedef TUid  TPositionModuleId;

/**
 * Defines the NULL module Id 
 */
const TPositionModuleId KPositionNullModuleId = {KNullUidValue};


/**
 * The base class for classes used to store position information
 */
class TPositionClassTypeBase
	{
public:
    /**
     * Get information about the type of the position class.
     * @return The type of the TPositionClassTypeBase-derived class
     */
	IMPORT_C TUint32 PositionClassType() const;

    /**
     * Get the size of the position class.
     * @return The size of the TPositionClassTypeBase-derived class
     */
	IMPORT_C TUint PositionClassSize() const;

protected:
	TPositionClassTypeBase();

protected:
	/** The type of the derived class */
	TUint32 iPosClassType;
	/** The size of the derived class */
	TUint iPosClassSize;
	};


/**
 * This is an internal class that holds the value for position quality 
 * attributes.
 * The client should not use this class. Instead the client should
 * use TPositionQuality class.
 */
class TPositionQualityItem
	{
public:
    /** Enumerator for the comparison of position quality items. */
	enum TResult
		{
		/** The value in this quality class object is of better quality */
		EIsBetter, 
		/** Both the items that are being compared are of the same quality */
		EIsEqual,
		/** The value in this quality class object is of worse quality */
		EIsWorse
		};

	enum TValuePreference
		{
		EPreferSmallerValues,
		EPreferGreaterValues
		};

    /** Defines the data type of the position quality item */
	enum TDataType
		{
		EUndefined, /// Undefined data type. This value should not be used.
		ETInt8,     /// TInt8 datatype
		ETInt16,    /// TInt16 datatype
		ETInt32,    /// TInt32 datatype
		ETInt64,    /// TInt64 datatype
		ETUint8,    /// TUint8 datatype
		ETUint16,   /// TUint16 datatype
		ETUint32,   /// TUint32 datatype
		ETReal32,   /// TReal32 datatype
		ETReal64,   /// TReal64 datatype
		ETTime,     /// TTime datatype
		ETTimeIntervalMicroSeconds /// Time in micro seconds.
		};

	TPositionQualityItem();

	TInt Compare(const TPositionQualityItem& aItem, TResult& aComparison) const;

	void Set(TDataType aDataType, TValuePreference aValuePreference,
			 const TAny* aData, TUint aSizeOfData);

	TInt Get(TDataType aDataType, TAny* aData, TUint aSizeOfData) const;

	TBool IsDefined() const;

private:
	TDataType iDataType;
	TValuePreference iScaleDirection;
	TUint8 iData[KPositionMaxSizeQualityItem];
	};

/**
 * The base class for classes used to store position quality information
 */
class TPositionQualityBase : public TPositionClassTypeBase
	{
public:

    /**
     * Compares a specified element of another TPositionQualityBase object to this
     * TPositionQualityBase.
     *
     * @param[in] aPositionQuality The position quality to compare against this position quality.
     * @param aElementToCompare The element number that we want to compare.
     * @param[out] aComparison On return contains whether the aPositionQuality is better that 
     * this quality object for the specified quality element.
     * @return KErrNone if comparison was successful.
     * @return KErrArgument if there is a mismatch of the datatypes of the value preference.
     */
	IMPORT_C TInt Compare(const TPositionQualityBase& aPositionQuality,
						  TInt aElementToCompare,
						  TPositionQualityItem::TResult& aComparison) const;

    /**
     * Find the validity of an element.
     * @return Whether or not an element has a state of EUndefined.
     */
	IMPORT_C TBool IsDefined(TInt aElementId) const;

    /**
     * @return The High Water Mark.
     */
	IMPORT_C TInt HighWaterMark() const;
protected:
	IMPORT_C TPositionQualityBase();

	IMPORT_C void ResetElement(TInt aElementId);

	template <class T>
		inline void SetElement(TInt aElementId, TPositionQualityItem::TDataType aDataType,
							   TPositionQualityItem::TValuePreference aValuePreference, T aData)
		{DoSetElement(aElementId, aDataType, aValuePreference, &aData, sizeof(T));}
	
	template <class T>
		inline TInt GetElement(TInt aElementId, TPositionQualityItem::TDataType aDataType,
							    T& aData) const
		{return DoGetElement(aElementId, aDataType, &aData, sizeof(T));}

private:
	IMPORT_C void DoSetElement(TInt aElementId, TPositionQualityItem::TDataType aDataType,
							   TPositionQualityItem::TValuePreference aValuePreference,
							   const TAny* aData, TUint aSizeOfData);

	IMPORT_C TInt DoGetElement(TInt aElementId, TPositionQualityItem::TDataType aDataType,
								TAny* aData, TUint aSizeOfData) const;
private:
	TFixedArray<TPositionQualityItem, KPositionMaxSectionFields> iPositionQualityData;
	TInt iHighwaterMark;
	};

/**
 * The standard position quality class.
 */
class TPositionQuality : public TPositionQualityBase
	{
public:
    /**
     * Indicates if there is likely to be a charge when obtaining location 
     * information using the associated positioning module.
     */
	enum TCostIndicator
		{
		/** This is an unassigned value and should not be returned. */
		ECostUnknown,
		/** 
		 * This value indicates that no cost is expected to be incurred when 
		 * obtaining a position fix.
		 */
		ECostZero,
		/**
		 * This value indicates that the positioning module is uncertain if 
		 * the user will incur a charge when using the positioning module to
		 * obtain position information.
		 */
		ECostPossible,
		/**
		 * This value indicates that the positioning module expects a charge to be 
		 * levied when obtaining position information using the specific positioning
		 * module.
		 */
		ECostCharge
		};

    /**
     * Indicates through a simple scale the likely power consumption associated 
     * with using a particular positioning module.
     */
	enum TPowerConsumption
		{
		/** 
		 * This value indicates that the positioning module is unable to 
		 * determine the likely power drain.
		 */
		EPowerUnknown,
		/**
		 * This value indicates that no internal power will be used when 
		 * obtaining position information.
		 */
		EPowerZero,
		/**
		 * This value indicates that the positioning module expects a minimum 
		 * power drain when using the associated technology. This may be 
		 * comparable to the power usage when the phone is in the Standby mode.
		 */
		EPowerLow,
		/**
		 * This value indicates that the positioning module expects a moderate
		 * power drain when using the associated technology. This may be 
		 * comparable to the power usage when the phone is being actively used.
		 */
		EPowerMedium,
		/**
		 * This value indicates that the positioning module expects a high 
		 * power drain when using the associated technology. The use of this
		 * module will quickly consume the phone’s battery.
		 */
		EPowerHigh
		};

public:
    /**
     * Default constructor for TPositionQuality
     * Note that the horizontal accuracy and vertical accuracy are initially NaNs.
     */
	IMPORT_C TPositionQuality();

    /**
     * Get the time taken for the first position fix. Different positioning 
     * technologies can take a different amount of time to obtain the first 
     * position fix and subsequent fixes. 
     * @return The time required to obtain an initial location fix
     */
	IMPORT_C TTimeIntervalMicroSeconds TimeToFirstFix() const;

    /**
     * Get the time taken for the subsequent position fixes. Different positioning
     * technologies can take a different amount of time to obtain 
     * the first position fix and subsequent fixes.  
     * @return The time required to obtain subsequent location fixes
     */
	IMPORT_C TTimeIntervalMicroSeconds TimeToNextFix()  const;  

    /**
     * Get the horizontal accuracy. Horizontal accuracy reflects the error for
     * the latitude and longitude components of a position. 
     * 
     * @return The horizontal accuracy in metres
     *
     * @note If no value is set, the default value is NaN. The client should
     * check if the value is NaN through Math::IsNaN() before using the accuracy 
     * value.
     */
	IMPORT_C TReal32 HorizontalAccuracy() const;

    /**
     * Get the vertical accuracy. Vertical accuracy is the error in the
     * altitude component. This method returns the vertical accuracy.
     *
     * @return The vertical accuracy in metres
     *
     * @note If no value is set, the default value is NaN. The client should
     * check if the value is NaN through Math::IsNaN() before using the accuracy 
     * value.
     */
	IMPORT_C TReal32 VerticalAccuracy()   const;

    /**
     * This method indicates if there will be a monetary charge for obtaining a 
     * position fix.
     * @return The cost indicator as an enumerated value of TCostIndicator
     */
	IMPORT_C TCostIndicator CostIndicator() const;

    /**
     * This method indicates if there will be power consumption for obtaining a 
     * position fix. It indicates the expected internal power usage.
     * @return The power consumption as an enumerated value of TPowerConsumption
     */
	IMPORT_C TPowerConsumption PowerConsumption() const;

    /**
     * Set the time required to obtain an initial location fix
     * @param aTimeToFirstFix The time required to obtain an initial location fix
     * @panic "Lbs Client Fault" 12 if aTimeToFirstFix is negative.
     */
	IMPORT_C void SetTimeToFirstFix(TTimeIntervalMicroSeconds aTimeToFirstFix);

    /**
     * Set the time required to obtain subsequent location fixes after the first fix.
     * @param aTimeToNextFix The time required to obtain subsequent location fixes
     * @panic "Lbs Client Fault" 12 if aTimeToNextFix is negative.
     */
	IMPORT_C void SetTimeToNextFix(TTimeIntervalMicroSeconds aTimeToNextFix);

    /**
     * Set the Horizontal Accuracy
     * @param aHorizontalAccuracy The horizontal accuracy to set
     * @panic "Lbs Client Fault" 13 if aHorizontalAccuracy parameter is negative.
     */
	IMPORT_C void SetHorizontalAccuracy(TReal32 aHorizontalAccuracy);

    /**
     * Set the Vertical Accuracy
     * @param aVerticalAccuracy The vertical accuracy to set
     * @panic "Lbs Client Fault" 13 if aVerticalAccuracy parameter is negative.
     */
	IMPORT_C void SetVerticalAccuracy(TReal32 aVerticalAccuracy);

    /**
     * Set if there will be a monetary charge when a position 
     * fix is obtained.
     * @param aCost The cost indicator to set
     */
	IMPORT_C void SetCostIndicator(TCostIndicator aCost);

    /**
     * Set if there will be power consumption when a position 
     * fix is obtained.
     * @param aPower The power consumption to set
     */
	IMPORT_C void SetPowerConsumption(TPowerConsumption aPower);

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


/**
 * The base class for classes storing information about positioning modules
 */
class TPositionModuleInfoBase : public TPositionClassTypeBase
	{
protected:
	IMPORT_C TPositionModuleInfoBase();
	};

/**
 * The standard class for storing information about positioning modules.
 */
class TPositionModuleInfo : public TPositionModuleInfoBase
	{
public:

	/**
	 * @brief Defines the various positioning technology types that are
	 * used by positioning modules to obtain location information. 
	 * The enumerated values are specified in #_TTechnologyType.
	 */
	typedef TUint32 TTechnologyType;
	/**
	 * Technology types
	 */
	enum _TTechnologyType
		{
		/**
		 * indicates that the positioning module is unaware of the technology 
		 * used to obtain position information
		 */
		ETechnologyUnknown	= 0,
		/**
		 * indicates that the primary positioning technology is handset based.
		 */
		ETechnologyTerminal	= 0x01,
		/**
		 * indicates that the primary positioning technology is network based.
		 */
		ETechnologyNetwork	= 0x02,
        /**
         * indicates that the primary positioning mechanism receives assistance
         * in some form. Generally to obtain a quicker or more accurate fix.
         */
		ETechnologyAssisted	= 0x04
		};

	/**
	 * @brief Defines the way the positioning technology hardware is
	 * integrated to the system.
	 * The enumerated values are specified in #_TDeviceLocation.
	 */
	typedef TUint32 TDeviceLocation;
	/**
	 * Device locations
	 */
	enum _TDeviceLocation
		{
		/** 
		 * Indicates that the positioning module is unaware of the hardware 
		 * used to supply positioning information.
		 */
		EDeviceUnknown	= 0,
		/**
		 * indicates that the positioning hardware is integral to the terminal.
		 */
		EDeviceInternal	= 0x01,
		/**
		 * indicates that the positioning hardware is separate from the terminal
		 */
		EDeviceExternal	= 0x02
		};

	/**
	 * @brief Defines the different location attributes that a positioning 
	 * technology can provide the client.
	 * The enumerated values are specified in #_TCapabilities.
	 */
	typedef TUint32 TCapabilities;
	/**
	 * Position module capabilities
	 */
	enum _TCapabilities
		{
		/** An unassigned value */
		ECapabilityNone	       = 0,
		/** 
		 * Positioning modules with this capability support the 
		 * #TPositionInfo class and are able to provide latitude 
		 * and longitude related information
		 */
		ECapabilityHorizontal  = 0x0001,
		/** 
		 * Positioning modules with this capability support the 
		 * #TPositionInfo class and are able to provide altitude
		 * related information apart from latitude and longitude
		 */
		ECapabilityVertical    = 0x0002,
		/**
		 * Positioning modules with this capability support the 
		 * #TPositionCourseInfo class and are able to provide 
		 * information related to the current horizontal speed
		 */
		ECapabilitySpeed       = 0x0004,
		/**
		 * Positioning modules with this capability support the 
		 * #TPositionCourseInfo class and are able to provide 
		 * heading and course related information
		 */
		ECapabilityDirection   = 0x0008,
		/**
		 * Positioning modules with this capability support the 
		 * #TPositionSatelliteInfo class. Such a module is able 
		 * to return at least some satellite data
		 */
		ECapabilitySatellite   = 0x0010,
		/**
		 * Positioning modules with this capability are able to 
		 * return information related to a magnetic compass
		 */
		ECapabilityCompass     = 0x0020,
		/**
		 * Positioning modules with this capability are able to 
		 * return location information using NMEA formatted text strings
		 */
		ECapabilityNmea        = 0x0040,
		/**
		 * Positioning modules with this capability are able to 
		 * return information related to the postal address of the 
		 * current location
		 */
		ECapabilityAddress     = 0x0080,
		/**
		 * Positioning modules with this capability are able to return 
		 * the current position in terms of where it is within a building
		 */
		ECapabilityBuilding    = 0x0100,
		/**
		 * Positioning modules with this capability are able to provide 
		 * a link to further information about the location. The standard 
		 * mechanism is via a URL
		 */
		ECapabilityMedia       = 0x0200
		};

public:
    /**
     * Default constructor for TPositionModuleInfo
     */
	IMPORT_C TPositionModuleInfo();

    /**
     * Get the unique identifier that specifies the positioning module.
     * @return The module ID
     */
	IMPORT_C TPositionModuleId ModuleId() const;

    /**
     * Check if the positioning module is available for use.
     * @return Whether or not this module is available
     * @return ETrue if the module is available
     * @return EFalse if the module is not available
     */
	IMPORT_C TBool IsAvailable() const;

    /**
     * Obtain the positioning module name
     * @param[out] aModuleName The descriptor where the module's name will be placed
     */
	IMPORT_C void GetModuleName(TDes& aModuleName) const;

    /**
     * Get the quality of the positioning information that a 
     * positioning module is able to provide.
     * @param[out] aPosQuality The quality of the position
     */
	IMPORT_C void GetPositionQuality(TPositionQuality& aPosQuality) const;

    /**
     * Get the primary technologies used to obtain position information.
     * This is a bit mask consisting of the enumerated values of 
     * #_TTechnologyType. 
     * @return The technology type
     */
	IMPORT_C TTechnologyType TechnologyType() const;

    /**
     * Get information on whether the positioning hardware used by the 
     * positioning module is an integrated device or an external device.
     * @return The location of the positioning device associated with this module
     */
	IMPORT_C TDeviceLocation DeviceLocation() const;

    /**
     * Get information about the range of position information this positioning
     * module is capable of returning.
     * @return The capabilities of this module
     */
	IMPORT_C TCapabilities Capabilities() const ;

    /**
     * Get the classes supported by this positioning module
     * @param aClassType indicates the position class family to query
     * the support. For example, using EPositionInfoFamily returns a bit mask 
     * of values from the enumeration #TPositionInfoClassType. The returned 
     * bitmask indicates the position information classes that are supported 
     * by the positioning module
     * 
     * @see TPositionClassFamily for different family types.
     * @return bitmask of the classes supported for the specified family type.
     * @panic "Lbs Client Fault" 8 if the aClassType parameter does not 
     * represent a known family value.
     */
	IMPORT_C TUint32 ClassesSupported(TPositionClassFamily aClassType) const;

    /**
     * The version of the positioning module
     * @return The version of the module
     */
	IMPORT_C TVersion Version() const;

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set the module ID for the 
     * positioning module 
     * @param aModuleId The module ID to set
     */
	IMPORT_C void SetModuleId(TPositionModuleId aModuleId);

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set whether 
     * this positioning module is available for position determination 
     * or not.
     * @param aIsAvailable Whether or not the module is available for use
     */
	IMPORT_C void SetIsAvailable(TBool aIsAvailable);

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set the name 
     * of the positioning module.
     * @param[in] aModuleName The module name to set
     */
	IMPORT_C void SetModuleName(const TDesC& aModuleName);

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set the quality 
     * of the positioning information that the positioning module
     * can provide.
     * @param[in] aPosQuality The position quality to set
     */
	IMPORT_C void SetPositionQuality(const TPositionQuality& aPosQuality);

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set the primary 
     * technologies used to obtain position information.
     * This is a bit mask consisting of the enumerated values of 
     * #_TTechnologyType. 
     * @param aTechnologyType The technology type to set
     */
	IMPORT_C void SetTechnologyType(TTechnologyType aTechnologyType);

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set information on 
     * whether the positioning hardware used by the positioning 
     * module is an integrated device or an external device.
     * @param aDeviceLocation The positioning device location to set
     */
	IMPORT_C void SetDeviceLocation(TDeviceLocation aDeviceLocation);

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set information about 
     * the different positioning related fields that this positioning module is 
     * capable of returning.
     * @param aDeviceCapabilities Bitfield of the capabilities of this module to set
     */
	IMPORT_C void SetCapabilities(TCapabilities aDeviceCapabilities);

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set the different 
     * positioning information classes that this positioning module supports.
     * 
     * @param aClassType indicates the position class family.
     * @param aSupportedClasses a bit mask value of the supported classes
     * for the specified class family type.
     * @see TPositionClassFamily for different family types.
     */
	IMPORT_C void SetClassesSupported(TPositionClassFamily aClassType,
									  TUint32 aSupportedClasses);

    /**
     * This method is not intended for the client's usage.
     * This method is used by Location framework to set the version 
     * of this positioning module.
     * @param aVersion The version to set
     */
	IMPORT_C void SetVersion(TVersion aVersion);

protected:
	/** The module ID */
	TPositionModuleId	iModuleId;
	/** Whether or not the module is available */
	TBool iIsAvailable;
	/** The module name */
	TBuf<KPositionMaxModuleName> iModuleName;
	/** The position quality */
	TPositionQuality    iPosQuality;
	/** The technology type */
	TTechnologyType     iTechnologyType;
	/** The location of the device associated with this module */
	TDeviceLocation     iDeviceLocation;
	/** The capabilities of this module */
	TCapabilities		iCapabilities;
	/** The array of supported classes for the different class types */
	TFixedArray<TUint32, EPositionLastFamily> iSupportedClassTypes;
	/** The version of this module */
	TVersion            iVersion;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


/**
 * The base class for classes storing a position module's status
 */
class TPositionModuleStatusBase : public TPositionClassTypeBase
	{
protected:
	IMPORT_C TPositionModuleStatusBase();
	};

/**
 * The normal class for storing a position module's status
 */
class TPositionModuleStatus : public TPositionModuleStatusBase
	{
public:

	/**
	 * @brief Defines the status of the positioning device.
	 * The values are defined by the enumerator #_TDeviceStatus.
	 */
	typedef TInt TDeviceStatus;

	/**
	 * The device status
	 */
	enum _TDeviceStatus 
		{
		/** This is not a valid state and must never be reported */
		EDeviceUnknown,
		/** to indicate that there are problems when using the device */
		EDeviceError,
		/** 
		 * Although the device may be working properly, it has been taken 
		 * offline and is regarded as being unavailable to obtain position 
		 * information
		 */
		EDeviceDisabled,
		/** 
		 * indicates that the device is currently not being used by 
		 * Location Framework
		 */
		EDeviceInactive,
		/**
		 * This is a transient state. The device is being brought out of 
		 * the Inactive state but has not reached either the Ready or 
		 * Standby modes. The initializing state occurs when the positioning 
		 * module is first selected to provide a client application with 
		 * location information
		 */
		EDeviceInitialising,
		/**
		 * This state indicates that the device has entered the Sleep or 
		 * Power save mode. This signifies that the device is online, but 
		 * it is not actively retrieving position information. A device 
		 * generally enters this mode when the next position update is not 
		 * required for some time and it is more efficient to partially 
		 * power down
		 */
		EDeviceStandBy,
		/** 
		 * The positioning device is online and is ready to retrieve 
		 * position information
		 */
		EDeviceReady,
		/**
		 * The positioning device is actively in the process of retrieving 
		 * position information
		 */
		EDeviceActive
		};

	/**
	 * @brief Defines the quality of the data returned by the positioning device.
	 * The values are defined by the enumerator #_TDataQualityStatus.
	 */
	typedef TInt TDataQualityStatus;

	/**
	 * The data quality status
	 */
	enum _TDataQualityStatus
		{
		/**
		 * This is an unassigned valued. This state should only be reported 
		 * during an event indicating that a positioning module has been 
		 * removed
		 */
		EDataQualityUnknown,
		/**
		 * This state indicates that the accuracy and contents of the position
		 * information has been completely compromised. It is no longer
		 * possible to return any coherent data. This situation occurs if the
		 * device has lost track of all the transmitters (for example, 
		 * satellites or base stations). It should be noted that although it
		 * is currently not possible to obtain position information, the device
		 * may still be functioning correctly.
		 */
		EDataQualityLoss,
		/**
		 * This value indicates that there has been a partial degradation in the
		 * available position information. In particular, it is not possible to
		 * provide the required (or expected) quality of information
		 */
		EDataQualityPartial,
		/** The positioning device is functioning as expected */
		EDataQualityNormal
		};

    /**
     * Default constructor for TPositionModuleStatus
     */
	IMPORT_C TPositionModuleStatus();

    /**
     * Get the current condition of the device used by the positioning module
     * @return The module's device status
     */
	IMPORT_C TDeviceStatus DeviceStatus() const;

    /**
     * Get the quality of the position information determined by the 
     * positioning module
     * @return  The data quality status
     */
	IMPORT_C TDataQualityStatus DataQualityStatus() const;

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to sets the current condition
     * of the positioning device that it uses to obtain position information.
     * @param aStatus The device status to set
     */
	IMPORT_C void SetDeviceStatus(TDeviceStatus aStatus);

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to sets the quality of the
     * position information determined by the positioning module.
     * @param aStatus The data quality status to set
     */
	IMPORT_C void SetDataQualityStatus(TDataQualityStatus aStatus);
	
protected:
	/** The device status */
	TDeviceStatus      iDeviceStatus;
	/** The data quality status */
	TDataQualityStatus iDataQualityStatus;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[8];
	};


/**
 * The base class for classes storing position module status events
 */
class TPositionModuleStatusEventBase : public TPositionClassTypeBase
	{
public:
	/**
	 * @brief Defines the system wide events for a positioning module
	 * like installation/uninstalltion of a positioning module.
	 * The values are defined by the enumerator #_TSystemModuleEvent.
	 */
	typedef TUint32 TSystemModuleEvent;

	/**
	 * Module events
	 */
	enum _TSystemModuleEvent
		{
		/** This is not a valid state and should never be reported */
		ESystemUnknown				= 0,
		/** 
		 * indicates that there are problems using the module. 
		 * For example, the module may have terminated abnormally
		 */
		ESystemError,
		/**
		 * indicates that a new positioning module has been dynamically 
		 * added to the system
		 */
		ESystemModuleInstalled,
		/** indicates that a positioning module has been uninstalled */
		ESystemModuleRemoved
		};
	
	/**
	 * @brief Defines the type of event for by a positioning module. The
	 * events could be either system wide events or positioning related
	 * events. 
	 * The values are defined by the enumerator #_TModuleEvent.
	 */
	typedef TUint32 TModuleEvent;

	/**
	 * Module events
	 */
	enum _TModuleEvent
		{
		/** This is an unassigned value and should not be reported or used */
		EEventNone				= 0,
		/** Events about the general status of the device */
		EEventDeviceStatus      = 0x01,
		/** Events about the quality of the data a positioning module is able to return */
		EEventDataQualityStatus = 0x02,
		/** System level events about the status of modules */
		EEventSystemModuleEvent = 0x04,
		/** indicates any one of the above mentioned events */
		EEventAll				= EEventDeviceStatus |
								  EEventDataQualityStatus |
								  EEventSystemModuleEvent
		};

protected:
    /**
     * Default constructor for TPositionModuleStatusEventBase
     */
	IMPORT_C TPositionModuleStatusEventBase();
	/**
	 * Constructor
	 * @param aRequestedEventMask a bit mask that indicates the type of 
	 * status change events on which notification is requested
	 * @see RPositionServer::NotifyModuleStatusEvent() to request
	 * for event notification
	 */ 
	IMPORT_C TPositionModuleStatusEventBase(TModuleEvent aRequestedEventMask);

public:
    /**
     * Set the events for which notification is requested.
     * @param aRequestedEventMask The requested events to set
	 * @see RPositionServer::NotifyModuleStatusEvent() to request
	 * for event notification
     */
	IMPORT_C void SetRequestedEvents(TModuleEvent aRequestedEventMask);

    /**
     * Get the events for which notification is requested.
     * @return The requested events
     */
	IMPORT_C TModuleEvent RequestedEvents() const;

    /**
     * This method is not intended for the client's usage.
     * The Location framework uses this method to set the module event
     * that has occured for this positioning module.
     * @param aOccurredEventMask The occurred events to set
     */
	IMPORT_C void SetOccurredEvents(TModuleEvent aOccurredEventMask);

    /**
     * Get the events which have Occurred. 
     *
     * @return The events which have occurred
     * @return EEventSystemModuleEvent In this case the client should use
     * SystemModuleEvent() to determine the type of system event.
     * @return EEventDeviceStatus the client should call 
     * TPositionModuleStatusEvent::GetModuleStatus() to find the type of event.
     * @return EEventDataQualityStatus the client should call 
     * TPositionModuleStatusEvent::GetModuleStatus() to find the type of event.
     */
	IMPORT_C TModuleEvent OccurredEvents() const;

    /**
     * Get the unique identifier for the positioning module
     * @return The module ID
     */
	IMPORT_C TPositionModuleId ModuleId() const;

    /**
     * This method is not intended for the client's usage.
     * The Location framework uses this method to set the unique identifier
     * for the positioning module for which this event has occured.
     * @param aModuleId The module ID to set
     */
	IMPORT_C void SetModuleId(TPositionModuleId aModuleId);

    /**
     * This method is not intended for the client's usage.
     * The Location framework uses this method to set the system event
     * that has occured for this positioning module.
     * @param aSystemModuleEvent The system event to set.
     */
	IMPORT_C void SetSystemModuleEvent(TSystemModuleEvent aSystemModuleEvent);

    /**
     * Get the type of module system event that has occurred.
     * @return The system event type.
     */
	IMPORT_C TSystemModuleEvent SystemModuleEvent() const;

protected:
	IMPORT_C virtual void DoReset(TInt aSizeOfClass);

private:
	friend class RPositionServer;
	void Reset();

protected:
	/** A bitmask of the requested events */
	TModuleEvent iRequestedEvents;
	/** A bitmask of the events which occurred */
	TModuleEvent iOccurredEvents;
	/** System level module status events*/
	TSystemModuleEvent iSystemModuleEvent;
	/** The module ID causing the event*/
	TPositionModuleId  iModuleId;
	};

/**
 * The normal class for storing position module status events
 */
class TPositionModuleStatusEvent : public TPositionModuleStatusEventBase
	{
public:
    /**
     * Default constructor for TPositionModuleStatusEvent
     */
	IMPORT_C TPositionModuleStatusEvent();

    /**
     * Constructor for TPositionModuleStatusEvent (with events)
     * @param aRequestedEventMask a bit mask value that indicates the type of
     * events for which notification is requested
     */
	IMPORT_C TPositionModuleStatusEvent(TModuleEvent aRequestedEventMask);

    /**
     * This method is not intended for the client's usage.
     * The positioning module uses this method to set the status of the 
     * positioning device and the data quality status of the position
     * information returned by this positioning module.
     * @param[in] aModuleStatus The module status to set
     */
	IMPORT_C void SetModuleStatus(const TPositionModuleStatus& aModuleStatus);

    /**
     * Obtain the status of the positioning module.
     * @param[out] aModuleStatus Where the module status will be returned.
     */
	IMPORT_C void GetModuleStatus(TPositionModuleStatus& aModuleStatus) const;

protected:
	IMPORT_C virtual void DoReset(TInt aSizeOfClass);

protected:
	/** The module status */
	TPositionModuleStatus iModuleStatus;
	};


/**
 * The base class for classes storing position update options
 * This class is used to change the behavior of 
 * RPositioner::NotifyPositionUpdate(). It enables the client application
 * to request periodic updates. It can also be used to inform the positioning
 * module that the client application will accept partial (i.e. incomplete)
 * position information
 */
class TPositionUpdateOptionsBase : public TPositionClassTypeBase
	{
protected:
	IMPORT_C TPositionUpdateOptionsBase();
	IMPORT_C TPositionUpdateOptionsBase(TTimeIntervalMicroSeconds aInterval,
	                                    TTimeIntervalMicroSeconds aTimeOut = TTimeIntervalMicroSeconds(0),
	                                    TTimeIntervalMicroSeconds aMaxAge = TTimeIntervalMicroSeconds(0));

public:
    /**
     * This method allows the client application to specify if it wants to
     * receive updates at regular intervals. This means that as long as the
     * client re-issues the position request when the previous request is
     * completed, the client receives position updates at the specified
     * update interval periodicity.
     *
     * @param aInterval  This parameter specifies the time interval after which the 
     * client wants a position update. Note that even after setting this value
     * the client will have to call RPositioner::NotifyPositionUpdate() repeatedly to
     * get position information. The Location Server only gurantees that even if
     * the client makes a request immediately, the position information will be 
     * obtained and returned only after the specified update interval time.
     * - If the previous value was zero and aInterval is set to a non-zero 
     * value then the periodic updates is started.
     * - If the previous value was non-zero and aInterval is set to a different
     * non-zero value then the new periodic update interval is updated.
     * - If the aInterval was non-zero is set to zero then the periodic updates
     * is stopped.
     * @panic "Lbs Client Fault" 12 if aInterval is negative.
     *
     * @post the client should invoke RPositioner::SetUpdateOptions() to
     * set this option for the current session.
     */
	IMPORT_C void SetUpdateInterval(TTimeIntervalMicroSeconds aInterval);

    /**
     * This method allows the client application to specify the timeout
     * for RPositioner::NotifyPositionUpdate() request. If the positioning
     * module is unable to return a position fix within the specified timeout
     * interval then the request is cancelled.
     * @param aTimeOut This parameter specifies the timeout
     * for a RPositioner::NotifyPositionUpdate() request.
     * @panic with "Lbs Client Fault" 12 if aTimeOut is negative.
     *
     * @note When using a timeout, the application should also be aware of 
     * the time taken to obtain the initial fix and the time taken to obtain 
     * a subsequent fix of the positioning module that is being used to obtain
     * the fixes. These values can be obtained by calling 
     * RPositionServer::GetModuleInfoById() method.
     *
     * @post the client should invoke RPositioner::SetUpdateOptions() to
     * set this option for the current session.
     */
	IMPORT_C void SetUpdateTimeOut(TTimeIntervalMicroSeconds aTimeOut);

    /**
     * This method allows the client application to specify the maximum age
     * for the position information returned from 
     * RPositioner::NotifyPositionUpdate() request. This means that position
     * information can be returned from cache as long as the position is not 
     * older than the specified maximum age value.
     * @param aMaxAge This parameter specifies the expiry time for the position
     * information cache for this subsession. It means that when a position 
     * request is made the position information can be returned from the cache
     * as long as the cache is not older that the specified maximum age.
     * @panic with "Lbs Client Fault" 12 if aMaxAge is negative.
     *
     * @post the client should invoke RPositioner::SetUpdateOptions() to
     * set this option for the current session.
     */
	IMPORT_C void SetMaxUpdateAge(TTimeIntervalMicroSeconds aMaxAge);

    /**
     * Get the current update interval value.
     * @return The update interval
     *
     * @note this returns only the value within this class object.
     *
     * @pre The client should have called RPositioner::GetUpdateOptions() to 
     * obtain the current update interval for this session.
     */
	IMPORT_C TTimeIntervalMicroSeconds UpdateInterval() const;

    /**
     * Get the current timeout interval value.
     * @return The update timeout
     *
     * @note this returns only the value within this class object.
     *
     * @pre The client should have called RPositioner::GetUpdateOptions() to
     * obtain the current timeout interval for this session.
     */
	IMPORT_C TTimeIntervalMicroSeconds UpdateTimeOut() const;

    /**
     * Get the current maximum age value.
     * @return The maximum update age
     *
     * @note this returns only the value within this class object.
     *
     * @pre The client should have called RPositioner::GetUpdateOptions() to
     * obtain the current maxage for this session.
     */
	IMPORT_C TTimeIntervalMicroSeconds MaxUpdateAge() const;

protected:
	/** The update interval */
	TTimeIntervalMicroSeconds iUpdateInterval;
	/** The update timeout */
	TTimeIntervalMicroSeconds iUpdateTimeOut;
	/** The maximum update age */
	TTimeIntervalMicroSeconds iMaxUpdateAge;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[8];
	};

/**
 * The normal class for storing position update options
 */
class TPositionUpdateOptions : public TPositionUpdateOptionsBase
	{
public:

    /**
     * Default constructor for TPositionUpdateOptions
     */
	IMPORT_C TPositionUpdateOptions();

    /**
     * Constructor for TPositionUpdateOptions. All parameters except aInterval
     * have default values.
     *
     * @param aInterval The time interval at which the client is interested in
     * receiving position information from positioning server at regular 
     * intervals. This means that as long as the client re-issues the position
     * request when the previous position request is completed, the client receives 
     * position updates after the specified update interval periodicity.
     *
     * @param aTimeOut The timeout value for a position request. If the 
     * positioning module is unable to return a position fix within the specified
     * timeout interval then the request is cancelled. Defaults to zero.
     *
     * @param aMaxAge This parameter specifies the expiry time for the position
     * information cache for this subsession. It means that when a position 
     * request is made the position information can be returned from the cache
     * as long as the cache is not older that the specified maximum age. The default
     * value is zero ie the position information will never be returned from cache.
     *
     * @param aAcceptPartialUpdates If this parameter is set to true then the server
     * can choose to return only the timestamp value for a position request. All other 
     * fields like latitude, longitude and altitude etc are taken as optional fields.
     * If it is false, then it is mandatory for the server to return all fields of
     * the basic position information. The default value is false.
     */
	IMPORT_C TPositionUpdateOptions(TTimeIntervalMicroSeconds aInterval,
	                                TTimeIntervalMicroSeconds aTimeOut = TTimeIntervalMicroSeconds(0),
	                                TTimeIntervalMicroSeconds aMaxAge = TTimeIntervalMicroSeconds(0),
	                                TBool aAcceptPartialUpdates = EFalse);

    /**
     * Set whether partial updates can be accepted.
     * If partial updates are allowed, then timestamp is the only mandatory field.
     * All other information like latitude, longitude etc. can be missing from 
     * the returned position information.
     * @param aAcceptPartialUpdates If this parameter is set to true then the server
     * can choose to return only the timestamp value for a position request. All other 
     * fields like latitude, longitude and altitude etc are taken as optional fields.
     * If it is false, then it is mandatory for the server to return all fields of
     * the basic position information. The default value is false.
     *
     * @post the client should invoke RPositioner::SetUpdateOptions() to
     * set this option for the current session.
     */
	IMPORT_C void SetAcceptPartialUpdates(TBool aAcceptPartialUpdates);

    /**
     * Check if partial update option was set for this session.
     * @return ETrue if partial updates are accepted, EFalse otherwise
     *
     * @note this returns only the value within this class object.
     *
     * @pre The client should have called RPositioner::GetUpdateOptions() to
     * retrieve information about whether partial updates option has 
     * been set to true or false.
     */
	IMPORT_C TBool AcceptPartialUpdates() const;

protected:
	/** Whether partial updates are accepted */
	TBool iAcceptPartialUpdates;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


#endif //__LBSCOMMON_H__
