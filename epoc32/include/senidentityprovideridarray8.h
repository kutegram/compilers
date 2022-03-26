/*
* ==============================================================================
*  Name        : SenIdentityProviderIdArray8.h
*  Part of     : Web Services Description
*  Interface   : 
*  Description : Array utility class for listing pre-known ProviderIDs
*  Version     : 
*
*  Copyright � 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef SEN_IDENTITY_PROVIDER_ID_ARRAY_8_H
#define SEN_IDENTITY_PROVIDER_ID_ARRAY_8_H

//  INCLUDES
#include <e32base.h>
#include <badesca.h>
#include <e32std.h>
#include <MSenIdentityProviderIdArray.h>

// CLASS DECLARATION

/**
*  Array utility class for listing pre-known ProviderIDs
*  Typical use of this class is to define a strict list
*  of ProviderIDs pointing to certain IDPs, which are to
*  be accepted as only suitable services when initiating
*  an new service connection.
*  Other possiblity is to instantiate a non-strict array,
*  which only acts as "recommendation" of those Identity
*  Providers, that should be first checked when initiating
*  new service connection. In such case, because it is a
*  non-strict list, also other IDPs may be used, if none
*  matching with this "recommendation" is found.
*  @lib SenServDesc.lib
*  @since Series60 3.0
*/
class CSenIdentityProviderIdArray8 :    public CDesC8ArraySeg,
                                        public MSenIdentityProviderIdArray
{
    public:  // Constructors and destructor
        
        /**
        *   Constructor with no arguments create non-strict arrays.. 
        *   (iStrict = EFalse)
        */ 
        IMPORT_C static CSenIdentityProviderIdArray8* NewL();

        /**
        *   Constructor with no arguments create non-strict arrays.. 
        *   (iStrict = EFalse)
        */ 
        IMPORT_C static CSenIdentityProviderIdArray8* NewLC();

        /**
        * Basic constructor with a default value for iStrict.
        * @since Series60 3.0
        * @param aStrict the value to be set to iStrict
        */
        IMPORT_C static CSenIdentityProviderIdArray8* NewL(const TBool aStrict);

        /**
        * Basic constructor with a default value for iStrict.
        * @since Series60 3.0
        * @param aStrict the value to be set to iStrict
        */
        IMPORT_C static CSenIdentityProviderIdArray8* NewLC(const TBool aStrict);

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CSenIdentityProviderIdArray8();

        // Functions from base classes

        // From MSenIdentityProviderIdArray
        
        /**
        * Getter for iStrict
        * @since Series60 3.0
        * @return ETrue if iStrict is true, otherwise EFalse
        */
        IMPORT_C virtual TBool IsStrict() const;
        
        /**
        * Setter for iStrict
        * @since Series60 3.0
        * @param aStrict the value to be set to iStrict
        */
        IMPORT_C void SetStrict(TBool aStrict);
        
    protected:  // New functions
        
        /**
        * C++ default constructor.
        */
        CSenIdentityProviderIdArray8(const TBool aStrict);  
        
        /**
        * Default 2nd phase constructor
        * @since Series60 3.0
        */
        void ConstructL();

    private:    // Data
        TBool iStrict;         
    };
    
#endif // SEN_IDENTITY_PROVIDER_ID_ARRAY_8_H

// End of File



