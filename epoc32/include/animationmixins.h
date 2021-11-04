// AnimationMixins.h
//
// Copyright (c) Symbian Software Ltd. 2004-2005. All rights reserved.
//

#ifndef __ANIMATIONMIXINS_H__
#define __ANIMATIONMIXINS_H__

#include <e32base.h>

/** Interface from a data provider to an animation

An animation which has a data provider receives information from it via this
interface.

You do not need to derive an implementation from this class unless you are
writing a new animation type.

@publishedAll 

@see CAnimationDataProvider
@see CAnimation
@see CAnimator*/
class MAnimationDataProviderObserver
	{
public:
	/** Receives an event from a data provider.
	@param aEvent The event code.
	@param aData Any data associated with the event. Can be NULL.
	@param aDataSize The size in bytes of the item pointed to by aData.*/
	virtual void DataProviderEventL(TInt aEvent, TAny* aData, TInt aDataSize) = 0;
protected:
	IMPORT_C virtual void MAnimationDataProviderObserver_Reserved1();
	IMPORT_C virtual void MAnimationDataProviderObserver_Reserved2();
	};

class CAnimationTicker;

/** Interface used by an animator to during the rendering process.

A class implementing this interface is provided to an animator by an animation.
It may or may not be the animation itself.

You do not need to derive an implementation from this class unless you are
writing a new animation type.

@publishedAll 

@see CAnimator*/
class MAnimationDrawer
	{
public:
	/** Called by the animator when it needs to draw a new frame */
	virtual void AnimatorDraw() = 0;
	/** Called by the animator when it is ready to begin running. 
	@param aSize The size of the smallest bounding rectangle that will be required to render the animation */
	virtual void AnimatorInitialisedL(const TSize& aSize) = 0;
	/** Called by the animator when it is no longer ready, usually in
	response to TAnimationEvent::EAnimationDataChanged */
	virtual void AnimatorResetL() = 0;
	/** Called by the animator plugin loading routine to determine the type
	of data for which an animator is required.
	@return An 8 bit descriptor containing the data type.*/
	virtual const TPtrC8 AnimatorDataType() const = 0;
	/** Called by the animator to obtain an AnimatorTicker, to which it will
	add itself whenever it is running.
	@return A reference to a CAnimationTicker.*/
	virtual CAnimationTicker& AnimatorTicker() = 0;
private:
	IMPORT_C virtual void MAnimationDrawer_Reserved1();
	IMPORT_C virtual void MAnimationDrawer_Reserved2();
	};

class CAnimation;

/** Interface used by an animation to report events to the client application.

An animation can inform the client application of particular events through this
mechanism.  Only errors are reported in this way in v9.1, but more events may
be added in future.

Use of this interface by the client application is optional.

@publishedAll 

@see CAnimation*/
class MAnimationObserver
	{
public:
	/** Represents generic events which can be sent to the observer. */
	enum TEvent
		{
		/** Indicates that an error has occurred in the data provider.
		For events of this type, aData is a pointer to a TInt error code. */
		EDataProviderError,
		/** Indicates that the animator initialised (and therefore knows it's size) */
		EAnimationInitialized=0x01,
		/** Any user defined animations introducing new events should use
		values greater than EReserved */
		EReserved=0xFFFF,
		};
public:
	/** Receives events from an animation.
	
	The receiver is not required to take any action atall in response to this
	call.  The receiver should not delete the animation whilst responding
	to this call.
	
	@param aSender A reference to the animation which sent the event.
	@param aEvent The event code.
	@param aData An event specific data item.*/
	virtual void AnimationEvent(CAnimation& aSender, TInt aEvent, TAny* aData) = 0;
protected:
	IMPORT_C virtual void MAnimationObserver_Reserved1();
	IMPORT_C virtual void MAnimationObserver_Reserved2();
	};

/** Interface used for receiving animation ticks.

Animators receive regular ticks, during which they perform any required processing.

You do not need to derive an implementation from this class unless you are writing
a new animator type.

@publishedAll 

@see CAnimator
@see CAnimationTicker*/
class MAnimationTickee
	{
public:
	/** This function is called regularly by any ticker to which the tickee
	has been added */
	virtual void Tick() = 0;
protected:
	IMPORT_C virtual void MAnimationTickee_Reserved1();
	IMPORT_C virtual void MAnimationTickee_Reserved2();
	};

/** Internal interface used by the ICL data loader to communicate with the
ICL data provider. Not intended for user derivation.
@internalComponent*/
class MICLAnimationDataLoaderObserver
	{
public:
	enum TDataLoaderEvent
		{
		EImagePartialConvert,
		EImageConvertComplete,
		};
public:	
	IMPORT_C virtual void DataLoaderEventL(TDataLoaderEvent aMessage, TInt aError) = 0;
	};

//__ANIMATIONMIXINS_H__
#endif
