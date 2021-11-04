// ZipFileMemberIterator.h
//
// Copyright (c) 2003-2006 Symbian Software Ltd.  All rights reserved.
//

// $Revision$

#ifndef _ZIP_FILE_MEMBER_ITERATOR_H_
#define _ZIP_FILE_MEMBER_ITERATOR_H_

#include <e32std.h>

// Forward Class Declaration(s)

class CZipFileMember;

// End of  Forward Class Declaration(s)

/**
An iterator class for iterating though all the entries in the archive.

@publishedAll

*/
class CZipFileMemberIterator
	{
friend class CZipFile;

public:
	IMPORT_C CZipFileMember* NextL(void);

private:
	CZipFileMemberIterator(CZipFile*);
	
private:
	CZipFile* iZipFile;
	TInt      iIndex;
	};

#endif /* !_ZIP_FILE_MEMBER_ITERATOR_H_ */
