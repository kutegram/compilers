//
// FLOGGER.INL
//
// Copyright (c) Symbian Software Ltd. 1997-2007.  All rights reserved.
//

/**
@file

@internalTechnology
*/

#ifndef __FLOGGER_INL__
#define __FLOGGER_INL__

#include <flogger.h>

/**
TSignal inline functions
*/

inline FLogger::TSignal::TSignal(TRequestStatus& aStatus)
	:iStatus(&aStatus),iId(RThread().Id())
/**
Sets aStatus with the value KRequestPending.

*/
	{
	aStatus=KRequestPending;
	}

inline TPtrC FLogger::TSignal::Command() const
/**
*/
	{
	return TPtrC((const TText*)this,sizeof(*this)/sizeof(TText));
	}

inline TInt FLogger::TSignal::Set(const TDesC& aCommand)
/**
Sets aCommand with "this" pointer value.

@return KErrNone, if successful.
*/
	{
	if (aCommand.Size()!=sizeof(*this))
		return KErrGeneral;
	
	return (Mem::Copy(this,aCommand.Ptr(),sizeof(*this)),KErrNone);
	}

/**
TLogFile inline functions
*/

inline TBool TLogFile::Valid() const
/**
@return EFalse for invalid file name.
*/
	{
	return iValid;
	}

inline TFileName TLogFile::Directory() const
/**
@return iDirectory the full path of the folder.
*/
	{
	return iDirectory;
	}
	
inline TFileName TLogFile::Name() const
/**
@return iName the file name of the log.
*/
	{
	return iName;
	}

inline TFileLoggingMode TLogFile::Mode() const
/**
@return iMode the mode of the log file.
*/
	{
	return iMode;
	}	

inline void TLogFile::SetValid(TBool aValid)
/**
Sets iValid with the value aValid.
*/
	{
	iValid=aValid;
	}

// __FLOGGER_INL__
#endif

