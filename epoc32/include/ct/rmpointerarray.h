// RMPointerArray.h
//
// Copyright (c) 2001 Symbian Software Ltd. All rights reserved.
//
/**
 * @file
 *
 * @publishedAll
 * 
 */

#ifndef __RMPOINTERARRAY_H__
#define __RMPOINTERARRAY_H__


/**
 * An array of pointers to objects, that adds close type behaviour.
 *
 * For use with M class pointers, which have a release method and are owned by 
 * the array. When the array is closed, the objects will be released.
 *
 * @see RMPointerArray
 * @publishedPartner
 * 
 * 
 */
template<class T> class RMPointerArray : public RPointerArray<T>
	{
 public:
	/** Constructor */
	inline RMPointerArray();
	/** Frees all resources, calling Release() on the contents of the array */
	inline void Close();
	};

/** Default constructor. */
template <class T>
inline RMPointerArray<T>::RMPointerArray()
	{
	}

/** 
 * Closes the array and frees all resources; this includes deleting the objects 
 * whose pointers are held by the array. 
 */
template <class T>
inline void RMPointerArray<T>::Close()
	{
	TInt count = this->Count();
	for (TInt ii = 0; ii < count; ii++)
		(*this)[ii]->Release();
	this->Reset();
	}

#endif
