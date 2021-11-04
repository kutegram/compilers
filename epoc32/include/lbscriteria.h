/*
* ==============================================================================
*  Name        : LbsCriteria.h
*  Part of     : Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Criteria classes
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

#ifndef __LBSCRITERIA_H__
#define __LBSCRITERIA_H__

#include <LbsCommon.h>

/**
 * This class is used as part of the TPositionCriteria class to chose a
 * positioning module that will provide the desired quality of information.
 * It allows position-quality-metrics to be given priorities, enabling them
 * to be given preference in the decision.
 */
class TPositionSelectionOrder
	{
public:
	/**
	 * Specifies the priority of selection parameters.
	 */
	enum TOrder
		{
		EOrderDontCare   = 0,
		EOrderDefault    = 1,
		EOrderVeryLow    = 25,
		EOrderLow        = 50,
		EOrderFairlyLow  = 75,
		EOrderMedium     = 100,
		EOrderFairlyHigh = 125,
		EOrderHigh       = 150,
		EOrderVeryHigh   = 175
		};

	/**
	 * Specifies the quality of position metrics that can be prioritized.
	 */
	enum TField
		{
		EFieldTimeToFirstFix,
		EFieldTimeToNextFix,
		EFieldHorizontalAccuracy,
		EFieldVerticalAccuracy,
		EFieldCost,
		EFieldPower,
		EFieldNumFields,       // Do not use this value. Must appear after all other field values.
		EFieldLast = KMaxTInt8 // Do not use this value. Must appear at end.
		};

    /**
     * Default constructor for TPositionSelectionOrder.
     */
	IMPORT_C TPositionSelectionOrder();

    /**
     * Assigns a priority to the time to first fix when selecting a positioning
     * module.
     *
     * @param aOrder is the priority of the time to first fix when choosing a
     * positioning module.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt SetOrderTimeToFirstFix(TOrder aOrder);

    /**
     * Assigns a priority to the time to subsequent fixes when selecting a
     * positioning module.
     *
     * @param aOrder is the priority of the time to subsequent fixes when choosing
     * a positioning module.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt SetOrderTimeToNextFix(TOrder aOrder);

    /**
     * Assigns a priority to the horizontal accuracy when selecting a positioning
     * module.
     *
     * @param aOrder is the priority of horizontal accuracy when choosing a
     * positioning module.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt SetOrderHorizontalAccuracy(TOrder aOrder);

    /**
     * Assigns a priority to the vertical accuracy when selecting a positioning
     * module.
     *
     * @param aOrder is the priority of vertical accuracy when choosing a
     * positioning module.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt SetOrderVerticalAccuracy(TOrder aOrder);

    /**
     * Assigns a priority to the cost of a positioning technology when selecting
     * a positioning module.
     *
     * @param aOrder is the priority of cost when choosing a positioning module.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt SetOrderCostIndicator(TOrder aOrder);

    /**
     * Assigns a priority to the power consumption of a positioning technology
     * when selecting a positioning module.
     *
     * @param aOrder is the priority of power consumption when choosing a
     * positioning module.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt SetOrderPowerConsumption(TOrder aOrder);

    /**
     * Used to restore the default selection ordering.
     */
	IMPORT_C void ResetSelectionOrder();

    /**
     * Clear all values including defaults. This is useful if the application
     * wishes to specify its own priorities.
     */
	IMPORT_C void ClearSelectionOrder();

    /**
     * Not generally called by client applications. It retrieves the number of
     * selection parameters.
     *
     * @return the number of selection items.
     */
	IMPORT_C TUint NumSelectionItems() const;

    /**
     * Not generally called by client applications. It retrieves a particular
     * selection parameter.
     *
     * @param aIndex the index of a selection parameter
     * @param[out] aField is set, upon successful completion, to the field ID at
     * index aIndex.
     * @param[out] aOrder is set, upon successful completion, to the priority of the
     * field at index aIndex.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt GetSelectionItem(TUint aIndex,
	                               TField& aField,
	                               TOrder& aOrder) const;

protected:
	struct SItem
	/**
	 * Stores a field / priority pair.
	 */
		{
		/** A position quality metric identifier. */
		TField iField;
		/** The priority given to the iField position quality metric. */
		TOrder iOrder;
		};

protected:
	TInt AddItem(TField aField, TOrder aOrder);

protected:
	/** The number of selection items in the iItems array. */
	TUint iNumItems;
	/** Array of users position quality priorities. */
	SItem iItems[KPositionMaxSectionFields];
	};


