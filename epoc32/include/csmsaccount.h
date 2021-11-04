//	CSMSACCOUNT.H
//
//	Copyright (c) Symbian Software Ltd 2004. All rights reserved.
//

#ifndef __CSMSACCOUNT_H__
#define __CSMSACCOUNT_H__


#include <e32base.h>
#include <msvapi.h>


class CSmsSettings;
class CMsvOffPeakTimes;
class CMsvScheduleSettings;
class CMsvSendErrorActions;
class CMsvSysAgentActions;
class CRepository;


/**
Stores SMS service and Schedule Send settings to Central Repository. 

@publishedAll

*/
class CSmsAccount : public CBase, public MMsvSessionObserver
	{
public:

	IMPORT_C static CSmsAccount* NewL();
	IMPORT_C static CSmsAccount* NewLC();
	IMPORT_C virtual ~CSmsAccount();

	IMPORT_C void InitialiseDefaultSettingsL(CSmsSettings& aSmsSettings);
	IMPORT_C void InitialiseDefaultSettingsL(CMsvScheduleSettings& aScheduleSettings, CMsvOffPeakTimes& aOffPeakTimes, CMsvSendErrorActions& aErrorActions, CMsvSysAgentActions& aSysAgentActions);
	IMPORT_C void LoadSettingsL(CSmsSettings& aSmsSettings);
	IMPORT_C void LoadSettingsL(CMsvScheduleSettings& aScheduleSettings, CMsvOffPeakTimes& aOffPeakTimes, CMsvSendErrorActions& aErrorActions, CMsvSysAgentActions& aSysAgentActions);
    IMPORT_C void SaveSettingsL(const CSmsSettings& aSmsSettings) const;
	IMPORT_C void SaveSettingsL(const CMsvScheduleSettings& aScheduleSettings, const CMsvOffPeakTimes& aOffPeakTimes, const CMsvSendErrorActions& aErrorActions, const CMsvSysAgentActions& aSysAgentActions) const;

private:
	CSmsAccount();
	void ConstructL();
	void HandleSessionEventL(TMsvSessionEvent , TAny* , TAny* , TAny* );
	CMsvSession& SessionL();	
	
	TMsvId CreateSmsServiceL();
	void ResetSettings();

private:
	enum TSmsSettingsCenRepId
		{
		// Service Settings		
		ESmsServiceId					= 0x00000000,
		ESmsSettingsVersionId			= 0x00000001,
		ESmsSettingsMesssageVersionId	= 0x00000002,
		ESmsValidityPeriodId			= 0x00000003,
		ESmsValidityPeriodFormatId	   	= 0x00000004,     	
		ESmsAlphabetId					= 0x00000005,
		ESmsMsgFlagsId					= 0x00000006,
		ESmsMessageConversionId			= 0x00000007,
		ESmsFlagsId						= 0x00000008,
		ESmsStatusReportHandlingId		= 0x00000009,
		ESmsSpecialMessageHandlingId	= 0x0000000A,
		ESmsCommDbActionId				= 0x0000000B,
		ESmsDeliveryId					= 0x0000000C,
		ESmsDefaultSCId					= 0x0000000D,
		ESmsSCAddressesCountId			= 0x0000000E,
		ESmsBearerActionId				= 0x0000000F,
		ESmsBearerId					= 0x00000010,
		ESmsClass2FolderId				= 0x00000020,
		ESmsDescriptionLengthId			= 0x00000030,
		ESmsAccountNameId				= 0x00000040,
		
		ESmsSCAddressesPartialId		= 0x00001000
		};

private:
	CMsvSession* iMsvSession;
	CRepository* iRepository;
	};

// __CSMSACCOUNT_H__
#endif
