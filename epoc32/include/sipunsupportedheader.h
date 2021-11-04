/*
* =============================================================================
*  Name        : sipunsupportedheader.h
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


#ifndef CSIPUNSUPPORTEDHEADER_H
#define CSIPUNSUPPORTEDHEADER_H

//  INCLUDES
#include "siptokenheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting SIP "Unsupported" header.
*
* 
*/
class CSIPUnsupportedHeader : public CSIPTokenHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPUnsupportedHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Unsupported"-header
		* @return an array containing 1..n instances of CSIPUnsupportedHeader 
		*/
		IMPORT_C static RPointerArray<CSIPUnsupportedHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPUnsupportedHeader
		* @param aValue a tag value 
		* @return a new instance of CSIPUnsupportedHeader
		*/
		IMPORT_C static CSIPUnsupportedHeader* NewL (RStringF aValue);

		/**
		* Creates a new instance of CSIPUnsupportedHeader 
		* and puts it to CleanupStack
		* @param aValue a tag value   
		* @return a new instance of CSIPUnsupportedHeader
		*/
		IMPORT_C static CSIPUnsupportedHeader* NewLC(RStringF aValue);

		/**
		* Destructor, deletes the resources of CSIPUnsupportedHeader.
		*/
		IMPORT_C ~CSIPUnsupportedHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPUnsupportedHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPUnsupportedHeader
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

	private: // Constructors

		CSIPUnsupportedHeader();
		CSIPUnsupportedHeader(const CSIPUnsupportedHeader& aHeader);
	};

// CSIPUNSUPPORTEDHEADER_H
#endif

// End of File
