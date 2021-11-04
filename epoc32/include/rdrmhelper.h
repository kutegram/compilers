/*
* ==============================================================================
*  Name        : RDRMHelper.h
*  Part of     : DRMHelper
*  Interface   : 
*  Description : the client side class for DRMHelperServer
*
*  Copyright (c) 2004 Nokia Corporation.
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

#ifndef RDRMHELPER_H
#define RDRMHELPER_H

// INCLUDES
#include <e32base.h>

// DATA TYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION




/**
*  This class provides the client-side interface to the server session
*
*  @since Series 60 2.6
*/

class RDRMHelper : public RSessionBase
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
	    RDRMHelper();

    public:  // New functions
      
        /**
        * Connects to server.
        * @return System-wide error code
        */
	    TInt Connect();

        /**
        * Gets the version number 
        * @return version number
        */
	    TVersion Version() const;

        /**
        * Register the given content uri as an automated content.
        * @param aUri: content URI
        * @param aActive: active or passive registration
        * @param aAutomatedType: type of automated content
        * @param aIntent: intent how content is used
        * @return System-wide error code
        */
        TInt SetAutomated( 
            const TDesC8& aUri, 
            TBool aActive, 
            TInt aAutomatedType, 
            TInt aIntent ) const;

        /**
        * Unregister the given content.
        * @param aUri: content URI
        * @param aActive: active or passive registration
        * @param aAutomatedType: type of automated content
        * @param aIntent: intent how content is used
        * @return System-wide error code
        */
        TInt RemoveAutomated( 
            const TDesC8& aUri, 
            TBool aActive, 
            TInt aAutomatedType, 
            TInt aIntent ) const;

        /**
        * Unregister all instances of the given content.
        * @param aUri: content URI
        * @param aActive: active or passive registration
        * @param aAutomatedType: type of automated content
        * @param aIntent: intent how content is used
        * @return System-wide error code
        */
        TInt RemoveAutomatedAll( 
            const TDesC8& aUri, 
            TBool aActive, 
            TInt aAutomatedType, 
            TInt aIntent ) const;

        /**
        * Indicate that idle-screen has been activated.
        * @return System-wide error code
        */
        TInt IndicateIdle() const;       

        /**
        * Has given content been registered as automated content.
        * @param aUri content URI of the content
        * @param aAutomated (out) ETrue if registered as automated.
        * @param aType (out) Tells whether content has been registered as active or passive.
        * @return System-wide error code
        */
        TInt IsAutomated( 
            const TDesC8& aUri,
            TInt aAutomatedType, 
            TInt aIntent, 
            TBool& aAutomated, 
            TInt& aType ) const;       

    private:
        
        TInt StartServer();
        TInt CreateServerProcess();
    };



#endif      // DRMHELPERCLIENT_H   
            
// End of File
