/*
* ==============================================================================
*  Name        : LbsPositionInfo.h
*  Part of     : Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Position Info classes
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

#ifndef __LBSPOSITIONINFO_H__
#define __LBSPOSITIONINFO_H__

#include <LbsPosition.h>
#include <LbsCommon.h>
#include <LbsFields.h>

/**
 * @file LbsPositionInfo.h
 * This file contains the declaration for all the positioning information
 * related data classes.
 */

/**
 * The default size for a HPositionGenericInfo position information buffer
 */
const TInt KPositionGenericInfoDefaultBufferSize = 1024;
/**
 * The default number of requested fields for a HPositionGenericInfo 
 * position information buffer
 */
const TInt KPositionGenericInfoDefaultMaxFields = 32;
/**
 * Position update types
 */
enum _TPositionUpdateType
	{
	EPositionUpdateUnknown = 0,
	EPositionUpdateGeneral = 0x01
	};

/**
 * @typedef TPositionUpdateType
 * @brief Defines the type of position update provided by the positioning module.
 * The values are defined by the enumerator #_TPositionUpdateType
 */
typedef TUint32 TPositionUpdateType;


/**
 * This class provides the interface used by RPositioner to get a location fix,
 * and as such all classes used to get location info from the location server should
 * derive from this class.
 *
 * Class contains info about the update type and the ID of the module that gave the 
 * location fix
 */
