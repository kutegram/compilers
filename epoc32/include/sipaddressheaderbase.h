/*
* =============================================================================
*  Name        : sipaddressheaderbase.h
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


#ifndef CSIPADDRESSHEADERBASE_H
#define CSIPADDRESSHEADERBASE_H

//  INCLUDES
#include "SipParameterHeaderBase.h"
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPAddress;
class CSIPHeaderGenericParams;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* A base class for SIP headers having syntax
* ( name-addr/ addr-spec ) *(generic-param)
*
*  
*/
class CSIPAddressHeaderBase : public CSIPParameterHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Destructor, deletes the resources of CSIPAddressHeaderBase.
		*/
        IMPORT_C virtual ~CSIPAddressHeaderBase();


	public: // New functions

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


	protected: // Constructors

		CSIPAddressHeaderBase();
        void ConstructL();
		void ConstructL(CSIPAddress* aSIPAddress);
        void ConstructL(const CSIPAddressHeaderBase& aHeader);

	protected: // Data

		/**
		 * @internalComponent
		 */
		CSIPAddress* iSIPAddress;
		
		/**
		 * @internalComponent
		 */
		CSIPHeaderGenericParams* iParams;

	protected: // New functions

		void DoInternalizeValueL(RReadStream& aReadStream);

	protected: // From CSIPHeaderBase

		/**
		 * @internalComponent
		 */
		void ExternalizeValueL(RWriteStream& aWriteStream) const;

	private: // From CSIPParameterHeaderBase

		HBufC8* ToTextMandatoryPartLC() const;
		void ParseMandatoryPartL(const TDesC8& aMandatoryPart);
		const CSIPParamContainerBase& Params() const;
		CSIPParamContainerBase& Params();
	};

// end of CSIPADDRESSHEADERBASE_H
#endif

// End of File
