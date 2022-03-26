/*
* ============================================================================
*  Name        : sensrvdatalistener.h
*  Interface   : Sensor Channel API
*  Description : Data listener
*  Version     : %version: 6 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright � 2008 Nokia.  All rights reserved.
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

#ifndef SENSRVDATALISTENER_H
#define SENSRVDATALISTENER_H


#include <e32base.h>
#include <sensrvchannel.h>
#include <sensrvtypes.h>

/**
* Data listener callback interface to indicate when data is available for clients to read.
* 
* This class is for use with the CSensrvChannel::StartDataListeningL() method. Clients wishing to
* use data listening must inherit from this class and provide a reference to an instance of it in
* CSensrvChannel::StartDataListeningL().
* 
* @see CSensrvChannel::StartDataListeningL()
* @see CSensrvChannel::GetData()
* @see CSensrvChannel::StopDataListening()
* 
* 
*/
class MSensrvDataListener
    {
    public:
    /**
    * Callback implemented by a client so that they can be notified that data is available to read.
    * A client can read the data using CSensrvChannel::GetData(). Data is valid until this
    * DataReceived() notification occurs again.
    
    * Data loss can occur if the client does not retrieve data, using SensrvChannel::GetData(), from
    * server fast enough after the client has been told it is availble. This can happen when system
    * is under heavy load and the client process has lower priority than sensor server process.
    * If data loss is a problem consider using a higher object count in data listening, which will
    * reduce the number of IPC context switches.
    * 
    * Clients providing an implementation for this callback must ensure that the operation does not
    * leave. If a leave does occur then the behaviour is undefined.
    * 
    * 
    * @param  aChannel Channel associated with the listener
    * @param  aCount Data object count contained in data to be read
    * @param  aDataLost Number of lost data items.
    * @see CSensrvChannel::GetData()
    */  
    virtual void DataReceived( CSensrvChannel& aChannel, 
                               TInt aCount, 
                               TInt aDataLost ) = 0;
    
    /**
    * Callback implemented by a client so that they can be notified when data listening has failed.
    * If the error is fatal the channel will be closed, the sensor server session has been terminated
    * and the channel object is no longer useable. If the error is minor, some data has potentially
    * been lost, however listening is still active.
    * 
    * Clients providing an implementation for this callback must ensure that the operation does not
    * leave. If a leave does occur then the behaviour is undefined.
    * 
    * 
    * @param  aChannel Channel associated with the listener
    * @param  aError The error severity
    */
    virtual void DataError( CSensrvChannel& aChannel, 
                            TSensrvErrorSeverity aError ) = 0;
    
    /** 
    * Callback to future proof this API so that additional callbacks can be added in the future 
    * without breaking binary compatibility.
    * 
    * 
    * @param  aInterfaceUid Identifier for the interface to be retrieved
    * @param  aInterface A reference to a pointer for the specified interface. Implementation sets
    * aInterface to a valid pointer if the M-class identified by aInterfaceUid is supported, otherwise
    * it is set to NULL on exit.
    * @leave  One of the system-wide error codes
    */
	virtual void GetDataListenerInterfaceL( TUid aInterfaceUid, TAny*& aInterface ) = 0;

    };
 
//SENSRVDATALISTENER_H
#endif

// End of File
