/*
* ==============================================================================
*  Name        : imerrors.h
*  Part of     : IM SDK API
*  Interface   : 
*  Description : Open IM API errors
*  Version     : 1.0
*
*  Copyright © 2004, 2005 Nokia Corporation.
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

#ifndef OPENAPI_IM_ERRORS_H
#define OPENAPI_IM_ERRORS_H

const TInt KImErrorBase = -30130;

enum TImErrors   // SDK API errors
    {
    /**
    * General Error
    */
    KImApiGeneralError = KImErrorBase -1,
    
    /**
    * Error not registered
    */
    KImApiErrNotRegistered = KImErrorBase - 2,
    
    /**
    * Error already registered
    */
    KImApiErrAlreadyRegistered = KImErrorBase - 3,
    
    /**
    * Error not logged
    */
    KImApiErrNotLogged = KImErrorBase - 4,
    
    /**
    * Login is already ongoing
    */
    KImApiErrLoginInProgress = KImErrorBase - 5,
    
    /**
    * The contact ID provided in SendPToPMessage is invalid
    */
    KImApiErrInvalidContactId = KImErrorBase - 6,

    /**
    * The user ID provided in SendPToPMessage is invalid
    */
    KImApiErrInvalidUserId = KImErrorBase - 7,

    /**
    * Not all the users have a valid User ID when sending message
    */
    KImApiErrPartialSuccess = KImErrorBase - 8,

    /**
    * Special IM error code: the sender is blocked by the recipient 
    */
    KImApiErrSenderBlocked = KImErrorBase - 9,

    /** 
    * Special IM error code: the recipient is not logged in 
    */
    KImApiErrRecipientNotLogged = KImErrorBase - 10,

	/**
    * Logout is already in progress
    */
    KImApiErrLogoutInProgress = KImErrorBase - 11,

    /**
    * CancelLogin is already in progress
    */
    KImApiErrCancelLoginInProgress = KImErrorBase - 12,
    
    /** 
    * Already logged in
    */
    KImApiErrAlreadyLoggedIn = KImErrorBase - 13,
    
    /** 
    * Wrong Password
    */
    KImApiErrWrongPassword = KImErrorBase -14
    };


#endif // OPENAPI_IM_ERRORS_H

//  End of File
