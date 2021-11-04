/*
* ==============================================================================
*  Name        : cmmanagerdef.h
*  Part of     : Networking Utilities / Connection Method Manager
*  Description : Definition module for Connection Method Manager
*  Version     : %version: he1cfnet#10 %
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
#ifndef CMMANAGERDEF_H
#define CMMANAGERDEF_H

// System includes
#include <E32def.h>
#include <e32std.h>
           
namespace CMManager
    {
    /**
     * Metadata items
     */
    enum TSnapMetadataField
        {
        /**
        * If set this destination is for internet usage.
        * There can be only one such destination.
        * (TBool - default: EFalse)
        * @deprecated
        */
        ESnapMetadataInternet               =   0x00000001,
        
        /**
        * If set this destination is highlighted by default
        * in the Agent dialog.
        * (TBool - default: EFalse)
        */
        ESnapMetadataHighlight              =   0x00000002,
        
        /**
        * If set this destination is hidden in the 
        * Agent dialog.
        * (TBool - default: EFalse)
        */
        ESnapMetadataHiddenAgent            =   0x00000004,
        /**
        * This set of flags identifies the fixed destinations which have localised names.
        * The possible values for this flag-set are the enums of TLocalisedDestinations.
        */
        ESnapMetadataDestinationIsLocalised =   0x000000F0,

        /**
        * This set of flags identifies the fixed destinations for fixed
        * purposes.
        * The possible values for this flag-set are the enums of TSnapPurpose.
        */
        ESnapMetadataPurpose =   0x00000F00
        };

    /**
    * This is the enum set of the TSnapMetadataField's ESnapMetadataDestinationIsLocalised 
    */
    enum TLocalisedDestinations
        {
        /**
        * Used to sign that the destination is not localised at all
        */
        ENotLocalisedDest = 0x00000000,

        /**
        * Used to sign that the destination is localised as 'Internet'
        */
        ELocalisedDestInternet       =   0x00000001,

        /**
        * Used to sign that the destination is localised as 'Wap'
        */
        ELocalisedDestWap            =   0x00000002,

        /**
        * Used to sign that the destination is localised as 'MMS'
        */
        ELocalisedDestMMS       =   0x00000003
        };

    /**
    * This is the enum set of the TSnapMetadataField's ESnapMetadataPurpose
    */
    enum TSnapPurpose
        {
        ESnapPurposeUnknown = 0x00000000,

        /**
        * Used to sign that the destination is identified as 'Internet'
        */
        ESnapPurposeInternet = 0x00000001,

        /**
        * Used to sign that the destination is identified as 'Operator'
        */
        ESnapPurposeOperator = 0x00000002,

        /**
        * Used to sign that the destination is identified as 'MMS'
        */
        ESnapPurposeMMS = 0x00000003,

        /**
        * Used to sign that the destination is identified as 'Intranet'
        */
        ESnapPurposeIntranet = 0x00000004
        };

    /**
     * Protection Levels
     */      
    enum TProtectionLevel
        {
        EProtLevel0 = 0,    /**<
                            * No protection
                            */
                            
        EProtLevel1 = 1,    /**<
                            * A destination and its contents
                            */
                            
        EProtLevel2 = 2,    /**<
                            * A destination
                            */
                            
        EProtLevel3 = 3     /**<
                            * Note: Level 3 - Set the ECmProtected attr on 
                            * connection method
                            */
        };  

    const TInt KDataMobilitySelectionPolicyPriorityWildCard = 256;
    } // namespace CMManager

/**
 * TBearerPriority is a representation of a bearer priority defined in
 * commsdat
 *
 *  @lib cmmanager.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TBearerPriority )
    {
    public:
        
        HBufC*     iServiceType;    /**<
                                    * Name of the service table to identify
                                    * type of bearer 
                                    */
                                    
        TUint32    iPriority;       /**<
                                    * Priority of the bearer. 
                                    * Values must be unique within the table 
                                    */
                                    
        TUint32    iUIPriority;     /**<
                                    * Priority of this bearer type when shown
                                    * in UI for configuring a new IAP. 
                                    * Values must be unique within the table 
                                    */
    };       
    
#endif // CMMANAGERDEF_H
