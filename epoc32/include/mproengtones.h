/*
* ==============================================================================
*  Name        : MProEngTones.h
*  Part of     : Profiles Engine / Profiles Engine Wrapper
*  Interface   : SDK, Profiles Engine Wrapper
*  Description : Profile tones interface.
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


#ifndef MPROENGTONES_H
#define MPROENGTONES_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class MProEngTonesExt;

// CLASS DECLARATION

/**
*  Profile tones interface.
*  This interface offers methods to get line 1 and 2 ringing tone,
*  message alert tone, e-mail alert tone and video call alert tone.
*
*  @lib ProfileEngine.lib
*  @since 3.1
*/
class MProEngTones
    {
    protected:  // Destructor

        virtual ~MProEngTones() {};

    public:

        /**
        * Returns line 1 ringing tone file name.
        * @since 3.1
        * @return Returns line 1 ringing tone file name.
        */
        virtual const TDesC& RingingTone1() const = 0;

        /**
        * Returns line 2 ringing tone file name. If alternate line service
        * isn't supported by the network, this isn't used for anything.
        * @since 3.1
        * @return Returns line 2 ringing tone file name.
        */
        virtual const TDesC& RingingTone2() const = 0;

        /**
        * Returns message alert tone file name.
        * @since 3.1
        * @return Returns message alert tone file name.
        */
        virtual const TDesC& MessageAlertTone() const = 0;

        /**
        * Returns Email alert tone file name.
        * @since 3.1
        * @return Returns Email alert tone file name.
        */
        virtual const TDesC& EmailAlertTone() const = 0;

        /**
        * Returns Video call ringing tone file name.
        * @since 3.1
        * @return Returns Video call ringing tone file name.
        */
        virtual const TDesC& VideoCallRingingTone() const = 0;

        /**
        * Set line 1 ringing tone.
        * @since 3.1
        * @param aRingingTone File name of the ringing tone. If the ringing tone
        *        should be left empty, this should be KNullDesC.
        * @return KErrNone if succesful, KErrAccessDenied if line 1 ringing tone
        *         setting of this profile is read-only.
        */
        virtual TInt SetRingingTone1L( const TDesC& aRingingTone ) = 0;

        /**
        * Set line 2 ringing tone. Note, that this tone can be set even if the
        * network does not support the alternate line service. In this case, the
        * value of line 2 ringing tone is still saved in Profiles data but it
        * isn't used for anything.
        * @since 3.1
        * @param aRingingTone File name of the ringing tone. If the line 2
        *        ringing tone should be left empty, this should be KNullDesC.
        * @return KErrNone if succesful, KErrAccessDenied if line 2 ringing tone
        *         setting of this profile is read-only.
        */
        virtual TInt SetRingingTone2L( const TDesC& aRingingTone ) = 0;

        /**
        * Set message alert tone.
        * @since 3.1
        * @param aMessageAlertTone File name of the message alert tone. If the
        *        alert tone should be left empty, this should be KNullDesC.
        * @return KErrNone if succesful, KErrAccessDenied if message alert tone
        *         setting of this profile is read-only.
        */
        virtual TInt SetMessageAlertToneL(
            const TDesC& aMessageAlertTone ) = 0;

        /**
        * Set Email alert tone file name.
        * @since 3.1
        * @param aEmailAlertTone Email alert tone. If the alert tone should be
        *        be left empty, this should be KNullDesC.
        * @return KErrNone if succesful, KErrAccessDenied if e-mail alert tone
        *         setting of this profile is read-only.
        */
        virtual TInt SetEmailAlertToneL(
            const TDesC& aEmailAlertTone ) = 0;

        /**
        * Set Video call ringing tone file name.
        * @since 3.1
        * @param aRingingTone Video call ringing tone file name. If the alert
        *        tone should be left empty, this should be KNullDesC.
        * @return KErrNone if succesful, KErrAccessDenied if video call ringing
        *         tone setting of this profile is read-only.
        */
        virtual TInt SetVideoCallRingingToneL(
            const TDesC& aRingingTone ) = 0;

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MProEngTonesExt* Extension() { return NULL; }

    };

#endif      // MPROENGTONES_H

// End of File

