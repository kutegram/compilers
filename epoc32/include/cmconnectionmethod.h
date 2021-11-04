/*
* ===========================================================================
*  Name        : cmconnectionmethod.h
*  Part of     : Networking Utilities / Connection Method Manager
*  Description : Connection Method interface class.
*  Version     : %version: 11 %
*
*  Copyright © 2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ===========================================================================
*/
#ifndef CMCONNECTIONMETHOD_H
#define CMCONNECTIONMETHOD_H

// INCLUDES
#include <e32base.h>
#include <cmconnectionmethoddef.h>

// CLASS DECLARATION
class CCmPluginBaseEng;
class RCmDestination;

/**
 *  RCmConnectionMethod is for getting values of a connection method.
 *  @lib cmmanager.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( RCmConnectionMethod )
    {
    //=====================================================================
    // Constructors/Destructors
    // 
    public:
    
        /**
        * Default constructor. 
        */
        IMPORT_C RCmConnectionMethod();


        /**
        * Copy constructor. 
        */
        IMPORT_C RCmConnectionMethod(const RCmConnectionMethod& aItem);


        /**
        * Destructor. 
        */
        IMPORT_C ~RCmConnectionMethod();

    //=====================================================================
    // API functions
    public:
    
        /**
        * Close the session
        *
        * @since S60 3.2
        */
        IMPORT_C void Close();
        
        /**
        * Gets the value for a TInt attribute.
        *
        * @since S60 3.2
        * @param aAttribute Identifies the attribute to be retrieved.
        * @return contains the requested TInt attribute.
        */
        IMPORT_C TUint32 GetIntAttributeL( TUint32 aAttribute ) const;

        /**
        * Gets the value for a TBool attribute.
        *
        * @since S60 3.2
        * @param aAttribute Identifies the attribute to be retrieved.
        * @return contains the requested TBool attribute.
        */
        IMPORT_C TBool GetBoolAttributeL( TUint32 aAttribute ) const;

        /**
        * Gets the value for a String16 attribute.
        * HBuf ownership is passed to the caller
        *
        * @since S60 3.2
        * @param aAttribute Identifies the attribute to be retrieved.
        * @return copy of the requested attribute. Ownership is passed.
        */
        IMPORT_C HBufC* GetStringAttributeL( TUint32 aAttribute ) const;
        
        /**
        * Gets the value for a String8 attribute.
        * HBuf ownership is passed to the caller
        *
        * @since S60 3.2
        * @param aAttribute Identifies the attribute to be retrieved.
        * @return copy of the requested attribute. Ownership is passed.
        */
        IMPORT_C HBufC8* GetString8AttributeL( 
                                        const TUint32 aAttribute ) const;

        /**
        * Call this function only if this CM is an embedded destination!
        *
        * @since S60 3.2
        * @return embedded destination
        */
        IMPORT_C RCmDestination DestinationL() const;

        
        /**
        * checks if connection methods are the same 
        * 
        * @since S60 3.2
        * @param aConnMethod the connection method being compared
        * @return ETrue if the destinations are the same
        */
        IMPORT_C TBool operator==( RCmConnectionMethod& aConnMethod ) const;
        
        /**
        * checks if connection methods are not the same 
        * 
        * @since S60 3.2
        * @param aConnMethod the connection method being compared
        * @return ETrue if the destinations are different
        */
        IMPORT_C TBool operator!=( RCmConnectionMethod& aConnMethod ) const;
        

        /**
        * assignment operator 
        * 
        * @since S60 3.2
        * @return RCmConnectionMethod
        */
        IMPORT_C RCmConnectionMethod& operator=(const RCmConnectionMethod& 
                                                    aConnMethod);
    private:
    
        friend class RCmDestination;
        friend class RCmManager;
        
    private:
        
        /**
         * the implementation class
         */
        CCmPluginBaseEng* iImplementation;
    };

#include <cmconnectionmethod.inl>
    
#endif      // CMCONNECTIONMETHOD_H
