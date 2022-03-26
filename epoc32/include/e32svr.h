// e32\include\e32svr.h
//
// Copyright (c) 1995-2005 Symbian Software Ltd. All rights reserved.
//

#ifndef __E32SVR_H__
#define __E32SVR_H__
#include <e32hal.h>
#include <d32locd.h>
#include <e32notif.h>
#include <e32ldr.h>
#include <e32event.h>
#include <e32ktran.h>
#include <e32debug.h>
#include <e32lmsg.h>

/**
@internalComponent
@removed
*/
enum TBlockType {EBlocked,EUnBlocked,ERelease};

/**
A collection of static functions that are intended for internal use only, 
except for AddEvent.
@see UserSvr::AddEvent()
@publishedPartner

*/
class UserSvr
	{
public:
	IMPORT_C static void CaptureEventHook();	/**< @internalAll */
	IMPORT_C static void ReleaseEventHook();	/**< @internalAll */
	IMPORT_C static void RequestEvent(TRawEventBuf &anEvent,TRequestStatus &aStatus);	/**< @internalAll */
	IMPORT_C static void RequestEventCancel();	/**< @internalAll */
	IMPORT_C static TInt AddEvent(const TRawEvent& anEvent);
	IMPORT_C static void ScreenInfo(TDes8& anInfo);	/**< @internalAll */
	IMPORT_C static TInt DllSetTls(TInt aHandle, TAny *aPtr);	/**<@internalAll */
	IMPORT_C static TInt DllSetTls(TInt aHandle, TInt aDllUid, TAny *aPtr);	/**< @internalComponent */
	IMPORT_C static TAny *DllTls(TInt aHandle);	/**< @internalAll */
	IMPORT_C static TAny *DllTls(TInt aHandle, TInt aDllUid);	/**< @internalComponent */
	IMPORT_C static void DllFreeTls(TInt aHandle);	/**< @internalAll */
	IMPORT_C static void DllFileName(TInt aHandle, TDes &aFileName);	/**< @internalAll */
	IMPORT_C static void FsRegisterThread();	/**< @internalAll */
	IMPORT_C static void WsRegisterThread();	/**< @internalAll */
    IMPORT_C static TBool TestBootSequence();	/**< @internalAll */
    IMPORT_C static void WsRegisterSwitchOnScreenHandling(TBool aState);	/**< @internalAll */
    IMPORT_C static void WsSwitchOnScreen();	/**< @internalAll */
    IMPORT_C static TInt ChangeLocale(const TDesC& aLocaleDllName);	/**< @internalAll */
	IMPORT_C static TInt ResetMachine(TMachineStartupType aType);	/**< @internalAll */
	IMPORT_C static void UnlockRamDrive();	/**< @internalAll */
	IMPORT_C static void LockRamDrive();	/**< @internalAll */
	IMPORT_C static TUint32 RomRootDirectoryAddress();	/**< @internalAll */
	IMPORT_C static TInt ExecuteInSupervisorMode(TSupervisorFunction aFunction, TAny* aParameter);	/**< @internalAll */
	IMPORT_C static TUint32 RomHeaderAddress();	/**< @internalAll */
	IMPORT_C static TUint32 DebugMask();	/**< @internalAll */ //Return the kernel debug mask 0
	IMPORT_C static TUint32 DebugMask(TUint aIndex);	/**<@internalAll */	// Return the kernel debug mask
	IMPORT_C static TInt HalFunction(TInt aGroup, TInt aFunction, TAny* a1, TAny* a2);	/**<@internalAll */
	IMPORT_C static TInt HalFunction(TInt aGroup, TInt aFunction, TAny* a1, TAny* a2, TInt aDeviceNumber);	/**<@internalAll */
	IMPORT_C static TInt HalGet(TInt,TAny*);	/**<@internalAll */ // redundant - only here for BC
	IMPORT_C static TInt HalSet(TInt,TAny*);	/**<@internalAll */ // redundant - only here for BC
	IMPORT_C static TInt SetMemoryThresholds(TInt aLowThreshold, TInt aGoodThreshold); /**<@internalAll */
	IMPORT_C static TBool IpcV1Available();	/**<@internalAll */
	IMPORT_C static TLinAddr ExceptionDescriptor(TLinAddr aCodeAddress); /**< @internalTechnology */
	IMPORT_C static TInt LocalePropertiesSetDefaults();	/**< @internalTechnology */
	};

#endif

