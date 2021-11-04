// ES_PROT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.


inline TInt CProtocolBase::RefCount() const
/**
Reference counting by protocols created by protocol families.

@return number of protocols
*/
	{ return iRefCount; }

inline TInt CProtocolFamilyBase::RefCount() const
	{
	return iRefCount;
	}

inline void CResolverProvdBase::SetNotify(MResolverNotify * aNotifier)
	{ iNotify=aNotifier; }

