// EIKIRFTY.H
//
// Copyright (c) 1997-2006 Symbian Ltd.  All rights reserved.
//
// Defines mix-in interace to break dependencey of Eikon Application UI 
// on EikIr library

#ifndef __EIKIRFTY_H__
#define __EIKIRFTY_H__

#include <f32file.h>
#include <e32base.h>
#include <eikdef.h>

class CEikEdwin;

/**
@publishedPartner 

*/
class MEikIrFactory
	{
public:
	virtual void SendDataOverIrL(CEikEdwin* aEditor) = 0;
	virtual void ReceiveDataOverIrL(CEikEdwin* aEditor) = 0;
	};


// __EIKIRFTY_H__
#endif
