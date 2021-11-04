/*
* ============================================================================
*  Name     : MPbkFetchDlgSelection from MPbkFetchDlgSelection.h
*  Part of  : PbkView.dll
*
*  Description:
*       Interface to allow observer accept/decline selections in 
*		phonebook fetch dialog
*  Version:
*
*  Copyright (C) 2005 Nokia Corporation.
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

#ifndef __MPbkFetchDlgSelection_H__
#define __MPbkFetchDlgSelection_H__

#include <cntdef.h>     // TContactItemId


// CLASS DECLARATION

/**
 * Interface for accepting/refusing selections in Phonebook fetch dialog.
 * A client can use this interface to implement restrictions on fetch dialog
 * selection. For example on the maximum number of contacts selected by 
 * the user.
 */
class MPbkFetchDlgSelection
	{

	public: // Interface
        /**
         * Decides whether a contact selection made in fetch dialog should be
         * accepted or declined
         * @param aItemId ID of the item that is being selected.
         * @param aCurrentSelectedCount Number of already selected items BEFORE
         *		  current selection
         * @return ETrue if the selection is accepted. Otherwise EFalse
         */	
        virtual TBool ContactSelectionAcceptedL
        	(TContactItemId aItemId, 
        	 TInt aCurrentSelectedCount) const = 0;
    };
	
#endif // __MPbkFetchDlgSelection_H__

// End of File
