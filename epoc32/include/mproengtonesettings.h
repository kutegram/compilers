/*
* ==============================================================================
*  Name        : MProEngToneSettings.h
*  Part of     : Profiles Engine / Profiles Engine Wrapper
*  Interface   : SDK, Profiles Engine Wrapper
*  Description : Profile tone settings interface.
*  Version     :
*
*  Copyright © 3.12 Nokia Corporation.
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


#ifndef MPROENGTONESETTINGS_H
#define MPROENGTONESETTINGS_H

// INCLUDES
#include <e32std.h>
#include <profile.hrh>

// FORWARD DECLARATIONS
class MProEngToneSettingsExt;

// CLASS DECLARATION

/**
*  Profile tone settings interface.
*  This interface offers methods to set and get the following settings: ringing
*  type, keypad volume, ringing volume, vibrating alert, warning and game tones
*  and text-to-speech.
*
*  @lib ProfileEngine.lib
*  @since 3.1
*/
class MProEngToneSettings
    {
    protected:  // Destructor

        virtual ~MProEngToneSettings() {};

    public:

        /**
        * Returns the ringing type.
        * @since 3.1
        * @return Returns the ringing type.
        */
        virtual TProfileRingingType RingingType() const = 0;

        /**
        * Returns the keypad volume.
        * @since 3.1
        * @return Returns the keypad volume.
        */
        virtual TProfileKeypadVolume KeypadVolume() const = 0;

        /**
        * Returns the ringing volume.
        * @since 3.1
        * @return Returns the ringing volume.
        */
        virtual TProfileRingingVolume RingingVolume() const = 0;

        /**
        * Returns the state of vibrating alert setting.
        * @since 3.1
        * @return Returns the state of vibrating alert setting.
        */
        virtual TBool VibratingAlert() const = 0;

        /**
        * Returns the state of warning and game tones setting.
        * @since 3.1
        * @return Returns the state of warning and game tones setting.
        */
        virtual TBool WarningAndGameTones() const = 0;

        /**
        * Returns the state of text-to-speech setting.
        * @since 3.1
        * @return Returns the state of text-to-speech setting.
        */
        virtual TBool TextToSpeech() const = 0;

        /**
        * Sets the ringing type.
        * @since 3.1
        * @param aRingingType The new value for ringing type.
        * @return KErrNone if succesful, KErrAccessDenied if ringing type
        *         setting of this profile is read-only.
        */
        virtual TInt SetRingingType( TProfileRingingType aRingingType ) = 0;

        /**
        * Sets the keypad volume.
        * @since 3.1
        * @param aKeypadVolume The new value for keypad tones volume.
        * @return KErrNone if succesful, KErrAccessDenied if keypad tones
        *         setting of this profile is read-only.
        */
        virtual TInt SetKeypadVolume( TProfileKeypadVolume aKeypadVolume ) = 0;

        /**
        * Sets the ringing volume.
        * @since 3.1
        * @param aRingingVolume The new value for ringing volume.
        * @return KErrNone if succesful, KErrAccessDenied if ringing volume
        *         setting of this profile is read-only.
        */
        virtual TInt SetRingingVolume(
                TProfileRingingVolume aRingingVolume ) = 0;

        /**
        * Sets the state of vibrating alert setting.
        * @since 3.1
        * @param aVibratingAlert The new state for the vibrating alert setting.
        * @return KErrNone if succesful, KErrAccessDenied if vibrating alert
        *         setting of this profile is read-only.
        */
        virtual TInt SetVibratingAlert( TBool aVibratingAlert ) = 0;

        /**
        * Sets the state of warning and game tones setting.
        * @since 3.1
        * @param aWarningAndGameTones The new state for Warning and Game tones
        * setting.
        * @return KErrNone if succesful, KErrAccessDenied if warning and game
        *         tones setting of this profile is read-only.
        */
        virtual TInt SetWarningAndGameTones( TBool aWarningAndGameTones ) = 0;

        /**
        * Sets the state of text-to-speech setting.
        * @since 3.1
        * @param aTextToSpeech The new state for text-to-speech setting.
        * @return KErrNone if succesful, KErrAccessDenied if text-to-speech
        *         setting of this profile is read-only.
        */
        virtual TInt SetTextToSpeech( TBool aTextToSpeech ) = 0;

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MProEngToneSettingsExt* Extension() { return NULL; }

    };

#endif      // MPROENGTONESETTINGS_H

// End of File


