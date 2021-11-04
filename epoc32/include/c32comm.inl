// C32COMM.INL
//
// Copyright (c) Symbian Software Ltd. 1997-2006.  All rights reserved.
//

#ifndef SYMBIAN_C32_SERCOMMS_V2
// PLEASE NOTE: This file is part of Version 2 of C32 - that is, the multi-threaded version.
// The single-threaded C32 version of this file is in c32\Version1\SCOMM
// All defect fixes should be applied to both versions where appropriate.
// PLEASE NOTE: This comment is applicable to SercommsV2 but is surrounded by an "#ifndef"
// to enable the automatic removal of this comment once non-C32 V2 code is removed.
#endif


/**
 * @file
 *
 * implements inline methods of RComm
 */

inline void RComm::SetSignals(TUint aSetMask, TUint aClearMask)
/** Sets or clears RS232 output lines (DTR and RTS).

For many applications, these lines will be read and set under driver control 
as determined by the handshaking options selected.

@param aSetMask Set the handshaking lines in the mask. 
@param aClearMask Clear the handshaking lines in the mask. 
@publishedAll

*/
	{
	SetSignalsToMark(aSetMask);
	SetSignalsToSpace(aClearMask);
	}
