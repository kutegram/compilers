/*
* ============================================================================
*  Name       : ScreensaverpluginIntDef.h
*  Part of    : Screensaver
*  Description: Defines screensaver plugin Ecom interface.
*  Version:
*
*  Copyright © 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
#ifndef SCREEN_SAVER_PLUGIN_INT_DEF_H
#define SCREEN_SAVER_PLUGIN_INT_DEF_H

//  INCLUDES
#include <e32base.h>
#include <Ecom\ImplementationInformation.h>
#include <Screensaverplugin.h>

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* This base class for screensaver ECom plugin implemenation. Every plugin module
* must inherit and implement this class. 
*/
class CScreensaverPluginInterfaceDefinition: public CBase,
                                             public MScreensaverPlugin
    {
    public:         
        /*
        * Function which instantiates an object of this type
        */
        inline static CScreensaverPluginInterfaceDefinition* NewL(TUid aImplementationUid);

        /*
        * Function which lists the currently available screensaver implementations
        *
        * * @param aImplInfoArray A reference to a client-owned array, which on return
        *                         is filled with interface implementation data.
        *                         Any existing data in the array is destroyed.
        */
        inline static void ListImplementationsL(RImplInfoPtrArray& aImplInfoArray);

		/**
		*  Virtual desctructor.
		*/
		inline virtual ~CScreensaverPluginInterfaceDefinition();

    private:
        /**
        *  Required attribute for the framework
        *  (An identifier used during destruction)
        */
        TUid iDtor_ID_Key;
    };

#include "ScreensaverpluginIntDef.inl"

#endif   // SCREEN_SAVER_PLUGIN_INT_DEF_H
// End of file.
