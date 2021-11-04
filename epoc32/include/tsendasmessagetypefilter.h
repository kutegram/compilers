// TSendAsMessageTypeFilter.h
//
// Copyright (c) 2004-2005 Symbian Software Ltd. All rights reserved.
//

#ifndef __TSENDASMESSAGETYPEFILTER_H__
#define __TSENDASMESSAGETYPEFILTER_H__


#include <rsendas.h>

/**
This class encapsulates filter information for available message type modules
(MTMs) held by the SendAs session.

@publishedAll

*/
class TSendAsMessageTypeFilter
	{
public:
	IMPORT_C TSendAsMessageTypeFilter();
	IMPORT_C TSendAsMessageTypeFilter(TUid aMsgCap);
	IMPORT_C TSendAsMessageTypeFilter(TUid aMsgCap, TInt aVal, RSendAs::TSendAsConditionType aCond);
	IMPORT_C void Reset();
public:
	TUid iMessageCapability;
	TInt iValue;
	RSendAs::TSendAsConditionType iCondition;
	};


// __TSENDASMESSAGETYPEFILTER_H__
#endif

