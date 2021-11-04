/*
* =============================================================================
*  Name          : SdpRtpmapValue.h
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

#ifndef TSDPRTPMAPVALUE_H
#define TSDPRTPMAPVALUE_H

// INCLUDES
#include <e32std.h>
#include <stringpool.h>
#include "_sdpdefs.h"

// FORWARD DECLARATIONS
class RWriteStream;

// CLASS DECLARATION
/**
 *  @publishedAll
 *  
 *
 *	Utility class for manipulating the value of an rtpmap-attribute.
 *
 *	The normative reference for correct formatting and values is
 *	draft-ietf-mmusic-sdp-new-14 unless specified otherwise in
 *  member documentation. The implementation supports this normative
 *  reference, but does not enforce it fully. 
 *
 *  
 */
class TSdpRtpmapValue
	{
    public: // Constructors and destructor

		/**
		 *	Initializes the instance to refer to the given rtpmap components.
		 *	The parameters must stay in scope as long as this instance exists.
		 *	Otherwise, the member variables of this class will point to
		 *	a released memory.
		 *  
		 *	@param aEncodingName Valid rtpmap encoding name value.	
		 *	@param aClockrate Valid rtpmap clockrate value.	
		 *	@param aEncodingParameters Valid rtpmap encoding 
         *         parameter list.	
		 */
		IMPORT_C TSdpRtpmapValue( 
						const TPtrC8& aEncodingName,
						const TPtrC8& aClockrate,
						const TPtrC8& aEncodingParameters );

    public: // New functions

		/**
		 *	Tries to parse a string as an rtpmap attribute value up to the end 
		 *	of the string or CRLF, whichever comes first, and set pointers to 
		 *	the components found. The parameter must stay in scope as long as 
         *  this instance exists. Otherwise, the member variables of this class 
         *  will point to a released memory.
		 *         
		 *	@param aText String containing the value of an rtpmap attribute.
         *  @return a new instance 
		 *	@leave  KErrArgument if parsing fails.
		 */
		IMPORT_C static TSdpRtpmapValue DecodeL( const TDesC8& aText );

		/**
		 *	Outputs the attribute value formatted according to SDP syntax.
		 *  The field terminating CRLF is not included in the output.
         *  When constructing CSdpFmtAttributeField, return value of this 
         *  function can be used as aValue in CSdpFmtAttributeField::NewL
         *  (RStringF aAttribute, const TDesC8& aFormat, const TDesC8& aValue)
         *  function.
		 * 
         *  @return Encoded value. Ovnership of buffer is changed to caller.
		 */
		IMPORT_C HBufC8* EncodeL() const;        

    public: // Data

		/** 
		 * Encoding name part of an rtpmap value 
		 * @internalComponent
		 */
		TPtrC8 iEncName;

		/** 
		 * Clockrate part of an rtpmap value. 
		 * @internalComponent
		 */
		
		TPtrC8 iClockrate;

		/** 
		 * Encoding parameters part of an rtpmap value. 
		 * @internalComponent
		 */
		TPtrC8 iEncParams;
	};

// TSDPRTPMAPVALUE_H
#endif
