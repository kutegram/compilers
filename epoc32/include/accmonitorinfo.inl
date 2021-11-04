/*
* ============================================================================
*  Name        : AccMonitorInfo.inl
*  Part of     : Accessory Services / AccessoryMonitor
*  Description : Inline functions to access CAccMonitorInfo
*  Version     : %version: 1 %
*
*  Copyright © 2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.0
*/

// -----------------------------------------------------------------------------
// CAccMonitorInfo::Reset
// Other items commented in header.
// -----------------------------------------------------------------------------
//
inline void CAccMonitorInfo::Reset()
    {
    iAccCapabilityArray.Reset();
    iAccessoryDeviceType = 0;
    iAccessoryPhysicalConnection = 0;
    iDeviceAddress = 0;
    iAccessoryID = 0;
    iReserved1 = 0;
    iReserved2 = 0;
    }

// -----------------------------------------------------------------------------
// CAccMonitorInfo::AccDeviceType
// Other items commented in header.
// -----------------------------------------------------------------------------
//
inline TAccMonCapability CAccMonitorInfo::AccDeviceType() const 
    {
    return iAccessoryDeviceType;
    }

// -----------------------------------------------------------------------------
// CAccMonitorInfo::AccPhysicalConnection
// Other items commented in header.
// -----------------------------------------------------------------------------
//
inline TAccMonCapability CAccMonitorInfo::AccPhysicalConnection() const 
    {
    return iAccessoryPhysicalConnection;
    }

// -----------------------------------------------------------------------------
// CAccMonitorInfo::AccDeviceAddress
// Other items commented in header.
// -----------------------------------------------------------------------------
//
inline TUint64 CAccMonitorInfo::AccDeviceAddress() const 
    {
    return iDeviceAddress;
    }

// -----------------------------------------------------------------------------
// CAccMonitorInfo::AccCapabilityAtIndex
// Other items commented in header.
// -----------------------------------------------------------------------------
//
inline TAccMonCapability CAccMonitorInfo::AccCapabilityAtIndex( TInt aIndex ) const 
    {
    return iAccCapabilityArray[ aIndex ]; 
    }

// -----------------------------------------------------------------------------
// CAccMonitorInfo::Count
// Other items commented in header.
// -----------------------------------------------------------------------------
//
inline TInt CAccMonitorInfo::Count() const 
    {
    return iAccCapabilityArray.Count();
    }

// -----------------------------------------------------------------------------
// CAccMonitorInfo::Exists
// Other items commented in header.
// -----------------------------------------------------------------------------
//
inline TBool CAccMonitorInfo::Exists( TAccMonCapability aCapability ) const 
    {
    TBool retValue( ETrue );
    if( iAccCapabilityArray.Find( aCapability ) != KErrNotFound )
        { 
        retValue = ETrue;
        }
    else
        {
        retValue = EFalse;  
        }
    return retValue;
    }

//End of file
