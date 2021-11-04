/*
* ==============================================================================
*  Name        : LbsRequestor.h
*  Part of     : Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Requestor classes
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

#ifndef __LBSREQUESTOR_H__
#define __LBSREQUESTOR_H__

#include <e32base.h>

// Forward declarations
class RReadStream;
class RWriteStream;


/**
 * This is the base class for the requestor information class.
 */
class CRequestorBase : public CBase
	{
public:
    /**
     * @typedef TRequestorType
     * @brief indicates the type of the requestor. It is one of the enumerated
     * values of CRequestorBase::_TRequestorType
     */
	typedef TInt TRequestorType;

    /** Requestor types */
	enum _TRequestorType
		{
		/** an unassigned value and should not be reported or used */
		ERequestorUnknown,
		/** 
		 * indicates that the request for location information originates from
		 * an application, network services or other entity. In particular, 
		 * the requestor is not a person.
		 */
		ERequestorService,
		/** 
		 * indicate that the request for location information originates from 
		 * a person.
		 */
		ERequestorContact
		};

    /**
     * @typedef TRequestorFormat
     * @brief indicates the format of the requestor. It is one of the enumerated
     * values of CRequestorBase::_TRequestorFormat
     */
	typedef TInt TRequestorFormat;

    /** Requestor formats */
	enum _TRequestorFormat
		{
		/** unassigned value and should not be reported or used */
		EFormatUnknown,
		/**
		 * Indicates that requestor data contains the textual name of an application. 
		 * Used only if the requestor type is ERequestorService
		 */
		EFormatApplication,
		/**
		 * Indicates that requestor data contains a telephone number. This 
		 * should be in the international format without spaces.
		 */
		EFormatTelephone,
		/** Indicates that requestor data contains an address in the URL format */
		EFormatUrl,
		/** Indicates that requestor data contains an email address in the standard format */
		EFormatMail
		};

    /**
     * Destructor for CRequestorBase.
     */
	IMPORT_C ~CRequestorBase();

    /**
     * Set the type, format and string fields for this requestor object.
     * - The type field indicates whether this requestor is a service 
     * or a contact. 
     * - The format field indicates whether the string is a telephone 
     * number, URL or email address. 
     * - The requestor string is the data of the requestor.
     * @param aType identifies the type of the requestor, a service or a contact.
     * @param aFormat identifies the format of the requestor.
     * @param[in] aData identifies the requestor string. The requestor string can 
     * be a telephone number, a URL etc.
     */
	IMPORT_C void SetRequestorL(TRequestorType aType,
	                            TRequestorFormat aFormat,
	                            const TDesC& aData);
    /**
     * Obtain the type, format and string fields of this requestor object.
     * - The type field indicates whether the requestor is a service 
     * or a contact. 
     * - The format field indicates whether the string is a telephone 
     * number, URL or email address. 
     * - The requestor string is the data of the requestor.
     * @param[out] aType will be set to the type of the requestor.
     * @param[out] aFormat will be set to the format of the requestor.
     * @param[out] aData will be set to point to the requestor string.
     */
	IMPORT_C void GetRequestor(TRequestorType& aType,
	                           TRequestorFormat& aFormat,
	                           TPtrC& aData) const;

    /**
     * Get the type field of the requestor. The type field indicates 
     * whether the requestor is a service or a contact.
     * @return the type of requestor, a service or a contact.
     */
	IMPORT_C TRequestorType RequestorType() const;

    /**
     * Get the format field of the requestor. The format field indicates 
     * whether the requestor string is a telephone number, URL or email address.
     * @return the format of data held in this requestor.
     */
	IMPORT_C TRequestorFormat RequestorFormat() const;

    /**
     * Get the requestor string field of this requestor. The requestor string is a
     * descriptor value.
     * @return the requestor string.
     */
	IMPORT_C TDesC& RequestorData() const;

    /**
     * Read and store the type, format and requestor string from a stream.
     * @param[in] aStream the stream from which the requestor information is read.
     */
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);

    /**
     * Write the type, format and requestor string of this requestor to a stream.
     * @param[out] aStream the stream to which the requestor information is written.
     */
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;

protected:
    /**
     * default constructor
     */
	IMPORT_C CRequestorBase();

    /**
     * symbian 2nd phase constructor
     */
	IMPORT_C void ConstructL(TRequestorType aType,
							 TRequestorFormat aFormat,
							 const TDesC& aData);
	// Reserved for future expansion - derived classes should see documentation
	// on how this is to be used.
	IMPORT_C virtual TAny* ExtendedInterface(TInt aFunctionNumber, TAny* aPtr1, TAny* aPtr2);

