// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//
// cdblen.h
//

/**
@file
@publishedAll
@deprecated since v9.1. Functionality is replaced with commsdat.

Maximum length of a text field from the Comms database
in a file alone so it can be used in a resource file.

*/

#ifndef CDBLEN_H
#define CDBLEN_H

#include <e32def.h>

/**
Maximum text field length (in characters).
@publishedAll

*/
const TInt KCommsDbSvrMaxFieldLength=50;

/**
@publishedAll

*/
const TInt KCommsDbSvrDefaultTextFieldLength=50;
const TInt KCommsDbSvrMaxUserIdPassLength=255;
const TInt KCommsDbSvrRealMaxFieldLength=KCommsDbSvrMaxUserIdPassLength;

/** Maximum length of table and column names. 
@publishedAll
*/
const TInt KCommsDbSvrMaxColumnNameLength=50;

#endif
