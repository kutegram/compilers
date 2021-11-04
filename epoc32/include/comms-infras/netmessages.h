//
// NetMessages.h
// Copyright (c) 2004 Symbian Ltd.  All rights reserved.
//

/**
 * @file
 * @internalTechnology
 */


#if !defined(NETMESSAGES_H)
#define NETMESSAGES_H

#include <comms-infras/metadata.h>
#include <comms-infras/metabuffer.h>

#define NET_MESSAGE_DECL( _class, _uid, _type ) \
public: \
	static inline _class * NewL(void) \
		{ Meta::STypeId typeId( (_uid ) , (_type) ); \
	  return static_cast< _class *>(Meta::SMetaDataECom::NewInstanceL(typeId)); } \
	static inline _class * LoadL(TPtrC8& aDes) \
		{ return static_cast< _class *>(Meta::SMetaDataECom::LoadL(aDes)); } \
	static inline TUid GetUid(void) { return TUid::Uid(_uid) ; } \
public: \
	DATA_VTABLE

namespace NetMessages
{

/** An class recognised by CWorkerThread. When a client of the root server wants to send a message to a module
via RRootServ::SendMessage method it serialises an instance of CNetMessage based class and passes it as
a aData parameter
@see RRootServ::SendMessage

*/
class CMessage : public Meta::SMetaDataECom
	{
public:
	TYPEID_TABLE
	};

} // namespace NetMessages
// NETMESSAGES_H
#endif
