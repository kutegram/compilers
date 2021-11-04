/*
* ============================================================================
*  Name     : CSatelliteInfoUI.h
*  Part of  : SatInfo.dll
*  Interface: Public
*  Description: Implements interface for SatelliteInfoUI.
*  Version:
*
*  Copyright (c) 2005 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing,  adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef __SATELLITE_INFO_UI_H__
#define __SATELLITE_INFO_UI_H__

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATION
class CSatellite;

// CLASS DECLARATION
/**
 * Implements entry point class to Satellite Info UI
 */
 
class CSatelliteInfoUI : public CBase
    {
    public:
    	/**
    	* Enumeration to specify the default launch view of the 
    	* dialog. 
    	*/
    	enum TSatelliteView
    		{
    	    /** Launch option for firmament view. Firmament view
    		  * displays all the satellites in view with the satellite's
    		  * number on a firmament.
    		  */
    		ESatelliteFirmamentView 		= 0x0001,
    	    /** Launch option for signal strength view. Signal strength
    	      * view displays all the satellite with their correspoinding
    	      * signal strength represented by bars.
    		  */
			ESatelliteSignalStrengthView	= 0x0002
			};
    		
    public:
        /**
         * Two-phased constructor.
         *
         * @return CSatelliteInfoUI object.
         */
        IMPORT_C static CSatelliteInfoUI* NewL();

        /**
         * Destructor.
         */
        IMPORT_C virtual ~CSatelliteInfoUI();

    private:
        /**
         * By default Symbian 2nd phase constructor is private.
         */
        void ConstructL();

        /**
         * C++ default constructor.
         */
        CSatelliteInfoUI();

    public: // new functions
        /**
         * Display satellite's information dialog.
         * 
         * This library uses the services provided by Location Framework.
         * Once the dialog is launched satellite information is continuously 
         * requested via Location Acquisition API. The Location Acquisition 
         * API is offered by Location Framework. The user can switch between the 
         * two views once the dialog is launched.
         *
         * @param aNameOfRule is requestor data for Location FW which will be used 
         * for privacy verification in the future. Application name should be 
         * used to specify the requestor. The string should not be empty.
         * @return TInt value of the selected softkey, which is EEikCommandTypeExitOrBack,
         * because it is the only softkey of the dialog.
         *
         * @leave KErrArgument if requestor data (aNameOfRule argument) length exceeds 
         * 255 characters or if it is empty. This function may also leave with any 
         * one of the standard error codes such as out of memory (e.g. KErrNoMemory)
         */
        IMPORT_C TInt ExecuteLD( const TDesC& aNameOfRule );

        /**
         * Dialog switched to foreground or background
         * @param aForeground ETrue to switch to the foreground. 
         * EFalse to switch to background.
         */
        IMPORT_C void HandleForegroundEventL(TBool aForeground);
        
        /**
        * Used to set the dialog's launch view
        * 
        * This method is used to set the view in which the dialog should
        * be launched. The two available views are signal strength and
        * firmament view. Constants for settings default view specified 
        * in enum #TSatelliteView. This method should be called before the 
        * method #ExecuteLD is invoked. 
        * 
        * @param aLaunchView ESatelliteFirmamentView for firmament view 
        * and ESatelliteSignalStrengthView for signal strength view.
        *
        * @panic EAknPanicOutOfRange if the method is invoked with an invalid parameter.
        * Values provided apart from those specified in #TSatelliteView are
        * invalid and will cause the method to panic.
        */
        IMPORT_C void SetLaunchView(TSatelliteView aLaunchView);

    private: //Data

        /// Own: A pointer to CSatellite. Contains the engine and
        /// the dialog implementation.
        CSatellite* iSatellite;

        /// Own: A pointer to TBool
        TBool* iDestroyedPtr;

    };

#endif // __SATELLITE_INFO_UI_H__

// End of File
