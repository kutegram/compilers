/*
* =============================================================================
*  Name        : AknSoundSystem.h
*  Part of     : Avkon
*
*  Description : This is an interface for controlling keysounds.
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

#if !defined(__AKNSOUNDSYSTEM_H__)
#define __AKNSOUNDSYSTEM_H__

// INCLUDES
#include <e32base.h>
#include <w32std.h>
#include <aknSoundInfo.h>


// CLASS DECLARATION
class CAknSoundPlayer;
class CAknKeySoundStack;

/**
*  This is an interface for controlling keysounds from Avkon.
*  Provides support for handling key sounds.
*  @since Series 60 0.9
*/
NONSHARABLE_CLASS(CAknKeySoundSystem) : public CBase
    {
public:
    /**
    * Base class default constructor.
    * @param aUid Application UID.
    * @return A pointer to a new @c CAknKeySoundSystem object.
    */
    IMPORT_C static CAknKeySoundSystem* NewL(TInt aUid);
    
    /**
    * Destructor.
    */
    IMPORT_C ~CAknKeySoundSystem();
    
    /**
    * Function reads resource data from resource file and push the context
    * to the server session. The most common Avkon resources in this case are
    * @c R_AVKON_DEFAULT_SOUND_LIST, @c R_AVKON_DEFAULT_SKEY_LIST and 
    * @c R_AVKON_SILENT_SKEY_LIST.
    * If a leave occurs the framework generates a Symbian Leave code.
    * @param aResourceId Avkon resource ID.
    */
    IMPORT_C void PushContextL(TInt aResourceId);
    
    /**
    * Pop the context from the server session object.
    */
    IMPORT_C void PopContext();
    
    /**
    * This function plays key event sounds.
    * @param aKeyEvent The scan code of the key that caused the event.
    */
    IMPORT_C void PlaySound(const TKeyEvent& aKeyEvent);
        
    /**
    * This function plays sounds by sound ID.
    * @param aSid Sound ID. These SID numbers are specified in Avkon 
    * enum @c TAvkonSystemSID.
    */
    IMPORT_C void PlaySound(TInt aSid);
    
    /**
    * Function reads resource data from resource file. And adds the
    * application sound info list to the server session.
    * If the leave occurs the framework generates a Symbian Leave code.
    * @param aResourceId Avkon resource ID.
    */
    IMPORT_C void AddAppSoundInfoListL(TInt aResourceId);
        
    /**
    * This function brings the sounds back to foreground. This function should
    * be called from @c HandleForegroundEventL(). @c HandleForegroundEventL() is 
    * implemented in @c CAknAppUi and it is reimplemented in @c CAknViewAppUi.
    */ 
    IMPORT_C void BringToForeground();

    /**
    * Stops playing the sound with given ID.
    * @param aSid Sound ID. Application defined SID's should be less than 1000.
    */
    IMPORT_C void StopSound(TInt aSid);

    /**
    * Locks context.
    */
    IMPORT_C void LockContext();

    /**
    * Releases context.
    */
    IMPORT_C void ReleaseContext();

    /**
    * Reads sound information from given Avkon sound ID.
    * @since Series 60 2.0
    * @param aAvkonSid ID for Avkon sound whose information is requested.
    * @param aInfo Sound information will be put in this structure.
    * @return @c KErrNone if succesful, @c KErrNotFound if requested 
    * sound ID is not found.
    */
    IMPORT_C TInt RequestSoundInfoL(TInt aAvkonSid, CAknSoundInfo& aInfo);

    /**
    * Returns top context id from the session.
    * 
    * @since 3.1
    * @return The resource id of the context that is at the top of the soundstack. 
    */
    IMPORT_C TInt TopContext();
    
public:    
    
    /**
    * Disables next matching key sound until next pointer up event
    * 
    * @since 5.0
    * @param aScanCode ScanCode of key which sound is disabled.
    */
    void DisableNextKeySound( TInt aScanCode );

private:
    CAknKeySoundSystem();
    void ConstructL(TInt aUid);
private:
    CAknSoundPlayer* iSoundPlayer;
    TInt iSpare;
    };

#endif // __AKNSOUNDSYSTEM_H__
