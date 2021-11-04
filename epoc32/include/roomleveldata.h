/*
* ==============================================================================
*  Name        : RoomLevelData.h
*  Part of     : Effects Framework
*  Interface   : Audio Effects
*  Description : This file contains definitions of audio effects data structures for
*                RoomLevel.
*  Version     : 0.4
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
* ==============================================================================
*/


#ifndef TEFROOMLEVEL_H
#define TEFROOMLEVEL_H

//  INCLUDES
#include <e32std.h>
#include <AudioEffectData.h>


// CLASS DECLARATION

/**
*  This class defines the effect data structure to be passed between client and
*  server.
*
*  @lib RoomLevelEffect.lib
*  @since 3.0
*/
class TEfRoomLevel : public TEfCommon
    {
    public:

        /**
        * Constructor.
        */
        TEfRoomLevel() {}

    	// Data
        // RoomLevel values of a RoomLevel object

        TUint32 iEnvironmentalReverbId;		
		TInt32 iStreamRoomLevel;
     	TInt32 iStreamMinRoomLevel;
	    TInt32 iStreamMaxRoomLevel;
	};

typedef TPckgBuf<TEfRoomLevel> TEfRoomLevelDataPckg;

#endif      // TEFROOMLEVEL_H

// End of File
