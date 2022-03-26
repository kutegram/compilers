/*
* ============================================================================
*  Name     : ApNetworkItem.h
*  Part of  : Access Point Engine
*
*  Description:
*     Declaration of the CApNetworkItem class.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef CAPNETWORKITEM_H
#define CAPNETWORKITEM_H

// Deprecation warning
#warning This header file has been deprecated. Will be removed in one of the next SDK releases.
 
 
//  INCLUDES
#include <commdb.h>
#include <ApEngineVer.h>
#include <ApEngineConsts.h>

// CLASS DECLARATION
/**
*  Representation of a Network item.
*/
NONSHARABLE_CLASS( CApNetworkItem ) :public CBase
                                         ///< This class is used to hold
                                         ///< the main information of a
                                         ///< Network item.
                                         ///< It is used in CApNetworks.
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack.
        * @return The constructed CApNetworkItem.
        *
        * @deprecated
        */
        IMPORT_C static CApNetworkItem* NewLC();


        /**
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack.
        * @param aItem a pointer to a CApNetworkItem.
        * @return The constructed CApNetworkItem.
        *
        * @deprecated
        */
        IMPORT_C static CApNetworkItem* NewLC( CApNetworkItem* aItem );


        /**
        * Destructor.
        *
        * @deprecated
        */
        IMPORT_C virtual ~CApNetworkItem();


        /**
        * Copies the data from another CApNetworkItem
        * Substitutes the "Assignment operator."
        * @return No return value.
        *
        * @deprecated
        */
        IMPORT_C void CopyFromL( const CApNetworkItem& aCopyFrom );


    private:      // Constructors
        /**
        * C++ default constructor.
        *
        * @deprecated
        */
        IMPORT_C CApNetworkItem();


        /**
        * Second-phase constructor.
        * @param aUid The UID
        * @param aName The name
        *
        * @deprecated
        */
        IMPORT_C void ConstructL( TUint32 aUid,
                                  const TDesC& aName
                                  );


        /**
        * Second-phase constructor.
        *
        * @deprecated
        */
        IMPORT_C void ConstructL();


    public: // New functions

        /**
        * Gets the name of the network group
        * Ownership of the returned text is not passed.
        * @return The name of the network group
        *
        * @deprecated
        */
        IMPORT_C const TDesC& Name() const;


        /**
        * Gets the UID of this network group
        * @return The UID of this network group
        *
        * @deprecated
        */
        IMPORT_C TUint32 Uid() const;



        /**
        * Sets a UID of the network group.
        * @param aUid a uid to set.
        *
        * @deprecated
        */
        IMPORT_C void SetUid( TUint32 aUid );


        /**
        * Sets the network name
        * @param aName The name to set.
        *
        * @deprecated
        */
        IMPORT_C void SetNameL( const TDesC& aName );


    private:    // Data
        TUint32         iUid;           ///< The ID of the network group
        HBufC*          iName;          ///< The name of the network group 

    };



#endif      // CAPNETWORKITEM_H

// End of File
