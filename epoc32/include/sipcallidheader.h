/*
* =============================================================================
*  Name          : sipcallidheader.h
*  Part of       : SIP Codec
*  Description   : 
*  Version       : SIP/4.0 
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


#ifndef CSIPCALLIDHEADER_H
#define CSIPCALLIDHEADER_H

//  INCLUDES
#include "sipheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class for a SIP Call-ID header.
*
* 
*/
class CSIPCallIDHeader : public CSIPHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPCallIDHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Call-ID"-header (e.g. "ab2x@zb7y")
		* @returns a new instance of CSIPCallIDHeader
		*/
		IMPORT_C static CSIPCallIDHeader* DecodeL(const TDesC8& aValue);

		/**
		* Destructor
		*/
		IMPORT_C ~CSIPCallIDHeader ();


	public: // New functions

		/**
		* Compares this instance to another "Call-ID" header object
		* @param aCallIDHeader a header to compare to
		* @returns ETrue if "Call-ID" headers are similar
		*/
		IMPORT_C TBool operator==(const CSIPCallIDHeader& aCallIDHeader);
		
		/**
		* Constructs an instance of a CSIPCallIDHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*	     externalized object (header name not included). 
		* @return an instance of a CSIPCallIDHeader
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

		/**
		* From CSIPHeaderBase ToTextValueL
		*/
		IMPORT_C HBufC8* ToTextValueL() const;
		

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

	private: // From CSIPHeaderBase

		void ExternalizeValueL (RWriteStream& aWriteStream) const;

	private: // Constructors

		CSIPCallIDHeader();

	private: // New functions

		void ParseL(const TDesC8& aValue);

	private: // Data

		HBufC8* iCallID;

	private: // For testing purposes
	
		UNIT_TEST(CSIPCallIDHeaderTest)
	};


// end of CSIPCALLIDHEADER_H
#endif

// End of File
