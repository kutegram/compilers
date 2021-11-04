/*
* ============================================================================
*  Name     : ApNetworkItemList.h
*  Part of  : Access Point Engine
*
*  Description: Declaration of the CApNetworkItemList class.
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

#ifndef CAPNETWORKITEMLIST_H
#define CAPNETWORKITEMLIST_H

// Deprecation warning
#warning This header file has been deprecated. Will be removed in one of the next SDK releases.
 
 
//  INCLUDES
#include <e32base.h>
#include <ApEngineVer.h>

// FORWARD DECLARATION

class CApNetworkItem;

// CLASS DECLARATION
/**
*  A list of CApNetworkItem-s pointers; items are owned.
*/
class CApNetworkItemList : public CArrayPtrFlat<CApNetworkItem>
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        *
        * @deprecated
        */
        IMPORT_C CApNetworkItemList();

        /**
        * Destructor. Items in the list are destroyed.
        *
        * @deprecated
        */
        IMPORT_C virtual ~CApNetworkItemList();

    public:  // New methods

        /**
        * Get pointer to the item having aUid,
        * or NULL if no such item is in the
        * list.
        * @param aUid Uid of item to get.
        * @return Pointer to the item having uid aUid, or NULL. Ownership
        * not passed (the list still owns the item).
        *
        * @deprecated
        */
        IMPORT_C const CApNetworkItem* ItemForUid( TUint32 aUid ) const;

    };

#endif // CAPNETWORKITEMLIST_H

// End of File
