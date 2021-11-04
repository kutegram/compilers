// LOOKUPTABLE.H
//
// Copyright (c) Symbian Software Ltd 2006. All rights reserved.
//

#ifndef __LOOKUPTABLE_H__
#define __LOOKUPTABLE_H__

#include <e32std.h>

/**
@internalTechnology
*/
 IMPORT_C const TUint16* Convert16to32bppLow();
 IMPORT_C const TUint32* Convert16to32bppHigh();

/**
Returns the pointer to the table of 16-bit normalisation table.
The table is currently used for performing un-multiplying Premultiplied Alpha color channels.
Use: Let x be c * a/255, and y = c, then y = (x/a)*255, where a is in 0-255 range.
		To use this table, use y = (x * Table[a])>>8. i.e, the inaccurate division is converted 
		to more accurate multiplication and shift.
		
@return pointer to the normalisation table.
@internalTechnology

*/
IMPORT_C const TUint16* PtrTo16BitNormalisationTable();



#endif
