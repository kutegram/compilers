// ETELMM.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __ETELMM_H__
#define __ETELMM_H__

#include <e32base.h>
#include <s32mem.h>
#include <etel.h>

class RMobilePhone : public RPhone
	{
	// cut-down version of this class for compilation consistency
public:

	// class needed to support TMobilePhoneStoreEntryV1 below
	class TMultimodeType
		{
	public:
		IMPORT_C TInt ExtensionId() const;
	protected:
		TMultimodeType();
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	protected:
		TInt iExtensionId;
		};

	// enum needed by TGsmSmsTypeOfAddress in gsmuelem.h
	enum TMobileTON
		{
		EUnknownNumber,			// 0
		EInternationalNumber,	// 1
		ENationalNumber,		// 2
		ENetworkSpecificNumber, // 3
		ESubscriberNumber,		// 4 - Also defined as "dedicated, short code" in GSM 04.08
		EAlphanumericNumber,	// 5
		EAbbreviatedNumber		// 6
		};

	// enum needed by TGsmSmsTypeOfAddress in gsmuelem.h
	enum TMobileNPI
		{
		EUnknownNumberingPlan =0,
		EIsdnNumberPlan=1,		
		EDataNumberPlan=3,		
		ETelexNumberPlan=4,	
		EServiceCentreSpecificPlan1=5,
		EServiceCentreSpecificPlan2=6,
		ENationalNumberPlan=8,
		EPrivateNumberPlan=9,
		EERMESNumberPlan=10
		};

	// enum needed below
	enum 
		{
		KMaxMobilePasswordSize=10,
		KMaxMobileNameSize=32,
		KMaxMobileTelNumberSize=100
		};

	// class needed to support TMobileGsmSmsEntryV1 below
	class TMobileAddress
		{
	public:
		IMPORT_C TMobileAddress();
			
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
			
	public:
		TMobileTON iTypeOfNumber;
		TMobileNPI iNumberPlan;
		TBuf<KMaxMobileTelNumberSize> iTelNumber;
		};
	
	// typedef used by TGsmSmsSlot in gsmumsg.h
	typedef TBuf<KMaxMobileNameSize> TMobileName;

	// enum needed for CCommsDbAccess in dbaccess.h
	enum TMobilePhoneNetworkMode
		{
		ENetworkModeUnknown,
		ENetworkModeUnregistered,
		ENetworkModeGsm,
		ENetworkModeAmps,
		ENetworkModeCdma95,
		ENetworkModeCdma2000,
		ENetworkModeWcdma
		};
	};


// class needed to support RMobilePhoneStore below
class RMobilePhoneStore : public RTelSubSessionBase
	{
	// cut-down version of this class for compilation consistency
	public:

		// class needed to support TMobileSmsEntryV1 below
		class TMobilePhoneStoreEntryV1 : public RMobilePhone::TMultimodeType
		{
	protected:
		TMobilePhoneStoreEntryV1();
	public:
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	public:
		TInt  iIndex;
		};
	};


class RMobileSmsMessaging
	{
	// cut-down version of this class for compilation consistency
public:

	// enum needed below
	enum 
		{ 
		KGsmTpduSize = 165,		// 140 bytes user data + 25 bytes TPDU header
		KCdmaTpduSize  = 256	// Max size of Bearer Data in Transport Layer message
		};

	// typedef needed below
	typedef TBuf8<KGsmTpduSize>	TMobileSmsGsmTpdu;
	
	// enum needed by CSmsSettings in smutset.h
	enum TMobileSmsBearer
		{
		ESmsBearerPacketOnly,
		ESmsBearerCircuitOnly,
		ESmsBearerPacketPreferred,
		ESmsBearerCircuitPreferred
		};
	};


class RMobileSmsStore : public RMobilePhoneStore
	{ 
	// cut-down version of this class for compilation consistency
public:

	// enum needed to support CSmsMessage in gsmumsg.h and gsmumsg.inl
	enum TMobileSmsStoreStatus
		{
		EStoredMessageUnknownStatus,
		EStoredMessageUnread,
		EStoredMessageRead,
		EStoredMessageUnsent,
		EStoredMessageSent,
		EStoredMessageDelivered
		};

	// class needed to support TMobileGsmSmsEntryV1 below
	class TMobileSmsEntryV1 : public RMobilePhoneStore::TMobilePhoneStoreEntryV1
		{
	public:
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	protected:
		TMobileSmsEntryV1();
	public:
		TMobileSmsStoreStatus	iMsgStatus;	
		};

	// class needed to support a TGsmSlot constructor used in file gsmumsg.h
	class TMobileGsmSmsEntryV1 : public TMobileSmsEntryV1
		{
	public:
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	public:
		IMPORT_C TMobileGsmSmsEntryV1();
	public:
		RMobilePhone::TMobileAddress iServiceCentre;
		RMobileSmsMessaging::TMobileSmsGsmTpdu	iMsgData;	
		};
	};
	
#endif
