// TCTFindTokenTypesByInterface.h
//
// Copyright (c) 2001 Symbian Software Ltd. All rights reserved.
//
/**
 * @file
 *
 * @publishedPartner
 * 
 */

#ifndef __TCTFINDTOKENTYPESBYINTERFACE_H__
#define __TCTFINDTOKENTYPESBYINTERFACE_H__

#include <ct/mcttokentypefilter.h>


/** 
 * A filter that returns only those token types that match the required set of 
 * interfaces.
 *
 * On construction, an array containing the required interfaces is passed in.
 *
 * Token types will be matched if every interface in the supplied array is supported 
 * by the token type. 
 *
 * 
 */
class TCTFindTokenTypesByInterface : public MCTTokenTypeFilter
	{
 public:
	/** 
	 * Constructor.
	 *
	 * @param aInterfaces	An array of Uids corresponding to the interfaces that the 
	 * 						token type must support. */
	IMPORT_C TCTFindTokenTypesByInterface(const TArray<TUid> aInterfaces);

	/** 
	 * Tests whether all the interfaces associated with the filter are supported by 
	 * the token type.
	 *
	 * @param aTokenType	The token type to be tested.
	 * @return				ETrue if all the interfaces associated with the filter are supported 
	 * 						by the token type; EFalse, otherwise. 
	 */
	virtual TBool Accept(const CCTTokenTypeInfo& aTokenType) const;

 private:
	const TArray<TUid> iInterfaces;
	};

// __TCTFINDTOKENTYPESBYINTERFACE_H__
#endif
