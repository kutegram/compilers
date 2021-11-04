// hal\inc\hal.h
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

#ifndef __HAL_H__
#define __HAL_H__

#include <e32def.h>
#include <hal_data.h>
#include <e32property.h>




/**
@publishedPartner


A set of static functions to get and set hardware attributes.

@see HALData
*/
class HAL : public HALData
	{
public:

    /**
    Synonyms for the attribute properties
    HALData::TAttributeProperty, and used in SEntry.
    */
	enum TEntryProperty
		{
		/**		
		When set, means that an attribute is meaningful on this device.
		*/
		EEntryValid=0x1,
		
		
		/**
		When set, means that an attribute is modifiable.
		*/
		EEntryDynamic=0x2,
		};

    
    /**
    Defines an entry in the array that is returned in a call to HAL::GetAll().
    */
	struct SEntry
		{
		/**
		The properties of the attribute.
		
		@see HAL::TEntryProperty
		*/
		TInt iProperties;
		
		/**
		The attribute value.
		
		@see HALData::TAttribute
		*/
		TInt iValue;
		};
public:
    /**
    Gets the value of the specified HAL attribute.

    @param aAttribute The HAL attribute.
    @param aValue      On successful return, contains the attribute value.

    @return  KErrNone, if successful;
             KErrNotSupported, if the attribute is not defined in the list
             of attributes, or is not meaningful for this device.
         
    @see HALData::TAttribute
    @see HALData::TAttributeProperty
    */
	IMPORT_C static TInt Get(TAttribute aAttribute, TInt& aValue);

	
	/**
    Sets the specified HAL attribute.

    @param aAttribute The HAL attribute.
    @param aValue      The attribute value.

    @return  KErrNone, if successful;
             KErrNotSupported, if the attribute is not defined in the list
             of attributes, or is not meaningful for this device, or is
             not settable.
         
    @see HALData::TAttribute
    @see HALData::TAttributeProperty

    @capability WriteDeviceData or other capability specified
    for individual attributes in TAttribute
    */
	IMPORT_C static TInt Set(TAttribute aAttribute, TInt aValue);


    /**
    Gets all HAL attributes, and their properties.

    For attributes that are not meaningful on this device, the attribute value
    and its associated property value are set to zero in the returned array.

    @param aNumEntries On successful return, contains the total number
                       of HAL attributes.
                       If the function returns KErrNoMemory, this value is set
                       to zero.
    @param aData       On successful return, contains a pointer to an array
                       of SEntry objects, each of which contains an attribute value
                       and its property value. Note that the property value is
                       defined by the HAL::TEntry synonym.
                       If the function returns KErrNoMemory, this pointer is set
                       to NULL.

    @return KErrNone, if succesful;
            KErrNoMemory, if there is insufficient memory. 
    */
	IMPORT_C static TInt GetAll(TInt& aNumEntries, SEntry*& aData);

	
    /**
    Gets the value of the specified HAL attribute.

    @param aDeviceNumber The device number. (eg: screen number)
    @param aAttribute The HAL attribute.
    @param aValue      On successful return, contains the attribute value.

    @return  KErrNone, if successful;
             KErrNotSupported, if the attribute is not defined in the list
             of attributes, or is not meaningful for this device.
         
    @see HALData::TAttribute
    @see HALData::TAttributeProperty
    */
	IMPORT_C static TInt Get(TInt aDeviceNumber, TAttribute aAttribute, TInt& aValue);
	
	
    /**
    Sets the specified HAL attribute.

    @param aDeviceNumber The device number. (eg: screen number)
    @param aAttribute The HAL attribute.
    @param aValue      The attribute value.

    @return  KErrNone, if successful;
             KErrNotSupported, if the attribute is not defined in the list
             of attributes, or is not meaningful for this device, or is
             not settable.
         
    @see HALData::TAttribute
    @see HALData::TAttributeProperty

    @capability WriteDeviceData or other capability specified
    for individual attributes in TAttribute
    */
	IMPORT_C static TInt Set(TInt aDeviceNumber, TAttribute aAttribute, TInt aValue);
	};


/**
@internalComponent
*/
static const TInt32 KUidHalPropertyKeyBase = 0x1020E306;

__ASSERT_COMPILE(HAL::ENumHalAttributes<256); // only 256 UIDs allocated for HAL property keys



#endif
