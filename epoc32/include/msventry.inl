// MSVENTRY.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


//**********************************
// CMsvServerEntry
//**********************************

inline const TMsvEntry& CMsvServerEntry::Entry() const
/** Gets the context's index entry.

@return The current entry */
	{
	return iEntry;
	}

inline const TMsvSelectionOrdering& CMsvServerEntry::Sort()
/** Gets the current sort order of children of the entry. 

@return Current sort type */
	{
	return iOrdering;
	}

inline void CMsvServerEntry::SetSort(TMsvSelectionOrdering& aOrdering)
/** Sets the sort order that is used when listing children, for example with GetChildren().

@param aOrdering Sort order to use */
	{
	iOrdering=aOrdering;
	}

inline void CMsvServerEntry::SetMtm(TUid aMtm)
/** Sets this MTM sorting type to specified UID. When children of an entry are 
sorted, entries belonging to the same MTM type can be grouped together. 

@param aMtm UID of MTM for sort */
	{
	iMtm=aMtm;
	}
