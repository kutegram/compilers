// ICLAnimationDataProvider.h
//
// Copyright (c) 2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __ICLANIMATIONDATAPROVIDER_H__
#define __ICLANIMATIONDATAPROVIDER_H__

#include <animationdataprovider.h>

#include <e32std.h>
#include <animationframe.h>
#include <animationmixins.h>

_LIT8(KBitmapAnimationDataType, "bitmap");

class CICLAnimationDataLoader;

/**
Data provider for frame based animations.

This data provider expects to be provided with a file which can be interpreted
as an animation using the Image Conversion Library (ICL).  An example would be
an animated GIF.  The default data type for this provider is "bitmap".

@see CBitmapAnimator
@publishedAll

*/
class CICLAnimationDataProvider : public CAnimationDataProvider, public MICLAnimationDataLoaderObserver
	{
public:
    IMPORT_C CICLAnimationDataProvider();
    IMPORT_C ~CICLAnimationDataProvider();
    IMPORT_C void SetFileL(RFs & aFs, const TFileName& aFileName);
    IMPORT_C TPtrC8 DataType();
    virtual void StartL();
protected:
	IMPORT_C virtual void CICLAnimationDataProvider_Reserved1();
	IMPORT_C virtual void CICLAnimationDataProvider_Reserved2();
	// From CAnimationDataProvider
	IMPORT_C virtual void CAnimationDataProvider_Reserved1();
	IMPORT_C virtual void CAnimationDataProvider_Reserved2();
private:
	TInt iCICLAnimationDataProvider_Reserved;
private:
    CAnimationFrame::THandles CurrentFrame() const;
    void DecodeImageL();
    void DataDeliveryL();
    void Reset();
    // From MICLAnimationDataLoaderObserver
    virtual void DataLoaderEventL(TDataLoaderEvent aEvent, TInt aError);
private: 
	CICLAnimationDataLoader* iDataLoader;
	CAnimationFrame* iCurrentFrame;
	TInt iFlags;
	};

//__ICLANIMATIONDATAPROVIDER_H__
#endif

