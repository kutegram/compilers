/*
* ==============================================================================
*  Name        : AknSoundInfo.h
*  Part of     : Avkon / EikKeySoundServer
*  Interface   : API, CAknSoundInfo
*  Description : Provides API for sound info delivery
*  Version     : 1.0
*
*  Copyright (c) 2002 Nokia Corporation.
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


#ifndef AKNSOUNDINFO_H
#define AKNSOUNDINFO_H

//  INCLUDES
#include <e32base.h>

// DATA TYPES
enum TSoundType
    {
    ESoundTone = 1,
    ESoundFile = 2,
    ESoundSequence = 3
    };

// FORWARD DECLARATIONS
class RWriteStream;

// CLASS DECLARATION

/**
*  Provides structure needed for passing the sound information for applications that create own instances to MediaServer
*
*  @lib Avkon.lib
*  @since 2.0
*/
NONSHARABLE_CLASS(CAknSoundInfo) : public CBase
    {
    public:
        /**
        * Constructor
        */
        IMPORT_C static CAknSoundInfo* NewL();

        /**
        * Destructor.
        */
        IMPORT_C ~CAknSoundInfo();

    public: // New functions
        IMPORT_C void InternalizeL( RReadStream& aStream );     
        IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;  
        
    public:     // Data
        TInt16 iPriority;
        TInt16 iFrequency;
        TInt iPreference;
        HBufC* iFile;
        TInt iDuration;
        HBufC8* iSequence;
        TUint8 iVolume;
        TSoundType iType;

    private:
        /**
        * Default Constructor
        */
        CAknSoundInfo();
    };

#endif      // AKNSOUNDINFO_H   
            
// End of File
