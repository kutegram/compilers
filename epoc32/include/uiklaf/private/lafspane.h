// LAFSPANE.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __LAFSPANE_H__
#define __LAFSPANE_H__

#include <e32std.h>

// forward declaration
class CEikStatusPaneBackground;

class LafStatusPaneContainer
/** Status pane LAF support.

@publishedPartner 
*/
	{
public:
	/** Tests if fading the status pane is allowed.
	
	@return True if fading is allowed.
	@see CEikStatusPane::SetFaded() */
	IMPORT_C static TBool AllowFading();

 	/** Creates a background object for the status pane. The background 
 	object class is derived from the virtual class CEikStatusPaneBackground 
 	
 	@return Pointer to a background object derived from CEikStatusPaneBackground */
	IMPORT_C static CEikStatusPaneBackground* CreateStatusPaneBackgroundL();
	};

// __LAFSPANE_H__
#endif
