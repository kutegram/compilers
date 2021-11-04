/*
* ============================================================================
*  Name        : CMessageAddress.h
*  Part of     : SendUi
*  Description : Encapsulates message real addressa and alias
*  Version     : %version: % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright © 2002-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.1
*/

#ifndef C_MESSAGEADDRESS_H
#define C_MESSAGEADDRESS_H

#include <e32Base.h>

class CMessageAddressImpl;
class RWriteStream;
class RReadStream;

/**
 *  Encapsulates message recipient real address and alias.
 *
 *  @lib sendui
 *  @since S60 v3.0
 */
class CMessageAddress : public CBase
{
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    IMPORT_C static CMessageAddress* NewL();
    
    /**
    * Two-phased constructor. Leaves object to cleanup stack.
    */
    IMPORT_C static CMessageAddress* NewLC();
    
    /**
    * Destructor.
    */
    IMPORT_C virtual ~CMessageAddress();

public: // New functions

   /**
    * Sets real address.
    *
    * @since Series 60 3.0
    * @param aAddress Real address.
    * @return None.
    */
    IMPORT_C void SetAddressL( const TDesC& aAddress );

   /**
    * Returns real address.
    *
    * @since Series 60 3.0
    * @return Real address.
    */
    IMPORT_C const TPtrC Address() const;

    /**
    * Sets alias for the real address.
    *
    * @since Series 60 3.0
    * @param aAlias Alias for the real address.
    * @return None.
    */
    IMPORT_C void SetAliasL( const TDesC& aAlias );

   /**
    * Returns alias for the address.
    *
    * @since Series 60 3.0
    * @return Alias for the real address.
    */
    IMPORT_C const TPtrC Alias() const;

    /**
    * Externalizes address data to a stream
    *
    * @since Series 60 3.2
    * @param aStream Destination stream
    * @return None.
    */ 
    IMPORT_C void ExternalizeL( RWriteStream& aStream );
    
    /**
    * Internalizes message data from a stream
    *
    * @since Series 60 3.2
    * @param Source stream
    * @return None.
    */ 
    IMPORT_C void InternalizeL( RReadStream& aStream );

private:
    
    /**
    * C++ default constructor.
    */
    CMessageAddress();
    
    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL();

private:  // Data

    /**
     * Message address implementation.
     * Own.
     */
    CMessageAddressImpl* iMessageAddressImpl;
    };

/**  Address array */
   
typedef CArrayPtrFlat<CMessageAddress> CMessageAddressArray;

#endif      // C_MESSAGEADDRESS_H

// End of File
