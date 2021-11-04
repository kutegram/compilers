// $Workfile: irmsgtypeuid.h $
//
// Copyright (c) 2001-2007 Symbian Ltd.  All rights reserved.
//
// $Author: Stevep $
// $Revision: 4 $
// $Date: 4/12/01 9:45 $

/**
* @file
* @publishedAll
* 
*/

#if !defined (__IRMSGTYPEUID_H__)
#define __IRMSGTYPEUID_H__

const TInt32 KUidMsgTypeIrTInt32 = 0x100053A4;
// This is defined in irobutil.h, which we don't control.
// const TUid KUidMsgTypeIr = {KUidMsgTypeIrTInt32};

const TInt32 KUidMsgTypeIr			 =	0x100053A4;

const TUid KUidMsgTypeIrUID = {KUidMsgTypeIr};	// we will revert this when we persuade PAN to make the other one a real TUid.

// __IRMSGTYPEUID_H__
#endif
