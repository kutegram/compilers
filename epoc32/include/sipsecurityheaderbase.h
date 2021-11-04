/*
* =============================================================================
*  Name        : sipsecurityheaderbase.h
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


#ifndef CSIPSECURITYHEADERBASE_H
#define CSIPSECURITYHEADERBASE_H

//  INCLUDES
#include "SipParameterHeaderBase.h"
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPSecurityHeaderBaseParams;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* A base class for Security-Client, Security-Server and Security-Verify.
*
*  
*/
class CSIPSecurityHeaderBase : public CSIPParameterHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Destructor, deletes the resources of CSIPSecurityHeaderBase.
		*/
		IMPORT_C virtual ~CSIPSecurityHeaderBase();

	public: // New functions

		/**
		* Gets the value of "q"-parameter
		* @return the "q"-parameter value, zero if not present 
		*/
		IMPORT_C TReal PreferenceParam() const;

		/**
		* Sets the "q"-parameter value
		* @param aPreferenceValue a "q"-parameter value to set
		*/
		IMPORT_C void SetPreferenceParamL(TReal aPreferenceValue);

		/**
		* Gets the Mechanism-Name from the Security header
		* @return a Mechanism-Name
		*/
		IMPORT_C const TDesC8& MechanismName() const;

		/**
		* Sets the Mechanism-Name in the Security header
		* @param aMechanismName a Mechanism-Name
		*/
		IMPORT_C void SetMechanismNameL(const TDesC8& aMechanismName);

	public: // From CSIPHeaderBase, for internal use

		/**
		 * @internalComponent
		 */
		TBool MoreThanOneAllowed() const;
		
		/**
		 * @internalComponent
		 */
		TPreferredPlace PreferredPlaceInMessage() const;

	protected: // Constructors

		CSIPSecurityHeaderBase();
		void ConstructL();
		void ConstructL(const TDesC8& aMechanismName);
		void ConstructL(const CSIPSecurityHeaderBase& aSecurityHeaderBase);
	
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

		HBufC8* iMechanismName;
		CSIPSecurityHeaderBaseParams* iParams;

	private: // For testing purposes
	
		UNIT_TEST(CSIPSecurityHeaderBaseTest)
	};

// CSIPSECURITYHEADERBASE_H
#endif

// End of File
