// ES_SOCK.INL
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.

inline TSockIOBufC::TSockIOBufC()	: TPckgC<TSockIO>(iArgs)

	{}

inline TSockOpenBufC::TSockOpenBufC()	: TPckgC<TSockOpen>(iArgs)

	{}

inline SSockAddr *TSockAddr::BasePtr() const
/**
This function returns the end point to a connection.

@return socket address
*/
	{ return (SSockAddr*)iBuf; }


inline TUint8 *TSockAddr::UserPtr() const
/** Gets an offset to place data after the base class data. This function is mainly 
intended for use in derived classes.
@return Pointer to derived class intended data area */
	{ return (TUint8*)(BasePtr()+1); }

inline TUint16 ByteOrder::Swap16(TUint aVal)
/** 
Reverses the order of the bytes in a 16-bit value.
	
@param aVal The value to reverse. 
@return The reversed value. 
*/
	{ return ByteOrder::Swap16((TUint16)aVal); }

inline TNameRecord::TNameRecord()
	:iName(),iAddr(),iFlags(0)	
/** 
Trivial C++ constructor. This sets the fields in the 
class to suitable default values. 
*/
	{}

inline TNifProgress::TNifProgress()	:iStage(0), iError(KErrNone) 
/**
It sets the iStage data member to 0 and the iError data member to KErrNone.
*/
	{}

inline RSubConnection::TEventFilter::TEventFilter(TInt32 aEventGroupId, TUint32 aEventMask)
	: iEventGroupUid(aEventGroupId), iEventMask(aEventMask)
	{
	}

inline TUint32 CSubConParameterFamily::Id()
/**
Fetch the identity of the sub-connection parameter family
*/
	{
	return iFamilyId;
	}

inline TAccessPointInfo::TAccessPointInfo(TUint aApId)
/** Initialises the object using the specified 32-bit long integer ID of the access point.

@param aApId The 32-bit long integer ID of the access point to initialise the object with. */
	{
	iAccessPointId = aApId;
	}

inline TUint TAccessPointInfo::AccessPoint() const
/** Returns the 32-bit long integer ID of the access point.

@return The 32-bit long integer ID of the access point. */
	{
	return iAccessPointId;
	}

inline void TAccessPointInfo::SetAccessPoint(TUint aAccessPoint)
/** Sets the 32-bit long integer ID of the access point.

@param aAccessPoint The 32-bit long integer ID of the access point. */
	{
	iAccessPointId = aAccessPoint;
	}
	
inline TBool TAccessPointInfo::operator== (const TAccessPointInfo& aRhs) const
/** Compares the 32-bit long integer ID of the specified object with our own.

@param aRhs The TAccessPointInfo to compare.
@return A boolean value of ETrue if the TAccessPointInfo object has the same ID or false otherwise. */
	{
	return iAccessPointId == aRhs.iAccessPointId;
	}
