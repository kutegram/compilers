// COESNDPY.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2006. All rights reserved.
//

#ifndef __COESNDPY_H__
#define __COESNDPY_H__

#include <e32std.h>

class TBaSystemSoundType;
class CCoeSoundPlayerManager;


/** Utility class for simple sound playing.

Must be used in the same thread as an active UI Control Framework environment 
(CCoeEnv). 

This class plays the sound specified by a TBaSystemSoundType object. The 
caller can request the sound to be repeated, and the time between repeats. 
If the exact sound cannot be found on a particular device, a match only by 
category (first UID) is used. No sound will play if a match is not found.

@publishedAll
*/
class CoeSoundPlayer
	{
public:
	enum { ENoRepeat=1, ERepeatForever=KMaxTInt};
public:
	inline static void PlaySound(const TBaSystemSoundType& aType);
	inline static void PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,const TTimeIntervalMicroSeconds32& aGap);
	inline static void PlaySoundNow(const TBaSystemSoundType& aType);
	inline static void PlaySoundNow(const TBaSystemSoundType& aType,TInt aPlayCount,const TTimeIntervalMicroSeconds32& aGap);
	IMPORT_C static void CancelSound(const TBaSystemSoundType& aType);
private:
	IMPORT_C static void PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,
											TTimeIntervalMicroSeconds32 aGap,TBool aInterrupt);
	static CCoeSoundPlayerManager* ManagerL();
	};





/** Plays the specified sound. 

This function only interrupts another, currently playing, sound if the new 
sound has a higher priority than the currently playing sound. If you wish 
to interrupt any currently playing sound and play a new one, use PlaySoundNow() 
instead of PlaySound().

@param aType The sound to play.*/
inline void CoeSoundPlayer::PlaySound(const TBaSystemSoundType& aType)
	{CoeSoundPlayer::PlaySound(aType,ENoRepeat,TTimeIntervalMicroSeconds32(0),EFalse);}

/** Plays the specified sound for the specifed number of times with the specified 
interval. 

This function only interrupts another, currently playing, sound if the new sound 
has a higher priority than the current one. If you wish to interrupt 
any currently playing sound and play a new one, use PlaySoundNow() instead of PlaySound().

@param aType The sound to play. 
@param aPlayCount The number of times the sound is played.
@param aGap The interval in microseconds between each time the sound is played. */
inline void CoeSoundPlayer::PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,const TTimeIntervalMicroSeconds32& aGap)
	{CoeSoundPlayer::PlaySound(aType,aPlayCount,aGap,EFalse);}

/** Plays the specified sound, interrupting any other sound that is currently playing.

@param aType The sound to play. */
inline void CoeSoundPlayer::PlaySoundNow(const TBaSystemSoundType& aType)
	{CoeSoundPlayer::PlaySound(aType,ENoRepeat,TTimeIntervalMicroSeconds32(0),ETrue);}

/** Plays the specified sound the specifed number of times with the 
specified interval, interrupting any other sound that is currently playing.

@param aType The sound to play.
@param aPlayCount The number of times the sound is played.
@param aGap The interval in microseconds between each time the sound is played. */
inline void CoeSoundPlayer::PlaySoundNow(const TBaSystemSoundType& aType,TInt aPlayCount,const TTimeIntervalMicroSeconds32& aGap)
	{CoeSoundPlayer::PlaySound(aType,aPlayCount,aGap,ETrue);}

// __COESNDPY_H__
#endif
