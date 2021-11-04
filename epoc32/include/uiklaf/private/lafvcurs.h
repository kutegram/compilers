// LAFVCURS.H
//
// Copyright 1997-1999 Symbian Ltd. All rights reserved
//

#ifndef __LAFVCURS_H__
#define __LAFVCURS_H__

#include <e32std.h>
#include <w32std.h>


class LafVirtualCursor
/** Virtual cursor LAF support.

@publishedPartner 
*/
	{
public:
	/** Gets the mode that should be used when the virtual cursor is switched on. 
	
	The return value has no effect for devices not using a virtual cursor. 
	
	@return Cursor mode */
	IMPORT_C static TPointerCursorMode PointerCursorOnMode();
	};

#endif
