/*
* ==============================================================================
*  Name        : EPos_CPosLmOperation.inl
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK/S60, Landmarks API
*  Description : Inline utility methods for CPosLmOperation class
*  Version     : %version: 2 % 
*
*  Copyright © 2005-2006 Nokia.  All rights reserved.
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
// ExecuteAndDeleteLD
//
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
inline void ExecuteAndDeleteLD(CPosLmOperation* aOperation)
    {
    CleanupStack::PushL(aOperation);
    aOperation->ExecuteL();
    CleanupStack::PopAndDestroy(aOperation);
    }


//  End of File
