// GifScaler.h
//
// Copyright (c) Symbian Software Ltd 2003-2006.  All rights reserved.
//
// This is the public client API for the GifScaler Library

#ifndef __GIFSCALER_H__
#define __GIFSCALER_H__

#include <e32base.h>
#include <fbs.h>


/**
The public API for clients to call the GifScaler scaling and color quantization library.

@publishedAll

*/
class CGifScaler : public CBase
	{
public:
	/**
	TOptions is an enumeration within the namespace CGifScaler
	The enumeration provides a set of supported quantization levels:
	(EHighQualityQuantization is the default setting as it provides the
	best balance between quality and speed)
	*/
	enum TOptions
		{
		/** Provides the lowest quality, but also the fastest.
		*/
		ELowQualityQuantization,
		/** Provides medium quality quantization
		*/
		EMediumQualityQuantization,
		/** Provides high quality quantization
		*/
		EHighQualityQuantization,
		/** Provides the highest quality quantization, but is also the slowest.
		*/
		EMaximumQualityQuantization
		};

public:
	IMPORT_C static CGifScaler* NewL(CFbsBitmap& aSource, TOptions aOptions = EHighQualityQuantization);
	IMPORT_C static CGifScaler* NewL(CFbsBitmap& aSource, CFbsBitmap& aSourceMask, TOptions aOptions = EHighQualityQuantization);
	IMPORT_C ~CGifScaler();

	// Scale source and mask -> 8bpp destination. (One of the palette indices is transparent, if a mask is supplied)
	IMPORT_C void Scale(TRequestStatus* aStatus, CFbsBitmap& aDestination, CPalette& aPalette, TBool aMaintainAspectRatio = ETrue);

	// Scale source and mask -> 8bpp destination. (As above, except that the transparency threshold must be specified)
	IMPORT_C void ThresholdScale(TRequestStatus* aStatus, CFbsBitmap& aDestination, CPalette& aPalette, TUint8 aTransparencyThreshold, TBool aMaintainAspectRatio = ETrue);

	// Cancel scaling.
	IMPORT_C void Cancel();

private:
	CGifScaler();
	void ConstructL(CFbsBitmap& aSource, CFbsBitmap* aSourceMask, TOptions aOptions);

private:
	class CBody;
	CBody* iBody;
	};

// __GIFSCALER_H__
#endif
