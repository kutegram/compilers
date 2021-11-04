/*
* =============================================================================
*  Name        : sipsupportedheader.h
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


#ifndef CSIPSUPPORTEDHEADER_H
#define CSIPSUPPORTEDHEADER_H

//  INCLUDES
#include "siptokenheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting SIP "Supported" header.
*
* 
*/
class CSIPSupportedHeader : public CSIPTokenHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPSupportedHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Supported"-header
		* @return an array containing 1..n instances of CSIPSupportedHeader  
		*/
		IMPORT_C static RPointerArray<CSIPSupportedHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPSupportedHeader
		* @param aValue a tag value 
		* @return a new instance of CSIPSupportedHeader
		*/
		IMPORT_C static CSIPSupportedHeader* NewL(RStringF aValue);

		/**
		* Creates a new instance of CSIPSupportedHeader 
		* and puts it to CleanupStack
		* @param aValue a tag value   
		* @return a new instance of CSIPSupportedHeader
		*/
		IMPORT_C static CSIPSupportedHeader* NewLC(RStringF aValue);

		/**
		* Destructor, deletes the resources of CSIPSupportedHeader.
		*/
		IMPORT_C ~CSIPSupportedHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPSupportedHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPSupportedHeader
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
		TBool HasCompactName() const;
		
		/**
		 * @internalComponent
		 */
		RStringF CompactName() const;
		
		/**
		 * @internalComponent
		 */
		TPreferredPlace PreferredPlaceInMessage() const;

	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

	private: // New functions

		CSIPSupportedHeader();
		CSIPSupportedHeader(const CSIPSupportedHeader& aHeader);

	private: // For testing purposes
	
		UNIT_TEST(CSIPSupportedHeaderTest)
	};

// CSIPSUPPORTEDHEADER_H
#endif

// End of File
