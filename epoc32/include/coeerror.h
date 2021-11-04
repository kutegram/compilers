// COEERROR.H
//
// Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
//

#ifndef __COEERROR_H__
#define __COEERROR_H__

/**
@internalTechnology
*/
#define KUidConeDllValue16 0x10003a41

/**
@internalTechnology
*/
const TUid KUidConeDll16={KUidConeDllValue16};


#if defined(_UNICODE)
/**
@internalTechnology
*/
#define KUidConeDllValue KUidConeDllValue16
/**
@internalTechnology
*/
const TUid KUidConeDll={KUidConeDllValue};
#else
#define KUidConeDllValue KUidConeDllValue8
const TUid KUidConeDll={KUidConeDllValue};
#endif


/** UI Control Framework errors.

@publishedAll
@deprecated */
enum
	{
	/** Not used. */
	KErrCoeResourceFileDuplicateOffset,
	/** Read fail. CCoeEnv::ReadResource() sets this as the
	active scheduler's extended error number if the read fails.	*/
	KErrCoeFailedToReadFromProgDisk
	};

// __COEERROR_H__
#endif

