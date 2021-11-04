//
// BitmapTransforms.inl
//
// Copyright (c) Symbian Software Ltd 2002-2007.  All rights reserved.
//

#ifndef __BitmapTransforms_inl
#define __BitmapTransforms_inl

#include <bitmaptransforms.h>

const TUid KICLUidPostProcessCommand = { 0x101F7C18 };
const TUid KICLUidUseLowMemoryAlgorithmCommand = { 0x101F7C42 };
const TUid KICLUidSetQualityAlgorithmCommand = { 0x101F7C4C }; 


/**
@publishedAll

SetPostProcessing

@param 	aState
		a boolean flag which if true will set post processing on
		(Note by defualt the scaler has post processing on)


*/
inline TInt CBitmapScaler::DisablePostProcessing( TBool aState )
	{
	return CustomCommand( KICLUidPostProcessCommand,&aState);
	}

/**
@publishedAll

UseLowMemory

@param 	aState
		a boolean flag which if true will enable the low memory algorithm
		(Note by defualt the scaler does not use the low memory algorithm)


*/
inline TInt CBitmapScaler::UseLowMemoryAlgorithm( TBool aState )
	{
	return CustomCommand( KICLUidUseLowMemoryAlgorithmCommand, &aState);
	}

/**
@publishedAll

SetQualityAlgorithm

@param 	aQualityLevel
		an enumeration which sets the quality algorithm


*/
inline TInt CBitmapScaler::SetQualityAlgorithm( TQualityAlgorithm aQualityLevel )
	{
	return CustomCommand( KICLUidSetQualityAlgorithmCommand, &aQualityLevel );
	}

// __BitmapTransforms_inl
#endif
