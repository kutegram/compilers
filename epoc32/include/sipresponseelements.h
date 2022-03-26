/*
* ==============================================================================
*  Name        : sipresponseelements.h
*  Part of     : SIP Client
*  Interface   : SDK API, SIP API
*  Description : 
*  Version     : 1.0
*
*  Copyright (c) 2005 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef CSIPRESPONSEELEMENTS_H
#define CSIPRESPONSEELEMENTS_H

//  INCLUDES
#include <e32base.h>
#include <s32strm.h>
#include <stringpool.h>
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPMessageElements;
class CSIPFromHeader;
class CSIPToHeader;
class CSIPCSeqHeader;

// CLASS DECLARATION

/**
*  @publishedAll
*  
*
*  Class provides services for creating and manipulating SIP responses
*  This class is used for creating and manipulating SIP responses including
*  status code, reason phrase and optional elements such user headers,
*  content and its type.
*
*  
*/
class CSIPResponseElements : public CBase
	{
    public:  // Constructors and destructor       
	    /**
        * Two-phased constructor.
        * @pre aStatusCode > 100 && aStatusCode < 700
	    * @param aStatusCode a known SIP response status code. Cannot be 100.
		* @param aReasonPhrase a SIP response reason phrase.
        */
		IMPORT_C static CSIPResponseElements* NewL(TUint aStatusCode,
		                                           RStringF aReasonPhrase);
										
	    /**
        * Two-phased constructor.
        * @pre aStatusCode > 100 && aStatusCode < 700
	    * @param aStatusCode a known SIP response status code. Cannot be 100.
		* @param aReasonPhrase a SIP response reason phrase.
        */
		IMPORT_C static CSIPResponseElements* NewLC(TUint aStatusCode,
		                                            RStringF aReasonPhrase);
											
        /**
        * Destructor.
        */
		IMPORT_C ~CSIPResponseElements();

    public: // New functions
		/**
		* Sets a SIP Response extension status code. It is not possible to set
        * value 100.
        * @pre aStatusCode > 100 && aStatusCode < 700
		* @param aStatusCode extension status code
		* @leave KErrArgument if aStatusCode < 100 or aStatusCode >= 700
		*/
		IMPORT_C void SetStatusCodeL(TUint aStatusCode);

		/**
		* Gets the SIP Response status code
		* @return SIP Response status code
		*/
		IMPORT_C TUint StatusCode() const;

		/**
		* Sets a SIP Response Reason Phrase.
		* @param aReasonPhrase a SIP response reason phrase.
		*/
		IMPORT_C void SetReasonPhraseL(RStringF aReasonPhrase);
			
		/**
		* Gets a SIP Response Reason Phrase.
		* @return a SIP response reason phrase or an empty string if
        *   the reason phrase is not defined.
		*/
		IMPORT_C RStringF ReasonPhrase() const;

		/**
		* Gets the originator's From-header
		* @return a From-header or a 0-pointer if not present. Ownership is
        *   not transferred.
		*/
		IMPORT_C const CSIPFromHeader* FromHeader() const;

		/**
		* Gets the recipient's To-header
		* @return a To-header or a 0-pointer if not present. Ownership is
        *   not transferred.
		*/
		IMPORT_C const CSIPToHeader* ToHeader() const;

		/**
		* Gets CSeq-header
		* @return a CSeq-header or a 0-pointer if not present. Ownership is
        *   not transferred.
		*/		
		IMPORT_C const CSIPCSeqHeader* CSeqHeader() const;

		/**
		* Gets message elements (contains all SIP user headers and content)
		* @return message elements
		*/
		IMPORT_C const CSIPMessageElements& MessageElements() const;

		/**
		* Gets message elements (contains all SIP user headers and content)
		* The response elements can be populated with SIP user headers
		* and content using returned reference to the message elements.
		* @return message elements
		*/
		IMPORT_C CSIPMessageElements& MessageElements();

    public: // New functions, for internal use
        static CSIPResponseElements* InternalizeL (RReadStream& aReadStream);
        static CSIPResponseElements* InternalizeLC (RReadStream& aReadStream);
        void ExternalizeL (RWriteStream& aWriteStream) const;

    private:
	    CSIPResponseElements();
	    void ConstructL(TUint aStatusCode, RStringF aReasonPhrase);
	    void DoInternalizeL (RReadStream& aReadStream);

    private: // Data
	    TUint iStatusCode;
	    RStringF iReasonPhrase;
        CSIPMessageElements* iMessageElements;
	};

// end of CSIPRESPONSEELEMENTS_H
#endif
