/*
* =============================================================================
*  Name        : sipextensionheader.h
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


#ifndef CSIPEXTENSIONHEADER_H
#define CSIPEXTENSIONHEADER_H

//  INCLUDES
#include "sipheaderbase.h"
#include "_sipcodecdefs.h"


// CLASS DECLARATION
/**
* @publishedAll
* 
*
* The class stores unknown and extension headers that are either not 
* supported by the current SIP codec implementation or not specified in
* current SIP RFC or both.
*
*  
*/
class CSIPExtensionHeader : public CSIPHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Creates a new instance of CSIPExtensionHeader
		* @param aName the full or compact name of the header
		* @param aValue the value of the header
		* @return a new instance of CSIPExtensionHeader
		*/
		IMPORT_C static CSIPExtensionHeader* 
			NewL(const TDesC8& aName, const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPExtensionHeader 
		* and puts it to CleanupStack
		* @param aName the full or compact name of the header
		* @param aValue the value of the header
		* @return a new instance of CSIPExtensionHeader
		*/
		IMPORT_C static CSIPExtensionHeader* 
			NewLC(const TDesC8& aName, const TDesC8& aValue);

		/**
		* Destructor, deletes the resources of CSIPExtensionHeader.
		*/
		IMPORT_C ~CSIPExtensionHeader();


	public: // New functions

		/**
		* Sets the header value
		* @param aValue the header value to be set
		*/
		IMPORT_C void SetValueL(const TDesC8& aValue);

		/**
		* Gets the header value
		* @return the header value
		*/
		IMPORT_C const TDesC8& Value() const;

		/**
		* Constructs an instance of a CSIPExtensionHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized header object (header name not included).
		* @return an instance of a CSIPExtensionHeader
		*/

		IMPORT_C static CSIPExtensionHeader* 
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

		/**
		* From CSIPHeaderBase ExternalizeSupported
		*/
		IMPORT_C TBool ExternalizeSupported() const;


	public: // New functions, for internal use

		void SetNameL(const TDesC8& aName);

	public: // From CSIPHeaderBase, for internal use
	
		/**
		 * @internalComponent
		 */
		TBool IsExtensionHeader() const;
		
		/**
		 * @internalComponent
		 */
		TBool EncodeMultipleToOneLine() const;
		
		/**
		 * @internalComponent
		 */
		TBool MoreThanOneAllowed() const;
		
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

	private: // From CSIPHeaderBase

		void ExternalizeValueL(RWriteStream& aWriteStream) const;

	private: // Constructors

		CSIPExtensionHeader();
		void ConstructL(const TDesC8& aName, const TDesC8& aValue);
		void ConstructL(const CSIPExtensionHeader& aExtensionHeader);
		void DoInternalizeValueL(RReadStream& aReadStream);

	private: // New functions

		TBool CheckValue (const TDesC8& aValue);
	
	private: // Data

		// data
		RStringF iName;
		HBufC8* iValue;

	private: // For testing purposes
	
		UNIT_TEST(CSIPExtensionHeaderTest)
		UNIT_TEST(CSIPHeaderLookupTest)
	};

// CSIPEXTENSIONHEADER_H
#endif

// End of File
