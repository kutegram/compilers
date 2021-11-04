/*
* ==============================================================================
*  Name        : LbsClassTypes.h
*  Part of     : Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Position data class' types
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

#ifndef __LBSCLASSTYPES_H__
#define __LBSCLASSTYPES_H__

/**
 * @file LbsClassTypes.h
 * This file defines the enumerations for the various positioning related information
 * classes that the positioning module can return.
 */ 
/**
 * @enum TPositionClassFamily 
 * The type of position class
 */
enum TPositionClassFamily
	{
	/** 
	 * indicates all the TPositionInfoBase derived classes supported by the 
	 * positioning module.
	 * When this values is passed to the TPositionModuleInfo::ClassesSupported()
	 * method, it returns a bit mask of values corresponding to the enumeration 
	 * _TPositionInfoClassType
	 */
	EPositionInfoFamily,
	/** 
	 * indicates all the TPositionModuleInfoBase derived classes supported by the 
	 * positioning module.
	 * When this values is passed to the TPositionModuleInfo::ClassesSupported()
	 * method, it returns a bit mask of values corresponding to the enumeration 
	 * _TPositionModuleInfoClassType
	 */
	EPositionModuleInfoFamily,
	/** 
	 * indicates all the TPositionModuleStatusBase derived classes supported by the 
	 * positioning module.
	 * When this values is passed to the TPositionModuleInfo::ClassesSupported()
	 * method, it returns a bit mask of values corresponding to the enumeration 
	 * _TPositionModuleStatusClassType
	 */
	EPositionModuleStatusFamily,
	/** 
	 * indicates all the TPositionModuleStatusEventBase derived classes supported 
	 * by the positioning module.
	 * When this values is passed to the TPositionModuleInfo::ClassesSupported()
	 * method, it returns a bit mask of values corresponding to the enumeration 
	 * _TPositionModuleStatusEventClassType
	 */
	EPositionModuleStatusEventFamily,
	/** 
	 * indicates all the TPositionModuleQualityBase derived classes supported 
	 * by the positioning module.
	 * When this values is passed to the TPositionModuleInfo::ClassesSupported()
	 * method, it returns a bit mask of values corresponding to the enumeration 
	 * _TPositionModuleQualityClassType
	 */
	EPositionModuleQualityFamily,
	/** 
	 * indicates all the TPositionCriteriaBase derived classes supported 
	 * by the positioning module.
	 * When this values is passed to the TPositionModuleInfo::ClassesSupported()
	 * method, it returns a bit mask of values corresponding to the enumeration 
	 * _TPositionCriteriaClassType
	 */
	EPositionPositionCriteriaFamily,
	/** 
	 * indicates all the TPositionUpdateOptionsBase derived classes supported 
	 * by the positioning module.
	 * When this values is passed to the TPositionModuleInfo::ClassesSupported()
	 * method, it returns a bit mask of values corresponding to the enumeration 
	 * _TPositionUpdateOptionsClassType
	 */
	EPositionUpdateOptionsFamily,

	EPositionLastFamily = 20
	};

/**
 * @enum _TPositionQualityClassType 
 * TPositionQualityBase derived position quality class types
 */
enum _TPositionQualityClassType
	{
	/** Unknown position quality class type */
	EPositionQualityUnknownClass		= 0,
	/** Indicates that the class is TPositionQuality */
	EPositionQualityClass				= 0x01,
	/** starting value for user defined position quality class types */
	EPositionQualityFirstCustomClass	= 0x01000000
	};

/**
 * @enum _TPositionModuleInfoClassType 
 * TPositionModuleInfoBase derived position module information class types
 */
enum _TPositionModuleInfoClassType
	{
	/** Unknown position module information class type */
	EPositionModuleInfoUnknownClass		= 0,
	/** Indicates that the class is TPositionModuleInfo */
	EPositionModuleInfoClass			= 0x01,
	/** starting value for user defined position module information class types */
	EPositionModuleInfoFirstCustomClass	= 0x01000000
	};

/**
 * @enum _TPositionModuleStatusClassType 
 * TPositionModuleStatusBase derived position module status class types
 */
enum _TPositionModuleStatusClassType
	{
	/** Unknown position module status class type */
	EPositionModuleStatusUnknownClass		= 0,
	/** Indicates that the class is TPositionModuleStatus */
	EPositionModuleStatusClass				= 0x01,
	/** starting value for user defined position module status class types */
	EPositionModuleStatusFirstCustomClass	= 0x01000000
	};

/**
 * @enum _TPositionModuleStatusEventClassType 
 * TPositionModuleStatusEventBase derived position module status event class types
 */
enum _TPositionModuleStatusEventClassType
	{
	/** Unknown position module status event class type */
	EPositionModuleStatusEventUnknownClass		= 0,
	/** Indicates that the class is TPositionModuleStatusEvent */
	EPositionModuleStatusEventClass				= 0x01,
	/** starting value for user defined position module status event class types */
	EPositionModuleStatusEventFirstCustomClass	= 0x01000000
	};

/**
 * @enum _TPositionUpdateOptionsClassType 
 * TPositionUpdateOptionsBase derived position update options class types
 */
enum _TPositionUpdateOptionsClassType
	{
	/** Unknown position update options class type */
	EPositionUpdateOptionsUnknownClass		= 0,
	/** Indicates that the class is TPositionUpdateOptions */
	EPositionUpdateOptionsClass				= 0x01,
	/** starting value for user defined position update options class types */
	EPositionUpdateOptionsFirstCustomClass	= 0x01000000
	};

/**
 * @enum _TPositionInfoClassType 
 * TPositionInfoBase derived classes class types
 */
enum _TPositionInfoClassType
	{
	/** Unknown position info class type */
	EPositionInfoUnknownClass		= 0,
	/** Indicates that the class is a TPositionInfo */
	EPositionInfoClass				= 0x01,
	/** Indicates that the class is a HPositionGenericInfo */
	EPositionGenericInfoClass		= 0x02,
	/** Indicates that the class is a TPositionCourseInfo */
	EPositionCourseInfoClass		= 0x04,
	/** Indicates that the class is a TPositionSatelliteInfo */
	EPositionSatelliteInfoClass		= 0x08,
	/** starting value for user defined position info class types */
	EPositionInfoFirstCustomClass	= 0x01000000
	};

/**
 * @enum _TPositionCriteriaClassType 
 * TPositionCriteriaBase derived classes class types
 */
enum _TPositionCriteriaClassType
	{
	EPositionCriteriaUnknownClass		= 0,
	EPositionCriteriaClass				= 0x01,
	EPositionCriteriaFirstCustomClass	= 0x01000000
	};

/**
 * @typedef TPositionInfoClassType
 * @brief Indicates the types of Position Information classes supported by a 
 * PSY. Its value is a bitmask of enumerated values of #_TPositionInfoClassType
 */
typedef TUint32 TPositionInfoClassType;


#endif //__LBSCLASSTYPES_H__
