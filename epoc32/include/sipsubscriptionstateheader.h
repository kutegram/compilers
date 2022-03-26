/*
* =============================================================================
*  Name        : sipsubscriptionstateheader.h
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


#ifndef CSIPSUBSCRIPTIONSTATEHEADER_H
#define CSIPSUBSCRIPTIONSTATEHEADER_H

//  INCLUDES
#include "SipParameterHeaderBase.h"
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPSubscriptionStateHeaderParams;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting SIP "Subscription-State"
* header fields.
*
*  
*/
class CSIPSubscriptionStateHeader : public CSIPParameterHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPSubscriptionStateHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Subscription-State"-header
		* @return a new instance of CSIPSubscriptionStateHeader
		*/
		IMPORT_C static CSIPSubscriptionStateHeader* DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPSubscriptionStateHeader
		* @param aSubStateValue a substate-value value
		* @return a new instance of CSIPSubscriptionStateHeader
		*/
		IMPORT_C static CSIPSubscriptionStateHeader* 
			NewL(const TDesC8& aSubStateValue);

		/**
		* Creates a new instance of CSIPSubscriptionStateHeader 
		* and puts it to CleanupStack
		* @param aSubStateValue a substate-value value
		* @return a new instance of CSIPSubscriptionStateHeader
		*/
		IMPORT_C static CSIPSubscriptionStateHeader* 
			NewLC(const TDesC8& aSubStateValue);

		/**
		* Destructor, deletes the resources of CSIPSubscriptionStateHeader.
		*/
		IMPORT_C ~CSIPSubscriptionStateHeader();


	public: // New functions
	
		/**
		* Gets the substate-value parameter from the "Subscription-State" header
		* @return the substate-value parameter
		*/
		IMPORT_C const TDesC8& SubStateValue() const;

		/**
		* Sets the substate-value parameter in the "Subscription-State" header; 
		* @param aSubStateValue a substate-value parameter to set
		*/
		IMPORT_C void SetSubStateValueL(const TDesC8& aSubStateValue);

		/**
		* Gets the value of the "expires"-parameter
		* @return "expires"-parameter or KErrNotFound if not present
		*/
		IMPORT_C TInt ExpiresParameter() const;

		/**
		* Sets the "expires"-parameter
		* @pre aExpiresParam >= 0
		* @param aExpiresParam a "expires"-parameter value to set
		*/
		IMPORT_C void SetExpiresParameterL(TInt aExpiresParam);

		/**
		* Gets the value of the "retry-after"-parameter
		* @return "retry-after"-parameter or KErrNotFound if not present
		*/
		IMPORT_C TInt RetryAfterParameter() const;

		/**
		* Sets the "retry-after"-parameter
		* @pre aRetryAfterParam >= 0
		* @param aRetryAfterParam a "retry-after"-parameter value to set
		*/
		IMPORT_C void SetRetryAfterParameterL(TInt aRetryAfterParam);
	
		/**
		* Constructs an instance of a CSIPSubscriptionStateHeader 
		* from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPSubscriptionStateHeader
		*/
		IMPORT_C static CSIPHeaderBase* 
			InternalizeValueL(RReadStream& aReadStream);


	public: // From CSIPHeaderBase
		
		/**
		* From CSIPHeaderBase CloneL
		*/
		IMPORT_C CSIPHeaderBase* CloneL() const;

		/**
		* From CSIPHeaderBase Name
		*/
		IMPORT_C RStringF Name() const;


	public: // From CSIPHeaderBase, for internal use

		/**
		 * @internalComponent
		 */
		TPreferredPlace PreferredPlaceInMessage() const;
	
	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

	private: // From CSIPHeaderBase

		void ExternalizeValueL(RWriteStream& aWriteStream) const;

	private: // From CSIPParameterHeaderBase

		HBufC8* ToTextMandatoryPartLC() const;
		void ParseMandatoryPartL(const TDesC8& aMandatoryPart);
		const CSIPParamContainerBase& Params() const;
		CSIPParamContainerBase& Params();

	private: // Constructors

		CSIPSubscriptionStateHeader();
		void ConstructL();
		void ConstructL(const TDesC8& aSubStateValue);
        void ConstructL (const CSIPSubscriptionStateHeader&
            aSubscriptionStateHeader);
	
	private: // New functions 

		void DoInternalizeValueL(RReadStream& aReadStream);

	private: // Data

		HBufC8* iSubStateValue;
		CSIPSubscriptionStateHeaderParams* iParams;

	private: // For testing purposes
	
		UNIT_TEST(CSIPSubscriptionStateHeaderTest)
	};


// CSIPSUBSCRIPTIONSTATEHEADER_H
#endif

// End of File
