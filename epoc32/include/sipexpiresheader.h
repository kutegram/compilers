/*
* =============================================================================
*  Name        : sipexpiresheader.h
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


#ifndef CSIPEXPIRESHEADER_H
#define CSIPEXPIRESHEADER_H

//  INCLUDES
#include "sipunsignedintheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class encapsulates a "Expires" header value.
*
*  
*/
class CSIPExpiresHeader : public CSIPUnsignedIntHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPExpiresHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Expires"-header (e.g. "3600")
		* @return a new instance of CSIPExpiresHeader
		*/
		IMPORT_C static CSIPExpiresHeader* DecodeL(const TDesC8& aValue);
	
		/**
		* Constructor
		* @param aValue the value to set
		*/
		IMPORT_C CSIPExpiresHeader(TUint aValue);
	
		/**
		* Destructor, deletes the resources of CSIPExpiresHeader.
		*/
		IMPORT_C ~CSIPExpiresHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPExpiresHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized header object (header name not included).
		* @return an instance of a CSIPExpiresHeader
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

	private: // For testing purposes
	
		UNIT_TEST(CSIPExpiresHeaderTest)
	};

// CSIPEXPIRESHEADER_H
#endif

// End of File