protected:
    /** The type of the requestor. One of the enumerated values of CRequestorBase::_TRequestorType */
	TRequestorType   iRequestorType;
    /** The format of the requestor. One of the enumerated values of CRequestorBase::_TRequestorFormat */
	TRequestorFormat iFormat;
private:
	/** This is owned by the CRequestor */
	HBufC* iData;
	/** Reserved data for future extension */
	TAny* iBaseReservedPtr;
	};


/**
 * Each instance of a CRequestor class is used to hold the identity of one
 * of the parties involved requesting the location. The class contains three
 * data fields that indicate:
 * - If the requesting party is a "service" or an actual person ("contact").
 * - A descriptor that contains the requestor string and
 * - A field that identifies the format of the requestor string. For example, the requestor
 *  may be a telephone number, URL or email address.
 */
class CRequestor : public CRequestorBase
	{
public:
    /**
     * Allocates and constructs a CRequestor object.
     * This construction method initializes the requestor type, format and 
     * string with the respective values in the arguments.
     *
     * The function is a non-leaving variation which returns NULL if there is 
     * insufficient memory.
     *
     * @param aType identifies the type of the requestor, a service or a contact.
     * @param aFormat identifies the format of the requestor string. The format field indicates 
     * whether the requestor string is a telephone number, URL or email address.
     * @param[in] aData identifies the requestor string. The requestor string can 
     * be a telephone number, a URL etc.
     * @return a newly created CRequestor object, or NULL.
     */
	IMPORT_C static CRequestor* New(TRequestorType aType,
	                                TRequestorFormat aFormat,
	                                const TDesC& aData);

    /**
     * Allocates and constructs a CRequestor object.
     * This construction method initializes the requestor type, format and 
     * string with the respective values in the arguments.
     *
     * The function leaves if there is insufficient memory.
     *
     * @param aType identifies the type of requestor, a service or a contact.
     * @param aFormat identifies the format of the requestor string. The format field indicates 
     * whether the requestor string is a telephone number, URL or email address.
     * @param[in] aData identifies the requestor string. The requestor string can 
     * be a telephone number, a URL etc.
     * @return a newly created CRequestor object.
     */
	IMPORT_C static CRequestor* NewL(TRequestorType aType,
	                                 TRequestorFormat aFormat,
	                                 const TDesC& aData);

    /**
     * Allocates and constructs a CRequestor object, and leaves
     * the object on the cleanup stack.
     * This construction method initializes the requestor type, format and 
     * string with the respective values in the arguments.
     *
     * The function leaves if there is insufficient memory.
     *
     * @param aType identifies the type of requestor, a service or a contact.
     * @param aFormat identifies the format of the requestor string. The format field indicates 
     * whether the requestor string is a telephone number, URL or email address.
     * @param[in] aData identifies the requestor string. The requestor string can 
     * be a telephone number, a URL etc.
     * @return a newly created CRequestor object.
     */
	IMPORT_C static CRequestor* NewLC(TRequestorType aType,
	                                  TRequestorFormat aFormat,
	                                  const TDesC& aData);

    /**
     * Allocates and constructs a CRequestor object.
     * This construction method initializes the requestor type, format and 
     * string with the respective values read from the read stream.
     *
     * The function leaves if there is insufficient memory.
     *
     * @param[in] aStream The stream that contains an externalized CRequestor 
     * object.
     * @return a newly created CRequestor object.
     */
	IMPORT_C static CRequestor* NewL(RReadStream& aStream);

    /**
     * Destructor for CRequestor.
     */
	~CRequestor();

private:
	CRequestor();
	};

/**
 * This class is used to hold a chain of requestors identifying the clients 
 * that are involved in requesting the location information of the terminal.
 * For example, if a remote party is requesting the location and this 
 * is routed through a local application. In this situation, the 
 * application should identify both itself and the remote party.
 *
 * Most standard applications will not use the RRequestorStack. Instead,
 * they will call the simpler RPositioner::SetRequestor() method to
 * identify themselves.
 *
 * @see RPointerArray
 */
class RRequestorStack : public RPointerArray<CRequestor>
	{
public:
    /**
     * Restores a collection of requestors from a stream.
     * @param[in] aStream The stream from which requestors are read.
     */
	IMPORT_C void InternalizeL(RReadStream& aStream);

    /**
     * Stores a collection of requestors to a stream.
     * @param[out] aStream The stream to which requestors are written.
     */
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
    /**
     * helper method. For internal usage only
     */
	static void CleanupResetAndDestroy(TAny* aArray);

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[8];
	};

#endif //__LBSREQUESTOR_H__
