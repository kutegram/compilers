// TCTAllTokenTypes.h
//
// Copyright (c) 2001 Symbian Software Ltd. All rights reserved.
//
/**
 * @file
 *
 * @publishedPartner
 * 
 */

#ifndef __TCTALLTOKENTYPES_H__
#define __TCTALLTOKENTYPES_H__

#include <ct/mcttokentypefilter.h>


/**
 * A filter that includes all token types.
 *
 * Used by CCTTokenTypeInfo::ListL()
 *
 *  @see MCTTokenTypeFilter. 
 */
class TCTAllTokenTypes : public MCTTokenTypeFilter
	{
 public:
	/** 
	 * Tests whether to accept all token types.
	 *
	 * Note that it always returns ETrue.
	 * 
	 * @param aTokenType	The token type to be tested.
	 * @return				ETrue always. 
	 */
	IMPORT_C virtual TBool Accept(const CCTTokenTypeInfo& aTokenType) const;
	};

// __TCTALLTOKENTYPES_H__
#endif
