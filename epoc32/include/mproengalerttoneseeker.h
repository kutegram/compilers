/*
* ==============================================================================
*  Name        : MProEngAlertToneSeeker.h
*  Part of     : Profiles / Profiles Engine Wrapper
*  Interface   : SDK, Profiles Engine Wrapper
*  Description :
*  Version     :
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


#ifndef MPROENGALERTTONESEEKER_H
#define MPROENGALERTTONESEEKER_H

//  INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class MProEngAlertToneSeekerExt;
class MProEngAlertToneSeekerObserver;

// CLASS DECLARATION

/**
*  This class can be used to find media files suitable to be set as an alert
*  tone in Profiles.
*
*  @lib ProfileEngine.lib
*  @since Series 60 3.1
*/
class MProEngAlertToneSeeker
    {
    public: // New functions

        /**
        * Asynchronous method that searches all the tone files that can be used
        * as alert tones in Profiles. The resulting list of the tone paths is
        * delivered to the MProEngAlertToneSeekerObserver.
        * This is a very long lasting operation (~minutes), so this shouldn't
        * be performed too often.
        * @since S 60 3.1
        * @param aObserver Reference to the client-implemented observer which
        *        will get the list of tones after the list has been constructed.
        */
        virtual void FetchAlertToneListL(
                MProEngAlertToneSeekerObserver& aObserver ) = 0;

        /**
         * Cancels the asynchronous fetch operation.
         * @since S60 3.1
         */
        virtual void CancelFetch() = 0;

    public:

        /**
        * Destructor.
        */
        virtual ~MProEngAlertToneSeeker() {}

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MProEngAlertToneSeekerExt* Extension() { return NULL; }

    };

#endif      // MPROENGALERTTONESEEKER_H

// End of File

