//
// obextypes.h
//
// Copyright (c) 2003-2005 Symbian Software Ltd.  All rights reserved.
//

/**
@file
@publishedAll

*/

#ifndef __OBEXTYPES_H
#define __OBEXTYPES_H

#include <e32std.h>
#include <e32des8.h>
#include <e32des16.h>
#include <utf.h> // Required for source compatability
#include <obexconstants.h>
#include <obex/internal/obextransportconstants.h>

class TObexProtocolInfo;
class TObexIrProtocolInfo;
class TObexBluetoothProtocolInfo;
class TObexUsbProtocolInfo;
class TObexUsbProtocolInfoV2;
class TObexProcotolPolicy;
struct TObexConnectionInfo;
class TObexConnectInfo;

class CObexPacket;
class CObexHeader;
class CObexUnderlyingHeader;
class MObexHeaderCheck;
class CObexHeaderSet;
class CObexBaseObject;
class CObexFileObject;
class CObexBufObject;
class CObexNullObject;
class MObexNotify;
class MObexAuthChallengeHandler;
class CObexTransport;
class CObexConnector;
class TObexInternalHeader;
class CObexAuthenticator;
class CObex;
class TObexSetPathData;
class CObexClient;
class MObexServerNotify;
class CObexServer;
class CObexServerStateMachine;
class MObexServerNotify;
class MObexServerNotifyAsync;
class CObexServerNotifySyncWrapper;


// __OBEXTYPES_H
#endif
