/*
* ==============================================================================
*  Name        : sipregistrationcontext.h
*  Part of     : SIP Client
*  Interface   : SDK API, SIP API
*  Description : 
*  Version     : 1.0
*
*  Copyright (c) 2005 Nokia Corporation.
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


#ifndef MSIPREGISTRATIONCONTEXT_H
#define MSIPREGISTRATIONCONTEXT_H

//  INCLUDES
#include <e32base.h>

// CLASS DECLARATION

/**
*  @publishedAll
*  
*
*  The interface for providing
*  information for the SIP request and
*  dialog creation.
*
*  
*/
class MSIPRegistrationContext
	{
     public: // New functions
        /**
		* Destructor
		*/
        virtual ~MSIPRegistrationContext() {}

		/**
		* Checks if the registration context can be
		* used for creating SIP messages/dialogs
        *
		* @return ETrue if can be used, EFalse otherwise
		*/
		virtual TBool IsContextActive() const = 0;

		/**
		* Gets the context id.
        *
		* @return Context id
		* For internal use only
		*/
		virtual TUint32 ContextId() const = 0;
	};

#endif
