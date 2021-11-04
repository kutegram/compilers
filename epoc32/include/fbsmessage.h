// FbsMessage.H
//
// Copyright (C) 2005-2007 Symbian Software Ltd. All rights reserved.
//

#ifndef __FBSMESSAGE_H__
#define __FBSMESSAGE_H__

/**
@internalComponent
*/
enum TFbsMessage
	{
	EFbsMessInit,
	EFbsMessShutdown,
	EFbsMessClose,
	EFbsMessResourceCount,
	EFbsMessNumTypefaces,
	EFbsMessTypefaceSupport,
	EFbsMessFontHeightInTwips,
	EFbsMessFontHeightInPixels,
	EFbsMessAddFontStoreFile,
	EFbsMessInstallFontStoreFile,
	EFbsMessRemoveFontStoreFile,
	EFbsMessSetPixelHeight,
	EFbsMessGetFontById,
	EFbsMessFontDuplicate,
	EFbsMessBitmapCreate,
	EFbsMessBitmapResize,
	EFbsMessBitmapDuplicate,
	EFbsMessBitmapLoad,
	EFbsMessDefaultAllocFail,
	EFbsMessDefaultMark,
	EFbsMessDefaultMarkEnd,
	EFbsMessUserAllocFail,
	EFbsMessUserMark,
	EFbsMessUserMarkEnd,
	EFbsMessHeapCheck,
	EFbsMessRasterize,
	EFbsMessFaceAttrib,
	EFbsMessHasCharacter,
	EFbsMessSetDefaultGlyphBitmapType,
	EFbsMessGetDefaultGlyphBitmapType,
	EFbsMessFontNameAlias,
	EFbsMessBitmapCompress,
	EFbsMessGetHeapSizes,
	EFbsMessGetNearestFontToDesignHeightInTwips,
	EFbsMessGetNearestFontToMaxHeightInTwips,
	EFbsMessGetNearestFontToDesignHeightInPixels,
	EFbsMessGetNearestFontToMaxHeightInPixels,
 	EFbsMessShapeText,
 	EFbsMessShapeDelete,
	EFbsMessDefaultLanguageForMetrics,
	EFbsMessSetTwipsHeight,
	EFbsMessGetTwipsHeight,
	EFbsCompress,
	EFbsMessBitmapBgCompress,
	EFbsUnused1,
	EFbsSetSystemDefaultTypefaceName,
	EFbsGetAllBitmapHandles,
	EFbsMessCreateLinkedTypeface, 	//linked font registration
	EFbsMessSetHeapFail,	//for memory testing only
	EFbsMessHeapCount, //for memory testing only
	EFbsMessSetHeapReset, //for memory testing only
	EFbsMessSetHeapCheck, //for memory testing only
	EFbsMessHeap, //for memory testing only
	EFbsMessLinkedCache, //to put a character in the linked fonts cache
	EFbsMessBitmapClean, // replace a dirty bitmap with the clean one
	EFbsMessBitmapLoadFast, // for loading bitmap from mbm or rsc file not opened by the client
	EFbsMessBitmapNotifyDirty, // notify when any bitmap becomes dirty
	EFbsMessBitmapCancelNotifyDirty, // cancel request for notification of any bitmap becoming dirty
	};

// __FBSMESSAGE_H__
#endif
