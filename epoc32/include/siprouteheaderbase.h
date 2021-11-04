/*
* =============================================================================
*  Name        : siprouteheaderbase.h
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


#ifndef CSIPROUTEHEADERBASE_H
#define CSIPROUTEHEADERBASE_H

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
* A base class for "Route"-, "Record-Route"- and "Service-Route"-headers.
*
*  
*/
class CSIPRouteHeaderBase : public CSIPParameterHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Destructor, deletes the resources of CSIPRouteHeaderBase.
		*/
		IMPORT_C virtual ~CSIPRouteHeaderBase();


	public:	// New functions
		
		/**
		* Sets the name-address
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred
		*/
		IMPORT_C void SetSIPAddressL(CSIPAddress* aSIPAddress);
	
		/**
		* Gets the name-address as const
		* @return name-address
		*/
		IMPORT_C const CSIPAddress& SIPAddress() const;

		/**
		* Gets the name-address
		* @return name-address
		*/
		IMPORT_C CSIPAddress& SIPAddress();


	public: // From CSIPHeaderBase, for internal use
	
		/**
		 * @internalComponent
		 */
		TBool MoreThanOneAllowed() const;
		
		/**
		 * @internalComponent
		 */
		TPreferredPlace PreferredPlaceInMessage() const;

	protected: // Contructors

		CSIPRouteHeaderBase();
		void ConstructL();
		void ConstructL(CSIPAddress* aSIPAddress);
		void ConstructL(const CSIPRouteHeaderBase& aRouteHeaderBase);

	protected: // Data

		/**
		 * @internalComponent
		 */
		CSIPAddress* iSIPAddress;
		
		/**
		 * @internalComponent
		 */
		CSIPHeaderGenericParams* iParams;

	private: // From CSIPParameterHeaderBase

		HBufC8* ToTextMandatoryPartLC() const;
		void ParseMandatoryPartL(const TDesC8& aMandatoryPart);
		const CSIPParamContainerBase& Params() const;
		CSIPParamContainerBase& Params();

	private: // For testing purposes
	
		UNIT_TEST(CSIPRouteHeaderBaseTest)
	};

// CSIPROUTEHEADERBASE_H
#endif

// End of File
