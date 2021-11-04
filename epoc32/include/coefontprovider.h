// COEFONTPROVIDER.H
//
// Copyright (c) Symbian Software Ltd. 1997-2006. All rights reserved.
//

#ifndef __COEFONTPROVIDER_H__
#define __COEFONTPROVIDER_H__

#include <e32base.h>
#include <e32def.h>
#include <coefont.h>
#include <coemain.h>
#include <coeaui.h>
#include <coecntss.h>

/** A helper object designed to make obtaining a font easier, taking into account
zoom factors.

@publishedAll

*/
class CCoeFontProvider : public CBase 
        { 
public:        // life 
        IMPORT_C static CCoeFontProvider* NewL(); 
        IMPORT_C static CCoeFontProvider* NewL(const TDesC& aTypefaceName); 
        ~CCoeFontProvider(); 
public:        // methods 
        IMPORT_C const CFont& Font(const TCoeFont& aFont, const TZoomFactor& aZoomFactor) const; 
public:        // properties                 
        IMPORT_C void SetTypeface(const TTypeface aTypeface); 
        IMPORT_C void UseSystemTypeface(); 
        IMPORT_C TTypeface Typeface() const;
public:			//but not exported
		void RefetchPixelMappingL();

private: 
        CCoeFontProvider(const TDesC& aTypefaceName); 
        void ConstructL(); 
        void ReleaseAllFonts(); 
private: 
        class TFont 
                { 
        public: 
                TFont(const TCoeFont& aFontSpec, TInt aZoomFactor, const CFont* aFont = NULL); 
                static TInt Compare(const TFont& aFirst, const TFont& aSecond); 
        public: 
                const TCoeFont iCoeFont; 
                const TInt iZoomFactor; 
                const CFont* iFont; 
                }; 
private: 
        mutable RArray<TFont> iFonts; 
        TTypeface iTypeface; 
        RArray<TInt> iLogicalToPixelSizes; 
        }; 

// __COEFONTPROVIDER_H__
#endif
