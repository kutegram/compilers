/*
* =============================================================================
*  Name        : sipallowheader.h
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


#ifndef CSIPALLOWHEADER_H
#define CSIPALLOWHEADER_H

//  INCLUDES
#include "siptokenheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting parameters 
* in SIP "Allow" header.
*
*  
*/
class CSIPAllowHeader : public CSIPTokenHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPAllowHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Allow"-header
		* @return an array containing one to many instances of CSIPAllowHeader
		*/
		IMPORT_C static RPointerArray<CSIPAllowHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPAllowHeader
		* @param aValue a value 
		* @return a new instance of CSIPAllowHeader
		*/
		IMPORT_C static CSIPAllowHeader* NewL(RStringF aValue);

		/**
		* Creates a new instance of CSIPAllowHeader and puts it to CleanupStack
		* @param aValue a value   
		* @return a new instance of CSIPAllowHeader
		*/
		IMPORT_C static CSIPAllowHeader* NewLC(RStringF aValue);

		/**
		* Destructor, deletes the resources of CSIPAllowHeader.
		*/
		IMPORT_C ~CSIPAllowHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPAllowHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPAllowHeader
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

		CSIPAllowHeader();
		CSIPAllowHeader(const CSIPAllowHeader& aHeader);
	};

// CSIPALLOWHEADER_H
#endif

// End of File
