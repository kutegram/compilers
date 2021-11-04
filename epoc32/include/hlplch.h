// HLPLCH.H
// Copyright (c) 2003 Symbian Ltd. All rights reserved.
//
// Help Launcher module
//

#ifndef __HLPLCH_H__
#define __HLPLCH_H__

#if !defined(__APGTASK_H__)
#include <apgtask.h>
#endif

#if !defined(__EIKDLL_H__)
#include <eikdll.h>
#endif

#if !defined(__WSERV_H__)
#include <w32std.h>
#endif

#if !defined(__COEHELP_H__)
#include <coehelp.h>
#endif

/** Help application UID. 
@internalComponent

*/
const TUid KHlpAppUid={ 0x10005234 };

/** UID of window message to send to application. 
@internalComponent

*/
const TUid KHlpAppWsMsg={ 0x100055c7 };

/** Maximum length of command line to launch application. 
@internalComponent

*/
const TInt KMaxCmdLineLength = 512;

// resource file name
_LIT(KHelpLauncherResource, "z:\\resource\\apps\\lch.rsc");

class CHlpCmdLine : public CBase
/**
@internalComponent

*/
	{
public:
	static CHlpCmdLine* NewL(CArrayFix<TCoeHelpContext>* aContextList);
	static CHlpCmdLine* NewLC(CArrayFix<TCoeHelpContext>* aContextList);
	~CHlpCmdLine();
public:
	TPtr8 CmdLineL();
private:
	void BuildCmdLineL();
	void AddContextL(TCoeHelpContext& aContext);
private:
	void ConstructL();
	CHlpCmdLine(CArrayFix<TCoeHelpContext>* aContextList);
private:
	CArrayFix<TCoeHelpContext>* iContextList;
	CBufFlat* iCmdLine;
	};

class HlpLauncher
/** Launches the help application.

It assumes that such an application is at z:\\Sys\\Bin\\CsHelp.exe

@publishedAll

*/
	{
public:
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession, CArrayFix<TCoeHelpContext>* aContextList);
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession, TUid aUid);
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession);
private:
	static void DoLaunchHelpApplicationL(RWsSession& aWsSession, const TDesC8& aCmdLine);
	};

#endif
