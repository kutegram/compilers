/*
* ==============================================================================
*  Name        : cmmanager.h
*  Part of     : Networking Utilities / Connection Method Manager
*  Description : Connection manager IF class.
*  Version     : %version: 19 %
*
*  Copyright © 2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ==============================================================================
*/
#ifndef CMMANAGER_H
#define CMMANAGER_H

// System Includes
#include <e32std.h>
#include <e32base.h>
#include <e32cmn.h>
#include <cmdefconnvalues.h>

// Forward Declarations
class RCmConnectionMethod;
class RCmDestination;
class CCmManagerImpl;
class TBearerPriority;

/**
 *  RCmManager gives access to network destinations and connection methods.
 *
 *  @lib cmmanager.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS(RCmManager)
      {          
    //=====================================================================
    // Constructors/Destructors
    // 
    public:
    
        /**
        * Default constructor. 
        */
        inline RCmManager();

    //=====================================================================
    // API functions
    public:
        
        /**
        * Symbian constructor
        *
        * @since S60 3.2
        */
        IMPORT_C void OpenL();    
        
        /**
        * Symbian constructor
        * Pushes the object on the cleanup stack
        *
        * @since S60 3.2
        */
        IMPORT_C void OpenLC();    
        
        /**
        * Secondary destructor
        *
        * @since S60 3.2
        */
        IMPORT_C void Close();
        
    //=======================================================================
    // Getter API
    public:    
      
        /**
        * Used to query bearer information that doesn't belong
        * to a specific connection method, such as 
        * ECmCoverage or ECmDefaultPriority etc.
        *
        * @since S60 3.2
        * @param aBearerType the bearer
        * @param aAttribute the setting value
        * @return the setting value
        */
        IMPORT_C TUint32 GetBearerInfoIntL( TUint32 aBearerType,
                                  TUint32 aAttribute ) const;
                                  
        
        /**
        * Used to query bearer information that doesn't belong
        * to a specific connection method, such as 
        * ECmCoverage or ECmDefaultPriority etc.
        *
        * @since S60 3.2
        * @param aBearerType the bearer
        * @param aAttribute the setting value
        * @return the setting value
        */
        IMPORT_C TBool GetBearerInfoBoolL( TUint32 aBearerType,
                                 TUint32 aAttribute ) const;
        /**
        * Used to query bearer information that doesn't belong
        * to a specific connection method, such as 
        * ECmCoverage or ECmDefaultPriority etc.
        * HBuf ownership is passed to the caller
        *
        * @since S60 3.2
        * @param aBearerType the bearer
        * @param aAttribute the setting value
        * @return the setting value
        */        
        IMPORT_C HBufC* GetBearerInfoStringL( TUint32 aBearerType,
                                    TUint32 aAttribute ) const;
        /**
        * Used to query bearer information that does not belong
        * to a specific connection method, such as 
        * ECmCoverage or ECmDefaultPriority, etc.
        * HBuf ownership is passed to the caller
        *
        * @since S60 3.2
        * @param aBearerType the bearer
        * @param aAttribute the setting value
        * @return the setting value
        */
        IMPORT_C HBufC8* GetBearerInfoString8L( TUint32 aBearerType,
                                    TUint32 aAttribute ) const;
                    
        /**
        * Used to query any non-bearer specific information about
        * a given connection method. This can be e.g. ECmBearerType,
        * ECmName, ECmStartPage, etc.
        *
        * @since S60 3.2
        * @param aIapId the connection method id
        * @param aAttribute the setting value
        * @return the setting value
        */
        IMPORT_C TUint32 GetConnectionMethodInfoIntL( TUint32 aIapId,
                                             TUint32 aAttribute ) const;
        
        /**
        * Used to query any, non-bearer specific information about
        * a given connection method. This can be e.g. ECmBearerType,
        * ECmName, ECmStartPage, etc.
        *
        * @since S60 3.2
        * @param aIapId the connection method id
        * @param aAttribute the setting value
        * @return the setting value
        */
        IMPORT_C TBool GetConnectionMethodInfoBoolL( TUint32 aIapId,
                                            TUint32 aAttribute ) const;

        /**
        * Used to query any non-bearer specific information about
        * a given connection method. This can be e.g. ECmBearerType,
        * ECmName, ECmStartPage, etc.
        * HBuf ownership is passed to the caller
        *
        * @since S60 3.2
        * @param aIapId the connection method id
        * @param aAttribute the setting value
        * @return the setting value
        */
        IMPORT_C HBufC* GetConnectionMethodInfoStringL( TUint32 aIapId,
                                               TUint32 aAttribute ) const;

        /**
        * Used to query any non-bearer specific information about
        * a given connection method. This can be e.g. ECmBearerType,
        * ECmName, ECmStartPage, etc.
        * HBuf ownership is passed to the caller
        *
        * @since S60 3.2
        * @param aIapId the connection method id
        * @param aAttribute the setting value
        * @return the setting value
        */
        IMPORT_C HBufC8* GetConnectionMethodInfoString8L( TUint32 aIapId,
                                               TUint32 aAttribute ) const;
                
        /**
        * Returns the connection method queried by its ID
        *
        * @since S60 3.2
        * @param aConnectionMethodId id of the connection method
        * @return RCmConnectionMethod connection method
        */
        IMPORT_C RCmConnectionMethod ConnectionMethodL( 
                                     TUint32 aConnectionMethodId ) const;
                        
        /**
        * Returns the list of connection methods. Connection Methods are 
        * filtered by the switch parameters e.g. aLegacyOnly.
        *
        * @since S60 3.2
        * @param aCMArray on return it is the array of IAP ids.
        * @param aCheckBearerType If ETrue only connection methods with 
        *                         supported bearer type are returned
        * @param aLegacyOnly when set to ETrue only Legacy IAP ids will
        *                         be returned
        * @param aEasyWlan when set to ETrue EasyWlan id is returned, too
        */
        IMPORT_C void ConnectionMethodL( RArray<TUint32>& aCMArray, 
                                         TBool aCheckBearerType = ETrue,
                                         TBool aLegacyOnly = ETrue,
                                         TBool aEasyWlan = EFalse ) const;
        
        /**
        * Returns an array of all destination id's
        *
        * @since S60 3.2
        * @param aDestArray list all available destinations' id
        */ 
        IMPORT_C void AllDestinationsL( RArray<TUint32>& aDestArray ) const;

        /**
        * Returns the destination to which a specified 
        * connection method belongs, search is by destination ID
        *
        * @since S60 3.2
        * @param aDestinationId id of destination
        * @return RCmDestination network destination 
        */
        IMPORT_C RCmDestination DestinationL( TUint32 aDestinationId ) const;
       
        /**
        * Returns the copy of the bearer priority array. Ownership is passed.
        *
        * @since S60 3.2
        * @param aArray bearer priority array
        */          
        IMPORT_C void BearerPriorityArrayL( 
                                   RArray<TBearerPriority>& aArray ) const;
       
        /**
        * Clean up passed global bearer priority array. Delete
        * the elements and calls Reset and Close on the array.
        *
        * @since S60 3.2
        * @param aArray array to be cleaned up
        */
        IMPORT_C void CleanupGlobalPriorityArray( 
                                   RArray<TBearerPriority>& aArray ) const;
        
        /**
        * Returns the id of the EasyWlan connection method.
        *
        * @since S60 3.2
        * @return id of the EasyWLan connection method. 0 if not found.
        */
        IMPORT_C TUint32 EasyWlanIdL() const;
        
        /**
        * Returns the default connection method/SNAP.
        *
        * @since S60 3.2
        */
        IMPORT_C void ReadDefConnL( TCmDefConnValue& aDCSetting );
        
    private:
        /**
        * This is a private copy constructor without implementation.
        * The sole purpose of this declaration is to forbid the copying of 
        * the objects of this class.
        */          
        RCmManager(RCmManager&  );
        /**
        * This is a private copy constructor without implementation.
        * The sole purpose of this declaration is to forbid the copying of 
        * the objects of this class.
        */          
        RCmManager& operator=( RCmManager& );
    //=========================================================================
    // Member data
    
    private:
    
        /**
         * the implementation class
         */
        CCmManagerImpl* iImplementation;
    };

#include "cmmanager.inl"
    
#endif // CMMANAGER_H
