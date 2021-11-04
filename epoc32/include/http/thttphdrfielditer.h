// THTTPHdrFieldIter.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file THTTPHdrFieldIter.h
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __THTTPHDRFIELDITER_H__
#define __THTTPHDRFIELDITER_H__

// System includes
#include <e32std.h>
#include <stringpool.h>

// Forward declarations
class CHeaders;


//##ModelId=3A914DFD005C
class THTTPHdrFieldIter
/** 
Iterator class to iterate the fields within a RHTTPHeaders. 
@publishedAll

*/
	{
public:
	/** Construct an iterator for the fields of the supplied header collection.
		@param aHeaders The header collection whose fields we want to iterate
	*/
	//##ModelId=3A914DFD0087
	THTTPHdrFieldIter(const CHeaders* aHeaders);
	/** Class destructor
	*/
	//##ModelId=3A914DFD0086
	IMPORT_C ~THTTPHdrFieldIter();

	/** Reset iterator to point at the first field in the header collection
	*/
	//##ModelId=3A914DFD0085
	IMPORT_C void First();

	/** Check if the iterator is at the end of the collection. If so,
	    further calls to operator() will return NULL.
		@return True if the iterator has reached the end of the header
		fields 
	*/
	//##ModelId=3A914DFD0084
	IMPORT_C TBool AtEnd() const;

	/** Advance the iterator to the next field.
		@return True if the iterator still points at a valid part
		after advancing.
	*/
	//##ModelId=3A914DFD007E
	IMPORT_C void operator++();

	/** Obtain the name of the header field currently pointed at by
		the iterator.
		@return The field name; or <empty string> if the iterator has
		gone off the end of the header collection 
	*/
	//##ModelId=3A914DFD007D
	IMPORT_C RStringTokenF operator()();

private:

	/** Check the iterator state for invalidity following deletions in the collection
	*/
	//##ModelId=3BA613240002
	void CheckInvalidation();

	/** The headers whose fields we are iterating.
	*/
	//##ModelId=3A914DFD007A
	const CHeaders* iHeaders;
	/** The index of the field in the header that is currently pointed
		at by the iterator
	*/
	//##ModelId=3A914DFD0072
	TInt iPosIdx;
	};

inline THTTPHdrFieldIter::THTTPHdrFieldIter(const CHeaders* aHeaders)
	: iHeaders(aHeaders)
	{
	First();
	}


// __THTTPHDRFIELDITER_H__
#endif
