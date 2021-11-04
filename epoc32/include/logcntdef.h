// LOGCNTDEF.H
//
// Copyright (c) Symbian Software Ltd 2006.  All rights reserved.
//
#ifndef __LOGCNTDEF_H__
#define __LOGCNTDEF_H__

#include <e32def.h>

/** Contact item ID. These are used to uniquely identify contact items within a contacts database.
@internalAll */
typedef TInt32 TLogContactItemId;

/** NULL contact item ID. Indicates that no contact item is present.	
@internalAll */
const TLogContactItemId KLogNullContactId=-1;

/** Format for Given name, Family name string.
  -  Western format is Given followed by Family
  -  Chinese format is Family followed by Given
   	
@internalAll */
enum TLogContactNameFormat {ELogWesternFormat, ELogChineseFormat} ;

#endif
