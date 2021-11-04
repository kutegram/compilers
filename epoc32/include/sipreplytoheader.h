/*
* =============================================================================
*  Name        : sipreplytoheader.h
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


#ifndef CSIPREPLYTOHEADER_H
#define CSIPREPLYTOHEADER_H

//  INCLUDES
#include "SIPAddressHeaderBase.h"
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPAddress;
class CSIPHeaderGenericParams;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting parameters in SIP 
* "Reply-To" header.
*
*  
*/
class CSIPReplyToHeader : public CSIPAddressHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPReplyToHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Refer-To"-header 
		*        (e.g. "User <user@host>")
		* @return a new instance of CSIPReplyToHeader   
		*/
		IMPORT_C static CSIPReplyToHeader* DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPReplyToHeader
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred.
		* @return a new instance of CSIPReplyToHeader
		*/
		IMPORT_C static CSIPReplyToHeader* NewL(CSIPAddress* aSIPAddress);

		/**
		* Creates a new instance of CSIPReplyToHeader and puts it to CleanupStack
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred,
		* @return a new instance of CSIPReplyToHeader
		*/
		IMPORT_C static CSIPReplyToHeader* NewLC(CSIPAddress* aSIPAddress);

		/**
		* Destructor, deletes the resources of CSIPReplyToHeader.
		*/
		IMPORT_C virtual ~CSIPReplyToHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPReplyToHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPReplyToHeader
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

		CSIPReplyToHeader();

	private: // For testing purposes
	
		UNIT_TEST(CSIPReplyToHeaderTest)
	};

// end of CSIPREPLYTOHEADER_H
#endif

// End of File
