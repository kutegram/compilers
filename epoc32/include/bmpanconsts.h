// BMPANCONSTS.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2007. All rights reserved.
//


#if !defined(__BMPANCONSTS_H__)
#define __BMPANCONSTS_H__

/**
TBitmapAnimCommand

@internalComponent
*/
enum TBitmapAnimCommand
	{
	EBitmapAnimCommandSetBackgroundFrame,
	EBitmapAnimCommandSetDataFrame,
	EBitmapAnimCommandSetFlash,
	EBitmapAnimCommandSetFrameIndex,
	EBitmapAnimCommandSetFrameInterval,
	EBitmapAnimCommandSetNumberOfCycles,
	EBitmapAnimCommandSetPlayMode,
	EBitmapAnimCommandSetPosition,
	EBitmapAnimCommandStartAnimation,
	EBitmapAnimCommandStopAnimation,	
	EBitmapAnimCommandStartAnimationAndKeepLastFrame,
	EBitmapAnimCommandResetFrameArray,
	EBitmapAnimCommandClearDataFrames
	};

#endif

