/*
* =============================================================================
*  Name        : siprseqheader.h
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


#ifndef CSIPRSEQHEADER_H
#define CSIPRSEQHEADER_H

//  INCLUDES
#include "sipunsignedintheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class encapsulates a "RSeq"-header value.
*
*  
*/
class CSIPRSeqHeader : public CSIPUnsignedIntHeaderBase
    {
    public: // Constructors and destructor

        /**
        * Constructs a CSIPRSeqHeader from textual representation 
        * of the header's value part.
        * @param aValue a value part of a "RSeq"-header (e.g. "123")
        * @return a new instance of CSIPRSeqHeader
        */
        IMPORT_C static CSIPRSeqHeader* DecodeL(const TDesC8& aValue);
    
        /**
        * Constructor
        * @param aValue the value to set
        */
        IMPORT_C CSIPRSeqHeader(TUint aValue);
    
        /**
        * Destructor, deletes the resources of CSIPRSeqHeader.
        */
        IMPORT_C ~CSIPRSeqHeader();


    public: // New functions

        /**
        * Constructs an instance of a CSIPRSeqHeader from a RReadStream
        * @param aReadStream a stream containing the value of the
        *        externalized header object (header name not included).
        * @return an instance of a CSIPRSeqHeader
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

    public: // New functions, for internal use

        static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);

    private: // For testing purposes
    
        UNIT_TEST(CSIPRSeqHeaderTest)
    };

// CSIPRSEQHEADER_H
#endif

// End of File
