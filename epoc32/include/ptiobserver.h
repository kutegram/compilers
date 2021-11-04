/*
* ============================================================================
*  Name       : PtiObserver.h
*  Part of    : PtiEngine
*  Description: MPtiObserver class definition.  
*  Version:
*
*  Copyright © 2003-2007 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef _PTI_OBSERVER_H
#define _PTI_OBSERVER_H

/**
* PtiEngine observer interface. A client side application can request
* notifications for certain PtiEngine operations through this 
* interface. It is set via CPtiEngine::SetObserver method.
*/
class MPtiObserver
	{
	public:
	    /**
	    * This method is called when multitapping timer
	    * expires. Related to EPtiEngineMultitaping input mode.
	    */
		virtual void KeyTimerExpired() = 0;
		
		/**
		* This method is called when last item in prediction
		* candidate list is reached. Related to EPtiEnginePredictive
		* input mode.
		*/
		virtual void LastWordInSelectionList() = 0;
		
	    /**
		* This method is called when the first item in prediction
		* candidate list is reached. Related to EPtiEnginePredictive
		* input mode.
		*/		
		virtual void FirstWordInSelectionList() = 0;
	};


#endif // _PTI_OBSERVER_H

// End of file
