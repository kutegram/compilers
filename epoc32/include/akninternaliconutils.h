/*
* ==============================================================================
*  Name        : AknInternalIconUtils.h
*  Part of     : AknIcon
*  Interface   : AknIcon
*  Description : Utility functions related to scalable icons.
*
*  Version     : 1
*
*  Copyright (c) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef AKN_INTERNAL_ICON_UTILS_H
#define AKN_INTERNAL_ICON_UTILS_H

class AknInternalIconUtils
    {
    public:	
    	//Set an app flag on if AknIcon
			IMPORT_C static void SetAppIcon(CFbsBitmap* aBmp);
			//not exported
			static TBool IsAknBitmap( const CFbsBitmap* aBitmap ); 
		};
#endif