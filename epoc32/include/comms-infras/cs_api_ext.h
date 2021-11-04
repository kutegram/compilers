// CS_API_EXT.H
//
// Copyright (c) Symbian Software Ltd. 1997-2007.  All rights reserved.
//
/** @file
@internalTechnology

*/

#ifndef CS_API_EXT_H
#define CS_API_EXT_H

#include <es_sock.h>
#include <comms-infras/api_ext_list.h>
#include <comms-infras/trbuf.h>

class CCommsApiExtReqMsg;
class CCommsApiExtRespMsg;

class RCommsApiExtensionBase
/**
Base class for Comms API extensions.

@internalTechnology

*/
	{
protected:
	IMPORT_C explicit RCommsApiExtensionBase();
	IMPORT_C TInt Open(RCommsSubSession& aExtensionProvider, TSupportedCommsApiExt aInterfaceId);
	IMPORT_C void Close();
	IMPORT_C void SendRequest(CCommsApiExtReqMsg& aRequestMsg, TDes8& aResponseBuf, TRequestStatus& aStatus);
	IMPORT_C void SendMessage(CCommsApiExtReqMsg& aRequestMsg);

protected:
	RCommsSubSession iSubSession;
	TSupportedCommsApiExt iInterfaceId;

private:
	RPointerArray<Elements::TRBuf8> iBuffers;
	};

template<TSupportedCommsApiExt T>
class RCommsApiExtension : public RCommsApiExtensionBase
/**
Comms API extensions template. New extension APIs may derive from this template.

@internalTechnology

*/
	{
public:
	inline TInt Open(RCommsSubSession& aExtensionProvider);
	};

template<TSupportedCommsApiExt T>
TInt RCommsApiExtension<T>::Open(RCommsSubSession& aExtensionProvider)
	{
	return RCommsApiExtensionBase::Open(aExtensionProvider,T);
	}

// CS_API_EXT_H
#endif
