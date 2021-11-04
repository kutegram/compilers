/*
* =============================================================================
*  Name        : sipfromheader.h
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


#ifndef CSIPFROMHEADER_H
#define CSIPFROMHEADER_H

//  INCLUDES
#include "sipfromtoheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting SIP "From" header.
*
*  
*/
class CSIPFromHeader : public CSIPFromToHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPFromHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "From"-header (e.g. "<user@host>...")
		* @return a new instance of CSIPFromHeader    
		*/
		IMPORT_C static CSIPFromHeader* DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPFromHeader
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred.
		* @return a new instance of CSIPFromHeader
		*/
		IMPORT_C static CSIPFromHeader* NewL(CSIPAddress* aSIPAddress);

		/**
		* Creates a new instance of CSIPFromHeader and puts it to CleanupStack
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred,
		* @return a new instance of CSIPFromHeader
		*/
		IMPORT_C static CSIPFromHeader* NewLC(CSIPAddress* aSIPAddress);

		/**
		* Creates a deep-copy of a CSIPFromToHeaderBase
		* Note that this function can be used for creating a From-header
		* using an existing To-header.
		* @param aHeader CSIPFromToHeaderBase to be copied
		* @return a new instance of CSIPFromHeader
		*/
		IMPORT_C static CSIPFromHeader* 
			NewL(const CSIPFromToHeaderBase& aHeader);

		/**
		* Creates a deep-copy of a CSIPFromToHeaderBase and 
		* puts it to CleanupStack
		* Note that this function can be used for creating a From-header
		* using an existing To-header.
		* @param aHeader CSIPFromToHeaderBase to be copied
		* @return a new instance of CSIPFromHeader
		*/
		IMPORT_C static CSIPFromHeader* 
			NewLC(const CSIPFromToHeaderBase& aHeader);

		/**
		* Destructor, deletes the resources of CSIPFromHeader.
		*/
		IMPORT_C ~CSIPFromHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPFromHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPFromHeader
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
		RStringF CompactName() const;

	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

	private: // Constructors

		CSIPFromHeader();
	};

// CSIPFROMHEADER_H
#endif

// End of File
