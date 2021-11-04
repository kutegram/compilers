/*
* ==============================================================================
*  Name        : ExifTag.h
*  Part of     : Exif Library
*  Interface   : Public API
*  Description : Exif tag wrapper 
*  Version     : 
*
*  Copyright (c) 2003, 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef EXIFTAG_H
#define EXIFTAG_H

//  INCLUDES
#include <e32base.h>

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class TExifTagInfo;

// CLASS DECLARATION

/**
*  Interface class for handling Exif Tags. 
*  This class is used to get tag data from an Exif image.
*  @lib ExifLib
*  @since 2.6 
*/
NONSHARABLE_CLASS( CExifTag ): public CBase
    {
	public:  // Enumerations

        /**
        * Tag Data type enumeration.
        */
    	enum TExifTagDataType
            {
        	ETagByte = 1,
        	ETagAscii = 2,
        	ETagShort = 3,
        	ETagLong = 4,
        	ETagRational = 5,
        	ETagUndefined = 7,
        	ETagSlong = 9,
        	ETagSrational = 10
            };

    public:
        
        /**
        * Destructor.
        */
        virtual ~CExifTag();

    public: // New functions
        
        /**
        * Duplicate constructor. Creates an exact copy instance of the tag.
        * @since 2.6 
        * @param 
        * @return An instance of this class including the same contents of 
        * this instance.
        */
     	virtual CExifTag* DuplicateL() const = 0;

        /**
        * Returns the informative fields of a tag.
        * @since 2.6 
        * @param 
        * @return TExifTagInfo structure including informative fields of a tag
        */
    	virtual TExifTagInfo TagInfo() const = 0;

        /**
        * Returns data contents of a tag
        * @since 2.6 
        * @param 
        * @return Unmodifiable pointer to tag data.
        */
    	virtual TPtrC8 Data() const = 0;

    };


class TExifTagInfo
    {    
    public:  // Constructors and destructor

        IMPORT_C TExifTagInfo( 
            TUint16 aTagId, 
            CExifTag::TExifTagDataType aDataType, 
            TUint32 aDataCount );
    
    public:     // Data

        // Tag ID
    	TUint16 iId;

        // Tag data type
    	CExifTag::TExifTagDataType iDataType;

        // Number of tag data elements (having tag data type).
    	TUint32 iDataCount;
    };

#endif      // EXIFTAG_H   
            
// End of File
