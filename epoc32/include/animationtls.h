// AnimationTls.h
//
// Copyright (c) Symbian Software Ltd. 2004-2005. All rights reserved.
//

#ifndef __ANIMATIONTLS_H__
#define __ANIMATIONTLS_H__

#include <e32base.h>

class CAnimationTicker;

/** This is a wrapper around the thread local storage, which simplifies its
use for obtaining a CAnimationTicker object that can be shared between
animations.  The object is reference counted, and only one will exist per
thread per DLL at any given time.

You do not need to instantiate an object of this type unless you are writing a
new animation type.  If you are writing a new animation type it is optional.

@see CAnimationTicker
@publishedAll
*/
NONSHARABLE_CLASS(CAnimationTls) : public CBase
	{
public:
	IMPORT_C static CAnimationTls* NewL();
	IMPORT_C void Close();
	IMPORT_C CAnimationTicker* Ticker();
protected:
	CAnimationTls();
	~CAnimationTls();
	IMPORT_C virtual void CAnimationTls_Reserved1();
	IMPORT_C virtual void CAnimationTls_Reserved2();
protected:
	/** A Reference count of the object */
	TInt iRefCount;
	/** This provides timing information for animators */
	CAnimationTicker* iTimer;
private:
	TInt iCAnimationTls_Reserved;
	};
	
// __ANIMATIONTLS_H__
#endif
