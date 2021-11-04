/*
* =============================================================================
*  Name        : sipheaderbase.h
*  Part of     : SIP Codec
*  Interface   : SDK API, SIP Codec API
*  Description : 
*  Version     : SIP/4.0 
*
*  Copyright (c) 2004 Nokia Corporation. 
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


#ifndef CSIPHEADERBASE_H
#define CSIPHEADERBASE_H

//  INCLUDES
#include <e32base.h>
#include <s32mem.h>
#include <stringpool.h>
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class provides a generic interface for all the SIP headers.
*
*  
*/
class CSIPHeaderBase : public CBase
	{
	public: // Constructors and destructors

		/**
		* Destructor, deletes the resources of CSIPHeaderBase.
		*/
		IMPORT_C virtual ~CSIPHeaderBase();

	
	public: // New functions
	
		/**
		* Creates a deep-copy of this CSIPHeaderBase object. 
		* The function has to be implemented in each of the sub-classes.
		* @return the deep-copied object, the ownership is transferred.
		*/
		IMPORT_C virtual CSIPHeaderBase* CloneL() const = 0;

		/**
		* Gets the full name of the header
		* The function is implemented in each of the sub-classes.
		* @return the full name of the header for example "From"
		*/
		IMPORT_C virtual RStringF Name() const = 0;

		/**
		* Encodes the header (name and value) into its textual representation.
		* @return a textual representation of the complete header,
		*         the ownership is transferred
		*/
		IMPORT_C HBufC8* ToTextL() const;

		/**
		* Encodes the header (name and value) into its textual representation
		* and pushes it to the CleanupStack.
		* @return a textual representation of the complete header,
		*         the ownership is transferred
		*/
		IMPORT_C HBufC8* ToTextLC() const;

		/**
		* Encodes the header's value into its textual representation.
		* @return a textual representation of the header's value,
		*         the ownership is transferred
		*/
		IMPORT_C virtual HBufC8* ToTextValueL() const = 0;

		/**
		* Encodes the header's value into its textual representation
		* and pushes it to the CleanupStack.
		* @return a textual representation of the header's value,
		*         the ownership is transferred
		*/
		IMPORT_C HBufC8* ToTextValueLC() const;

		/**
		* Writes the object to a RWriteStream
		* @param aWriteStream a stream where the object is to be externalized
		* @param aAddName if ETrue the name of the header is 
		*        also written to the stream
		*/
		IMPORT_C void ExternalizeL(RWriteStream& aWriteStream,
                                   TBool aAddName=ETrue) const;

		/**
		* Checks, if the header supports serialization.
		* In practice all the headers part of the API support it.
		* @return ETrue, if the header supports serialization, 
		*         otherwise EFalse
		*/
		IMPORT_C virtual TBool ExternalizeSupported() const;

		/**
		* Can be used when a RPointerArray<CSIPHeaderBase> needs to be pushed
		* to the CleanupStack for ResetAndDestroy.
		* @param aArray an array of CSIPHeaderBase pointers, 
		*        the ownership of the array is transferred
		*/
		IMPORT_C static void PushLC(RPointerArray<CSIPHeaderBase>* aArray);


	public: // For internal use

		/**
		 * @internalComponent
		 */
		enum TPreferredPlace
			{
			ETop,
			EMiddleTop,
			EMiddle,
			EMiddleBottom,
			EBottom
			};
		/**
		 * @internalComponent
		 */
		TSglQueLink iLink;

		/**
		 * @internalComponent
		 */
		virtual TBool EncodeMultipleToOneLine() const;
		
		/**
		 * @internalComponent
		 */
		virtual TBool MoreThanOneAllowed() const;
		
		/**
		 * @internalComponent
		 */
		virtual TBool IsExtensionHeader() const;
		
		/**
		 * @internalComponent
		 */
		virtual TBool HasCompactName() const;
		
		/**
		 * @internalComponent
		 */
		virtual RStringF CompactName() const;
		
		/**
		 * @internalComponent
		 */
		virtual TPreferredPlace PreferredPlaceInMessage() const = 0;

	protected: // Constructors

		CSIPHeaderBase();

	protected: // New functions

		void ExternalizeNameL(RWriteStream& aWriteStream) const;
		/**
		 * @internalComponent
		 */
		virtual void ExternalizeValueL(RWriteStream& aWriteStream) const;
		// Needed for cleanup of a RPointerArray<CSIPHeaderBase>:
		static void ResetAndDestroy(TAny* anArray);
	};

// CSIPHEADERBASE_H
#endif

// End of File
