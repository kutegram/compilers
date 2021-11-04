/*
* =============================================================================
*  Name        : sipfromtoheaderbase.h
*  Part of     : SIP Codec
*  Interface   : SDK API, SIP Codec API
*  Description : 
*  Version     : SIP/4.0 
*
*  Copyright (c) 2004 Nokia Corporation. 
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


#ifndef CSIPFROMTOHEADERBASE_H
#define CSIPFROMTOHEADERBASE_H

//  INCLUDES
#include "SipParameterHeaderBase.h"
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPAddress;
class CSIPFromToHeaderParams;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting parameters in SIP "From"
* and "To" header.
*
* This is an abstract class and cannot be instantiated.
*
* 
*/
class CSIPFromToHeaderBase : public CSIPParameterHeaderBase
	{
	public: // Constructors and destructor

		/**
		* Destructor, deletes the resources of CSIPFromToHeaderBase.
		*/
		IMPORT_C virtual ~CSIPFromToHeaderBase();


	public: // New functions

		/**
		* Compares this instance to another "From" or "To" header object
		* @param aHeader a header to compare to
		* @return ETrue, if the objects are equal otherwise EFalse
		*/
		IMPORT_C TBool operator==(const CSIPFromToHeaderBase& aHeader) const;

		/**
		* Sets the name-address
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address to set, the ownership is transferred
		*/
		IMPORT_C void SetSIPAddressL(CSIPAddress* aSIPAddress);

		/**
		* Gets the name-address as const
		* @return name-address object
		*/
		IMPORT_C const CSIPAddress& SIPAddress() const;

		/**
		* Gets the name-address
		* @return name-address object
		*/
		IMPORT_C CSIPAddress& SIPAddress();


	public: // From CSIPHeaderBase, for internal use

		/**
		 * @internalComponent
		 */
		TBool HasCompactName() const;
		
		/**
		 * @internalComponent
		 */
		TPreferredPlace PreferredPlaceInMessage() const;

	protected: // Constructors

		CSIPFromToHeaderBase();
		void ConstructL();
		void ConstructL(CSIPAddress* aSIPAddress);
		void ConstructL(CSIPAddress* aSIPAddress, const TDesC8& aTag);
		void ConstructL(const CSIPFromToHeaderBase& aSIPFromToHeaderBase);

	protected: // New functions

		void DoInternalizeValueL(RReadStream& aReadStream);

	private: // From CSIPHeaderBase

		void ExternalizeValueL(RWriteStream& aWriteStream) const;

	private: // From CSIPParameterHeaderBase

		HBufC8* ToTextMandatoryPartLC() const;
		void ParseMandatoryPartL(const TDesC8& aMandatoryPart);
		const CSIPParamContainerBase& Params() const;
		CSIPParamContainerBase& Params();

	private: // Data

		CSIPAddress* iSIPAddress;
		CSIPFromToHeaderParams* iParams;

private: // For testing purposes
	
		UNIT_TEST(CSIPFromToHeaderTest)
	};


// CSIPFROMTOHEADERBASE_H
#endif

// End of File
