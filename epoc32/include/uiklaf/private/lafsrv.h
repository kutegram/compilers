// LAFSRV.H
//
// Copyright (c) Symbian Software Ltd 2000 - 2006. All rights reserved.
//

#ifndef __LAFSRV_H__
#define __LAFSRV_H__

#include <w32std.h>
#include <coemain.h>


class LafServAppUiBase
/** Eikon server LAF support.

@publishedPartner 
*/
	{
public:
	/** Gets the number of pointer cursors supplied by the LAF.
	
	This can be zero for some devices.
	
	@return Number of pointer cursors */
	IMPORT_C static TInt NumberOfCursorsInSystemCursorList();
	/** Claims the pointer cursor list, enabling the Eikon server to change the system 
	pointer cursor.
	
	If this device has a global pointer cursor list, the function should claim 
	it by calling RWsSession::ClaimSystemPointerCursorList(); otherwise, it should 
	do nothing.
	
	@param aEnv Thread's control environment
	@return System wide error code */
	IMPORT_C static TInt ClaimPointerCursorListIfNeeded(CCoeEnv& aEnv);
	/** Releases the system pointer cursor list.
	
	If this device has a global pointer cursor list, the function should claim 
	it by calling RWsSession::FreeSystemPointerCursorList(); otherwise, it should 
	do nothing.
	
	@param aEnv Thread's control environment */
	IMPORT_C static void FreePointerCursorListIfNeeded(CCoeEnv& aEnv);
	/** Constructs a specified pointer cursor.
	
	The function should return NULL for devices with no system pointer cursors.
	
	@param aCursorNumber Index of the cursor to construct
	@param aSpriteMember On return, the sprite member added to the pointer cursor
	@param aEnv Thread's control environment
	@return Fully constructed pointer cursor */
	IMPORT_C static RWsPointerCursor* ConstructPointerCursorL(TInt aCursorNumber, TSpriteMember& aSpriteMember, CCoeEnv& aEnv);
	};

// __LAFSRV_H__
#endif
