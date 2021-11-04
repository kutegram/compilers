// EIKFCTRY.H
//
// Copyright (c) Symbian Software Ltd 1997-2006.  All rights reserved.
//

#ifndef __EIKFCTRY_H__
#define __EIKFCTRY_H__

#include <e32def.h>

class CCoeControl;

/** Flags to determine the control status.

@publishedPartner

*/
enum
	{
	/** Flag to determine whether a control has ears. Ears are triangular buttons
	for moving forwards or backwards through the list. */
	EEikControlHasEars=0x01,
	/** Flag to determine whether the control is unable to receive keyboard focus. */
	EEikControlIsNonFocusing=0x02,
	/** Flag to determine whether the control is higher than a normal control. */
	EEikControlHasExtraAscent=0x04,
	/** Flag to determine if a control should be placed directly
	 in the view/dialog or if it should be placed in a pop-out control. */
	EEikControlIsNonEditInPlace=0x08
	};

/** Structure to hold the control specific information. It is used by 
EikControlFactory.

@see EikControlFactory
@publishedAll

*/
struct SEikControlInfo
    {
    CCoeControl* iControl;
	TInt iTrailerTextId;
    TInt iFlags;
    };


/** Abstract factory that creates controls by type. 

This class provides a unified way to create controls according to the 
specified control integer ID. 

@publishedAll 
*/
class EikControlFactory
	{
public:
    IMPORT_C static SEikControlInfo CreateByTypeL(TInt aControlType);
	};

// __EIKFCTRY_H__
#endif
