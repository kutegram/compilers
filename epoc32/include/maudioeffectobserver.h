/*
* ==============================================================================
*  Name        : MAudioEffectObserver.h
*  Part of     : Effects Framework
*  Interface   : Audio Effect Observer
*  Description : Definition of the Audio Effect Observer class.
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


#ifndef AUDIOEFFECTOBSERVER_H
#define AUDIOEFFECTOBSERVER_H

// CLASS DECLARATION


/**
*  Interface class to be implemented by objects that are interested in receiving events from
*  audio effect.
*
*  @since 3.0
*/
class MAudioEffectObserver
    {
    public:

		static const TUint KEnabled = 1;				// The effect is enabled.
		static const TUint KDisabled = 2;				// The effect is disabled
		static const TUint KEnforced = 3;				// The effect is enforced
		static const TUint KNotEnforced = 4;			// The effect is not enforced
		static const TUint KLostUpdateRights = 5;		// The effect has lost update rights
		static const TUint KGainedUpdateRights = 6;		// The effect has gained update rights
		static const TUint KSpecificEffectBase = 20;	// Offset to specific effect events

        /**
        * Invoked by the audio effect object when the status of the audio effect has changed.
        * @since 3.0
        * @param aObservedEffect The effect that changed
        * @param aEvent The specific event Id of the effect that changed.
        */
        virtual void EffectChanged( const CAudioEffect* aObservedEffect, TUint8 aEvent ) = 0;

    };

#endif      // AUDIOEFFECTOBSERVER_H

// End of File
