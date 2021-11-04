/*
* ==============================================================================
*  Name        : RSenDocument.h
*  Part of     : Web Services Fragment Base
*  Description : Class extends RDocument, enabling handle counting
*  Version     : 1.0
*
*  Copyright © 2002-2006 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef R_SEN_DOCUMENT
#define R_SEN_DOCUMENT

#include <xmlengdocument.h>
#include <xmlengdomimplementation.h>

typedef struct
    {
    TInt* ipOpenDocuments;
    void* iInternal;
    RXmlEngDOMImplementation iDomImpl;
    } TSenDocumentData;

class RSenDocument : public RXmlEngDocument
    {
    public:

        // TODO: proper CreateL() method for 2nd phase construction.

        /**
         * Default constructor.
         *
         * 
         */
        /*inline RSenDocument():RDocument()
            {
            ipOpenDocuments = new (ELeave) TInt(1);
            }*/

        /**
        * Create new document.
        *
        * 
        */
        IMPORT_C static RSenDocument NewL();

        /**
        * Create new document and put it on cleanup stack.
        *
        * 
        */
        IMPORT_C static RSenDocument NewLC();

        /**
        * Create new document.
        *
        * 
        * @param aInternal Document pointer
        */
        IMPORT_C static RSenDocument NewL(void* aInternal);

        /**
        * Create new document and put it on cleanup stack.
        *
        * 
        * @param aInternal Document pointer
        */
        IMPORT_C static RSenDocument NewLC(void* aInternal);

        /**
        * Copies a RSenDocument.
        * Both the original and the copy must be separately closed.
        *
        * 
        * @return Copy of this RSenDocument
        */
        IMPORT_C RSenDocument Copy();
        
        /**
        * Closes a RSenDocument.
        *
        * You must close (or destroy) every RSenDocument you create using NewL or NewLC.
        * In other words, every call to RSenDocument::Copy(), RSenDocument::NewL() and
        * RSenDocument::NewLC() must be matched by a close or destroy.
        * Note: Also Destroy() method can be used to close RSenDocument.
        *
        * 
        * @see RSenDocument::Destroy()
        */        
        IMPORT_C void Close();
        
        /**
        * Closes a RSenDocument.
        *
        * You must destroy (or close) every RSenDocument you create using NewL or NewLC.
        * In other words, every call to RSenDocument::Copy(), RSenDocument::NewL() and
        * RSenDocument::NewLC() must be matched by a close or destroy.
        * Note: Also Close() method can be used to destroy RSenDocument.
        *
        * 
        * @see RSenDocument::Close()
        */        
        IMPORT_C void Destroy();
        
        /**
        * Sets the Tls
        *
        * @return KErrNone
        *		  KErrUnknown if the Tls is unknown
        *		  KErrAlreadyExists	if the Tls already exist.
        */
        IMPORT_C static TInt ManualXmlEngineTlsAttachL();

        /**
        * Frees the Tls
        *
        * @return KErrNone
        *		  KErrNotFound if the Tls is not found
        */
        IMPORT_C static TInt ManualXmlEngineTlsCleanup();

    public:
    	TSenDocumentData* ipData;
    };

// R_SEN_DOCUMENT
#endif

// End of File


