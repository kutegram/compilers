// EIKUNDER.H
//
// Copyright (c) 1997-2007 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKUNDER_H__
#define __EIKUNDER_H__

#include <e32base.h>	// class CActive

class RThread;

/**
@publishedAll

*/
class MEikUndertakerObserver
	{
public:
	virtual void HandleThreadExitL(RThread& aThread) = 0;
	};

/**
@publishedAll

*/
class CEikUndertaker : public CActive
	{
public:
	IMPORT_C static CEikUndertaker* NewL(MEikUndertakerObserver& aObserver);
	IMPORT_C ~CEikUndertaker();
private:
	CEikUndertaker(MEikUndertakerObserver& aObserver);
	void ConstructL();
	void Request();
private: // from CActive
	void DoCancel();
	void RunL();
private:
	MEikUndertakerObserver& iObserver;
	RUndertaker iUndertaker;
	TInt iThreadHandle;
	};

// __EIKUNDER_H__
#endif
