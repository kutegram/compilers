/*
* =============================================================================
*  Name          : sipauthenticateheaderbase.h
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

#ifndef CSIPAUTHENTICATEHEADERBASE_H
#define CSIPAUTHENTICATEHEADERBASE_H

//  INCLUDES
#include "SipAuthHeaderBase.h"
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPAuthenticateHeaderParams;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* A base class for SIP Proxy-Authenticate- and WWW-Authenticate-headers
*
* 
*/
class CSIPAuthenticateHeaderBase : public CSIPAuthHeaderBase
	{
	public: // Constructors and destructor

		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CSIPAuthenticateHeaderBase();


	public: // New functions

		/**
		* Check whether a qop-value in qop-options is present. 
		* @param aQopValue the qop-value
		* @return ETrue if present, otherwise EFalse. 
		*/
		IMPORT_C TBool HasQopValueL(const TDesC8& aQopValue) const;

	public: // From CSIPHeaderBase

		/**
		* From CSIPHeaderBase ExternalizeSupported
		*/
		IMPORT_C virtual TBool ExternalizeSupported() const;
		
	protected: // Constructors

		CSIPAuthenticateHeaderBase();
		void ConstructL();
		void ConstructL(const CSIPAuthenticateHeaderBase& aHeader);

	protected: // From CSIPHeaderBase

		void ExternalizeValueL(RWriteStream& aWriteStream) const;

	protected: // From CSIPAuthBase

		const CSIPParamContainerBase& Params() const;
		CSIPParamContainerBase& Params();

	protected: // New functions

		void DoInternalizeValueL(RReadStream& aReadStream);

	protected: // Data

		CSIPAuthenticateHeaderParams* iParams;
	};

// CSIPAUTHENTICATEHEADERBASE_H
#endif

// End of File
