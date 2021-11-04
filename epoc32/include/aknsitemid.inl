/*
* ==============================================================================
*  Name        : AknsItemID.inl
*  Part of     : Avkon Skins / Skin Server
*  Description : ?Description
*  Version     : ?Version
*
*  Copyright © 2002 Nokia Corporation.
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

// INLINED MEMBERS
inline void TAknsItemID::Set( const TInt aMajor, const TInt aMinor )
    {
    iMajor = aMajor; iMinor = aMinor; 
    }

inline void TAknsItemID::Set( const TUid aMajor, const TInt aMinor )
    {
    iMajor = aMajor.iUid; iMinor = aMinor; 
    } //lint !e1746 TUid is a single word struct

inline void TAknsItemID::Set( const TAknsItemID& aID )
    {
    iMajor = aID.iMajor; iMinor = aID.iMinor;
    }

inline TBool operator==( const TAknsItemID& aFirst, const TAknsItemID& aSecond )
    { 
    return (aFirst.iMajor==aSecond.iMajor)&&(aFirst.iMinor==aSecond.iMinor); 
    }

inline TBool operator!=( const TAknsItemID& aFirst, const TAknsItemID& aSecond )
    { 
    return (aFirst.iMajor!=aSecond.iMajor)||(aFirst.iMinor!=aSecond.iMinor); 
    }

//  End of File  
