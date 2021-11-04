/*
* ==============================================================================
*  Name        : versioninfo.inl
*  Part of     : Common Services / Platform Environment
*  Interface   : SDK, Version Info API
*  Description : Interface for quering system version information.
*  Version     : %version: 1 %
*
*  Copyright © 2007 Nokia. All rights reserved.
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


// -----------------------------------------------------------------------------
// VersionInfo::TVersionBase::TVersionBase
// -----------------------------------------------------------------------------
//
inline VersionInfo::TVersionBase::TVersionBase( TInt aType ) :
        iType( aType )
    {
    }

// -----------------------------------------------------------------------------
// VersionInfo::TPlatformVersion::TPlatformVersion
// -----------------------------------------------------------------------------
//
inline VersionInfo::TPlatformVersion::TPlatformVersion() :
        TVersionBase( VersionInfo::EPlatformVersion )
    {
    }

// End of File
