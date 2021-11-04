// COEFONT.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2005. All rights reserved.
//

#ifndef __COEFONT_H__
#define __COEFONT_H__

#include <e32def.h>
#include <gdi.h>

/** A class to simplify font usage

@publishedAll

*/
class TCoeFont 
	{ 
public: 
	enum TFlags 
		{ 
		ENoFlags = 0x00, 
		ENonZooming = 0x01 
		}; 

	enum TLogicalSize 
		{ 
		EExtraSmall = 0, 
		ESmall, 
		EMedium, 
		ELarge, 
		EExtraLarge,
		EUndefinedSize = -1
		};         

	enum TStyle 
		{ 
		EPlain = 0x00, 
		EItalic = 0x01, 
		EBold = 0x02, 
		ESuper = 0x04, 
		ESub = 0x08 
		}; 

public:
	IMPORT_C TCoeFont(TLogicalSize aSize, TInt aStyle, TInt aFlags = ENoFlags); 
	IMPORT_C TCoeFont(TInt aHeightInPixels, TInt aStyle, TInt aFlags = ENoFlags); 
	IMPORT_C TCoeFont(const TCoeFont& aFont);
	IMPORT_C TCoeFont(); 
	IMPORT_C static TCoeFont NormalFont(TInt aFlags = ENoFlags);	// Medium, Plain 
	IMPORT_C static TCoeFont LegendFont(TInt aFlags = ENoFlags);	// Medium, Bold 
	IMPORT_C static TCoeFont AnnotationFont(TInt aFlags = ENoFlags);// Small, Plain 
	IMPORT_C static TCoeFont TitleFont(TInt aFlags = ENoFlags);		// Large, Bold 
public: // properties         
	IMPORT_C TLogicalSize LogicalSize() const; 
	IMPORT_C TInt HeightInPixels() const; 
	IMPORT_C TFontStyle Style() const; 
	IMPORT_C TBool IsNonZooming() const; 
public:         
	static TInt Compare(const TCoeFont& aFirst, const TCoeFont& aSecond); 
private: 
	TLogicalSize iLogicalSize; 
	TInt8 iHeightInPixels; 
	TInt8 iStyle; 
	TInt8 iFlags; 
	TTypeface iTypeface;	// Member unused at the moment but included for possible future extension
private:         
	TInt iSpare; 
	}; 

// __COEFONT_H__
#endif


