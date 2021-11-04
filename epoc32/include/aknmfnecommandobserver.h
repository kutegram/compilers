/*
* ==============================================================================
*  Name        : AknMfneCommandObserver.h
*  Part of     : EikStd / MFNE
*  Interface   : ?Interface_category, ?Interface_name
*  Description : 
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


#ifndef __AKNMFNECOMMANDOBSERVER
#define __AKNMFNECOMMANDOBSERVER

#include <e32base.h>

// CLASS DECLARATION

/**
*  Interface for giving commands to MFNE editors from the owning controls.
*  This interface was added to forward touch command button events to MFNE
*  editors. The interface can be extended later by adding more commands to 
*  TMfneCommand enum if needed.
*
*  @lib eikctl.lib
*  @since Series 60 3.0
*/
class MAknMfneCommandObserver
    {
    public:
        
        /**
        * List of commands that can be given to MFNE editor with 
        * HandleMfneCommand() function
        */
        enum TMfneCommand
            {
            EMfneIncrementCurrentFieldValue,
            EMfneDecrementCurrentFieldValue
            };
        
        /**
        * Interface function allowing other classes to give commands to MFNE editors.
        * The commands are defined in TMfneCommand enum.
        *
        * @since Series 60 5.0
        * @param aCommand Command defined in TMfneCommand
        */
        virtual void HandleMfneCommandL(TInt aCommand) = 0;
    };

#endif      // __AKNMFNECOMMANDOBSERVER  
            
// End of File
