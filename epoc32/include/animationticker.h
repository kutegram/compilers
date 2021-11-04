// AnimationTicker.h
//
// Copyright (c) Symbian Software Ltd. 2004-2005. All rights reserved.
//

#ifndef __ANIMATIONTICKER_H__
#define __ANIMATIONTICKER_H__

#include <e32base.h>

class MAnimationTickee;

/** This provides timing information for animators.

You do not need to instantiate an object of this type unless you are writing a
new animation type.

@see MAnimationTickee
@see CAnimationTls
@publishedAll
*/
NONSHARABLE_CLASS(CAnimationTicker) : public CBase
	{
public:
    IMPORT_C static CAnimationTicker* NewL(TTimeIntervalMicroSeconds32 aTickLength = 100000);
    IMPORT_C ~CAnimationTicker();
    
	IMPORT_C TInt Add(MAnimationTickee* aTickee);
	IMPORT_C TInt Remove(MAnimationTickee* aTickee);
	IMPORT_C void Freeze();
	IMPORT_C void Unfreeze();
	
	/** This provides the resolution of the timer.
	@return iTickLength The resolution of the timer */
	inline const TTimeIntervalMicroSeconds32& TickLength() const { return iTickLength; }
	void OnTick();
protected:
	IMPORT_C virtual void CAnimationTicker_Reserved1();
	IMPORT_C virtual void CAnimationTicker_Reserved2();
private:
	TInt iCAnimationTicker_Reserved;
private:
	CAnimationTicker();
	void ConstructL(TTimeIntervalMicroSeconds32 aTickLength);
	void StartTickingL();
	void StopTicking();
private:
	TInt iFreeze;
	TTimeIntervalMicroSeconds32 iTickLength;
	CPeriodic* iPeriodic;
	RPointerArray<MAnimationTickee> iTickees;
	};

//__ANIMATIONTICKER_H__
#endif
