// CMStack.inl
//
// Copyright (c) Symbian Software Ltd 1999-2007. All rights reserved.
//

#include <cmarkedstack.h>

/** Destructor.

It clears all marks.
*/
template <class T, TBool Owner>
inline CMarkedStack<T, Owner>::~CMarkedStack()
{
	iMarks.Clear();
}

/** Marks the stack's head item.

@param aMarkType Mark type
*/
template <class T, TBool Owner>
void 
inline CMarkedStack<T, Owner>::MarkL(TInt aMarkType)
	{
	TMarkPoint* point = new (ELeave) TMarkPoint(aMarkType, this->Count());
	iMarks.PushL(point);
	}

/** Removes all marks until a mark of the specified type is found.

@return Index of the stack item marked by the found mark
@param aMarkType Mark type
*/
template <class T, TBool Owner>
TInt 
inline CMarkedStack<T, Owner>::RemoveMark(TInt aMarkType)
	{
	TMarkPoint* point = NULL;
	do
		{
		delete point;
		point = iMarks.Pop();
		} while (point->iMarkType != aMarkType);
	TInt stackIndex = point->iStackIndex;
	delete point;
	return stackIndex;
	}

/** Pops and deletes items from the stack until the item marked with the specified mark type is at the head.

@param aMarkType Mark type
*/
template <class T, TBool Owner>
void 
inline CMarkedStack<T, Owner>::DeleteToMark(TInt aMarkType)
	{
	TInt lastMark = RemoveMark(aMarkType);
	while (this->Count() > lastMark)
		delete this->Pop();
	}

/** Pops items from the stack until the item marked with the specified mark type is at the head.

@param aMarkType Mark type
*/
template <class T, TBool Owner>
void 
inline CMarkedStack<T, Owner>::ResetToMark(TInt aMarkType)
	{
	TInt lastMark = RemoveMark(aMarkType);
	while (this->Count() > lastMark)
		this->Pop();
	}
