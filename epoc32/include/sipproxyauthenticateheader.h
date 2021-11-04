/*
* =============================================================================
*  Name          : sipproxyauthenticateheader.h
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

#ifndef CSIPPROXYAUTHENTICATEHEADER_H
#define CSIPPROXYAUTHENTICATEHEADER_H

//  INCLUDES
#include "sipauthenticateheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class for SIP Proxy-Authenticate-header manipulation.
*
* 
*/
class CSIPProxyAuthenticateHeader : public CSIPAuthenticateHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPProxyAuthenticateHeader from textual representation
		* of the header's value part.
		* @param aValue a value part of a "Proxy-Authenticate"-header 
		* @return a new instance of CSIPProxyAuthenticateHeader
		*/
		IMPORT_C static CSIPProxyAuthenticateHeader* 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPProxyAuthenticateHeader
		* @return a new instance of CSIPProxyAuthenticateHeader
		*/
		IMPORT_C static CSIPProxyAuthenticateHeader* 
			NewL(RStringF aAuthScheme);

		/**
		* Creates a new instance of CSIPProxyAuthenticateHeader
		* @return a new instance of CSIPProxyAuthenticateHeader
		*/
		IMPORT_C static CSIPProxyAuthenticateHeader* 
			NewLC(RStringF aAuthScheme);

		/**
		* Destructor
		*/
		IMPORT_C ~CSIPProxyAuthenticateHeader();

	public: // From CSIPHeaderBase

		/**
		* From CSIPHeaderBase CloneL
		*/
		IMPORT_C CSIPHeaderBase* CloneL() const;
		
		/**
		* From CSIPHeaderBase Name
		*/		
		IMPORT_C RStringF Name() const;


	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);
		static CSIPHeaderBase* InternalizeValueL(RReadStream& aReadStream);

	private: // Constructors

		CSIPProxyAuthenticateHeader();

    private: // For testing purposes

        UNIT_TEST(CSIPProxyAuthenticateHeaderTest)
	};

// CSIPPROXYAUTHENTICATEHEADER_H
#endif

// End of File
