/*
* =============================================================================
*  Name        : sipstrings.h
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

#ifndef SIPSTRINGS_H
#define SIPSTRINGS_H

//  INCLUDES
#include <e32base.h>
#include <stringpool.h>
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPStrings;

// CLASS DECLARATION
/**
 * @publishedAll
 * 
 *
 * This class defines string pool for SIP Codec.
 * The client of SIP Codec must call OpenL() before 
 * invoking any function of SIP Codec classes.
 * The client must close the string pool when finished using
 * SIP Codec classes.
 *
 * 
 */
class SIPStrings
	{
	public:	// Constructors and destructor
 		
		/**
		* Opens SIP Codec string pool.
		* Implemented with a reference count.
		*/
		IMPORT_C static void OpenL();

		/**
		* Closes SIP Codec string pool.
		* In other words decrements reference count and if it reaches
		* zero, closes the string pool.	 
		* The user must not call Close() if it has not called OpenL().
		*/
		IMPORT_C static void Close(); 


	public: // New functions
	
		/**
		* Gets a case-insensitive string specified 
		* in the original string table.
		*
		* @param aIndex The string table enumeration value
		* @return Initialised RStringF object
		*/
		IMPORT_C static RStringF StringF(TInt aIndex);

		/**
		* Gets the string pool used by SIP Codec.
		*
		* @return RStringPool: A handle to a string pool
		*/
		IMPORT_C static RStringPool Pool();

		/**
		* Gets the string table used by SIP Codec.
		*
		* @return TStringTable&: The string pool table
		*/
		IMPORT_C static const TStringTable& Table();
	
	private:

		static CSIPStrings* Strings();
		};

// SIPSTRINGS_H
#endif

// End of File