class TPositionInfoBase : public TPositionClassTypeBase
	{
public:
    /**
     * Get the unique identifier of the positioning module that provided the fix.
     * @return Returns the module Id of the module that gave the position fix.
     */
	IMPORT_C TPositionModuleId ModuleId() const;

    /**
     * Set the unique identifier of the positioning module that provided the fix.
     * This is usually called by the Location framework. Clients need not
     * call this method.
     * @param aModuleId Module Id stored in this class is set to aModuleId.
     */
	IMPORT_C void SetModuleId(TPositionModuleId aModuleId);

    /**
     * Get the type of position update provided to the client.
     * @return Returns the update type of the position fix.
     */
	IMPORT_C TPositionUpdateType UpdateType() const;

    /**
     * Set the type of position update provided to the client.
     * This is usually called by the Location framework. Clients need not
     * call this method.
     * @param aUpdateType The update type of the position fix in this class is set to this.
     */
	IMPORT_C void SetUpdateType(TPositionUpdateType aUpdateType);

protected:
    /**
     * Helper method. To be used within the class 
     */
	IMPORT_C TPositionInfoBase();

protected:
	/** The Id of the module that gave the location fix. */
	TPositionModuleId iModuleId;
	/** The type of update that this location fix represents. */
	TUint32 iUpdateType;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


/**
 * Standard class for getting a TPosition location fix from the location server.
 */
class TPositionInfo : public TPositionInfoBase
	{
public:
    /**
     * Default constructor. Sets the class type and class size in the base class (TPositionInfoBase).
     */
	IMPORT_C TPositionInfo();

    /**
     * Get the position information returned by the positioning module
     * @param[out] aPosition The TPosition stored in this class is copied into aPosition
     */
	IMPORT_C void GetPosition(TPosition& aPosition) const;

    /**
     * Set the position information.
     * This is usually called by the Location framework. Clients need not
     * call this method.
     * @param[in] aPosition The TPosition stored in this class is set to aPosition
     */
	IMPORT_C void SetPosition(const TPosition& aPosition);

protected:
	/** The TPosition. */
	TPosition iPosition;
	};


/**
 * Class for getting a TCourse from the location server.
 */
class TPositionCourseInfo : public TPositionInfo
	{
public:
    /**
     * Default constructor. Sets the class type and class size in the base class (TPositionInfoBase).
     */
	IMPORT_C TPositionCourseInfo();

    /**
     * Get the course information returned by the positioning module
     * @param[out] aCourse The TCourse stored in this class is copied into aCourse.
     */
	IMPORT_C void GetCourse(TCourse& aCourse) const;

    /**
     * Set the course information.
     * This is usually called by the Location framework. Clients need not
     * call this method.
     * @param[in] aCourse The TCourse stored in this class is set to aCourse.
     */
	IMPORT_C void SetCourse(const TCourse& aCourse);

protected:
	/** The TCourse. */
	TCourse iCourse;
	};


/**
 * Class for getting arbitrary positioning related information back from the location server. 
 * The client can set upto KPositionMaxRequestedFields as the number of requested fields.
 * The definitions of the fields are given in the enum #_TPositionFieldId. The client must 
 * know what data type will be returned for each of the fields. The server will make a best 
 * attempt to fill in the requested fields.
 *
 * The client needs to allocate a big enough buffer to store the information it is requesting.
 * In order to be sure of getting back all the information the client must know and allocate 
 * memory considering the return value for each requested field.
 */
class HPositionGenericInfo : public TPositionInfo
	{
public:

    /**
     * Non-leaving constructor that allocs a HPositionGenericInfo on the heap.
     * @param aBufferSize Sets the size of the buffer that the HPositionGenericInfo will have.
     * @param aMaxFields Sets the maximum number of fields that the HPositionGenericInfo will have.
     * @return position information in HPositionGenericInfo structure.
     * @return NULL if heap allocation failed.
     * @return Pointer to a HPositionGenericInfo instance if alloc was successful.
     */
	IMPORT_C static HPositionGenericInfo* New(TInt aBufferSize = KPositionGenericInfoDefaultBufferSize,
											  TInt aMaxFields = KPositionGenericInfoDefaultMaxFields);

    /**
     * Leaving constructor that allocs a HPositionGenericInfo on the heap.
     * @param aBufferSize Sets the size of the buffer that the HPositionGenericInfo will have.
     * @param aMaxFields Sets the maximum number of fields that the HPositionGenericInfo will have.
     * @return Pointer to a HPositionGenericInfo instance.
     */
	IMPORT_C static HPositionGenericInfo* NewL(TInt aBufferSize = KPositionGenericInfoDefaultBufferSize,
											   TInt aMaxFields = KPositionGenericInfoDefaultMaxFields);

    /**
     * Leaving constructor that allocs a HPositionGenericInfo on the heap and leaves a 
     * pointer to the object on the cleanup stack.
     * @param aBufferSize Sets the size of the buffer that the HPositionGenericInfo will have.
     * @param aMaxFields Sets the maximum number of fields that the HPositionGenericInfo will have.
     * @return Pointer to a HPositionGenericInfo instance.
     */
	IMPORT_C static HPositionGenericInfo* NewLC(TInt aBufferSize = KPositionGenericInfoDefaultBufferSize,
												TInt aMaxFields = KPositionGenericInfoDefaultMaxFields);

    /**
     * Clears all the requested fields.
     */
	IMPORT_C void ClearRequestedFields();

    /**
     * Method sets a field as requested.
     * @param aFieldId Field Id to be set as requested.
     * @return a symbian OS error code.
     * @return KErrNone if aFieldId was successfully set as requested.
     * @return KErrArgument if aFieldId is not strictly between ::EPositionFieldNone and ::EPositionFieldIdLast.
     * @return KErrOverflow if KPositionMaxRequestedFields requested fields have already been set.
     */
	IMPORT_C TInt SetRequestedField(TPositionFieldId aFieldId);
	
    /**
     * Sets multiple TPositionFieldId objects as requested.
     * @param aFieldIdList List of field Id's to be set as requested. The list is terminated 
     * with a ::EPositionFieldNone entry.
     * @return a symbian OS error code.
     * @return KErrNone if all Field Ids were successfully set as requested.
     * @return KErrArgument if a filed Id is not strictly between ::EPositionFieldNone and ::EPositionFieldIdLast.
     * @return KErrOverflow if > KPositionMaxRequestedFields requested fields are attempted to be set.
     */
	IMPORT_C TInt SetRequestedFields(const TPositionFieldIdList aFieldIdList);

    /**
     * Returns whether a field has been set as requested.
     * @param aFieldId Field Id to search for.
     * @return If the requested field has been set or not.
     * @return ETrue if aFieldId has been set as requested.
     * @return EFalse if aFieldId has not been set as requested.
     */
	IMPORT_C TInt IsRequestedField(TPositionFieldId aFieldId) const;

    /**
     * Looks through the list of requested fields for the lowest valued field Id.
     * @return The lowest valued requested field if there are any.
     * @return ::EPositionFieldNone if there are no requested fields.
     */
	IMPORT_C TPositionFieldId FirstRequestedFieldId() const;

    /**
     * Looks for the next field Id in the list greater than aFieldId. 
     * @param aFieldId Function will return next field Id in the list greater than this Id.
     * @return Next field Id in the list greater than aFieldId.
     * @return ::EPositionFieldNone if there are no field Id's in the list greater than aFieldId
     */
	IMPORT_C TPositionFieldId NextRequestedFieldId(TPositionFieldId aFieldId) const;

    /**
     * Looks through the available fields and returns whether aFieldId is in the list.
     * @param aFieldId This is the field Id that is searched for.
     * @return If the requested field is available or not.
     * @return ETrue if the field is available.
     * @return EFalse if the field is not available.
     */
	IMPORT_C TBool IsFieldAvailable(TPositionFieldId aFieldId) const;

    /**
     * Resets the object to clear all info to that as it was on construction except the requested
     * fields. Use in the server to clear the info before putting together a new location fix
     * and passing it back to the client.
     */
	IMPORT_C void ClearPositionData();	//Required on server side

    /**
     * Method returns the size of the buffer set in the constructor
     * @return The size of the buffer that was set in the constructor.
     */
	IMPORT_C TInt BufferSize() const;

    /**
     * @return The maximum field that is requestable/returnable that was set 
     * in the constructor.
     */
	IMPORT_C TInt MaxFields() const;

    /**
     * Used to store position information.
     * @param aFieldId Standard position field identifier. See @ref _TPositionFieldId
     * @param[in] aValue The parameter aValue can be of the type 
     * TInt8, TInt16, TInt32, TInt64, TUint8, TUint16, TUint32, 
     * TReal32, TReal64, TTime, TTimeIntervalMicroSeconds, Des8, or Des16.
     * @return a symbian OS error code.
     * @return KErrNone on successful operation.
     * @return KErrPositionBufferOverflow if the data contained in the 
     * parameter aValue cannot be added to the class due to the buffer being too small.
     */
	template <class TType>
		inline TInt SetValue(TPositionFieldId aFieldId, const TType& aValue) 
			{return PositionFieldManager::SetValue(aFieldId, aValue, *this);}

    /**
     * Used to retrieve position information.
     * @param aFieldId Standard position field identifier. See @ref _TPositionFieldId
     * @param[out] aValue The parameter aValue can be of the type 
     * TInt8, TInt16, TInt32, TInt64, TUint8, TUint16, TUint32, 
     * TReal32, TReal64, TTime, TTimeIntervalMicroSeconds, Des8, or Des16.
     * Panics with EPositionGenericInfoMismatchDataType if there is a 
     * mismatch in the data type of a field. 
     * @return a symbian OS error code.
     * @return KErrNone on successful operation.
     * @return KErrOverflow if the supplied descriptor is too short to contain the requested field.
     * @note This method must use the same data type as that assigned by @ref SetValue().
     */
	template <class TType>
		inline TInt GetValue(TPositionFieldId aFieldId, TType& aValue) const 
			{return PositionFieldManager::GetValue(aFieldId, aValue, *this);}

private:
    /**
     * private constructor. To be used within the class 
     */
	HPositionGenericInfo(TInt aDataBufferSize, TInt aMaxFields, 
		TUint aFieldIndexStartPoint, TUint aDataStartPoint, TBool aResetRequestedFields);
    /**
     * internal private method 
     */
	HPositionGenericInfo& operator=(const HPositionGenericInfo&);
    /**
     * internal private method 
     */
	HPositionGenericInfo(const HPositionGenericInfo&);

    /**
     * Helper method. For internal usage only 
     */
	TInt FindEmptyRequestedFieldOffset(TInt& aEmptyFieldOffset) const;

    /**
     * Helper method. For internal usage only 
     */
	inline TPositionFieldId* RequestedFieldPtr();
    /**
     * Helper method. For internal usage only 
     */
	inline const TPositionFieldId* RequestedFieldPtr() const;
    /**
     * Helper method. For internal usage only 
     */
	inline TPositionFieldIndex* FieldIndexPtr();
    /**
     * Helper method. For internal usage only 
     */
	inline const TPositionFieldIndex* FieldIndexPtr() const;

private:
	friend class TPositionFieldSetter;
	friend class TPositionFieldGetter;

	/**	Max number of requesable/returnable fields. */
	const TInt iMaxFields;

	/** Offset into iBuffer of the field index. */
	const TUint iFieldIndexStartPoint;

	/** Offset into iBuffer of the actual location data. */
	const TUint iDataStartPoint;

	/** Total size of the buffer */
	const TInt iTotalBufferSize;

	/** Start of the buffer. The heap cell allocated for an instance of this class
	has space for information up to iBuffer[iTotalBufferSize-1]*/
	TUint8 iBuffer[1];	//Must be at end of class
	};

#endif //__LBSPOSITIONINFO_H__
