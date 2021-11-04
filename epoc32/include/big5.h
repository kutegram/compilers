// BIG5.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__BIG5_H__)
#define __BIG5_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__CHARCONV_H__)
#include <CHARCONV.H>
#endif

class CnvBig5 
/**
only to be used by CHARCONV plug-in DLLs and by locale-DLLs (Locl::FatUtilityFunctions)
@internalComponent
*/
	{
public:
	IMPORT_C static const TDesC8& ReplacementForUnconvertibleUnicodeCharacters();
	IMPORT_C static const SCnvConversionData& ConversionData();
	};

#endif

