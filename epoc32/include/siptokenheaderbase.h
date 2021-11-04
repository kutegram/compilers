/*
* =============================================================================
*  Name        : siptokenheaderbase.h
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


#ifndef CSIPTOKENHEADERBASE_H
#define CSIPTOKENHEADERBASE_H

//  INCLUDES
#include "sipheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* A base class for SIP headers having form "Name: token *(COMMA token)"
*
* 
*/
class CSIPTokenHeaderBase : public CSIPHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Destructor, deletes the resources of CSIPTokenHeaderBase.
		*/
		IMPORT_C virtual ~CSIPTokenHeaderBase();


	public: // New functions

		/**
		* Sets the header value as a token 
		* @param aValue a value to set
		*/
		IMPORT_C void SetValueL(RStringF aValue);
	
		/**
		* Gets the header value as a token 
		* @return the header value
		*/
		IMPORT_C RStringF Value() const;


	public: // From CSIPHeaderBase

		/**
		* From CSIPHeaderBase ToTextValueL
		*/
		IMPORT_C HBufC8* ToTextValueL() const;


	public: // From CSIPHeaderBase, for internal use

		/**
		 * @internalComponent
		 */
		virtual TBool MoreThanOneAllowed() const;

	protected: // Constructors

		CSIPTokenHeaderBase();
	    CSIPTokenHeaderBase(const CSIPTokenHeaderBase& aHeader);
		void ConstructL(const TDesC8& aValue, TBool aEmptyValueAllowed=EFalse);
		void ConstructL(RStringF aValue, TBool aEmptyValueAllowed=EFalse);
		
	protected: // New functions		
		
		void DoInternalizeValueL(RReadStream& aReadStream);

	protected: // Data	
	
		/**
		 * @internalComponent
		 */
		RStringF iValue;

	private: // From CSIPHeaderBase

		void ExternalizeValueL(RWriteStream& aWriteStream) const;

	private: // New functions

		void SetValueL(const TDesC8& aValue);	

	private: // For testing purposes
	
		UNIT_TEST(CSIPTokenHeaderBaseTest)
	};

// CSIPTOKENHEADERBASE_H
#endif

// End of File
