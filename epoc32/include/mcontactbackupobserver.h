// MContactBackupObserver.h
//
// Copyright (c) 2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __MCONTACTBACKUPOBSERVER_H__
#define __MCONTACTBACKUPOBSERVER_H__


class MContactBackupObserver
/**	
	An observer class to which Contacts model clients should 
	subscribe in order to be informed about the progress of 
	a backup or restore operation.

	@publishedAll
	
*/
	{
public:
/**	
	Provides notification that a backup operation is to begin.
	The Contacts model client should not access the contacts database for 
	writing until BackupRestoreCompletedL() is called.
*/
	virtual void BackupBeginningL()	= 0;

/**	
	Provides notification that a restore operation is to begin.
	The Contacts model client should not access the contacts database at all 
	until BackupRestoreCompletedL() is called.
*/
	virtual void RestoreBeginningL() = 0;

/**	
	Provides notification that a backup/restore operation is complete.
	The contacts database can be accessed again.
*/
	virtual void BackupRestoreCompletedL() = 0;

	};


// __MCONTACTBACKUPOBSERVER_H__
#endif

