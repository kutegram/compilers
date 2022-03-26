// ASCLICLIENTUTILS.H
//
// Copyright (c) Symbian Software Ltd 1999-2005. All rights reserved.
//
#ifndef __ASCLICLIENTUTILS_H__
#define __ASCLICLIENTUTILS_H__

// System includes
#include <e32base.h>


///////////////////////////////////////////////////////////////////////////////////////
// ----> AlarmClientUtils (header)
///////////////////////////////////////////////////////////////////////////////////////
class AlarmClientUtils
/**
@publishedAll

*/
	{
///////////////////////////////////////////////////////////////////////////////////////
public:										// ENUMERATIONS
///////////////////////////////////////////////////////////////////////////////////////
	/** Panic numbers associated with the ALMSRVCLI panic category. */
	enum TAlarmClientPanic
		{
		EAlarmClientPanicArgument			= 0,
		EAlarmClientPanicCancel				= 1,
		EAlarmClientPanicSessionClose		= 2,
		EAlarmClientPanicSetAlarm			= 3,
		EAlarmClientPanicGetAlarm			= 4,
		EAlarmClientPanicInvalidAlarmID		= 5,
		EAlarmClientPanicAlarmInfo			= 6,
		EAlarmClientPanicSound				= 7,
		EAlarmClientPanicOwner				= 8,
		EAlarmClientPanicVerify				= 9,
		EAlarmClientPanicAlarmDay			= 10,
		EAlarmClientPanicNumber				= 11,
		EAlarmClientPanicNoArray			= 12,
		EAlarmClientPanicNotificationCancel	= 13,
		//
		EAlarmClientPanicLast
		};
	/** Panic numbers associated with the ALMSRVCLIFAULT panic category. */
	enum TAlarmClientFault
		{
		EAlarmClientFaultLogic				= 0,
		EAlarmClientFaultData				= 1,
		EAlarmClientFaultCouldNotLoadServer	= 2,
		//
		EAlarmClientFaultDebugFuncError		= 3,
		//
		EAlarmClientFaultLast
		};

///////////////////////////////////////////////////////////////////////////////////////
public:										// INTERNAL CONSTRUCT
///////////////////////////////////////////////////////////////////////////////////////

	static void								Panic(TAlarmClientPanic aPanic);

	static void								Fault(TAlarmClientFault aFault);

	IMPORT_C static TInt					StartAlarmServer();
	};

#endif
