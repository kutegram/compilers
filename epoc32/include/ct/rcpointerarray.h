// RCPointerArray.h
//
// Copyright (c) 2001, 2007 Symbian Software Ltd. All rights reserved.
//
/**
 * @file
 *
 * @publishedAll
 * 
 */


#ifndef __RCPOINTERARRAY_H
#define __RCPOINTERARRAY_H
#include <e32cmn.h>

/** 
 * An array of pointers to objects, that adds close type behaviour.
 *
 * For use with C class pointers that are owned by the array. 
 * @see RCPointerArray
 * 
 */
template<class T> class RCPointerArray : public RPointerArray<T>
	{
 public:
	/** Constructor */
	inline RCPointerArray();
	/** Closes the array and frees all resources (including deleting objects in the array). */
	inline void Close();
	};

/** Default constructor. */
template <class T>
inline RCPointerArray<T>::RCPointerArray()
	{
	}

/**
 * Closes the array and frees all resources; this includes deleting the objects 
 * whose pointers are held by the array (i.e. it's the same as ResetAndDestroy()).
 */
template <class T>
inline void RCPointerArray<T>::Close()
	{
	this->ResetAndDestroy();
	}

#endif
