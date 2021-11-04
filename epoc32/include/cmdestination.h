/*
* ==============================================================================
*  Name        : cmdestination.h
*  Part of     : Networking Utilities / Connection Method Manager
*  Description : Destination interface class.
*  Version     : %version: 12.1.1 %
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
#ifndef DESTINATION_H
#define DESTINATION_H

// System includes
#include <cmconnectionmethod.h>
#include <cmmanagerdef.h>
#include <E32def.h>
#include <e32base.h>
#include <metadatabase.h>

// FORWARD DECLARATIONS
class CCmManagerImpl;
class CCmDestinationData;
class CGulIcon;

/**
 *  RCmDestination is for getting values of a network destination.
 *
 *  @lib cmmanager.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS(RCmDestination)
    {
    //=====================================================================
    // Constructors/Destructors
    // 
    public:
    
        /** Default constructor. */
        IMPORT_C RCmDestination();

        IMPORT_C ~RCmDestination();

        IMPORT_C RCmDestination(const RCmDestination& aCmDestination);
        
    //=====================================================================
    // API functions
    public:

        /**
        * Close the session.
        *
        * @since S60 3.2
        */
        IMPORT_C void Close();
            
        /**
        * Returns the number of connection methods of the destination
        *
        * @since 3.2
        * @return the number of connection methods belonging to a destination        
        */                 
        IMPORT_C TInt ConnectionMethodCount() const;
        
        /**
        * Returns a reference to the connection method. 
        * The index must be less than the return value of 
        * ConnectionMethodCount().
        *
        * @since 3.2
        * @param anIndex
        * @return a connection method
        */        
        IMPORT_C RCmConnectionMethod ConnectionMethodL( TInt anIndex ) const;

        /**
        * Returns the connection method with the ECmId.
        * Leaves with KErrNotFound if not found.
        * @param aCmId unique id of the requested connection method.
        * @return connection method
        */
        IMPORT_C RCmConnectionMethod ConnectionMethodByIDL( 
                                                        TInt aCmId ) const;

        /**
        * Return the priority of the passed connection method
        *
        * @since 3.2
        * @param aCCMItem connection method
        * @return the priority of the queried connection method 
        */
        IMPORT_C TUint PriorityL(const RCmConnectionMethod& aCCMItem ) const;
        
        //Getting attributes

        /**
        * Returns the destination's Name attribute
        * HBuf ownership is passed to the caller
        *
        * @since 3.2
        * @return HBufC* Passes returned value's ownership to the caller
        */      
        IMPORT_C HBufC* NameLC() const;                        
        
        /**
        * Returns the destination's Id attribute
        *
        * @since 3.2
        * @return the destination's id
        */                    
        IMPORT_C TUint32 Id() const;
        
        /**
        * Returns the destination's ElementId attribute
        *
        * @since 3.2
        * @return the destination's element id        
        */            
        IMPORT_C TUint32 ElementId() const;        
                
        /**
        * Returns the Icon pointer
        * This function leaves if the client does not have a valid UI context
        *
        * @since 3.2
        * @return the destination icon  
        */ 
        IMPORT_C CGulIcon* IconL() const;

        /**
        * Returns the Metadata
        *
        * @since 3.2
        * @param aMetaField the meta data field to query
        * @return the value of the requested field        
        */            
        IMPORT_C TUint32 MetadataL( CMManager::TSnapMetadataField aMetaField ) const;
    
        /**
        * Return the protection level of the destination.
        *
        * @since 3.2              
        * @return protection level of the destination
        */
        IMPORT_C CMManager::TProtectionLevel ProtectionLevel() const;

        /**
        * Returns if there's a connection created with any of the destination's
        * connection method.
        *
        * @since 3.2        
        * @return ETrue if there's a connection with any of the destination's
        * connection method.
        */
        IMPORT_C TBool IsConnectedL() const;
        
        /**
        * Returns whether the destination is hidden or not.
        *
        * @since 3.2
        * @return ETrue if the destination is hidden
        */
        IMPORT_C TBool IsHidden() const;

        /**
        * checks if destinations are the same 
        * 
        * @since S60 3.2
        * @param aDestination the destination being compared
        * @return ETrue if the destinations are the same
        */
        IMPORT_C TBool operator==(const RCmDestination& aDestination ) const;
        
        /**
        * checks if destinations are not the same 
        * 
        * @since S60 3.2
        * @param aDestination the destination being compared
        * @return ETrue if the destinations are different
        */
        IMPORT_C TBool operator!=(const RCmDestination& aDestination ) const;

        /**
        * assignment operator 
        * 
        * @since S60 3.2
        * @param aDestination the destination being compared
        * @return RCmDestination
        */
        IMPORT_C RCmDestination& operator=(const RCmDestination& 
                                                    aCmDestination);

    //=======================================================================
    // Member variables
    //
    private: 
        
        /**
         * the implementation class
         */
        CCmDestinationData* iDestinatonData;

    private:
    
        friend class RCmManager;
        friend class RCmConnectionMethod;
    };
    

#endif // DESTINATION_H
