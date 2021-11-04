//
// MObexNotify.h
//
// Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
//

#ifndef __MOBEXNOTIFY_H__
#define __MOBEXNOTIFY_H__

#include <e32std.h>

class CObexPacket;

/**
@internalComponent

Provides the call back interface for anything owned by CObex.
Note:  This is an internal class which is not intended for use outside of
the Transport<->Obex interface.  Even where access rules allow it, external
users should not call these functions as their implementation may change.
*/
NONSHARABLE_CLASS(MObexNotify)

	{
	public:
		virtual void Process(CObexPacket &aPacket) =0;
		virtual void Error(TInt aError) =0;
		virtual void TransportUp() =0;			// Call back to start the obex session
		virtual void TransportDown(TBool aForceTransportDeletion) =0;
	};

// __MOBEXNOTIFY_H__
#endif
