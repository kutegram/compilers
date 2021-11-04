/*
* ============================================================================
*  Name        : sensrvpropertylistener.h
*  Interface   : Sensor Channel API
*  Description : Property listener callback interface
*  Version     : %version: 6 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright © 2008 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.1
*/

#ifndef SENSRVPROPERTYLISTENER_H
#define SENSRVPROPERTYLISTENER_H


#include <e32base.h>
#include <sensrvtypes.h>
#include <sensrvproperty.h>
#include <sensrvchannel.h>

// CLASS DECLARATIONS

/**
* Property listener callback interface to indicate when a property has changed or when
* clients access to setting properties has changed.
* 
* This class is for use with the CSensrvChannel::SetPropertyListenerL() method. Clients wishing
* to use property listening must inherit from this class and provide a reference to an instance
* of it in CSensrvChannel::SetPropertyListenerL().
* 
* @see CSensrvChannel::SetPropertyListenerL()
* 
* 
*/
class MSensrvPropertyListener
    {
    public:
    /**
    * Callback implemented by a client so that they can be notified when the value of a
    * property has changed. The client that set the property will not be notified.
    * 
    * Clients providing an implementation for this callback must ensure that the operation does
    * not leave. If a leave does occur then the behaviour is undefined.
    * 
    * 
    * @param  aChannel Channel associated with the listener
    * @param  aChangedProperty The property that has changed
    */  
    virtual void PropertyChanged( CSensrvChannel& aChannel, 
                                  const TSensrvProperty& aChangedProperty ) = 0;

    /**
    * Callback implemented by a client so that they can be notified when property listening
    * has failed. If the error is fatal the channel will be closed, the sensor server session
    * has been terminated and the channel object is no longer useable. If the error is minor,
    * some property changes have potentially been missed, however listening is still active.
    * 
    * Clients providing an implementation for this callback must ensure that the operation does
    * not leave. If a leave does occur then the behaviour is undefined.
    * 
    * 
    * @param  aChannel Channel associated with the listener
    * @param  aError The error severity
    */
    virtual void PropertyError( CSensrvChannel& aChannel, 
                                TSensrvErrorSeverity aError ) = 0;
    
    /**
    * Callback implemented by a client so that they can be notified when the clients access for 
    * setting properties has changed.
    * 
    * Clients providing an implementation for this callback must ensure that the operation does
    * not leave. If a leave does occur then the behaviour is undefined.
    * 
    * 
    * @param  aIndication Indication of the clients access for setting of properties  
    */
    virtual void SetPropertySuccessIndicationChanged( 
                 TSetPropertySuccessIndicator aIndication ) = 0;
        
    /** 
    * Callback to future proof this API so that additional callbacks can be added in the future 
    * without breaking binary compatibility.
    * 
    * @param  aInterfaceUid Identifier for the interface to be retrieved
    * @param  aInterface A reference to a pointer for the specified interface. Implementation sets
    * aInterface to a valid pointer if the M-class identified by aInterfaceUid is supported, otherwise
    * it is set to NULL on exit.
    * 
    * 
    * @leave  One of the system-wide error codes
    */
	virtual void GetPropertyListenerInterfaceL( TUid aInterfaceUid, TAny*& aInterface ) = 0;

    };
    
//SENSRVPROPERTYLISTENER_H
#endif

// End of File
