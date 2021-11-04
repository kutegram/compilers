//
// BitmapTransforms.h
//
// Copyright (c) Symbian Software Ltd 2002-2007.  All rights reserved.
//
// This is the public client API for the BitmapTransforms Library

#ifndef __BITMAPTRANSFORMS_H__
#define __BITMAPTRANSFORMS_H__

#include <e32base.h>
#include <fbs.h>
#include <bitdev.h>

class CBitmapRotatorBody;
class CBitmapScalerBody;
class CBitmapConverterBody;


/**
The public API for clients to call the BitmapTransforms Library bitmap rotation.

@publishedAll

*/

//The public API for clients to call the BitmapTransforms Library bitmap rotation
class CBitmapRotator : public CBase
{
public:

	/**
	The enumeration provides a set of supported rotation and mirror angles.
	TRotationAngle is an enumeration within the namespace CBitmapRotator.
	*/
	enum TRotationAngle
		{
		/** Used to rotate a bitmap 90 degrees clockwise.
		*/
		ERotation90DegreesClockwise,
		/** Used to rotate a bitmap 180 degrees clockwise.
		*/
		ERotation180DegreesClockwise,
		/** Used to rotate a bitmap 270 degrees clockwise.
		*/
		ERotation270DegreesClockwise,
		/** Used to mirror a bitmap about the horizontal axis.
		*/
		EMirrorHorizontalAxis,
		/** Used to mirror a bitmap about the vertical axis.
		*/
		EMirrorVerticalAxis
		};

public:
	IMPORT_C static CBitmapRotator* NewL();
	IMPORT_C ~CBitmapRotator();
	IMPORT_C void Rotate(TRequestStatus* aRequestStatus, CFbsBitmap& aSrcBitmap, CFbsBitmap& aTgtBitmap, TRotationAngle aAngle);
	IMPORT_C void Rotate(TRequestStatus* aRequestStatus, CFbsBitmap& aBitmap, TRotationAngle aAngle);
	IMPORT_C TInt CustomCommand(TUid aUid, TAny* aParam);
	IMPORT_C void Cancel();

private:
	CBitmapRotator();
	void ConstructL();

private:
	CBitmapRotatorBody	*iBody;
};

/**
The public API for clients to call the BitmapTransforms Library bitmap scaling.

@publishedAll

*/

//The public API for clients to call the BitmapTransforms library bitmap scaling
class CBitmapScaler : public CBase
{
public:
	/** An enumeration to specify the level of quality algorithm.
	*/
	enum TQualityAlgorithm
		{
		/**
		Fastest/lowest quality
		*/
		EMinimumQuality,
		/**
		Middle range speed/middle range quality
		*/
		EMediumQuality,
		/**
		Slowest/highest quality
		*/
		EMaximumQuality
		};

public:
	IMPORT_C static CBitmapScaler* NewL();
	IMPORT_C ~CBitmapScaler();
	IMPORT_C void Scale(TRequestStatus* aRequestStatus, CFbsBitmap& aSrcBitmap, CFbsBitmap& aTgtBitmap, TBool aMaintainAspectRatio = ETrue);
	IMPORT_C void Scale(TRequestStatus* aRequestStatus, CFbsBitmap& aBitmap, const TSize& aDestinationSize, TBool aMaintainAspectRatio = ETrue);
	IMPORT_C void Cancel();
	IMPORT_C TInt CustomCommand(TUid aUid, TAny* aParam);
    inline TInt DisablePostProcessing( TBool aState );
	inline TInt UseLowMemoryAlgorithm( TBool aState );
	inline TInt SetQualityAlgorithm( TQualityAlgorithm aQualityLevel );
private:
	CBitmapScaler();
	void ConstructL();

private:
	CBitmapScalerBody* iBody;
	};

#include <bitmaptransforms.inl>

//__BITMAPTRANSFORMS_H__
#endif

