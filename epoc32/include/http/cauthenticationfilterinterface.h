// CAuthenticationFilterInterface.h
//  
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file CAuthenticationFilterInterface.h
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef	__CAUTHENTICATIONFILTERINTERFACE_H__
#define	__CAUTHENTICATIONFILTERINTERFACE_H__

// System includes
#include <e32base.h>
#include <ecom/ecom.h>
#include <http/rhttpsession.h>

// Forward declarations
class MHTTPAuthenticationCallback;


class CAuthenticationFilterInterface : public CBase
/**
The ECOM interface definition for an HTTP authentication filter.  Implementations
of an authentication filter must inherit this class.
@publishedAll

*/
	{
public: // Methods
	/**
	@fn				InstallFilterL(RHTTPSession& aSession, MHTTPAuthenticationCallback* aCallback)
	Intended Usage:	This method is used to install the authentication filter to the filter queue.
					The returned pointer is not owned as the filters must be self-destroying when
					they are unloaded.
	@param			aSession A handle to the transport session
	@param			aCallback A pointer to the object implementing the callback function
	@return			Pointer to the newly installed plugin
	@pre 			The session had already been setup
	@post			The filter(s) have been installed
	*/
	inline static void InstallFilterL(RHTTPSession& aSession, MHTTPAuthenticationCallback* aCallback);

	/**
	@fn				~CAuthenticationFilterInterface()
	Intended Usage:	Virtual destructor
	@pre 			The object identified by the destructor key in iEcomDtorID exists
	@post			The object is destroyed
	*/
	inline ~CAuthenticationFilterInterface();

public:
	struct TAuthenticationParams
		{
		RHTTPSession* iSession;
		MHTTPAuthenticationCallback* iCallback;
		};

private: // Attributes
	/// The ECom destructor key identifier
	TUid iEcomDtorID;
	};

//----------------------------------------------------------------------------------------

inline void CAuthenticationFilterInterface::InstallFilterL(RHTTPSession& aSession, MHTTPAuthenticationCallback* aCallback)
	{
	const TUid KUidAuthenticationFilter = {0x101F447C};
	TAuthenticationParams authParams;
	authParams.iSession = &aSession;
	authParams.iCallback = aCallback;
	REComSession::CreateImplementationL(KUidAuthenticationFilter, _FOFF(CAuthenticationFilterInterface,iEcomDtorID), &authParams);
	}

inline CAuthenticationFilterInterface::~CAuthenticationFilterInterface()
	{
	REComSession::DestroyedImplementation(iEcomDtorID);
	}

// __CAUTHENTICATIONFILTERINTERFACE_H__
#endif
