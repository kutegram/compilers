// JpegYuvDecoder.h
//
// Copyright (c) Symbian Software Ltd 1999-2007.  All rights reserved.
//

#ifndef __JPEG_YUV_DECODER_H__
#define __JPEG_YUV_DECODER_H__

#include <imageconversion.h>

/**
@internalAll

Extended decoder for JPEG images.
*/
class CJpegYuvDecoder : public CImageDecoder
	{
public:
	/**
	Flags to control how the image is decoded.
	These can be combined using an OR operation.
	*/
	enum TOptions
		{
		/** No flag set
		*/
		EOptionNone = 0x00,

		/** Decode the pixels in YUV format
		*/
		EOptionYuvDecode = 0x01
		};

public:
	IMPORT_C void ConvertYuv(TRequestStatus* aRequestStatus, CFbsBitmap& aDestination, TInt aFrameNumber = 0);
	IMPORT_C void ConvertYuv(TRequestStatus* aRequestStatus, CFbsBitmap& aDestination, CFbsBitmap& aDestinationMask, TInt aFrameNumber = 0);
	};

// __JPEG_YUV_DECODER_H__
#endif
