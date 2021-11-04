/*
* ==============================================================================
*  Name        : sipprofiletypeinfo.h
*  Part of     : SIP Profile Client
*  Interface   : SDK API, SIP Profile API
*  Description : The class provides a container for the profile type information
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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

#ifndef TSIPPROFILETYPEINFO_H
#define TSIPPROFILETYPEINFO_H

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
*  @publishedAll
*  
*
*  Container for the profile type information.
*
*  
*/
class TSIPProfileTypeInfo
    {
    public:

        /** Profile type name */
        typedef TBuf8<25> TSIPProfileName;

        /** Profile classes */
        enum TSIPProfileClass
            {
            /** Network compliant with IETF standards */
            EInternet,
            /** Network compliant with 3GPP standards */
            EIms,
            /** Other */
            EOther
            };

    public:  // data members

        /** Profile class */
        TSIPProfileClass iSIPProfileClass;

        /** Profile type name */
        TSIPProfileName iSIPProfileName;
    };

// TSIPPROFILETYPEINFO_H
#endif
