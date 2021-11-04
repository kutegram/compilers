/*
* ==============================================================================
*  Name        : MStereoWideningObserver.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Listener orientation effect
*                observer class.
*
*  Version     : 0.2
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

#ifndef STEREOWIDENINGOBSERVER_H
#define STEREOWIDENINGOBSERVER_H

// INCLUDES

#include <e32base.h>
#include <StereoWideningBase.h>
#include <MAudioEffectObserver.h>


// CLASS DECLARATION

/**
*  This is the stereo wideing effect observer class. Object interested in receiving notification
*  when the CStereoWidening object changes state should derive from this class and implement its
*  interface.
*
*  @since 3.0
*/

class MStereoWideningObserver : public MAudioEffectObserver
	{
	public:
		static const TUint KStereoWideningLevelChanged = KSpecificEffectBase + 1;
	};

#endif	// of STEREOWIDENINGOBSERVER_H

// End of File