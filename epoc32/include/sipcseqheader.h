/*
* =============================================================================
*  Name        : sipcseqheader.h
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


#ifndef CSIPCSEQHEADER_H
#define CSIPCSEQHEADER_H

//  INCLUDES
#include "sipheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides functions for setting and getting sequence number and
* method in SIP "CSeq" header.
*
*  
*/
class CSIPCSeqHeader : public CSIPHeaderBase
	{
	public: // Constructors and destructor

		/**
		* Constructs a CSIPCSeqHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "CSeq"-header (e.g. "1 REGISTER")
		* @return a new instance of CSIPCSeqHeader.  
		*/
		IMPORT_C static CSIPCSeqHeader* DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPCSeqHeader
		* @param aSeq a sequence number to set.
		* @param aMethod a method to set. For example "REGISTER"
		* @return a new instance of CSIPCSeqHeader
		*/
		IMPORT_C static CSIPCSeqHeader* NewL(TUint aSeq, RStringF aMethod);

		/**
		* Creates a new instance of CSIPCSeqHeader and puts it to CleanupStack
		* @param aSeq a sequence number to set.
		* @param aMethod a method to set. For example "REGISTER"
		* @return a new instance of CSIPCSeqHeader
		*/
		IMPORT_C static CSIPCSeqHeader* NewLC(TUint aSeq, RStringF aMethod);

		/**
		* Destructor, deletes the resources of CSIPCSeqHeader.
		*/
		IMPORT_C ~CSIPCSeqHeader();


	public: // New functions

		/**
		* Gets the sequence number from the "CSeq" header
		* @return the current sequence number
		*/
		IMPORT_C TUint Seq() const;

		/**
		* Sets the sequence number in the "CSeq" header
		* @param aSeq a sequence number to set
		*/
		IMPORT_C void SetSeq(TUint aSeq);

		/**
		* Gets the method from the "CSeq" header
		* @return the method 
		*/
		IMPORT_C RStringF Method() const;

		/**
		* Sets the method in the "CSeq" header
		* @param aMethod a method to set
		*/
		IMPORT_C void SetMethodL(RStringF aMethod);

		/**
		* Constructs an instance of a CSIPCSeqHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*	     externalized object (header name not included). 
		* @return an instance of a CSIPCSeqHeader
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
		TPreferredPlace PreferredPlaceInMessage () const;

	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

	private: // From CSIPHeaderBase

		void ExternalizeValueL (RWriteStream& aWriteStream) const;

	private: // Constructors

		CSIPCSeqHeader();
		void ConstructL(TUint aCSeq, RStringF aMethod);
	
	private: // New functions
		
		void DoInternalizeValueL(RReadStream& aReadStream);
		void ParseL(const TDesC8& aValue);
		void SetMethodL(const TDesC8& aMethod);

	private: // Data

		TUint iSeq;
		RStringF iMethod;

	private: // For testing purposes
	
		UNIT_TEST(CSIPCSeqHeaderTest)
	};

// CSIPCSEQHEADER_H
#endif

// End of File
