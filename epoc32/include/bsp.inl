// bsp.inl
//
// Copyright (c) 1999 Symbian Software plc.  All rights reserved.
//

inline void TMsvBIOEntry::SetBIOParserUid(const TUid aId)
/** Sets the BIO parser UID.

@param aId BIO parser UID */
	{
	iBioType = aId.iUid;
	}
	
inline const TUid TMsvBIOEntry::BIOParserUid() const
/** Gets the BIO parser UID.

@return BIO parser UID */
	{
	return TUid::Uid(iBioType);
	}

inline void TMsvBIOEntry::SetLocationOfData(const TMsvBIODataLocation aLocation)
/** Sets the BIO data location flag.

@param aLocation BIO data location flag */
	{
	iLocationOfData = aLocation;
	}

inline const TMsvBIODataLocation TMsvBIOEntry::LocationOfData() const
/** Gets the BIO data location flag.

@return BIO data location flag */
	{
	return iLocationOfData;
	}
