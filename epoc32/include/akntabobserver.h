
/*
* ============================================================================
*  Name     : akntabobserver.h
*  Part of  : AVKON
*
*  Description:
*     Interface class for tab group observer.
*
*
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef AKNTABOBSERVER_H
#define AKNTABOBSERVER_H

#include <e32base.h>

class MAknTabObserver
{
public:

   	/**
     * Method for handling tab change events in observed classes. 
     * 
     * @param aIndex Index of the active tab.
     *
     */
	virtual void TabChangedL(TInt aIndex) = 0;
};


#endif
