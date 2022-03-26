/**
@file AGENTDIALOG.H
@internalTechnology

Copyright (c) 1997-2004 Symbian Ltd.  All rights reserved.
Generic Connection Dialog Client
*/

#ifndef __AGENTDIALOG_H__
#define __AGENTDIALOG_H__

#include <e32std.h>
#include <cdbcols.h>
#include <cdblen.h>
//#include <comms-infras\commsdebugutility.h> Cannot be included because it conflicts with flogger


/**
Server name in EKA2 case
@internalTechnology
*/
_LIT(KCommsDialogServerName, "!NetDialDialogServer");

//__FLOG_STMT(_LIT8(KDlgSvrLogSubsys, "agentdialog");)
//__FLOG_STMT(_LIT8(KDlgSvrLogComponent, "server");)
//__FLOG_STMT(_LIT8(KDlgCliLogComponent, "client");)

class TConnectionPrefs
/**
Specifies the rank and desired direction of the connection and bearer.

@internalTechnology
*/
	{
public:
	TUint32 iRank;
	TCommDbConnectionDirection iDirection;
	TUint32 iBearerSet;
	};

class TIspConnectionNames
/**
Specifies the Connection Names for ISP.

@internalTechnology
*/
	{
public:
	TBuf<KCommsDbSvrDefaultTextFieldLength> iServiceName;
	TBuf<KCommsDbSvrMaxColumnNameLength> iServiceTable;
	TBuf<KCommsDbSvrDefaultTextFieldLength> iModemName;
	TBuf<KCommsDbSvrDefaultTextFieldLength> iLocationName;
	TBuf<KCommsDbSvrDefaultTextFieldLength> iChargecardName;
	};

class TAuthenticationPair
/**
Specifies the Authentication for the User Name and Password.

@internalTechnology
*/
	{
public:
	TDes* iUsername;
	TDes* iPassword;
	};

class TPctResponse
/**
Allows the user to see the login script running, see what is sent and received, and allows the user to type responses.

@internalTechnology
*/
	{
public:
	TDes* iBuffer;
	};

class TNewIapConnectionPrefs
/**
Specifies Connection Preference for the New IAP.

@internalTechnology
*/
	{
public:
	TConnectionPrefs iPrefs;
	TInt iLastError;
	TBuf<KCommsDbSvrDefaultTextFieldLength> iName;
	};

class RDialogNotifier : public RNotifier
/**
Client interface to allow engines or other low level components to communicate with the UI.

Real implementations need three asynchronous message slots instead of RNotifiers default one slot
in order to implement the PCT functionality.  This is not used at all by the test dialog server
implementation.
 
@internalTechnology
*/
	{
public :
	TInt Connect();
	};

class RGenConAgentDialogServer : public RSessionBase
/**
RGenConAgentDialogServer. This components needs to be written as a 
proper polymorphic DLL in JetStream.

NOTE! Although the class inherits from RSessionBase this does not mean you 
have to implement the API as a client server mechanism.

@internalTechnology
*/
	{
public:
	IMPORT_C RGenConAgentDialogServer();
	IMPORT_C ~RGenConAgentDialogServer();
	IMPORT_C TVersion Version() const;
	IMPORT_C TInt Connect();
	IMPORT_C void Close();
	IMPORT_C void ModemAndLocationSelection(TUint32& aModemId,TUint32& aLocationId,TRequestStatus& aStatus);
	IMPORT_C void IapConnection(TUint32& aIAP, const TConnectionPrefs& aPrefs, TRequestStatus& aStatus);
	IMPORT_C void IapConnection(TUint32& aIAP, const TConnectionPrefs& aPrefs, TInt aLastError, TRequestStatus& aStatus);
	IMPORT_C void WarnNewIapConnection(const TConnectionPrefs& aPrefs, TInt aLastError, const TDesC& aNewIapName, TBool& aResponse, TRequestStatus& aStatus);
	IMPORT_C void Login(TDes& aUsername, TDes& aPassword, TBool aIsReconnect, TRequestStatus& aStatus);
	IMPORT_C void Authenticate(TDes& aUsername, TDes& aPassword, TBool aIsReconnect, TRequestStatus& aStatus);
	IMPORT_C void Reconnect(TBool& aResponse, TRequestStatus& aStatus);
	IMPORT_C TInt OpenPct();
	IMPORT_C TInt WritePct(const TDesC& aData);
	IMPORT_C void ReadPct(TDes& aData, TRequestStatus& aStatus);
	IMPORT_C void DestroyPctNotification(TRequestStatus& aStatus);
	IMPORT_C void ClosePct();
	IMPORT_C void QoSWarning(TBool& aResponse, TRequestStatus& aStatus);
	IMPORT_C void CancelModemAndLocationSelection();
	IMPORT_C void CancelIapConnection();
	IMPORT_C void CancelWarnNewIapConnection();
	IMPORT_C void CancelLogin();
	IMPORT_C void CancelAuthenticate();
	IMPORT_C void CancelReconnect();
	IMPORT_C void CancelReadPct();
	IMPORT_C void CancelDestroyPctNotification();
	IMPORT_C void CancelQoSWarning();
	IMPORT_C void AccessPointConnection(TUint32& aAccessPoint, TInt aAccessPointGroup, TRequestStatus& aStatus);
	IMPORT_C void CancelAccessPointConnection();
	IMPORT_C void AccessPointConnection(TUint32& aAP, TUint32 aAPType, TUint32& aBearerAPInd, TUint32 aBearerAPType, TRequestStatus& aStatus);

private:
	RDialogNotifier* iNotifier;
	TPckg<TUint32> iIAP;
	TPckg<TUint32> iModemId;
	TPckg<TUint32> iLocationId;
	TPckgBuf<TIspConnectionNames> iConNames;
	TPckgBuf<TConnectionPrefs> iPrefs;
	TPckg<TBool> iBool;
	TPckgBuf<TUint32> iPctBuffer;
	TPckgBuf<TPctResponse> iPctResponse;
	TPckgBuf<TAuthenticationPair> iAuthenticationPair;
	TPckgBuf<TNewIapConnectionPrefs> iNewIapPrefsBuffer;
	TPckgBuf<TUint32> iNotUsed;		// Parameters not used by plugin
	TRequestStatus iStatus;
	TPckg<TUint32> iAccessPoint;
//	__FLOG_DECLARATION_MEMBER;
	};

IMPORT_C TInt StartDialogThread();

#endif
