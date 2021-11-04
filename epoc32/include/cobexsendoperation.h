// CObexSendOperation.h
//
// Copyright (c) Symbian Software Ltd 2004.  All rights reserved. 
//


#ifndef __COBEXSENDOPERATION_H__
#define __COBEXSENDOPERATION_H__


#include <msvapi.h>


class CObexSendOperation : public CMsvSendOperation
/**
@internalComponent
*/
	{
public:
	IMPORT_C CObexSendOperation(CMsvSession& aMsvSession, TRequestStatus& aObserverRequestStatus);
	// from CMsvSendOperation		
	IMPORT_C virtual const TDesC8& TranslateProgress(const TDesC8& aProgress);
	};


// __COBEXSENDOPERATION_H__
#endif

