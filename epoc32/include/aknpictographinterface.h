/*
* ==============================================================================
*  Name        : AknPictographInterface.h
*  Part of     : AknPictograph
*  Interface   : Pictograph API
*  Description : Pictograph interface instance.
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


#ifndef AKN_PICTOGRAPH_INTERFACE_H
#define AKN_PICTOGRAPH_INTERFACE_H

// INCLUDES
#include <e32base.h>

// CONSTANTS

// FORWARD DECLARATIONS

class MAknPictographDrawer;
class MAknPictographAnimatorCallBack;
class CCoeControl;

// CLASS DECLARATION

/**
* Pictograph interface.
*
*  @lib AknPictograph.lib
*  @since 2.6
*/
NONSHARABLE_CLASS(CAknPictographInterface) : public CBase
	{
    public:  // Constructors and destructor
        
        /**
        * Returns a pictograph interface instance if pictograph feature is
        * supported.
        *
        * If pictograph feature is not supported, this method returns NULL.
        *
        * @since 2.6
        * @param aParent Not used at the moment. Reserved for future use.
        * @param aCallBack callback for drawing pictograph animations.
        */
	    IMPORT_C static CAknPictographInterface* NewL(
            CCoeControl& aParent,
            MAknPictographAnimatorCallBack& aCallBack );
        
        /**
        * Destructor.
        */
        ~CAknPictographInterface();

    public: // New functions

        inline MAknPictographDrawer* Interface() const;

    private:

        /**
        * C++ default constructor.
        */
        CAknPictographInterface(); 

        /**
        * 2nd phase constructor.
        */
        void ConstructL( MAknPictographAnimatorCallBack& aCallBack );

    private:    // Data        

        /**
        * Handle to the polymorphic pictograph DLL.
        */
        RLibrary iLib;

        /**
        * Pictograph interface instance. Owned.
        */
        MAknPictographDrawer* iInterface;

    };

#include "AknPictographInterface.inl"

#endif      // AKN_PICTOGRAPH_INTERFACE_H
            
// End of File
