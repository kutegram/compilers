//CommsDatUtils.h
//
// Copyright (c) Symbian Software Ltd. 2004.
//

/**
 * @file
 *
 * Utility functions to retrieve comms data for specific use-cases and present it in a particular way.
 *
 * @internalAll
 * 
 *
 *
 */
#ifndef __COMMSDATUTILS_H__
#define	__COMMSDATUTILS_H__

#include <cdbcols.h>
#include <dial.h>
#include <metadatabase.h>

class CCommsDatUtilImpl;
namespace CommsDatUtils

{

class CCommsDatUtils : public CBase
	{
	public :

		IMPORT_C static CCommsDatUtils* NewL();

		IMPORT_C ~CCommsDatUtils();

		//  Set `aDialString` to be the appropriate string based on the directory
		//	number, where the dial is being performed and the chargecard to use.
		//	`ResolvePhoneNumberL()` opens a comms database to perform the
		//	resolution
		IMPORT_C static void ResolvePhoneNumberL(TDesC& aNumber, TDes& aDialString, TParseMode aDialParseMode, TUint32 aLocationId, TUint32 aChargecardId);

		// Set `aDialString` to be the appropriate string based on the directory
		//	number, where the dial is being performed and the chargecard to use.
		IMPORT_C static void ResolvePhoneNumberFromDatabaseL(TDesC& aNumber, TDes& aDialString, TParseMode aDialParseMode, TUint32 aLocationId, TUint32 aChargecardId);

    	// Check access to database fields
	    IMPORT_C TInt CheckReadCapability( const TDesC& aField, const RMessagePtr2* aMessage );

	    IMPORT_C TInt CheckWriteCapability( const TDesC& aField, const RMessagePtr2* aMessage );

	private:
		CCommsDatUtils() {};
		void ConstructL();

	private :

		CCommsDatUtilImpl* iUtilsImpl;
	};


#ifndef SYMBIAN_NON_SEAMLESS_NETWORK_BEARER_MOBILITY
class NameLookUp
	{
	public:
		/** Looks up the field specified and supplies a descriptor matching the name.
		@param aElementId 	The field to look up.
		@param aFieldName 	returns a pointer to the HBufC containing the string.
		@param aDataType 	returns the data type of the found field.
		@return The reversed value. */
		IMPORT_C static TInt FieldNameLookup(CommsDat::TMDBElementId aElementId, HBufC*& aFieldName, TInt& aDataType );
	private:
		NameLookUp() {} // no construction since we are now private.
	};
// SYMBIAN_NON_SEAMLESS_NETWORK_BEARER_MOBILITY
#endif



} //end namespace CommsDat::utils


//__COMMSDATUTILS_H__
#endif
