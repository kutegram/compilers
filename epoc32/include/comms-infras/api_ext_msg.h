// API_EXT_MSG.H
//
// Copyright (c) Symbian Software Ltd. 1997-2007.  All rights reserved.
//
/** @file
@publishedPartner
@prototype
*/

#ifndef API_EXT_MSG_H
#define API_EXT_MSG_H

#include <comms-infras/metadata.h>
#include <comms-infras/netmessages.h>
#include <es_prot.h>

class CCommsApiExtensionMsg : public NetMessages::CMessage
/**
Comms API extension message.

@publishedPartner
@prototype
*/
	{
public:
	/** Creates a new api extension message using ECOM.

    @param aTypeId Id of the class (Composed of Uid of the implementation and an integer sub-type).
    @return a generic pointer to a specific message if successful, otherwise leaves with system error code.
    */
	IMPORT_C static CCommsApiExtensionMsg* NewL(const Meta::STypeId& aTypeId);

	/** Creates a new api extension message using ECOM.

    @param aMsgBuffer a buffer containing the serialised form of the message object.
    @return a generic pointer to a specific event if successful, otherwise leaves with system error code.
    */
	IMPORT_C static CCommsApiExtensionMsg* NewL(const TDesC8& aMsgBuffer);
	};

namespace NetInterfaces
	{
	class TInterfaceControl;
	}
namespace Elements
{
	class CResponseMsg;
}

class CCommsApiExtReqMsg : public CCommsApiExtensionMsg
/**
Comms API extension request message.

@publishedPartner
@prototype
*/
	{
public:
	virtual void DispatchL(NetInterfaces::TInterfaceControl& aIntfCtl, const TSubSessionUniqueId& aSubSessionUniqueId, Elements::CResponseMsg* aResponseMsg) = 0;
	};

class CCommsApiExtRespMsg : public CCommsApiExtensionMsg
/**
Comms API extension response message.

@publishedPartner
@prototype
*/
	{
	};

// API_EXT_MSG_H
#endif
