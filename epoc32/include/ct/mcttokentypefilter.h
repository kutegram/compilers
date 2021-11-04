// MCTTokenTypeFilter.h
//
// Copyright (c) 2001 Symbian Software Ltd. All rights reserved.
//
/**
 * @file
 *
 * @publishedPartner
 * 
 */
 
#ifndef __MCTTOKENTYPEFILTER_H__
#define __MCTTOKENTYPEFILTER_H__

class CCTTokenTypeInfo;


/** 
 * A filter that is used to control which token types appear in a list returned 
 * by CCTTokenTypeInfo::ListL().
 * 
 * Each possible token type is offered to the filter in turn, which returns ETrue 
 * if it is to be included. 
 * 
 * For most clients one of the following three defined subclasses will do what is wanted:
 * @li	TCTAllTokenTypes --							returns everything
 * @li	TCTFindTokenTypesByInterface --				finds token types that support all of 
 * 													a supplied set of interfaces
 * @li TCTFindTokenTypesByInterfaceAndAttribute --	finds token types that match a particular 
 * 													list of interfaces, and a particular set of 
 * 													attribute/value pairs.
 * 
 * Clients wanting more unusual matching criteria may need to write their own subclasses. 
 *
 * 
 */
class MCTTokenTypeFilter
	{
 public:
	/** 
	 * Tests whether the supplied token type should be included in the list.
	 *
	 * @param aTokenType	The token type to be tested.
	 * @return				ETrue, if the supplied token type should be included in the list; EFalse, otherwise. 
	 */
	virtual TBool Accept(const CCTTokenTypeInfo& aTokenType) const = 0;
	};

// __MCTTOKENTYPEFILTER_H__
#endif

