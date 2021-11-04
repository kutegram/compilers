/*
* =============================================================================
*  Name        : siprefertoheader.h
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


#ifndef CSIPREFERTOHEADER_H
#define CSIPREFERTOHEADER_H

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
* "Refer-To" header.
*
*  
*/
class CSIPReferToHeader : public CSIPAddressHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPReferToHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Refer-To"-header 
		*        (e.g. "User <user@host>")
		* @return a new instance of CSIPReferToHeader   
		*/
		IMPORT_C static CSIPReferToHeader* DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPReferToHeader
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred.
		* @return a new instance of CSIPReferToHeader
		*/
		IMPORT_C static CSIPReferToHeader* NewL(CSIPAddress* aSIPAddress);

		/**
		* Creates a new instance of CSIPReferToHeader and puts it to CleanupStack
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred,
		* @return a new instance of CSIPReferToHeader
		*/
		IMPORT_C static CSIPReferToHeader* NewLC(CSIPAddress* aSIPAddress);

		/**
		* Destructor, deletes the resources of CSIPReferToHeader.
		*/
		IMPORT_C virtual ~CSIPReferToHeader();


	public: // New functions

		/**
		* Constructs an instance of a CSIPReferToHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPReferToHeader
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

		CSIPReferToHeader();

    private: // For testing purposes
	
		UNIT_TEST(CSIPReferToHeaderTest)
	};

// end of CSIPREFERTOHEADER_H
#endif

// End of File