// If the following line generates an error, too many fields have been added
// to the TPositionSelectionOrder::TOrder enumeration, some must be removed
// to maintain BC.
POSITION_COMPILE_TIME_ASSERT(TPositionSelectionOrder::EFieldNumFields <= KPositionMaxSectionFields);


/**
 * The base class for classes used to store position module selection
 * criteria information.
 */
class TPositionCriteriaBase : public TPositionClassTypeBase
	{
protected:
    /**
     * Default constructor
     */
	IMPORT_C TPositionCriteriaBase();
    /**
     * constructor with capabilities input.
     * @param aCapabilityMask a bitmask of values form the enumeration
     * TPositionModuleInfo::_TCapabilities that specifies the capabilites
     * requested by the client from the positioning module.
     */
	IMPORT_C TPositionCriteriaBase(TPositionModuleInfo::TCapabilities aCapabilityMask);

public:

    /**
     * Specifies mandatory additional capabilities of the positioning module used
     * to provide the application with position information.
     * @param aCapabilityMask is a bit mask of values from the enumeration
     * TPositionModuleInfo::_TCapabilities.
     */
	IMPORT_C void AddRequiredCapabilities(TPositionModuleInfo::TCapabilities aCapabilityMask);

    /**
     * Clears the mandatory additional capabilities of the positioning module used
     * to provide the application with position information.
     */
	IMPORT_C void ClearRequiredCapabilities();

    /**
     * Returns the current set of required criteria including the default.
     * @return the current set of required criteria including the default.
     */
	IMPORT_C TPositionModuleInfo::TCapabilities RequiredCapabilities() const;

    /**
     * Set the mandatory upper bound for the quality of information that
     * the application will accept.
     * @param[in] aPosQuality is the new required quality of positioning information.
     */
	IMPORT_C void SetRequiredQuality(const TPositionQuality& aPosQuality);

    /**
     * Get any currently specified quality limits.
     * @param[out] aPosQuality will be set to the required quality of positioning
     * information.
     */
	IMPORT_C void GetRequiredQuality(TPositionQuality& aPosQuality) const;

    /**
     * Sets the selection order to be used by the positioning server in
     * selecting a positioning module.
     * @param[in] aSelectionOrder is the new selection ordering to be used.
     */
	IMPORT_C void SetSelectionOrder(const TPositionSelectionOrder& aSelectionOrder); 

    /**
     * Retrieves the current selection order that will be used by the positioning
     * server in selecting a positioning module.
     * @param[out] aSelectionOrder will be set to the current selection ordering.
     */
	IMPORT_C void GetSelectionOrder(TPositionSelectionOrder& aSelectionOrder) const;

    /**
     * Used to restore the criteria to the default values. This includes the
     * required capabilities, quality of position information and selection
     * ordering details.
     */
	IMPORT_C void ResetCriteria();

    /**
     * Removes all criteria including the default values. This includes all
     * required capabilities, all quality of position information and all selection
     * ordering details. This is useful if horizontal position information is
     * not required by the application.
     */
	IMPORT_C void ClearCriteria();

protected:
	/** The capabilities a positioning module must have. */
	TPositionModuleInfo::TCapabilities iRequiredCaps;
	/** The quality required of a positioning module. */
	TPositionQuality iRequiredQuality;
	/** The priorities assigned to the various quality metrics. */
	TPositionSelectionOrder	iSelectionOrder;
	};


/**
 * The standard class criteria class for selecting a positioning module.
 */
class TPositionCriteria : public TPositionCriteriaBase
	{
public:

    /**
     * Default constructor for TPositionCriteria.
     */
	IMPORT_C TPositionCriteria();

    /**
     * Constructor for TPositionCriteria that specifies mandatory additional
     * capabilities of the positioning module used to provide the application with
     * position information.
     *
     * @param aCapabilityMask is a bit mask of values from the enumeration
     * TPositionModuleInfo::_TCapabilities. Defaults to TPositionModuleInfo::ECapabilityHorizontal.
     */
	IMPORT_C TPositionCriteria(TPositionModuleInfo::TCapabilities aCapabilityMask);

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[4];
	};

#endif // __LBSCRITERIA_H__
