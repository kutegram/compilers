/*
* ==============================================================================
*  Name        : TSendingCapabilities.inl
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

// ============================ MEMBER FUNCTIONS ===============================

inline TSendingCapabilities TSendingCapabilities::CapabilitiesForAllServices()
    {
    TSendingCapabilities capabilities = 
        TSendingCapabilities( 0, 0, EAllServices );

    return capabilities;
    }
            
// End of File
