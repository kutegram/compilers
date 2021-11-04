/*
* ==============================================================================
*  Name        : driveinfo.inl
*  Part of     : Common Services / Platform Environment
*  Interface   : SDK, Platform Environment API
*  Description : Interface for quering the drive information of the system.
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
// DriveInfo::TDriveArray::TDriveArray
// -----------------------------------------------------------------------------
//
inline DriveInfo::TDriveArray::TDriveArray()
    {
    }

// -----------------------------------------------------------------------------
// DriveInfo::TDriveArray::TDriveArray
// -----------------------------------------------------------------------------
//
inline DriveInfo::TDriveArray::TDriveArray( const TDriveList& aDriveList )
    {
    Set( aDriveList );
    }

// -----------------------------------------------------------------------------
// DriveInfo::TDriveArray::Reset
// -----------------------------------------------------------------------------
//
inline void DriveInfo::TDriveArray::Reset()
    {
    iArray.Zero();
    }

// -----------------------------------------------------------------------------
// DriveInfo::TDriveArray::Count
// -----------------------------------------------------------------------------
//
inline TInt DriveInfo::TDriveArray::Count() const
    {
    return iArray.Length();
    }

// -----------------------------------------------------------------------------
// DriveInfo::TDriveArray::operator[]
// -----------------------------------------------------------------------------
//
inline TDriveNumber DriveInfo::TDriveArray::operator[]( TInt aIndex ) const
    {
    return static_cast< TDriveNumber >( iArray[ aIndex ] );
    }

// End of File
