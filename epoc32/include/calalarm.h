// calalarm.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#ifndef __CALALARM_H__
#define __CALALARM_H__

#include <e32base.h>
#include <calcontent.h>

NONSHARABLE_CLASS(CCalAlarm) : public CBase
/** Class representing an alarm. contains associated data extensions

This can be assigned to a calendar entry.

@publishedAll

*/
	{
 public:

	IMPORT_C static CCalAlarm* NewL();
	IMPORT_C ~CCalAlarm();
	IMPORT_C void SetTimeOffset(TTimeIntervalMinutes aOffset);
	IMPORT_C TTimeIntervalMinutes TimeOffset() const;
	IMPORT_C void SetAlarmSoundNameL(const TDesC& aAlarmSoundName);
	IMPORT_C const TDesC& AlarmSoundNameL() const;
	IMPORT_C void SetAlarmAction(CCalContent* aAlarmAction);
	IMPORT_C CCalContent* AlarmAction() const;
private:
	CCalAlarm();

private:
	TTimeIntervalMinutes iOffset;
	HBufC* iAlarmName;
	// the associated data for rich alarm action
	CCalContent* iAlarmAction;
	};


// __CALALARM_H__
#endif

