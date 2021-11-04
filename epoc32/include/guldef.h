// GULDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULDEF_H__)
#define __GULDEF_H__

/** The sides on which borders can be adjacent. 

@publishedAll
*/
enum TGulAdjacent
	{
	/** Indicates that rectangle borders are not adjacent. */
	EGulAdjNone		=0x00,
	/** Adjacent at the top. */
	EGulAdjTop		=0x01,
	/** Adjacent at the bottom. */
	EGulAdjBottom	=0x02,
	/** Adjacent at the left. */
	EGulAdjLeft		=0x04,
	/** Adjacent at the right. */
	EGulAdjRight	=0x08
	};
	
/** Symbian light grey.

@publishedAll
*/
#define KRgbDitheredLightGray 	TRgb(204,204,204)

/** Symbian dithered grey.

@publishedAll
*/
#define KRgb1in4DitheredGray 	TRgb(238,238,238)

/** Symbian green.

@publishedAll
*/
#define KRgbSymbianGreen 		TRgb(0,153,153)

/** Symbian light green.

@publishedAll
*/
#define KRgbSymbianGreenLight	TRgb(0,183,183)

/** Symbian blue.

@publishedAll
*/
#define KRgbSymbianBlue 		TRgb(0,102,153)

/** Symbian dark blue.

@publishedAll
*/
#define KRgbSymbianBlueDark		TRgb(0,72,123)

/** Symbian orange.

@publishedAll
*/
#define KRgbSymbianOrange		TRgb(255,218,155)

#endif
