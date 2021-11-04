// VCARD.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// CParserPropertyValueAgent
//
inline CParserVCard* CParserPropertyValueAgent::Value() const
/** Gets the agent object owned by the property value.

@return A pointer to the agent property value. */
	{return iValue;}

inline void CParserGroupedProperty::SetGroups(CDesC8Array* aArrayOfGroups)
/** Sets the list of groups to which the property belongs, replacing any existing 
list.

@param aArrayOfGroups Array of descriptors; each of which specifies 
a group name. The grouped property takes ownership of the array. */
	{iArrayOfGroups=aArrayOfGroups;}

inline const CDesC8Array* CParserGroupedProperty::Groups()
/** Gets the groups to which the property belongs.

@return Pointer to an array of descriptors. Each one specifies a group name. */
	{return iArrayOfGroups;}
