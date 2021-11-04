/*
* ==============================================================================
*  Name        : AknIconUtils.inl
*  Part of     : AknIcon
*  Interface   : AknIcon
*  Description : Inline file for AknIconUtils.h
*
*  Version     : 1
*
*  Copyright (c) 2002 Nokia Corporation.
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

inline TAknContentDimensions::TAknContentDimensions():
    iWidth(0),iHeight(0)
    {
    }

inline TAknContentDimensions::TAknContentDimensions(TReal32 aWidth, TReal32 aHeight):
    iWidth(aWidth),iHeight(aHeight)
    {
    }
  
inline void TAknContentDimensions::SetDimensions(TReal32 aWidth, TReal32 aHeight)
    {
    iWidth  = aWidth;
    iHeight = aHeight;
    }
    
inline void TAknContentDimensions::SetDimensions(const TSize& aDimensions)
    {
    iWidth  = aDimensions.iWidth;
    iHeight = aDimensions.iHeight;
    }
  
//  End of File
