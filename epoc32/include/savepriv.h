// SAVEPRIV.H
//
// Copyright (c) 1997-2007 Symbian Software Ltd. All rights reserved.
//

#if !defined(SAVEPRIV_H)
#define SAVEPRIV_H


_LIT(__SHUTDOWN_SERVER_NAME,"!ShutdownServer");

/**
@internalTechnology
*/
const TInt KShutdownMajorVN			=6;
const TInt KShutdownMinorVN			=0;
const TInt KShutdownBuildVN			=1;
const TInt KShutdownMessageSlots	=1;

/**
@internalTechnology
*/
enum TSaveNotifierOpCode
	{
	TSaveOpCodeNotify,
	TSaveOpCodeNotifyCancel,
	TSaveOpCodeHandleError,
	TSaveOpCodePowerOff,        //Supported only in special test debug build.
	TSaveOpCodeQueryPowerState  //Supported only in special test debug build.
	};

/**
@internalTechnology
*/
struct TErrorAndClientId
	{
	TInt iError;
	TUint iClientId;
	};

//
// TShutdownServerStart
//
/**
@internalTechnology
*/
class TShutdownServerStart
	{
public:
	TShutdownServerStart(TRequestStatus& aStatus);
	TPtrC AsCommand() const;
//
	TShutdownServerStart();
	TInt GetCommand();
	void SignalL();
private:
	TThreadId iId;
	TRequestStatus* iStatus;
	};


#endif
