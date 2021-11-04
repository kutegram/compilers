/*
* ==============================================================================
*  Name        : MRoomLevelObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the RoomLevel effect observer class.
*
*  Version     : 0.4
*
*  Copyright © 2004 Nokia Corporation.
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

#ifndef MROOMLEVELOBSERVER_H
#define MROOMLEVELOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <RoomLevelBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the RoomLevel effect observer class. Object interested in receiving notification
*  when the CRoomLevel object changes state should derive from this class and implement
*  its interface.
*
*  @since 3.0
*/

class MRoomLevelObserver : public MAudioEffectObserver
	{
	public:
	
		static const TUint KRoomLevelChanged = KSpecificEffectBase + 1;

	};

#endif	// of MROOMLEVELOBSERVER_H

// End of File