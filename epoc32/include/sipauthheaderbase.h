/*
* =============================================================================
*  Name          : sipauthheaderbase.h
*  Part of       : SIP Codec
*  Description   : 
*  Version       : SIP/5.0 
*
*  Copyright (c) 2006 Nokia Corporation. 
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation. 
* =============================================================================
*/

#ifndef CSIPAUTHHEADERBASE_H
#define CSIPAUTHHEADERBASE_H

//  INCLUDES
#include "SipHeaderBase.h"
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPParamContainerBase;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* A base class for SIP Authorization-, Proxy-Authenticate-, 
* Proxy-Authorization- and WWW-Authenticate-headers
*
* 
*/
class CSIPAuthHeaderBase : public CSIPHeaderBase
	{
	public: // Constructors and destructor

		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CSIPAuthHeaderBase();


	public:	// New functions

		/**
		* @return the value of the auth-scheme
		*/
		IMPORT_C RStringF AuthScheme() const;

		/**
		* Checks if a parameter is present
		* @param aName the name of the parameter
		* @return ETrue if present, otherwise EFalse
		*/
		IMPORT_C TBool HasParam(RStringF aName) const;

		/**
		* Gets a parameter value
		* @pre HasParam(aName) == ETrue
		* @param aName the name of the parameter
		* @return the parameter value if present,
		*         otherwise a zero-length length value.
		*/
		IMPORT_C RStringF ParamValue(RStringF aName) const;

		/**
		* Gets a parameter value stored as a descriptor
		* @pre HasParam(aName) == ETrue
		* @param aName the name of the parameter
		* @return the parameter value if present,
		*         otherwise a zero-length length value.
		*/
		IMPORT_C const TDesC8& DesParamValue(RStringF aName) const;

		/**
		* Sets a parameter with a value. 
		* Takes copies of the name and value,
		* so if the RStringFs have been dynamically allocated,
		* they can be closed if necessary after the function returns.
		* @pre HasParam(aName) == EFalse
		* @param aName the name of the parameter
		* @param aValue the parameter value to set
		*/
		IMPORT_C void SetParamL(RStringF aName, RStringF aValue);

		/**
		* Sets a parameter with a value. 
		* Takes copies of the name 
		* so if the RStringF have been dynamically allocated,
		* they can be closed if necessary after the function returns.
		* Stores the parameter value as a descriptor, so that the 
		* case-sensitivity is not lost in RStringF-descriptor conversions. 
		* @pre HasParam(aName) == EFalse
		* @param aName the name of the parameter
		* @param aValue the parameter value to set
		*/
		IMPORT_C void SetDesParamL(RStringF aName, const TDesC8& aValue);

		/**
		* Sets a parameter with a value and adds double quotes 
		* as the first and the last character in the value.
		* Takes copy of the name,
		* so if the RStringF has been dynamically allocated,
		* it can be closed if necessary after the function returns.
		* @pre HasParam(aName) == EFalse
		* @param aName the name of the parameter
		* @param aValue the parameter value 
		*        to which the double quotes will be added
		*/
		IMPORT_C void SetParamAndAddQuotesL(RStringF aName,
			                                const TDesC8& aValue);

		/**
		* Deletes a parameter
		* @param aName the parameter name to delete
		*/
		IMPORT_C void DeleteParam(RStringF aName);


	public: // From CSIPHeaderBase

		/**
		* From CSIPHeaderBase ExternalizeSupported
		*/
		IMPORT_C virtual TBool ExternalizeSupported() const;


	public: // From CSIPHeaderBase, for internal use

		TBool EncodeMultipleToOneLine() const;
		TBool MoreThanOneAllowed() const;
		TPreferredPlace PreferredPlaceInMessage() const;
        virtual HBufC8* ToTextValueL() const;

	protected: // Constructors

		CSIPAuthHeaderBase();
		void ConstructL(RStringF aAuthScheme);

	protected: // New functions

		void SetAuthSchemeL(const TDesC8& aAuthScheme);
        void ParseL(const TDesC8& aValue);
        virtual const CSIPParamContainerBase& Params() const = 0;
        virtual CSIPParamContainerBase& Params() = 0;

	private: // Data

		RStringF iAuthScheme;
        TChar iSeparator;
	};

// CSIPAUTHHEADERBASE_H
#endif

// End of File
