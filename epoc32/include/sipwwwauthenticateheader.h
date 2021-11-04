/*
* =============================================================================
*  Name          : sipwwwauthenticateheader.h
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

#ifndef CSIPWWWAUTHENTICATEHEADER_H
#define CSIPWWWAUTHENTICATEHEADER_H

//  INCLUDES
#include "sipauthenticateheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class for SIP WWW-Authenticate-header manipulation.
*
* 
*/
class CSIPWWWAuthenticateHeader : public CSIPAuthenticateHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPWWWAuthenticateHeader from textual representation
		* of the header's value part.
		* @param aValue a value part of a "WWW-Authenticate"-header 
		* @return a new instance of CSIPWWWAuthenticateHeader
		*/
		IMPORT_C static CSIPWWWAuthenticateHeader* 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPWWWAuthenticateHeader
		* @return a new instance of CSIPWWWAuthenticateHeader
		*/
		IMPORT_C static CSIPWWWAuthenticateHeader* 
			NewL(RStringF aAuthScheme);

		/**
		* Creates a new instance of CSIPWWWAuthenticateHeader
		* @return a new instance of CSIPWWWAuthenticateHeader
		*/
		IMPORT_C static CSIPWWWAuthenticateHeader* 
			NewLC(RStringF aAuthScheme);

		/**
		* Destructor
		*/
		IMPORT_C ~CSIPWWWAuthenticateHeader();

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

		CSIPWWWAuthenticateHeader();
	
    private: // For testing purposes
	
		UNIT_TEST(CSIPWWWAuthenticateHeaderTest)
	};

// CSIPWWWAUTHENTICATEHEADER_H
#endif

// End of File
