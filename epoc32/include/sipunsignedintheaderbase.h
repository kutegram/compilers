/*
* =============================================================================
*  Name        : sipunsignedintheaderbase.h
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


#ifndef CSIPUNSIGNEDINTHEADERBASE_H
#define CSIPUNSIGNEDINTHEADERBASE_H

//  INCLUDES
#include "sipheaderbase.h"
#include "_sipcodecdefs.h"


// CLASS DECLARATION
/**
* @publishedAll
* 
*
* A base class for SIP headers having form: "Name: 1*DIGIT"
*
* 
*/
class CSIPUnsignedIntHeaderBase : public CSIPHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Destructor, deletes the resources of CSIPUnsignedIntHeaderBase.
		*/
		IMPORT_C virtual ~CSIPUnsignedIntHeaderBase();


	public: // New functions

		/**
		* Sets the header value as an unsigned integer 
		* @param aValue a value to set
		*/
		IMPORT_C void SetValue(TUint aValue);
	
		/**
		* Gets the header value as an unsigned integer 
		* @return the header value
		*/
		IMPORT_C TUint Value() const;


	public: // From CSIPHeaderBase

		/**
		* From CSIPHeaderBase ToTextValueL
		*/
		IMPORT_C HBufC8* ToTextValueL() const;


	protected: // Constructors

		CSIPUnsignedIntHeaderBase();
		CSIPUnsignedIntHeaderBase(TUint aValue);

	protected: // New functions

		void ParseL(const TDesC8& aValue, TInt aErrorIfParsingFails);
		void DoInternalizeValueL(RReadStream& aReadStream);

	protected: // From CSIPHeaderBase

		/**
		 * @internalComponent
		 */
		void ExternalizeValueL (RWriteStream& aWriteStream) const;

	protected: // Data
	
		/**
		 * @internalComponent
		 */
		TUint iValue;
	};

// CSIPUNSIGNEDINTHEADERBASE_H
#endif

// End of File
