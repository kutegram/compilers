// EIKSRVC.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2007. All rights reserved.
//

#ifndef __EIKSRVC_H__
#define __EIKSRVC_H__

#include <eiksrvs.h>
#include <eiksrv.h>

const TInt KNumConnectRetries = 5;
/** 
@internalComponent
*/
typedef TThreadFunction* (*EikSrvEntrypoint)();

class CEikDebugPreferences;

/**
@publishedPartner 

*/
class REikAppUiSession : public RSessionBase
	{
public:
	IMPORT_C REikAppUiSession();
	IMPORT_C TInt Connect();
	IMPORT_C void Close();
	IMPORT_C TVersion Version() const;
	IMPORT_C void LaunchTaskList() const;
	IMPORT_C void CycleTasks(TTaskCycleDirection aDirection) const;
	IMPORT_C TInt SetStatusPaneFlags(TInt aFlags) const;
	IMPORT_C TInt SetStatusPaneLayout(TInt aLayoutResId) const;
	IMPORT_C TInt BlankScreen() const;
	IMPORT_C TInt UnblankScreen() const;
	IMPORT_C CEikonEnv::TErrorValidity ResolveError(TDes& aText,TInt aError,TUid aAppUid) const;
	IMPORT_C void Extension(TUid aExtensionUid,const TDesC8& aBuffer,TRequestStatus& aRequestStatus) const;
	IMPORT_C TInt GetInstalledFepName(TDes& aName) const;
	IMPORT_C TInt SetInstalledFepName(const TDesC& aName, TBool aRaiseFileError) const;
	IMPORT_C CColorList* GetSystemColorsL() const;
	IMPORT_C void SetSystemColorsL(const CColorList& aColorList) const;
	IMPORT_C TInt OpenFepAttributes() const;
	IMPORT_C TInt GetFepAttribute(TUid aAttribUid, TDes8& aAttribData) const;
	IMPORT_C TInt SetFepAttribute(TUid aAttribUid, const TDesC8& aAttribData) const;
	IMPORT_C TInt CommitFepAttributes() const;
	IMPORT_C void CloseFepAttributes() const;
	IMPORT_C TInt EnableTaskList() const;
	IMPORT_C virtual void REikAppUiSession_Reserved1();
	IMPORT_C virtual void REikAppUiSession_Reserved2();
	IMPORT_C CEikDebugPreferences* GetDebugPreferencesL() const;
	IMPORT_C CEikonEnv::TErrorValidity ResolveErrorWithTitleL(TDes& aErrorText, TInt aError, TInt& aTextId, TUint& aFlags, TDes& aTitleText, TBool aIsMemoryAllocatedByErrResolver) const;
private:
	class CExtension;
	void StartServerL();
#if defined(__WINS__)
private:
	RLibrary iNotUsed; // kept for the moment to preserve sizeof(REikAppUiSession)
#endif
private:
	CExtension* iExtension;
	};

//**********************************
//global functions
//**********************************

/**
function to panic the server
@internalComponent
*/
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);


// __EIKSRVC_H__
#endif

