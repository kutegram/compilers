// ASCLISESSION.H
//
// Copyright (c) Symbian Software Ltd 1999-2005. All rights reserved.
//
#ifndef __ASCLISESSION_H__
#define __ASCLISESSION_H__

// System includes
#include <e32base.h>

// User includes
#include <asshddefs.h>

// Classes referenced
class TASShdAlarm;
class TASCliSoundPlayDefinition;


class RASCliSession : public RSessionBase
/** The client-side interface to the Symbian OS alarm server. 
@publishedAll

*/
	{
///////////////////////////////////////////////////////////////////////////////////////
public:										// CONNECT TO SERVER & VERSIONING
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C RASCliSession();

	IMPORT_C TInt							Connect();

	IMPORT_C TVersion						Version() const;

///////////////////////////////////////////////////////////////////////////////////////
public:										// ALARM SPECIFIC FUNCTIONALITY
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C TInt							AlarmAdd(TASShdAlarm& aAlarm) const;

	IMPORT_C TInt							AlarmAdd(TASShdAlarm& aAlarm, const TDesC8& aData) const;

	IMPORT_C void							AlarmAddWithNotification(TRequestStatus& aStatus, TASShdAlarm& aAlarm);

	IMPORT_C void							AlarmAddWithNotification(TRequestStatus& aStatus, TASShdAlarm& aAlarm, const TDesC8& aData);

	IMPORT_C void							AlarmNotificationCancelAndDequeue(TAlarmId aAlarmId) const;

	IMPORT_C TInt							GetAlarmDetails(TAlarmId aAlarmId, TASShdAlarm& aAlarm) const;
	
	IMPORT_C TInt							AlarmDelete(TAlarmId aAlarmId) const;

	IMPORT_C TInt							GetAlarmCategory(TAlarmId aAlarmId, TAlarmCategory& aCategory) const;

	IMPORT_C TInt							GetAlarmOwner(TAlarmId aAlarmId, TFullName& aThreadName) const;

	IMPORT_C TInt							SetAlarmStatus(TAlarmId aAlarmId, TAlarmStatus aStatus) const;

	IMPORT_C TInt							GetAlarmStatus(TAlarmId aAlarmId, TAlarmStatus& aStatus) const;

	IMPORT_C TInt							SetAlarmDayOrTimed(TAlarmId aAlarmId, TAlarmDayOrTimed aDayOrTimed) const;

	IMPORT_C TInt							GetAlarmDayOrTimed(TAlarmId aAlarmId, TAlarmDayOrTimed& aDayOrTimed) const;

	IMPORT_C TInt							SetAlarmCharacteristics(TAlarmId aAlarmId, TAlarmCharacteristicsFlags aCharacteristics) const;

	IMPORT_C TInt							GetAlarmCharacteristics(TAlarmId aAlarmId, TAlarmCharacteristicsFlags& aCharacteristics) const;

	IMPORT_C TInt							SetClientData(const TASShdAlarm& aAlarm);

///////////////////////////////////////////////////////////////////////////////////////
public:										// ALARM DATA FUNCTIONALITY
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C TInt							AlarmDataAttachL(TAlarmId aAlarmId, const TDesC8& aData) const;

	IMPORT_C TInt							AlarmDataDetach(TAlarmId aAlarmId) const;

	inline	 TInt							AlarmDataDetatch(TAlarmId aAlarmId) const;

	IMPORT_C TInt							AlarmDataSize(TAlarmId aAlarmId) const;

	IMPORT_C TInt							GetAlarmData(TAlarmId aAlarmId, TDes8& aSink) const;

	IMPORT_C TInt							GetAlarmData(TAlarmId aAlarmId, HBufC8*& aSink) const;

///////////////////////////////////////////////////////////////////////////////////////
public:										// CATEGORY-SPECIFIC FUNCTIONALITY
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C TInt							SetAlarmStatusByCategory(TAlarmCategory aCategory, TAlarmStatus aStatus) const;

	IMPORT_C TInt							GetAlarmCountForCategory(TAlarmCategory aCategory) const;

	IMPORT_C TInt							AlarmDeleteAllByCategory(TAlarmCategory aCategory, TBool aDeleteOnlyOrphanedAlarmsInCategory) const;

	IMPORT_C TInt							AlarmDeleteByCategory(TAlarmCategory aCategory, TDeleteType aWhatToDelete) const;

	IMPORT_C void							GetAvailableCategoryListL(RArray<TAlarmCategory>& aCategories) const;

	IMPORT_C void							GetAlarmIdListForCategoryL(TAlarmCategory aCategory, RArray<TAlarmId>& aAlarmIds) const;

///////////////////////////////////////////////////////////////////////////////////////
public:										// MISC FUNCTIONALITY
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C TInt							AlarmCountByState(TAlarmState aState) const;

	IMPORT_C void							GetAlarmIdListByStateL(TAlarmState aState, RArray<TAlarmId>& aAlarmIds) const;

	IMPORT_C void							GetAlarmIdListL(RArray<TAlarmId>& aAlarmIds) const;

	IMPORT_C TInt							GetNextDueAlarmId(TAlarmId& aAlarmId) const;

	IMPORT_C TInt							NumberOfAlarmsActiveInQueue() const;

///////////////////////////////////////////////////////////////////////////////////////
public:										// SOUND CONTROL
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C TInt							SetAlarmSoundState(TAlarmGlobalSoundState aState) const;

	IMPORT_C TInt							GetAlarmSoundState(TAlarmGlobalSoundState& aState) const;

	IMPORT_C TInt							SetAlarmSoundsSilentUntil(const TTime& aLocalTime) const;

	IMPORT_C TInt							SetAlarmSoundsSilentFor(TTimeIntervalMinutes aTimeToRemainSilentFor) const;

	IMPORT_C TInt							GetAlarmSoundsSilentUntil(TTime& aLocalTime) const;

	IMPORT_C TInt							CancelAlarmSilence() const;

	IMPORT_C TBool							AlarmSoundsTemporarilySilenced() const;

	IMPORT_C void							SetAlarmPlayIntervalsL(const CArrayFix<TASCliSoundPlayDefinition>& aIntervals) const;

	IMPORT_C void							GetAlarmPlayIntervalsL(CArrayFix<TASCliSoundPlayDefinition>& aIntervals) const;

///////////////////////////////////////////////////////////////////////////////////////
public:										// CHANGE NOTIFICATION
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C void							NotifyChange(TRequestStatus& aStatus, TAlarmId& aAlarmId);

	IMPORT_C void							NotifyChangeCancel() const;

///////////////////////////////////////////////////////////////////////////////////////
public:										// DEBUG ONLY
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C void							__DbgShutDownServer() const;

	IMPORT_C void							__DbgFailAlloc(TInt aCount) const;

	IMPORT_C void							__DbgPreventUserNotify(TBool aShouldStop) const;

	IMPORT_C TInt							__DbgSnoozeAlarm(TAlarmId aAlarmId, const TTime& aNewTime) const;
	
///////////////////////////////////////////////////////////////////////////////////////
private:									// MEMBER DATA
///////////////////////////////////////////////////////////////////////////////////////

	void									FetchAlarmIdsFromBufferL(RArray<TAlarmId>& aAlarmIds, TInt aBufferSize) const;

	CBufBase*								FetchTransferBufferLC(TInt aBufferSize) const;

	void									DoAlarmAddWithNotification(TRequestStatus& aStatus, TASShdAlarm& aAlarm, const TDesC8& aData);
	TInt									DoAlarmAdd(TASShdAlarm& aAlarm, const TDesC8& aData) const;

///////////////////////////////////////////////////////////////////////////////////////
private:									// MEMBER DATA
///////////////////////////////////////////////////////////////////////////////////////

	TPtr8									iPackage;
	TPtr8									iAlarmIdPointer;
	};

///////////////////////////////////////////////////////////////////////////////////////
// ----> RASCliSession (inlines)
///////////////////////////////////////////////////////////////////////////////////////
inline TInt RASCliSession::AlarmDataDetatch(TAlarmId aAlarmId) const
/** @deprecated 8.0

RASCliSession::AlarmDataDetach() should be used instead */
	{
	return AlarmDataDetach(aAlarmId);
	};

#endif
