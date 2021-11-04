// CONVGENERATEDCPP.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONVGENERATEDCPP_H__)
#define __CONVGENERATEDCPP_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__CONVDATA_H__)
#include <CONVDATA.H>
#endif

/** 
Contains the conversion data for the foreign character set. This object can 
be passed as the first parameter to CCnvCharacterSetConverter::DoConvertFromUnicode() 
or CCnvCharacterSetConverter::DoConvertToUnicode() 
@publishedAll

*/
GLREF_D const SCnvConversionData conversionData;

 
/** 
Returns the single character (as one or more byte values) which is used by 
default as the replacement for unconvertible Unicode characters. These byte 
values are output when converting from Unicode into a foreign character set 
for each Unicode character that has no equivalent in the foreign character 
set.

@return The single character which is used to replace unconvertible characters. 
@publishedAll

*/
GLREF_C const TDesC8& ReplacementForUnconvertibleUnicodeCharacters_internal();

#endif

