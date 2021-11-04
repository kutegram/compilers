// CSecurityPolicy.inl
//
// Copyright (c) Symbian Software Ltd 2001-2005. All rights reserved.

/** 
	@file CSecurityPolicy.inl
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __CSECURITYPOLICY_INL__
#define __CSECURITYPOLICY_INL__


inline CSecurityPolicy* CSecurityPolicy::NewL(RStringPool aStringPool)
	{
	_LIT8(KDataTypeName, "security-policy");

	// CSecurityPolicy ECOM Interface UID = 101F4485
	const TUid KUidSecPolInterface = {0x101F4485};

	// Set up the parameters which allow ECOM's resolver to pick the right implementation
	TEComResolverParams resParams;
	resParams.SetDataType(KDataTypeName());

	// Get the instantiation.  Allow ECOM to use the default resolver.  Pass in the init params.
	TAny* ptr = REComSession::CreateImplementationL(KUidSecPolInterface,
								 _FOFF(CSecurityPolicy, iDtor_ID_Key),
								 &aStringPool,
								 resParams);

	return REINTERPRET_CAST(CSecurityPolicy*, ptr);
	}

inline CSecurityPolicy::~CSecurityPolicy()
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}

inline CSecurityPolicy::CSecurityPolicy(RStringPool aStrPool)
	: iStrPool(aStrPool)
	{
	}



inline void CSecurityPolicy::Reserved1()
	{}
inline void CSecurityPolicy::Reserved2()
	{}


// __CSECURITYPOLICY_INL__
#endif
