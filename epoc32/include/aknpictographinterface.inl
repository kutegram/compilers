/*
* ==============================================================================
*  Name        : AknPictographInterface.inl
*  Part of     : AknPictograph
*  Description : 
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

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknPictographInterface::Interface()
// -----------------------------------------------------------------------------
//
inline MAknPictographDrawer* CAknPictographInterface::Interface() const
    {
    return iInterface;
    }   

//  End of File  
