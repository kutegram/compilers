/*
* ==============================================================================
*  Name        : MProEngEngine.h
*  Part of     : Profiles Engine / Profiles Engine Wrapper
*  Interface   : SDK, Profiles Engine Wrapper
*  Description : 
*  Version     : 
*
*  Copyright � 3.12 Nokia Corporation.
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


#ifndef MPROENGENGINE_H
#define MPROENGENGINE_H

// INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class RFs;
class MProEngProfile;
class MProEngProfileNameArray;
class MProEngChangeObserverExt;

// CLASS DECLARATION

/**
*  Profile engine interface.
*  This class offers methods to get active profile, active profile ID,
*  profile names array and set active profile.
*  How to use:
*  @code
*  // Create profile engine by using Factory:
*  MProEngEngine* profileEngine = NewEngineL();
*
*  // Free resources with MProEngEngine::Release();
*  profileEngine->Release();
*  // or if you release resources in destructor:
*  if( iEngine )
*      {
*      iEngine->Release();
*      }
*
*  // If you put this class to CleanupStack then use void CleanupReleasePushL()
*     CleanupReleasePushL( *profileEngine );
*  @endcode
*
*  @lib ProfileEngine.lib 
*  @since 3.1
*/
class MProEngEngine
    {
    public:  // Destructor

        virtual ~MProEngEngine() {};

    public:

        /**
        * Free resources of MProEngEngine.
        * @since 3.1
        */
        virtual void Release() = 0;

        /**
        * Return active profile, ownership transferred.
        * @since 3.1
        * @return Instance of the MProfile
        */
        virtual MProEngProfile* ActiveProfileLC() = 0;

        /**
        * Return active profile, ownership transferred.
        * @since 3.1
        * @return Instance of the MProfile
        */
        virtual MProEngProfile* ActiveProfileL() = 0;

        /**
        * Return active profile ID or system error code.
        * @since 3.1
        * @return Active profile ID or system error code.
        */
        virtual TInt ActiveProfileId() = 0;

        /**
        * Return profile name array, ownership transferred.
        * @since 3.1
        * @return Instance of the profile name array
        */
        virtual MProEngProfileNameArray* ProfileNameArrayLC() = 0;

        /**
        * Set the active profile, if ID is incorrect then leave with
        * KErrNotFound. This method can be called only by processes having
        * WriteDeviceData capability.
        * @since 3.1
        * @param aId Profile ID
        */
        virtual void SetActiveProfileL( TInt aId ) = 0;

        /**
        * Return the settings of the profile with the given ID. The created
        * object is pushed in the cleanup stack and the ownership is
        * transferred. Leave with KErrNotFound if a profile with the given ID
        * can not be found.
        * @since 3.1
        * @param aId Profile ID
        * @return Instance of the MProEngProfile
        */
        virtual MProEngProfile* ProfileLC( TInt aId ) = 0;

        /**
        * Return the settings of the profile with the given ID, the ownership
        * of the created object is transferred. Leave with KErrNotFound if a
        * profile with the given ID can not be found.
        * @since 3.1
        * @param aId Profile ID
        * @return Instance of the MProEngProfile
        */
        virtual MProEngProfile* ProfileL( TInt aId ) = 0;

    private: // Extension interface

        /**
        * This member is internal and not intended for use.
        */
        virtual MProEngChangeObserverExt* Extension() { return NULL; }

    };

#endif      //  MPROENGENGINE_H

// End of File

