// PushEntry.inl
//
// Copyright (c) 2000-2003 Symbian Ltd.  All rights reserved.
//

// WAP Push Message Inline functions  File for the Utility class

/** @file
@publishedPartner

*/

#include <msvapi.h>

inline const TMsvEntry& CPushMsgEntryBase::Entry() const
/** 
Gets the object's current message server index entry.

@return 
Message server index entry 
*/
	{
	return iEntry;
	}


inline TInt CPushMsgEntryBase::Status() const
/** 
Gets the Status value for the Push Message entry.

@return 
Status value: a TPushMsgStatus value 
*/
	{
	//The status value is one from an enumerated set. It is used to set Bits 0-3 
	//of the iMtmData1 member of TMsvEntry. A bitwise AND is performed with iMtmData1 
	//and a mask with value 0x000F to extract the status value.

	return iEntry.MtmData1() & KPushMaskOnlyStatus;//bitwise & to get Bits 0-3
	}
