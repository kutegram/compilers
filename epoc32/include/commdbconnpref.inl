// Copyright (c) 2006 Symbian Software Ltd.  All rights reserved.
//
// commdbconnpref.inl
//

/**
@file
@deprecated since v9.1. Functionality is replaced with commsdat.
*/

inline TBool TCommDbConnPref::operator==(const TCommDbConnPref& aPref) const
/**
Overloaded function for operator "==" 

@param aPref Reference to the class TCommDbConnPref
@return ETrue if Successful if both the objects are equal else EFalse
*/
	{
	return (Compare(aPref) == 0);
	}

inline TBool TCommDbConnPref::operator!=(const TCommDbConnPref& aPref) const
/**
Overloaded function for operator "!=" 

@param aPref Reference to the class TCommDbConnPref
@return Etrue if Successful if the objects are not equal else EFalse
*/
	{
	return (Compare(aPref) != 0);
	}

inline SCommDbConnPref* TCommDbConnPref::PrefPtr() const
	{
#ifdef SYMBIAN_NON_SEAMLESS_NETWORK_BEARER_MOBILITY
	return reinterpret_cast<SCommDbConnPref*>(UserPtr());
#else
	return (SCommDbConnPref*)UserPtr();
#endif
	}

inline TCommDbConnPref& TCommDbConnPref::Cast(const TConnPref& aPref)
/**
Casts the TConnPref object to TCommDbConnPref

@param aPref Connection preferences.
@return Reference to TCommDbConnPref
*/
	{
#ifdef SYMBIAN_NON_SEAMLESS_NETWORK_BEARER_MOBILITY
	// converting const TConnPref* to const TCommDbConnPref* and then casting away the constness
	return *const_cast<TCommDbConnPref*>((reinterpret_cast<const TCommDbConnPref*>(&aPref)));
#else
	return *((TCommDbConnPref*)&aPref);
#endif
	}

inline SCommDbMultiConnPref* TCommDbMultiConnPref::PrefPtr() const
	{
#ifdef SYMBIAN_NON_SEAMLESS_NETWORK_BEARER_MOBILITY
	return reinterpret_cast<SCommDbMultiConnPref*>(UserPtr());
#else
	return (SCommDbMultiConnPref*)UserPtr();
#endif
	}

inline TCommDbMultiConnPref& TCommDbMultiConnPref::Cast(const TConnPref& aPref)
/**
Casts the TConnPref object to TCommDbMultiConnPref

@param aPref Connection preferences.
@return Reference to TCommDbMultiConnPref
*/
	{
#ifdef SYMBIAN_NON_SEAMLESS_NETWORK_BEARER_MOBILITY
	// converting const TConnPref* to const TCommDbMultiConnPref* and then casting away the constness
	return *const_cast<TCommDbMultiConnPref*>((reinterpret_cast<const TCommDbMultiConnPref*>(&aPref)));
#else
	return *((TCommDbMultiConnPref*)&aPref);
#endif
	}
