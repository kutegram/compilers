// BidiVisual.h
//
// Copyright (C) 2002-2003 Symbian Ltd. All rights reserved.
//

#ifndef BIDIVISUAL_H_
#define BIDIVISUAL_H_

#include <bidi.h>

class TBidiLogicalToVisual
/** 
This class is a low-level class for bi-directionally reordering text. It 
allows the re-ordering of text using no leaving functions at all, and provides 
a finer degree of control than TBidiText. However, it should not be used 
without understanding the basics of the Unicode Bi-directional Reordering 
Algorithm. 
@publishedAll

*/
	{
public:
	enum {KMinCharAvailable = 4};

	IMPORT_C TBidiLogicalToVisual(const TDesC& aText, TBool aRightToLeft,
		TBidirectionalState::TRunInfo* aRunInfoArray, TInt aRunInfoLength);
	IMPORT_C TBidiLogicalToVisual(const TDesC& aText,
		TBidirectionalState::TRunInfo* aRunInfoArray, TInt aRunInfoLength);
	IMPORT_C TInt Reorder();
	IMPORT_C void GetVisualLine(TDes& aLine, TInt aStart, TInt aEnd,
		TChar aTruncationChar);
private:
	const TDesC& iText;
	TBool iRightToLeft;
	TBidirectionalState::TRunInfo* iRunInfoArray;
	TInt iRunInfoArrayLength;
	TInt iRuns;
	TUint32 iSpare2;
	};

#endif
