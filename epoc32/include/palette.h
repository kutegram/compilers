/*
* ============================================================================
*  Name        : palette.h
*  Part of     : S60 UI Framework / Palette
*  Description : Provides the TSeries60ColorScheme enumeration.
*  Version     : %version: tr1s60#9 %
*
*  Copyright © 2002 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/

#ifndef __PALETTE_H__
#define __PALETTE_H__

#include <e32base.h>

// This part of the file holds deprecated names
#define ECalypsoColorNokiaBlue		ESeries60ColorSchemeBlue
#define ECalypsoColorNokiaGreen		ESeries60ColorSchemeGreen
#define ECalypsoColorNokiaPurple	ESeries60ColorSchemePurple
#define EColorSchemeRed		        ESeries60ColorSchemeRed
#define EColorSchemePink	        ESeries60ColorSchemePink
#define EColorSchemeOrange	        ESeries60ColorSchemeOrange
#define TCalypsoColorScheme			TSeries60ColorScheme
#define SetCalypsoColorScheme( S )	SetSeries60ColorScheme( S )


enum TSeries60ColorScheme
	{
	ESeries60ColorSchemeBlue,
	ESeries60ColorSchemeGreen,
	ESeries60ColorSchemePurple,
	ESeries60ColorSchemeRed,
	ESeries60ColorSchemePink,
	ESeries60ColorSchemeOrange,
    ESeries60ColorSchemeGrey,
    ESeries60ColorSchemePalette1,
    ESeries60ColorSchemePalette2,
    ESeries60ColorSchemePalette3,
    ESeries60ColorSchemePalette4,
    ESeries60ColorSchemePalette5,
    ESeries60ColorSchemePalette6,
    ESeries60ColorSchemePalette7,
    ESeries60ColorSchemePalette8,
    ESeries60ColorSchemePalette9,
    ESeries60ColorSchemePalette10,
    ESeries60ColorSchemePalette11,
    ESeries60ColorSchemePalette12,
    ESeries60ColorSchemePalette13
	};


// Deprecated part over

//macro wrapper for old-style palette setting
#define SetSeries60ColorScheme(S){DynamicPalette::SetColor256Util((DynamicPalette::TIndex)(S));}
// end of macro wrapper





class TColor256Util;

/**
 *
 * Hooks to allow dynamic palette switching in 256 color mode.
 *
 * Using <code>TRgb::Color256</code> transparently invokes hooks in
 * this class. The behaviour of the system can be customized by replacing
 * the implementations with some device specific functionality to switch
 * the color palette at run-time.
 *
 * @since 7.0s
 * @lib " palette.lib "
 */
class DynamicPalette
	{
public:
	enum TIndex
		{
		EIndex0,
		EIndex1,
		EIndex2,
		EIndex3,
		EIndex4,
		EIndex5,
        EIndex6,
        EIndex7,
        EIndex8,
        EIndex9,
        EIndex10,
        EIndex11,
        EIndex12,
        EIndex13,
        EIndex14,
        EIndex15,
        EIndex16,
        EIndex17,
        EIndex18,
        EIndex19
		};

	IMPORT_C static const TColor256Util* DefaultColor256Util();
	IMPORT_C static void SetColor256Util(TIndex aIndex);

	IMPORT_C static const TUint32* Color16array();
	IMPORT_C static const TUint8* Color16inverse();
	};

#endif // __PALETTE_H__

// End of file
