/*
* =============================================================================
*  Name        : sippassociateduriheader.h
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


#ifndef CSIPPASSOCIATEDURIHEADER_H
#define CSIPPASSOCIATEDURIHEADER_H

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
* "P-Associated-URI" header.
*
*  
*/
class CSIPPAssociatedURIHeader : public CSIPAddressHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPPAssociatedURIHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "P-Associated-URI"-header 
		*        (e.g. "User <user@host>;param=value")
		* @return an array containing one to many instances 
        *         of CSIPPAssociatedURIHeader   
		*/
		IMPORT_C static RPointerArray<CSIPPAssociatedURIHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPPAssociatedURIHeader
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred.
		* @return a new instance of CSIPPAssociatedURIHeader
		*/
		IMPORT_C static CSIPPAssociatedURIHeader* 
            NewL(CSIPAddress* aSIPAddress);

		/**
		* Creates a new instance of CSIPPAssociatedURIHeader and 
        * puts it to CleanupStack
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred,
		* @return a new instance of CSIPPAssociatedURIHeader
		*/
		IMPORT_C static CSIPPAssociatedURIHeader* 
            NewLC(CSIPAddress* aSIPAddress);

		/**
		* Destructor, deletes the resources of CSIPPAssociatedURIHeader.
		*/
		IMPORT_C virtual ~CSIPPAssociatedURIHeader();


	public: // New functions

        /**
		* Constructs an instance of a CSIPPAssociatedURIHeader from 
        * a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPPAssociatedURIHeader
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
        
        /**
		 * @internalComponent
		 */
        TBool MoreThanOneAllowed() const;

	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

	private: // Constructors

		CSIPPAssociatedURIHeader();

    private: // For testing purposes

        UNIT_TEST(CSIPPAssociatedURIHeaderTest)
	};

// end of CSIPPASSOCIATEDURIHEADER_H
#endif

// End of File
