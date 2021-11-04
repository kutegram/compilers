// AnimationGroup.h
//
// Copyright (c) 2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __AnimationGroup_H__
#define __AnimationGroup_H__

#include <animation.h>

class CAnimationTls;

/**
Handles groups of other animations.

When it is appropriate to have several animations starting and stopping
together, add them all to an animation group and control them through that.

In addition to making the code easier to both read and write, the animation
group handles synchronisation issues which can occur when issuing a sequence
of asynchronous requests.

Care must be taken to remove an animation from any groups it may have been
added to before deleting it.

@publishedAll

*/
class CAnimationGroup : public CAnimation
	{
public:
	static CAnimationGroup* NewL();
	~CAnimationGroup();
	IMPORT_C const RPointerArray<CAnimation>& Animations() const;
	IMPORT_C RPointerArray<CAnimation>& Animations();
	// From CAnimation
	virtual void Start(const TAnimationConfig& aConfig);
	virtual void Stop();
	virtual void Pause();
	virtual void Resume();
	virtual void Hold();
	virtual void Unhold();
	virtual void Freeze();
	virtual void Unfreeze();
	virtual void SetPosition(const TPoint& aPoint);
protected:
	IMPORT_C virtual void CAnimationGroup_Reserved1();
	IMPORT_C virtual void CAnimationGroup_Reserved2();
private:
	TInt iCAnimationGroup_Reserved;
private:
	CAnimationGroup();
	void ConstructL();
	CAnimationGroup(const CAnimationGroup&); // no implementation
	CAnimationGroup& operator=(const CAnimationGroup&);		 // no implementation
private:
	TInt iFreezeCount;
	CAnimationTls* iTls;
	RPointerArray<CAnimation> iAnimations;
	};

//__AnimationGroup_H__
#endif

