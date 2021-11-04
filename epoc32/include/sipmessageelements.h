/*
* ==============================================================================
*  Name        : sipmessageelements.h
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

#ifndef CSIPMESSAGEELEMENTS_H
#define CSIPMESSAGEELEMENTS_H

// INCLUDES
#include <e32base.h>
#include <s32strm.h>
#include <stringpool.h>
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPHeaderBase;
class CSIPContentTypeHeader;
class CSIPFromHeader;
class CSIPToHeader;
class CSIPCSeqHeader;
class CSIPExtensionHeader;

// CLASS DECLARATION

/**
* @publishedAll
* 
*
* Class for creation and manipulation optional elements in a SIP message.
* 
* Class provides functions for setting and getting optional elements in a 
* SIP message. Optional elements include user SIP message headers, 
* content and content type.
* Following headers are not considered to be user SIP message headers and 
* cannot be set or retrieved using functions of this class: 
* "Authentication-Info", "Call-Id", "CSeq", "From" 
* "Max-Forwards", "Min-Expires", "Record-Route",
* "Security-Verify", "Service-Route", "To", "Via", "Security-Server" and
* "Proxy-Authorization".
*
*  
*/
class CSIPMessageElements : public CBase
	{
    public:  // Constructors and destructor    
	    /**
        * Two-phased constructor.
        */
		IMPORT_C static CSIPMessageElements* NewL();

	    /**
        * Two-phased constructor.
        */
		IMPORT_C static CSIPMessageElements* NewLC();

        /**
        * Destructor.
        */
		IMPORT_C ~CSIPMessageElements();

    public: //new functions
		/**
		* Sets an array of user headers i.e. headers that user is allowed
		* manipulate to a SIP message. An empty array resets the user headers.
		* Note that the Content-Type header must be set using SetContentL. 
		*
		* @param aHeaders an array of SIP headers.
        *        The ownership of objects in the array is transferred.
		*/
		IMPORT_C void SetUserHeadersL(RPointerArray<CSIPHeaderBase>& aHeaders);

		/**
		* Gets all user SIP headers this class contains
		* @return SIP headers. Ownership is not transferred.
		*/
		IMPORT_C const RPointerArray<CSIPHeaderBase>& UserHeaders() const;

		/**
		* Sets the SIP message content and its type.
		* A zero length content can be set by providing a pointer
		* to a zero length HBufC8 instance (the ownership is transferred).
		* @pre aContent != 0 && aContentType != 0
		* @param aContent the content of a SIP message,
		*        		  the ownership is transferred
		* @param aContentType the SIP message content type,
		*        			  the ownership is transferred
		* @leave KErrArgument if aContent == 0 or
		*						 aContentType == 0
		*/
		IMPORT_C void SetContentL(HBufC8* aContent,
							      CSIPContentTypeHeader* aContentType);

		/**
		* Gets the SIP message content
		* @return SIP message content. If content does not exist, an empty
        *   descriptor is returned.
		*/
		IMPORT_C const TDesC8& Content() const;

		/**
		* Gets the content type
		* @return Content-Type-header or a 0-pointer if not present; the ownership
        *         is not transferred.
		*/
		IMPORT_C const CSIPContentTypeHeader* ContentType() const;

		/*
		* Removes the SIP message content and destroys
        * Content-Type header as well.
		* @return SIP message content; the ownership is transferred.
		*/
		IMPORT_C HBufC8* ExtractContent();

    public: // New functions, for internal use

	    static CSIPMessageElements* InternalizeL(RReadStream& aReadStream);
    	void ExternalizeL(RWriteStream& aWriteStream) const;
        TInt UserHeaderCount(RStringF aName) const;
        const RPointerArray<CSIPHeaderBase> UserHeadersL(RStringF aName) const;
        TInt RemoveHeaders(RStringF aName);
        void DetachUserHeader(CSIPHeaderBase* aHeader);
	    void AddHeaderL(CSIPHeaderBase* aHeader);
        void SetToL(CSIPToHeader* aTo);
        const CSIPToHeader* To() const;
        void SetFromL (CSIPFromHeader* aFrom);
        const CSIPFromHeader* From() const;
        const CSIPCSeqHeader* CSeq() const;
        void SetContent(HBufC8* aContent);
        void DetachContent();

    private:

        CSIPMessageElements();
	    void ConstructL();
	    void DoInternalizeL(RReadStream& aReadStream);
	    void CheckUserHeaderL(const CSIPHeaderBase* aHeader) const;
        void ExternalizeUserHeadersL(RWriteStream& aWriteStream) const;
        void ExternalizeL(const CSIPExtensionHeader* aHeader,
                          RWriteStream& aWriteStream) const;

	private: // Data
	
	    RPointerArray<CSIPHeaderBase> iUserHeaders;
	    HBufC8* iContent;
        CSIPFromHeader* iFromHeader;
        CSIPToHeader* iToHeader;
        CSIPCSeqHeader* iCSeqHeader;
        CSIPContentTypeHeader* iContentTypeHeader;
        TBool iHeaderLookupOpen;

	private: // For testing purposes

	    UNIT_TEST(CSIPMessageElementsTest)
	};

#endif
