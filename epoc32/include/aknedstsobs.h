/*
* ==============================================================================
*  Name        : aknedstsobs.h
*  Part of     : Avkon
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Interface for handling control's state change.
*  Version     : ?Version
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/


#if !defined(__AKNEDSTSOBS_H__)
#define __AKNEDSTSOBS_H__

// FORWARD DECLERATIONS
class CAknEdwinState;


// CLASS DECLERATION
/**
* Interface for handling control's state change.
* 
* @since Series 60 0.9
*/
class MAknEdStateObserver
	{
public:
	/** 
    * Observer event types.
    */
	enum EAknEdwinStateEvent
        {
        /** The state has been updated */ 
        EAknEdwinStateEventStateUpdate, 
        /** The input mode has been updated */     
        EAknEdwinStateInputModeUpdate,
        /** The case mode has been updated */   
        EAknEdwinStateCaseModeUpdate,
        /** The local language has been updated */    
        EAknEdwinStateLocalLanguageUpdate, 
        /** The flags have been updated */  
        EAknEdwinStateFlagsUpdate,
        /** The edwin state needs to be sync'ed */
        EAknSyncEdwinState,
        /** Cursor position has changed in editor */
        EAknCursorPositionChanged,
        /** VKB/HW activation request */
        EAknActivatePenInputRequest
        };
public:
	/**
    * Handles an state event from a observed control.
    * Pure virtual function that is called when a control, for which this
    * control is the observer, calls @c ReportAknedstateEventL().
    * It should be implemented by the observer control and should handle all
    * state events sent by controls it observed. 
    * @param aAknEdwinState The control that sent the event.
    * @param aEventType The event type defined in @c EAknEdwinStateEvent.
    */
	virtual void HandleAknEdwinStateEventL(CAknEdwinState* aAknEdwinState,
		EAknEdwinStateEvent aEventType) = 0;
	};

#endif
