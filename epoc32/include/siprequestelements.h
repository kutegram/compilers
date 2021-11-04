/*
* ==============================================================================
*  Name        : siprequestelements.h
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

#ifndef CSIPREQUESTELEMENTS_H
#define CSIPREQUESTELEMENTS_H

//  INCLUDES
#include <e32base.h>
#include <s32strm.h>
#include <stringpool.h>
#include <uri8.h>
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPMessageElements;
class CSIPFromHeader;
class CSIPToHeader;
class CSIPCSeqHeader;
class CURIContainer;

// CLASS DECLARATION

/**
*  @publishedAll
*  
*
*  Class provides functions for creation and manipulation of originator's and
*  recipient's addresses in a SIP request. It also provide functions for
*  manipulation of SIP method for unknown SIP requests.
*  
*/
class CSIPRequestElements : public CBase
    {
    public:  // Constructors and destructor      
        /**
        * Two-phased constructor.
        * If the URI is SIP URI, no SIP URI headers are allowed.
        * @pre aRemoteURi != 0
        * @param aRemoteUri Remote target URI that identifies a resource that
        *        the request is addressed to. The ownership is transferred.
        */
        IMPORT_C static CSIPRequestElements* NewL(CUri8* aRemoteUri);

        /**
        * Two-phased constructor.
        * If the URI is SIP URI, no SIP URI headers are allowed.
        * @pre aRemoteURi != 0
        * @param aRemoteUri Remote target URI that identifies a resource that
        *        the request is addressed to. The ownership is transferred.
        */
        IMPORT_C static CSIPRequestElements* NewLC(CUri8* aRemoteUri);

        /**
        * Destructor.
        */
        IMPORT_C ~CSIPRequestElements();

    public: // New functions
        /**
        * Sets/resets the recipient's To-header
        * To-header must not contain tag-parameter.
        * @pre aTo != 0
        * @param aTo a To-header to be set, the ownership is transferred.
        */
        IMPORT_C void SetToHeaderL(CSIPToHeader* aTo);
            
        /**
        * Gets the recipient's To-header 
        * @return To-header or a 0-pointer if not present. Ownership is not
        *   transferred.
        */
        IMPORT_C const CSIPToHeader* ToHeader() const;

        /**
        * Sets/resets the originator's From-header.
        * From-header must not contain tag-parameter.
        * @pre aFrom != 0
         * @param aFrom a From-header to be set, the ownership is transferred.
        * @leave KErrArgument if aFrom == 0 
        */
        IMPORT_C void SetFromHeaderL(CSIPFromHeader* aFrom);
            
        /**
        * Gets the originator's From-header 
        * @return From-header or a 0-pointer if not present. Ownership is not
        *   transferred.
        */
        IMPORT_C const CSIPFromHeader* FromHeader() const;

        /**
        * Gets CSeq-header. Available for only incoming requests.
        * @return a CSeq-header or a 0-pointer if not present. 
        *         Ownership is not transferred.
        */        
        IMPORT_C const CSIPCSeqHeader* CSeqHeader() const;

        /**
        * Sets the remote URI.
        * If the URI is a SIP URI, no SIP URI headers are allowed.
        * @pre aRemoteUri != 0
         * @param aRemoteUri
        * @leave KErrArgument if aRemoteUri==0
        */
        IMPORT_C void SetRemoteUriL(CUri8* aRemoteUri);

        /**
        * Gets the remote target URI
        * @return remote target URI
        */
        IMPORT_C const CUri8& RemoteUri() const; 

        /**
        * Sets the SIP request method
        * @param aMethod a SIP method name.
        * @leave KErrArgument if method name given is syntactically
        *        incorrect
        */
        IMPORT_C void SetMethodL(RStringF aMethod);

        /**
        * Gets the SIP Method for a request
        * @return a SIP method name or a an empty string if the method
        *         is not defined
        */
        IMPORT_C RStringF Method() const;

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
        static CSIPRequestElements* InternalizeL (RReadStream& aReadStream);
        void ExternalizeL (RWriteStream& aWriteStream) const;

    private:
        CSIPRequestElements();
        void ConstructL(CUri8* aRemoteUri);
        void DoInternalizeL(RReadStream& aReadStream);

    private: // Data
        RStringF iMethod;
        CURIContainer* iRemoteURI;
        CSIPMessageElements* iMessageElements;

    private: // For testing purposes
        UNIT_TEST(CSIPRequestElementsTest)
    };

#endif
