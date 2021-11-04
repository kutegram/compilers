/*
* =============================================================================
*  Name        : siprequireheader.h
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


#ifndef CSIPREQUIREHEADER_H
#define CSIPREQUIREHEADER_H

//  INCLUDES
#include "siptokenheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting parameters in 
* SIP "Require" header.
*
*  
*/
class CSIPRequireHeader : public CSIPTokenHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPRequireHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Require"-header
		* @return an array containing 1..n instances of CSIPRequireHeader   
		*/
		IMPORT_C static RPointerArray<CSIPRequireHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPRequireHeader
		* @param aValue a tag value 
		* @return a new instance of CSIPRequireHeader
		*/
		IMPORT_C static CSIPRequireHeader* NewL(RStringF aValue);

		/**
		* Creates a new instance of CSIPRequireHeader 
		* and puts it to CleanupStack
		* @param aValue a tag value   
		* @return a new instance of CSIPRequireHeader 
		*/
		IMPORT_C static CSIPRequireHeader* NewLC(RStringF aValue);

		/**
		* Destructor, deletes the resources of CSIPRequireHeader.
		*/
		IMPORT_C ~CSIPRequireHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPRequireHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included).
		* @return an instance of a CSIPRequireHeader 
		*/
		IMPORT_C static CSIPHeaderBase* InternalizeValueL(RReadStream& aReadStream);


	public: // From CSIPHeaderBase

		/**
		* From CSIPHeaderBase CloneL
		*/
		IMPORT_C CSIPHeaderBase* CloneL() const;

		/**
		* From CSIPHeaderBase Name
		*/
		IMPORT_C RStringF Name() const;


	public: // From CSIPHeaderBase, For internal use
	
		/**
		 * @internalComponent
		 */
		TPreferredPlace PreferredPlaceInMessage() const;

	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

	private: // Constructors

		CSIPRequireHeader();
		CSIPRequireHeader(const CSIPRequireHeader& aHeader);		
	};

// end of CSIPREQUIREHEADER_H
#endif

// End of File
