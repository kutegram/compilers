// EIKLIBRY.H
//
// Copyright (c) Symbian Software Ltd 1997-2006.  All rights reserved.
//

#ifndef __EIKLIBRY_H__
#define __EIKLIBRY_H__

#include <f32file.h>
#include <e32base.h>
#include <eikfctry.h>

/**
@publishedPartner

*/
typedef SEikControlInfo (*TCreateByTypeFunction)(TInt);


/**
Abstract base class specifying the interface for a dynamically-loaded DLL
which goes on to configure other Uikon statically-loaded DLLs.

@publishedPartner
@deprecated
*/
class CEikLibrary : public CBase
	{
public:
	// When EikEnv dynamically loads a DLL, it calls its InitializeL function
	// which will set up any variables which EikEnv requires. 
	virtual void InitializeL() = 0;
	// These functions give the EikEnv access to the libraries
	// resources and Control Factories. 
	virtual CArrayFix<TFileName>*				ResourceFileArrayL() const = 0;
	virtual CArrayFix<TCreateByTypeFunction>*	ControlFactoryArrayL() const = 0;
	IMPORT_C virtual void PostAppUiInitializeL();
	};


/**
Abstract base class specifying the interface for a ECom plugin DLL
which goes on to configure other Uikon statically-loaded DLLs.

@publishedPartner

*/
class CEikLibrary2 : public CEikLibrary
	{
public:
	// Destructor.
	IMPORT_C virtual ~CEikLibrary2();
	IMPORT_C static CEikLibrary2* LoadLibraryL(TUid aImplementationUid); 
private:
	// UID of the implementation instantiated.
	TUid iDtrkey;
	};

// __EIKLIBRY_H__
#endif
