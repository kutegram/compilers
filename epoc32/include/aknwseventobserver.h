/*
* ==============================================================================
*  Name        : ?FileName.h
*  Part of     : ?Subsystem_name / ?Module_name
*  Interface   : ?Interface_category, ?Interface_name
*  Description : ?Description
*  Version     : ?Version
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
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

#if !defined(__AKNWSEVENTOBSERVER_H__)
#define __AKNWSEVENTOBSERVER_H__

// INCLUDES
#include <e32std.h>
//#include <w32std.h>
#include <coecntrl.h>

// CONSTANTS

enum TAknWsEventObserverPanic
	{
	EAknWsEventObserverFailedToAddObserver,
	EAknWsEventObserverUnknownObserverRemoved
	};

GLREF_C void Panic(TAknWsEventObserverPanic aPanic);


// CLASS DECLARATION

/**
*  Support for events to be sent independent of the control stack to other 
*  consumers yet internal to the application.
*
*  
*/
class MAknWsEventObserver
	{
public:
	virtual void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination) = 0;
	};


// CLASS DECLARATION

/**
*  This class distributes events to the window server event observers; 
*  It is itself a window server event observer.
*
*  @since Series 60 0.9
*/
class CAknWsEventMonitor: public CBase, public MAknWsEventObserver
{
public:

    /**
    * Two-phased constructor.
    */
	static CAknWsEventMonitor* NewL();

    /**
    * Destructor.
    */
	virtual ~CAknWsEventMonitor();

    /**
    * Two-phased constructor.
    */
	void ConstructL();

    /**
    * Adds an event observer if there is not one yet.
    * @param aEventObserver A pointer to the event observer.
    */
	IMPORT_C void AddObserverL(MAknWsEventObserver* aEventObserver);

    /**
    * Removes the event observer.
    * @param aEventObserver A pointer to the event observer. (not used in default implementation)
    */
	IMPORT_C void RemoveObserver(const MAknWsEventObserver* aEventObserver);

    /**
    * Window server event handler.
    * @param aEvent The event.
    * @param aDestination Event destination.
    */
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
	
    /**
    * Enables / disables event observer. AknAppUi provides all window server events to enabled monitor automatically
    *
    * @since S60 3.2
    */
    IMPORT_C void Enable(TBool aEnable = ETrue);
	
	/**
	* Internal to Avkon
	*
	* @since S60 3.2
	*/	
	TBool IsEnabled();
	
	

private:
	RPointerArray<MAknWsEventObserver>* iEventObservers;
	TBool iEnabled; // was TInt iSpare;

private:
// reserved virtual function space
	IMPORT_C virtual void Reserved_1();

};


#endif  // __AKNWSEVENTOBSERVER_H__
