// PluginKiller.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

/** @file
@publishedPartner

*/

#ifndef __PLUGINKILLER_H__
#define __PLUGINKILLER_H__


#include <e32base.h>

///Forward Declarations
class CPushHandlerBase;

/** 
Utility class used by a WAP Push Application plugin to delete itself. 

@publishedPartner

*/
class CPluginKiller: public CActive 
	{
public:
	virtual ~CPluginKiller();

	CPluginKiller(CPushHandlerBase* aPushPlugin);
	IMPORT_C void KillPushPlugin();

protected:
	virtual void DoCancel();
	virtual void RunL();

private:
	CPushHandlerBase*		iPushPlugin;
	TBool					iDeletePushPlugin;
	};

//_PLUGINKILLER_H
#endif
