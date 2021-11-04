// CalDataFormat.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#ifndef __CCALDATAFORMAT_H__ 
#define __CCALDATAFORMAT_H__ 

#include <e32cmn.h>

/** 
@file
@publishedAll
*/ 

/** The UID for a VCal 1.0 data parser
Used in vCalendar Import. */
const TUid KUidVCalendar = {0x1020DB7B};


/** These flags control the behaviour of the data exchange parser.*/
/** This flag overrides the default character set when parsing 
vCalendar 1.0 files to Shift-JIS */
const TUint32 KCalDataExchangeDefaultShiftJIS = 0x00000001; 


// __CCALDATAFORMAT_H__ 
#endif
