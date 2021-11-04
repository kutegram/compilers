// LOGENG.H
//
// Copyright (c) Symbian Ltd 2002-2007.  All rights reserved.
//

#ifndef __LOGENG_H__
#define __LOGENG_H__

#include <e32std.h>
#include <logwrap.h>
#include <logwrap.hrh>

/**
Event types
@publishedAll

*/
/** Voice call */
const TUid KLogCallEventTypeUid = {KLogCallEventType};
/** Data call. */
const TUid KLogDataEventTypeUid = {KLogDataEventType};
/** Fax call. */
const TUid KLogFaxEventTypeUid = {KLogFaxEventType};
/** SMS call. */
const TUid KLogShortMessageEventTypeUid = {KLogShortMessageEventType};
/** Email call. */
const TUid KLogMailEventTypeUid = {KLogMailEventType};
/** Task scheduler event. */
const TUid KLogTaskSchedulerEventTypeUid = {KLogTaskSchedulerEventType};

/**
Event types
@publishedPartner

*/
/** Lbs events. */
const TUid KLogLbsSelfLocateEventTypeUid = {KLogLbsSelfLocateEventType};
const TUid KLogLbsExternalLocateEventTypeUid = {KLogLbsExternalLocateEventType};
const TUid KLogLbsTransmitLocationEventTypeUid = {KLogLbsTransmitLocationEventType};
const TUid KLogLbsNetworkLocateEventTypeUid = {KLogLbsNetworkLocateEventType};
const TUid KLogLbsAssistanceDataEventTypeUid = {KLogLbsAssistanceDataEventType};

/**
@internalComponent
*/
const TUid KLogPacketDataEventTypeUid = {KLogPacketDataEventType};

/**
Duration Types
@internalComponent
*/
const TLogDurationType KLogDurationNone = 0;
const TLogDurationType KLogDurationValid = 1;
const TLogDurationType KLogDurationData = 2;
 
/**
Flags
Marks an event as having been "read".
@publishedAll

*/
const TLogFlags KLogEventRead = 0x1;

/**
@internalComponent
*/
const TLogFlags KLogEventContactSearched = 0x2;

class TLogSmsPduData
/**
The following should be used to store SMS PDU info in event data
@internalComponent
*/
	{
public:
	TInt iType; // message type;
	TInt iTotal;   //  total number of parts
	TInt iSent;   //  total number of parts sent
	TInt iDelivered;  //  total number of parts delivered to destination
	TInt iFailed;  //  total number of parts failed to be delivered to destination
	TInt iReceived;  //  total number of parts received for DELIVERs or SUBMITs read from the phone/SIM 
	};

#endif
