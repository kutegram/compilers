// Copyright (c) Symbian Software Ltd 2008. All rights reserved.

/** @file
@internalComponent
Operation information 
Used by both Remote Control server side and Remote Control client side library.
*/

#ifndef OPERATIONINFORMATION_H
#define OPERATIONINFORMATION_H

#include <e32base.h>
#include <remcon/messagetype.h>


class TOperationInformation
	{
public:
	TUint iOperationId;
	TRemConMessageSubType iMessageSubType;
	};


// OPERATIONINFORMATION_H
#endif
