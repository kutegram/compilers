/*
* =============================================================================
*  Name        : sipcontentencodingheader.h
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


#ifndef CSIPCONTENTENCODINGHEADER_H
#define CSIPCONTENTENCODINGHEADER_H

//  INCLUDES
#include "siptokenheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting parameters 
* in SIP "Content-Encoding" header.
*
*  
*/
class CSIPContentEncodingHeader : public CSIPTokenHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPContentEncodingHeader from textual representation
		* of the header's value part.
		* @param aValue a value part of a "Content-Encoding"-header
		* @return an array containing 1..n instances of 
		*         CSIPContentEncodingHeader
		*/
		IMPORT_C static RPointerArray<CSIPContentEncodingHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPContentEncodingHeader
		* @param aValue a content-coding value 
		* @return a new instance of CSIPContentEncodingHeader
		*/
		IMPORT_C static CSIPContentEncodingHeader* NewL(RStringF aValue);

		/**
		* Creates a new instance of CSIPContentEncodingHeader 
		* and puts it to CleanupStack
		* @param aValue a content-coding value
		* @return a new instance of CSIPContentEncodingHeader
		*/
		IMPORT_C static CSIPContentEncodingHeader* NewLC(RStringF aValue);

		/**
		* Destructor, deletes the resources of CSIPContentEncodingHeader.
		*/
		IMPORT_C ~CSIPContentEncodingHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPContentEncodingHeader 
		* from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included).
		* @return an instance of a CSIPContentEncodingHeader
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

	private: // Constructors

		CSIPContentEncodingHeader();
		CSIPContentEncodingHeader(const CSIPContentEncodingHeader& aHeader);
		};

// CSIPCONTENTENCODINGHEADER_H
#endif

// End of File
