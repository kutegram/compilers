/*
* =============================================================================
*  Name        : sipcontenttypeheader.h
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


#ifndef CSIPCONTENTTYPEHEADER_H
#define CSIPCONTENTTYPEHEADER_H

//  INCLUDES
#include "SipParameterHeaderBase.h"
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPContentTypeHeaderParams;

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting media types and
* parameters in SIP "Content-Type" header.
*
*  
*/
class CSIPContentTypeHeader : public CSIPParameterHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPContentTypeHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Content-Type"-header
		* @return a new instance of CSIPContentTypeHeader
		*/
		IMPORT_C static CSIPContentTypeHeader* DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPContentTypeHeader
		* @param aMediaType a media type to set. For example "application"
		* @param aMediaSubtype a media subtype to set. For example "sdp"
		* @return a new instance of CSIPContentTypeHeader
		*/
		IMPORT_C static CSIPContentTypeHeader* 
			NewL(const TDesC8& aMediaType, const TDesC8& aMediaSubtype);

		/**
		* Creates a new instance of CSIPContentTypeHeader 
		* and puts it onto the cleanup stack
		* @param aMediaType a media type to set. For example "application"
		* @param aMediaSubtype a media subtype to set. For example "sdp"
		* @return a new instance of CSIPContentTypeHeader
		*/
		IMPORT_C static CSIPContentTypeHeader* 
			NewLC(const TDesC8& aMediaType, const TDesC8& aMediaSubtype);

		/**
		* Destructor, deletes the resources of CSIPContentTypeHeader.
		*/
		IMPORT_C ~CSIPContentTypeHeader();

	public: // New functions

		/**
		* Gets the media type from the "Content-Type" header
		* @return a media type
		*/
		IMPORT_C const TDesC8& MediaType() const;

		/**
		* Sets the media type in the "Content-Type" header
		* @param aMediaType a media type
		*/
		IMPORT_C void SetMediaTypeL(const TDesC8& aMediaType);

		/**
		* Gets the media subtype from the "Content-Type" header
		* @return a media subtype
		*/
		IMPORT_C const TDesC8& MediaSubtype() const;

		/**
		* Sets the media subtype in the "Content-Type" header
		* @param aMediaSubtype a media subtype
		*/
		IMPORT_C void SetMediaSubtypeL(const TDesC8& aMediaSubtype);

		/**
		* Constructs an instance of a CSIPContentTypeHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized header object (header name not included).
		* @return an instance of a CSIPContentTypeHeader
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

	private: // From CSIPHeaderBase

		void ExternalizeValueL(RWriteStream& aWriteStream) const;

	private: // CSIPParameterHeaderBase

		HBufC8* ToTextMandatoryPartLC() const;
		void ParseMandatoryPartL(const TDesC8& aMandatoryPart);
		const CSIPParamContainerBase& Params() const;
		CSIPParamContainerBase& Params();

	private: // Constructors

		CSIPContentTypeHeader();
		void ConstructL();
		void ConstructL(const TDesC8& aMediaType, const TDesC8& aMediaSubtype);
		void ConstructL(const CSIPContentTypeHeader& aContentTypeHeader);

	private: // New functions

		void DoInternalizeValueL(RReadStream& aReadStream);

	private: // Data

		HBufC8* iMediaType;
		HBufC8* iMediaSubtype;
		CSIPContentTypeHeaderParams* iParams;

	private: // For testing purposes
	
		UNIT_TEST(CSIPContentTypeHeaderTest)
	};

// CSIPCONTENTTYPEHEADER_H
#endif

// End of File
