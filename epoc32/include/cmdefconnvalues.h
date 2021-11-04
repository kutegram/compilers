/*
* ============================================================================
*  Name        : cmdefconnvalues.h
*  Part of     : Networking Utilities / Connection Method Manager
*  Description : Declaration of default connection values
*  Version     : %version: 1 %
*
*  Copyright © 2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/
#ifndef C_CMDEFCONNVALUES_H
#define C_CMDEFCONNVALUES_H

enum TCmDefConnType
        {
        ECmDefConnAlwaysAsk,         /**<
                            * The user selected Always Ask
                            */
        ECmDefConnAskOnce,         /**<
                            * The user selected Ask Once
                            */
        ECmDefConnDestination,       /**<
                            * The user selected a destination
                            */
        ECmDefConnConnectionMethod,   /**<
                            * The user selected a connection method
                            */
        };
        
struct TCmDefConnValue 
    {
    /**
    * Type of default connection
    */
    TCmDefConnType iType;
    
    /**
    * Id of the selected destination or connection method
    */
    TUint iId;
    // -----------------------------------------------------------------------------
    // TCmDefConnValue::operator==
    // -----------------------------------------------------------------------------
    //
    inline TBool TCmDefConnValue::operator==( TCmDefConnValue& aDCSettingSelection ) const
        {
        return ( (iType == aDCSettingSelection.iType) && ( iId == aDCSettingSelection.iId ) );
        };

    // -----------------------------------------------------------------------------
    // TCmDefConnValue::operator!=
    // -----------------------------------------------------------------------------
    //
    inline TBool TCmDefConnValue::operator!=( TCmDefConnValue& aDCSettingSelection ) const
        {
        return (!( (iType == aDCSettingSelection.iType) && ( iId == aDCSettingSelection.iId ) ));
        };     
    };    
#endif // C_CMDEFCONNVALUES_H
