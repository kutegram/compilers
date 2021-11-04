/*
* ==============================================================================
*  Name        : sipmanagedprofileregistry.h
*  Part of     : SIP Profile Client
*  Interface   : SDK API, SIP Profile API
*  Description : The class for managing SIP profiles
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

#ifndef CSIPMANAGEDPROFILEREGISTRY_H
#define CSIPMANAGEDPROFILEREGISTRY_H

//  INCLUDES
#include <e32base.h>
#include <e32std.h>
#include "sipprofileregistrybase.h"

// FORWARD DECLARATIONS
class CSIPProfile;
class CSIPManagedProfile;
class MSIPProfileRegistryObserver;


// CLASS DECLARATION
/**
*  @publishedAll
*  
*
*  The class for managing SIP profiles.
*  This class provides the functions for
*  adding/updating/removing profiles.
*
*  
*/
class CSIPManagedProfileRegistry: public CSIPProfileRegistryBase
    {
    public:  // Constructors and destructor
        /**
        * Two-phased constructor.
        * @param aObserver a observer for SIP profile change events.
        */
        IMPORT_C static CSIPManagedProfileRegistry* NewL(
                        MSIPProfileRegistryObserver& aObserver);

        /**
        * Two-phased constructor.
        * Constructs an object and adds the pointer to the cleanup stack;
        * @param aObserver a observer for SIP profile change events.
        */
        IMPORT_C static CSIPManagedProfileRegistry* NewLC(
                        MSIPProfileRegistryObserver& aObserver);

        /**
        * Destructor
        */
        IMPORT_C ~CSIPManagedProfileRegistry();
    public: //new functions

        /**
        * Instantiates new profile with default values 
        * for given type.
        * @param aType a SIP profile type to be created
        * @return pre-filled instance of given type profile type;
                * the ownership is transferred
        */
        IMPORT_C CSIPManagedProfile* CreateL(const TSIPProfileTypeInfo& aType); 

        /**
        * Checks if profile is not used by other applications. 
        * If no other application is using the profile, profile
        * can be updated.
        * @param aSIPProfile a SIP profile
        * @return ETrue if available for update, EFalse otherwise
        * @capability ReadUserData
        */
        IMPORT_C TBool IsInUseL(const CSIPProfile& aSIPProfile) const; 

        /**
        * Saves new profile or changes to a profile to the persistent storage.
        * This function must be called after desired values are set or updated
        * in the SIP profile. 
        * If the profile is marked for auto-registration and the profile is 
        * updated the profile will be re-registered.
        * Function leaves on failure.
        * @pre IsInUse(aSIPProfile)==EFalse
        * @param aSIPProfile a sip profile to save
        * @capability WriteDeviceData
        * @capability NetworkServices
        */
        IMPORT_C void SaveL(CSIPProfile& aSIPProfile);

        /**
        * Removes and deletes SIP profile from the persistent storage.
        * Function leaves on failure.
        * If the profile is registered it will be de-registered before the
        * removal from the persistent storage.
        * @param aSIPProfile a sip profile to delete
        * @capability WriteDeviceData
        * @capability NetworkServices
        */
        IMPORT_C void DestroyL(CSIPProfile& aSIPProfile);

    private:

        CSIPManagedProfileRegistry(MSIPProfileRegistryObserver& aObserver);

        void ConstructL();

        /**
        * Creates a new instance of type CSIPManagedProfile
        * @return new instance
        */
        CSIPProfile* NewInstanceL();
    };

// CSIPMANAGEDPROFILEREGISTRY_H
#endif
