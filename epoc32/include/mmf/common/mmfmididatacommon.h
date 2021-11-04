// MmfMidiDataCommon.h
//
// Copyright (c) 2004 Symbian Ltd.  All rights reserved.
//

#ifndef __MMFMIDIDATACOMMON_H__
#define __MMFMIDIDATACOMMON_H__


/** 
Class used to hold MIP message values.

@publishedAll

*/
class TMipMessageEntry
	{
public:
	/**
	 * Channel whose MIP value is to be set.
	 */
	TInt iChannel;

	/**
	 * MIP value to use.
	 */
	TInt iMIPValue;
	};

/**
Defines the current playback rate of the currently open MIDI resource.

@publishedAll

*/
enum TPlaybackRate
	{
	/** 
	 * The original playback rate for the currently open MIDI resource prior to any modifications.
	 */
	EOriginalPlaybackRate = 100000
	};

#endif
