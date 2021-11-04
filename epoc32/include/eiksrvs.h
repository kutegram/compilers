// EIKSRVS.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2006. All rights reserved.
//

#ifndef __EIKSRVS_H__
#define __EIKSRVS_H__

#include <eikappui.h>
#include <eikenv.h>
#include <eiksrv.pan>
#include <apgtask.h>
#include <eiksrv.h>

class CDictionaryFileStore;

/**
@publishedPartner

*/
_LIT(EIKAPPUI_SERVER_NAME,"!EikAppUiServer");

/**
@publishedPartner

*/
_LIT(EIKAPPUI_SERVER_THREAD_NAME,"EikAppUiServerThread");

/**
@publishedPartner

*/
_LIT(EIKAPPUI_SERVER_SEMAPHORE,"EikAppUiServerStartSemaphore");

/**
@internalComponent
*/
const TInt KEikSrvDefaultHeapSize=0x10000;

/**
@internalComponent
*/
const TInt KEikSrvDefaultMaxHeapSize=0x100000;

enum TEikAppUiRanges
	{
	EFirstUnrestrictedOpcodeInEikAppUi
	};

/**
@internalComponent
*/
enum TEikUiOpCode
	{
	// No Capability requirement
	EEikAppUiFirst=EFirstUnrestrictedOpcodeInEikAppUi,
	EEikAppUiLaunchTaskList,
	EEikAppUiCycleTasks,
	EEikAppUiSetStatusPaneFlags,
	EEikAppUiSetStatusPaneLayout,
	EEikAppUiBlankScreen,
	EEikAppUiUnblankScreen,
	EEikAppUiResolveError,
	EEikAppUiExtension,
	EEikAppUiEnableTaskList,
	EEikAppUiGetDebugPreferences,	
	EEikAppUiResolveErrorWithTitleText,
	// End Marker no Capability
	EEikAppUiFirstUnusedOpcode,
	};

/**
function to panic the server

@internalComponent
*/
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);

// __EIKSRVS_H__
#endif
