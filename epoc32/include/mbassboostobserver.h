/*
* ==============================================================================
*  Name        : MBassBoostObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the bassboost effect observer class.
*
*  Version     : 2
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

#ifndef BASSBOOSTOBSERVER_H
#define BASSBOOSTOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <BassBoostBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the bassboost effect observer class. Object interested in receiving notification
*  when the CBassBoost object changes state should derive from this class and implement its
*  interface.
*
*  @since 3.0
*/

class MBassBoostObserver : public MAudioEffectObserver
	{
	public:
	static const TUint KBassBoostChanged = KSpecificEffectBase + 1;
	};

#endif	// of BASSBOOSTOBSERVER_H

// End of File