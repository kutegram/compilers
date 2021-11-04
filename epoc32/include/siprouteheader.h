/*
* =============================================================================
*  Name        : siprouteheader.h
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


#ifndef CSIPROUTEHEADER_H
#define CSIPROUTEHEADER_H

//  INCLUDES
#include "siprouteheaderbase.h"
#include "_sipcodecdefs.h"

// CLASS DECLARATION
/**
* @publishedAll
* 
*
* Class for SIP "Route"-header manipulation.
*
*  
*/
class CSIPRouteHeader : public CSIPRouteHeaderBase
	{
	public:	// Constructors and destructor

		/**
		* Constructs a CSIPRouteHeader from textual representation 
		* of the header's value part.
		* @param aValue a value part of a "Route"-header
		* @return an array containing one to many instances of CSIPRouteHeader
		*/
		IMPORT_C static RPointerArray<CSIPRouteHeader> 
			DecodeL(const TDesC8& aValue);

		/**
		* Creates a new instance of CSIPRouteHeader
		* @pre aSIPAddress != 0
		* @param aSIPAddress a name-address, the ownership is transferred 
		* @return a new instance of CSIPRouteHeader
		*/
		IMPORT_C static CSIPRouteHeader* NewL(CSIPAddress* aSIPAddress);

		/**
		* Creates a new instance of CSIPRouteHeader and puts it to CleanupStack
		* @pre aSIPAddress != 0
		* @pre aSIPAddress->Address().HostPort().HasHost() == ETrue
		* @param aSIPAddress a name-address, the ownership is transferred 
		* @return a new instance of CSIPRouteHeader
		*/
		IMPORT_C static CSIPRouteHeader* NewLC(CSIPAddress* aSIPAddress);

		/**
		* Destructor, deletes the resources of CSIPRouteHeader.
		*/
		IMPORT_C ~CSIPRouteHeader();


	public: // New functions

		/**
		* Constructs an instance of a CCSIPRouteHeader from a RReadStream
		* @param aReadStream a stream containing the value of the
		*        externalized object (header name not included). 
		* @return an instance of a CSIPRouteHeader
		*/
		IMPORT_C static CSIPHeaderBase* 
			InternalizeValueL(RReadStream& aReadStream);


	public: // From CSIPHeaderBase
		
		/**
		* From CSIPHeaderBase CloneL
		*/
		IMPORT_C CSIPHeaderBase* CloneL() const;

		/**
		* From CSIPHeaderBase Name
		*/
		IMPORT_C RStringF Name() const;


	public: // New functions, for internal use

		static RPointerArray<CSIPHeaderBase> BaseDecodeL(const TDesC8& aValue);
		static CSIPRouteHeader* NewL(const CSIPRouteHeaderBase& aHeader);		

	private: // From CSIPHeaderbase

		void ExternalizeValueL(RWriteStream& aWriteStream) const;

	private: // Constructors

		CSIPRouteHeader();

	private: // New functions

		void DoInternalizeValueL(RReadStream& aReadStream);
	};

// CSIPROUTEHEADER_H
#endif

// End of File
