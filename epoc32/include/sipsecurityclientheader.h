/*
* =============================================================================
*  Name        : sipsecurityclientheader.h
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


#ifndef CSIPSECURITYCLIENTHEADER_H
#define CSIPSECURITYCLIENTHEADER_H

//  INCLUDES
#include "SipSecurityHeaderBase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting SIP "Security-Client"
* header fields.
*
*  
*/
class CSIPSecurityClientHeader : public CSIPSecurityHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPSecurityClientHeader from textual representation
		* of the header's value part.
		* @param aValue a value part of a "Security-Client"-header
		* @return an array containing 1..n instances of CSIPSecurityClientHeader
		*/
		IMPORT_C static RPointerArray<CSIPSecurityClientHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPSecurityClientHeader
		* @param aMechanism a Mechanism-Name parameter 
		*        in the "Security-Client" header
		* @return a new instance of CSIPSecurityClientHeader
		*/
		IMPORT_C static CSIPSecurityClientHeader* 
			NewL(const TDesC8& aMechanism);

		/**
		* Creates a new instance of CSIPSecurityClientHeader 
		* and puts it to CleanupStack
		* @param aMechanism a Mechanism-Name parameter 
		* in the "Security-Client" header
		* @return a new instance of CSIPSecurityClientHeader
		*/
		IMPORT_C static CSIPSecurityClientHeader* 
			NewLC(const TDesC8& aMechanism);

		/**
		* Destructor, deletes the resources of CSIPSecurityClientHeader.
		*/
		IMPORT_C ~CSIPSecurityClientHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPSecurityClientHeader 
		* from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPSecurityClientHeader
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


	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

	private: // New functions

		CSIPSecurityClientHeader() ;

	private: // For testing purposes
	
		UNIT_TEST(CSIPSecurityHeaderBaseTest)
    };

// CSIPSECURITYCLIENTHEADER_H
#endif

// End of File
