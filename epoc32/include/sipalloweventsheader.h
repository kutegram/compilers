/*
* =============================================================================
*  Name        : sipalloweventsheader.h
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


#ifndef CSIPALLOWEVENTSHEADER_H
#define CSIPALLOWEVENTSHEADER_H

//  INCLUDES
#include <badesca.h>
#include "sipheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting parameters in 
* SIP "Allow-Events" header.
*
*  
*/
class CSIPAllowEventsHeader : public CSIPHeaderBase
	{
	public: // Constructors and destructor
	
		/**
		* Constructs a CSIPAllowEventsHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Allow-Events"-header
		* @return An array containing one to many instances of 
		*         CSIPAllowEventsHeader  
		*/
		IMPORT_C static RPointerArray<CSIPAllowEventsHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPAllowEventsHeader
		* @param aEventPackage a Event-Package value
		* @return a new instance of CSIPAllowEventsHeader
		*/
		IMPORT_C static CSIPAllowEventsHeader* 
			NewL(const TDesC8& aEventPackage);

		/**
		* Creates a new instance of CSIPAllowEventsHeader and 
		* puts it to CleanupStack
		* @param aEventPackage a Event-Package value
		* @return a new instance of CSIPAllowEventsHeader
		*/
		IMPORT_C static CSIPAllowEventsHeader* NewLC(const TDesC8& aEventPackage);

		/**
		* Destructor. deletes the resources of CSIPAllowEventsHeader.
		*/
		IMPORT_C ~CSIPAllowEventsHeader();

	public: // New functions

		/**
		* Gets the Event-Package parameter from the "Allow-Events" header
		* @return the Event-Package parameter
		*/
		IMPORT_C const TDesC8& EventPackage() const;

		/**
		* Sets the Event-Package parameter in the "Allow-Events" header; 
		* @param aEventPackage a Event-Package parameter to set
		*/
		IMPORT_C void SetEventPackageL(const TDesC8& aEventPackage);

		/**
		* Sets the event templates overwriting all the existing ones.
		* @param aEventTemplates
		*/
		IMPORT_C void SetEventTemplatesL(const MDesC8Array& aEventTemplates);
	
		/**
		* Gets the event templates.
		* @return a reference to the currently set event templates.
		*/

		IMPORT_C const MDesC8Array& EventTemplates() const;

		/**
		* Constructs an instance of a CSIPAllowEventsHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
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


	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

	public: // From CSIPHeaderBase, for internal use 
	
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

	private: // Contructors

		CSIPAllowEventsHeader();
		void ConstructL();
		void ConstructL(const TDesC8& aEventPackage);
		void ConstructL (const CSIPAllowEventsHeader& aSIPAllowEventsHeader);

	private: // New functions

		void DoInternalizeValueL(RReadStream& aReadStream);
		void ParseL(const TDesC8& aValue);
		void CheckTemplateL(const TDesC8& aParam) const;
		// Needed for cleanup of a RPointerArray<HBufC8>:
		static void ResetAndDestroy(TAny* anArray);

	private: // Data

		HBufC8* iEventPackage;
		CDesC8ArraySeg* iEventTemplates;

	private: // For testing purposes
	
		UNIT_TEST(CSIPAllowEventsHeaderTest)
	};

// CSIPALLOWEVENTSHEADER_H
#endif

// End of File
