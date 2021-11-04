// NumberConversion.h
//
// Copyright (c) 2002-2003 Symbian Ltd.  All rights reserved.
//

#ifndef NUMBERCONVERSION_H_
#define NUMBERCONVERSION_H_

#include <e32std.h>


class NumberConversion
/**
Functions for converting numbers between different numbers form different
scripts. The scripts supported are those given in enum TDigitType.
@publishedAll

*/
	{
public:
	enum TDigitMatchType
		{
		EMatchSingleTypeOnly,
		EMatchMultipleTypes
		};

	IMPORT_C static TInt ConvertFirstNumber(const TDesC& aText, TInt& aLength,
		TDigitType& aDigitType,
		TDigitMatchType aDigitMatchType = EMatchMultipleTypes);

	IMPORT_C static TInt PositionAndTypeOfNextNumber(const TDesC& aText,
		TDigitType& aDigitType, TInt aStartFrom = 0);

	IMPORT_C static void FormatNumber(TDes& aText, TInt aNumber,
		TDigitType aDigitType);

	IMPORT_C static void FormatDigit(TDes& aText, TInt aNumber, TInt aLeadingZero,
		TDigitType aDigitType);

	IMPORT_C static void AppendFormatNumber(TDes& aText, TInt aNumber,
		TDigitType aDigitType);

	IMPORT_C static void ConvertDigits(TDes& aText, TDigitType aDigitType);

	IMPORT_C static TInt LengthOfFormattedNumber(TInt aNumber,
		TDigitType aDigitType);

	IMPORT_C static TInt LengthOfConvertedText(const TDesC& aText,
		TDigitType aDigitType);

	IMPORT_C static void Format(TDigitType aDigitType,
		TRefByValue<TDes> aFmt,...);

	IMPORT_C static TChar ConvertDigit(TChar& aDigit, TDigitType aDigitType);
	};

#endif
