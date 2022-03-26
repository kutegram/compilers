/*
* ==============================================================================
*  Name        : sipmanagedprofile.h
*  Part of     : SIP Profile Client
*  Interface   : SDK API, SIP Profile API
*  Description : The class providing profile management of SIP service provider
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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

#ifndef CSIPMANAGEDPROFILE_H
#define CSIPMANAGEDPROFILE_H

// INCLUDES

#include <e32base.h>
#include <e32std.h>
#include <badesca.h>

#include "sipprofile.h"

//CONSTANTS

/** SIP Provider Name which value is type of TDesC8.
* Note that this parameter can only be retrieved
* if it has been explicitly configured */
const TUint32 KSIPPrivateIdentity = 500;

/** SIP HTTP Digest password which value is type of TDesC8.
* Note that this parameter cannot be retrieved */
const TUint32 KSIPDigestPassword = 501;

/** 
* SIP headers to be added to outgoing SIP requests generated 
* by SIP Profile Agent. The value is of type MDesC8Array.
* Each array element represents a complete SIP header (name and value). */
const TUint32 KSIPHeaders = 502;

/** 
* Setting for enabling/disabling IMS registration with certain types of
* smart card applications. The value is of type TUint32.
* If no value for this setting is configured, registration is allowed 
* with all types of smart card applications (SIM/USIM/ISIM).
* If the value is configured, the following values are possible:
* 1: Registration is allowed only when USIM or ISIM is present.
* 2: Registration is allowed only when ISIM present */
const TUint32 KSIPAllowIMSRegistration = 503;

/**
* Setting for enabling/disabling editing the profile after its creation.
* Serves as an indication for the clients that the profile 
* update and deletion operations are restricted. 
* The SIP Profile Agent implementation does not understand
* the semantics of the parameter.
* The value is of type TBool. */
const TUint32 KSIPProfileLocked = 504;

/**
* Defines how autoregistration profile behaves on home network/roaming
* situations. If value is ETrue, automatic registration is not allowed
* while roaming.
* The value is of type TBool. */
const TUint32 KSIPAllowAutoRegistrationOnlyOnHomeNetwork = 505;

// FORWARD DECLARATIONS

class CSIPManagedProfileRegistry;


// CLASS DECLARATION

/**
*  @publishedAll
*  
*
*  Class contains profile information of particular SIP service
*  provider. Class provides functions for setting and 
*  getting profile parameters.
* 
*  
*/
class CSIPManagedProfile: public CSIPProfile
    {
    public:  // Constructors and destructor
        /**
        * Destructor. 
        */                
        IMPORT_C ~CSIPManagedProfile();

    public: // New functions
        /**
        * Sets profile type information; 
        * @param aSIPProfileTypeInfo profile type information
        */
        IMPORT_C void SetType(const TSIPProfileTypeInfo& aSIPProfileTypeInfo);

        /** 
        * Sets profile parameter
        * @param aParam a parameter to set; zero-length descriptor resets the value
        * @param aVal a value to set
        * @return KErrNotFound if parameter was not found,
        *         KErrNoMemory if out of memory;
        *         KErrNone otherwise
        */
        IMPORT_C TInt SetParameter(TUint32 aParam, const TDesC8& aVal); 

        /** 
        * Sets profile parameter
        * @param aParam a parameter to set
        * @param aVal a value to set
        * @return KErrNotFound if parameter was not found, KErrNone otherwise
        */
        IMPORT_C TInt SetParameter(TUint32 aParam, TUint32 aVal);

        /** 
        * Sets profile parameter
        * @param aParam a parameter to set
        * @param aVal a value to set
        * @return KErrNotFound if parameter was not found, KErrNone otherwise
        */
        IMPORT_C TInt SetParameter(TUint32 aParam, TBool aVal);
    
        /** 
        * Sets profile parameter
        * @param aParam a parameter to set
        * @param aVal values to set; an empty array resets the value
        * @return KErrNotFound if parameter was not found, 
        *         KErrNoMemory if out of memory          
        *          KErrNone otherwise        
        */
        IMPORT_C TInt SetParameter(TUint32 aParam, const MDesC8Array& aVal);
        
        /** 
        * Sets profile parameter that is defined for a particular SIP server
        * @param aServerType a SIP server type
        * @param aParam a parameter to set
        * @param aVal a value to set; zero-length descriptor resets the value
        * @return KErrNotFound if parameter was not found,
        *          KErrNoMemory if out of memory;
        *         KErrNone otherwise
        */
        IMPORT_C TInt SetParameter(TUint32 aServerType, TUint32 aParam, const TDesC8& aVal);

        /** 
        * Creates deep copy of the object
        * @return deep copied instance
        * @leave KErrNoMemory if out of memory
        */
        IMPORT_C CSIPManagedProfile* CloneL() const;

    public:
        /**
        * Two-phased constructor.
        * @param aSIPRegistry a SIP profile client providing connection to SIP 
        *         profile server.
        */
        static CSIPManagedProfile* NewL(CSIPManagedProfileRegistry* aSIPRegistry);

        /**
        * Two-phased constructor.
        * @param aSIPRegistry a SIP profile client providing connection to SIP 
        *         profile server.
        * Constructs an object and adds the pointer to the cleanup stack;
        */
        static CSIPManagedProfile* NewLC(CSIPManagedProfileRegistry* aSIPRegistry);

    private:

        /**
        * Constructor. 
        */                
        CSIPManagedProfile(CSIPManagedProfileRegistry* aSIPRegistry);

        /** 
        * Sets profile parameter
        * @param aParam a parameter to set; zero-length descriptor resets the value
        * @param aVal a value to set
        */
        void SetParameterL(TUint32 aParam, const TDesC8& aVal);

        /** 
        * Sets profile parameter
        * @param aParam a parameter to set
        * @param aVal a value to set
        */
        void SetParameterL(TUint32 aParam, TUint32 aVal);

        /** 
        * Sets profile parameter
        * @param aParam a parameter to set
        * @param aVal a value to set
        */
        void SetParameterL(TUint32 aParam, TBool aVal);

        /** 
        * Sets profile parameter that is defined for a particular SIP server
        * @param aServerType a SIP server type
        * @param aParam a parameter to set
        * @param aVal a value to set; zero-length descriptor resets the value
        */
        void SetParameterL(TUint32 aServerType,
            TUint32 aParam, const TDesC8& aVal);

        /** 
        * Sets profile parameter
        * @param aParam a parameter to set
        * @param aVal values to set; an empty array resets the value
        */
        IMPORT_C void SetParameterL(TUint32 aParam, const MDesC8Array& aVal);
    };

// CSIPMANAGEDPROFILE_H
#endif
