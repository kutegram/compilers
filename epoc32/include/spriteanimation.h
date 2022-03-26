// SpriteAnimation.h
//
// Copyright (c) Symbian Software Ltd. 2004-2005. All rights reserved.
//

#ifndef __SPRITEANIMATION_H__
#define __SPRITEANIMATION_H__

#include <animation.h>

#include <e32base.h>
#include <w32std.h>

#include <animationconfig.h>
#include <spriteanimationclient.h>

class CAnimationDataProvider;
class CCoeControl;
class CSpriteAnimationExt;

/**
Implementation of CAnimation for sprite based animations.

A sprite animation displays the image using a sprite, which is a server side
graphic object.  This is likely to be more efficient than a basic animation,
and requires slightly less work in the client application.  However, it also
provides less control over the actual rendering of the image.

A sprite animation must be associated with an RWindow.  However, no redraw
events will be generated for it by the animation, and the client application
does not need to take any action once the animation has started.  Holding the
animation when the sprite is not visible is handled automatically on the server
side.

@see CAnimationDataProvider
@publishedAll

*/
class CSpriteAnimation : public CAnimation, public MAnimationDataProviderObserver
	{
public:
	IMPORT_C static CSpriteAnimation* NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession& aWsSession, RWindow& aWindow, MAnimationObserver* aObserver = 0);
	IMPORT_C static CSpriteAnimation* NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession& aWsSession, RWindow& aWindow, const TDesC8& aDataType, MAnimationObserver* aObserver = 0);
	IMPORT_C static CSpriteAnimation* NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, MAnimationObserver* aObserver = NULL, const CCoeControl* aHost = NULL);
	IMPORT_C static CSpriteAnimation* NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, const TDesC8& aDataType, MAnimationObserver* aObserver = NULL, const CCoeControl* aHost = NULL);
	IMPORT_C ~CSpriteAnimation();
	IMPORT_C TSize Size() const;

	/** Provides an CSpriteAnimation DataProvider interface to the client application.
	@return iDataProvider A CAnimationDataProvider */
	inline CAnimationDataProvider* DataProvider() { return iDataProvider; }
	// From CAnimationBase:
	virtual void Start(const TAnimationConfig& aConfig);
	virtual void Stop();
	virtual void Pause();
	virtual void Resume();
	virtual void Hold();
	virtual void Unhold();
	virtual void SetPosition(const TPoint& aPoint);
	virtual void Freeze();
	virtual void Unfreeze();	
public:
	IMPORT_C virtual void SetHostL(const CCoeControl* aHost);
		
protected:
	CSpriteAnimation();
	CSpriteAnimation(CAnimationDataProvider* aDataProvider, RWsSession& aWsSession);
	CSpriteAnimation(CAnimationDataProvider* aDataProvider, MAnimationObserver* aObserver, const CCoeControl* aHost);
	void ConstructL(const TPoint& aPoint, RWindow& aWindow, const TDesC8& aDataType, MAnimationObserver* aObserver);
	virtual void CSpriteAnimation_Reserved2();
	void ConstructL(const TPoint& aPoint, const TDesC8& aDataType);
	void ConstructL();
private:
	CSpriteAnimation(const CSpriteAnimation&);	// no implementation
	CSpriteAnimation& operator=(const CSpriteAnimation&);			// no implementation
	void InitializeL();
	void Reset();
	// from MAnimationDataProviderObserver
	virtual void DataProviderEventL(TInt aEvent, TAny* aData, TInt aDataSize);

private:
	enum TFlags 
		{
		EAnimationInitialized = 0x1	// Is the animation initialized?
		};
private:
	CSpriteAnimationExt* iSpriteAnimationExt;
	MAnimationObserver* iObserver;
//note the following data member is accessed via an inline function!
	CAnimationDataProvider* iDataProvider;
	RWsSession* iWsSession;
	RWsSprite* iWsSprite;
	RAnimDll iAnimDll;
	RSpriteAnimationClient* iClient;
	const CCoeControl* iHost;
	TInt iFlags;
	};

#endif
