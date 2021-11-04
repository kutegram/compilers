// FEPPLUGIN.H
//
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.
//

#ifndef __FEPPLUGIN_H__
#define __FEPPLUGIN_H__

#include <e32base.h>

class CCoeEnv;
class CCoeFep;
class CCoeFepParameters;

const TUid KUidFepPluginInterface = { 0x1020233F };

/**
CCoeFepPlugIn
Abstract base class for FEP plug ins
@publishedAll

*/
class CCoeFepPlugIn : public CBase
	{
public:
	inline static CCoeFepPlugIn* NewL(TUid aFepUid);
	virtual ~CCoeFepPlugIn();
public:
	/** Creates a fully constructed object of CCoeFEP.

	@param aConeEnvironment	A reference to the application's control environment.
	@param aFepParameters FEP parameters.
	@return A pointer to the newly created object.
	*/
	virtual CCoeFep* NewFepL(CCoeEnv& aConeEnvironment, const CCoeFepParameters& aFepParameters) = 0;

	/** Runs the FEP settings dialog. 
	
	@param aConeEnvironment A reference to the application's control environment.
	*/
	virtual void SynchronouslyExecuteSettingsDialogL(CCoeEnv& aConeEnvironment) = 0;

private:
	TUid iDtorTag;
	};

#include <fepplugin.inl>

// __FEPPLUGIN_H__
#endif
