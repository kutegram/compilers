// Telephony.inl
//
// Copyright (c) Symbian Software Ltd. 2003-2004.  All rights reserved.

// inline-functions are not embedded in Telephony.DLL.
// So, they don't get EXPORTed, and they don't
// have any associated ordinal at link-time.

/** @file
 *  Inline code, logically part of Etel3rdParty.h
 */

inline TVersion CTelephony::Version() const
/**
 Get current CTelephony version
 
 This function returns major, minor, and build version-numbers.
 
 @return	TVersion object, see E32STD.H
 */
	{
	return(TVersion(KTelephonyMajorVersionNumber,
					KTelephonyMinorVersionNumber,
					KTelephonyBuildVersionNumber));
	}
