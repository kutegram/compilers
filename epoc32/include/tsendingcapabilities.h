/*
* ==============================================================================
*  Name        : TSendingCapabilities.h
*  Part of     : SendUi
*  Description : Sending capabilities for sending services. Used by SendUi to
*                filter sending services from "Send" pop-up list query.
*  Version     : 1.0
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
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


#ifndef TSENDINGCAPABILITIES_H
#define TSENDINGCAPABILITIES_H

//  INCLUDES
#include <e32base.h>

// MACROS
#define KCapabilitiesForAllServices TSendingCapabilities::CapabilitiesForAllServices()

// CLASS DECLARATION

/**
*  Sending capabilities for sending services.
*  Used by SendUi to filter sending services from "Send" pop-up list query.
*
*  @lib CSendUi.lib
*  @since Series 60 3.0
*/
class TSendingCapabilities
    {
    public:

    enum TSendingFlags
        {
        EAllServices = 0,
        ESupportsAttachments = 1,
        ESupportsBodyText = 2,
        ESupportsBioSending = 4,
        ESupportsEditor = 8
        };

    public:  // Constructors and destructor

        /**
        * Default C++ constructor
        */
        IMPORT_C TSendingCapabilities();
        
        /**
        * C++ constructor
        * @param aBodySize Maximum body size.
        * @param aMessageSize Maximum whole message size (inc. attachments).
        * @param aFlags: TSendingFlags.
        */
        IMPORT_C TSendingCapabilities( 
            TInt aBodySize,
            TInt aMessageSize,
            TInt aFlags );
        
    public:  // New functions

        static inline TSendingCapabilities CapabilitiesForAllServices();

        /**
        * Overloaded equal operator.
        * @param aSendingCapabilities Sending capabilities to be compared
        * @return ETrue if equal, otherwise, EFalse
        */
        IMPORT_C TBool operator==(
            const TSendingCapabilities& aSendingCapabilities ) const;

        /**
        * Overloaded not equal operator.
        * @param aSendingCapabilities Sending capabilities to be compared
        * @return ETrue if not equal, otherwise, EFalse
        */
        IMPORT_C TBool operator!=(
            const TSendingCapabilities& aSendingCapabilities ) const;

    public:
        
        TInt iBodySize;
        TInt iMessageSize;
        TInt iFlags;
    };

#include "TSendingCapabilities.inl"

#endif      // TSENDINGCAPABILITIES_H  
            
// End of File

