/*
* ==============================================================================
*  Name        : AknControl.h
*  Part of     : Avkon
*  Interface   : Base Controls API
*  Description : Base class for all S60 UI framework UI controls.
*
*  Version     : 1
*
*  Copyright (c) 2005,2006 Nokia Corporation.
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
#ifndef AKN_CONTROL_H
#define AKN_CONTROL_H

// INCLUDES
#include <e32base.h>
#include <coecntrl.h>

// FORWARD DECLARATIONS

// CONSTANTS

// CLASS DEFINITIONS

/**
 * UI framework base class for all Avkon controls.
 *
 *  @lib avkon
 *  @since S60 3.0
 */
class CAknControl : public CCoeControl
    {
    public:
    /**
    * Constructor. 
    */
    IMPORT_C CAknControl();

    /**
     * Destructor
     */
    IMPORT_C ~CAknControl();
    
    private:
    /**
     * Virtual method provided to allow extensibility of virtual behaviour
     */
    IMPORT_C virtual void* ExtensionInterface( TUid aInterface );
    
    private:
    TInt iSpare[6];
    };

#endif // AKN_CONTROL_H
