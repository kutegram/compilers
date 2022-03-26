/*
* =============================================================================
*  Name          : SdpKeyField.h
*  Part of       : SDP Codec
*  Interface     : SDK API, SDP Codec API
*  Description   : 
*  Version       : 1.0
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
* =============================================================================
*/

#ifndef CSDPKEYFIELD_H
#define CSDPKEYFIELD_H

//  INCLUDES
#include <e32base.h>
#include <StringPool.h>
#include "_sdpdefs.h"

// FORWARD DECLARATIONS
class RReadStream;
class RWriteStream;

// CLASS DECLARATION
/**
 *  @publishedAll
 *  
 *
 *	This class encapsulates the encryption key field of 
 *  the Session Description Protocol.
 * 
 *	The normative reference for correct formatting and values is
 *	draft-ietf-mmusic-sdp-new-14 unless specified otherwise in
 *  member documentation. The implementation supports this normative
 *  reference, but does not enforce it fully. 
 *
 *  
 */
class CSdpKeyField : public CBase
	{
    public: // Constructors and destructor
        /**
         *	Constructs a new encryption key field.
		 *	
         *	@param aFieldValue A string containing a correctly 
         *         formatted field value terminated by a CRLF.
         *	@return a new instance.
         */
		IMPORT_C static CSdpKeyField* DecodeL(const TDesC8& aFieldValue);

        /**
         *	Constructs a new encryption key field and adds the pointer to 
         *  the cleanup stack.
		 *	
         *	@param aFieldValue A string containing a correctly 
         *              formatted field value terminated by a CRLF.
         *	@return a new instance.
         *  @leave  In error case function leaves.
         */
		IMPORT_C static CSdpKeyField* DecodeLC(const TDesC8& aFieldValue);

        /**
         *	Constructs a new encryption key field.
		 *	
         *	@param aMethod Encryption method from the pre-defined 
         *         SDP string table. User defined values are not accepted.
		 *  @param aEncryptionKey A valid encryption key value 
         *         or an empty descriptor to omit the key part.
         *	@return a new instance.
         */
		IMPORT_C static CSdpKeyField* NewL(RStringF aMethod,
											const TDesC8& aEncryptionKey);

        /**
         *	Constructs a new encryption key field and adds the pointer to 
         *  the cleanup stack.
		 *	
         *	@param aMethod Encryption method from the pre-defined 
         *         SDP string table. User defined values are not accepted.
		 *  @param aEncryptionKey A valid encryption key value 
         *         or an empty descriptor to omit the key part.
         *	@return a new instance.
         */
		IMPORT_C static CSdpKeyField* NewLC(RStringF aMethod,
											const TDesC8& aEncryptionKey);

		/**
		 *	Deletes the resources held by the instance.
		 */
		IMPORT_C ~CSdpKeyField();

    public: // New functions
		/**
		 *	Writes the instance as a complete SDP field encoded as UTF-8
		 *	and formatted as defined in draft-ietf-mmusic-sdp-new-14.
         *
		 *	@param aStream Stream used for output. On return 
         *         the stream includes correctly formatted key field.
		 */
		IMPORT_C void EncodeL(RWriteStream& aStream) const;

		/**
		 *	Creates a new instance that is equal to the target.
		 *
		 *	@return a new instance.
		 */
		IMPORT_C CSdpKeyField * CloneL() const;

		/**	
		 *	Compares this instance to another for equality.
		 *
		 *	@param aObj The instance to compare to.
		 *	@return ETrue if equal, EFalse if not.
		 */
		IMPORT_C TBool operator == (const CSdpKeyField& aObj) const;

		/**
		 *	Gets the encryption method.
		 *
		 *	@return The method.
		 */
		IMPORT_C RStringF Method() const;

		/**
		 *	Gets the encryption key.
		 *
		 *	@return The key or an empty descriptor if there is no key part.
		 */
		IMPORT_C const TDesC8& EncryptionKey() const;

		/**
		 *	Sets the encryption method and key.
		 *
         *	@param aMethod Encryption method from the pre-defined 
         *         SDP string table. User defined values are not accepted.
		 *  @param aEncryptionKey A valid encryption key value 
         *         or an empty descriptor to omit the key part.
		 */
		IMPORT_C void SetL(RStringF aMethod,
						   const TDesC8& aEncryptionKey);

    public:
    	/**
         *  Externalizes the object to stream
         *
         *  @param aStream Stream where the object's state will be stored
         */
		void ExternalizeL(RWriteStream& aStream) const;
		
		/**
         *  Creates object from the stream data
         *
         *  @param aStream Stream where the object's state will be read        
         *  @return Initialized object
         */
		static CSdpKeyField* InternalizeL(RReadStream& aStream);

	private:
		CSdpKeyField();
		void ConstructL(const TDesC8& aText);
		void ConstructL(RStringF aMethod, const TDesC8& aEncryptionKey);
        void DoInternalizeL(RReadStream& aStream);
        void SetMethodAndKeyL(RStringF aMethod, const TDesC8& aEncryptionKey, 
                              TBool aAllowEmptyKeyValue);

        void SetMethodClearAndKeyL(RStringF aMethod, const TDesC8& aEncryptionKey);
        void SetMethodBase64AndKeyL(RStringF aMethod, const TDesC8& aText);
        void SetMethodUriAndKeyL(RStringF aMethod, const TDesC8& aText);
        void SetMethodPromptL(RStringF aMethod, const TDesC8& aText);
        RArray<TPtrC8> GetElementsFromLineL( TLex8& aLexer);

    private: // Data
		RStringF iMethod;
        TBool iMethodOpen;
		HBufC8* iEncryptionKey;
        RStringPool iStringPool;

		__DECLARE_TEST;
	};

// CSDPKEYFIELD_H
#endif
