/*
* ============================================================================
*  Name        : AknNotify.h
*  Part of     : UI Framework Core / AVKON Notifiers Client
*  Description :
*  Version     : %version: %
*
*  Copyright © 2002-2007 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/
#ifndef __AKNNOTIFY_H__
#define __AKNNOTIFY_H__

// INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS 
class CAknSDData;

// CLASS DECLARATION
class RNotifier2 : public RNotifier
    {
public:
    TInt Connect();
    };
    
/**
*  Base class for handling @c RNotifier.
*
*  @since S60 0.9
*/
NONSHARABLE_CLASS(CAknNotifyBase) : public CBase
    {
public:
    /**
    * Destructor.
    */
    IMPORT_C ~CAknNotifyBase();

    /**
     * @since S60 3.1
     * Sets additional information to be sent to secondary display.
     * Takes ownership of object.
     * Must be called before sending data to notifier to have effect.
     * @internal to S60
     *
     * @aparam aData data to be sent to cover UI
     */
    IMPORT_C void SetSecondaryDisplayData(CAknSDData* aData);

protected:
    /**
    * C++ constructor.
    * @param aUid The UID identifying the plug-in notifier.
    */
    CAknNotifyBase(TUid aUid);
    
    /**
    * 2nd phase constructor.
    * Connects to the notifier server.
    */
    void ConstructL();
    
    /**
    * Starts or updates the notifier.
    * @param aBuffer Data that can be passed to notifier.
    * @param aResponse Data that can be returned by notifier.
    */
    void StartOrUpdateL(const TDesC8& aBuffer, TDes8& aResponse);
    
    /**
    * Starts the notifier.
    * @param aStatus The request status.
    * @param aBuffer Data that can be passed to the notifier.
    * @param aResponse Data that can be returned by the notifier.
    */
    void StartOrUpdateAndGetResponseL(
        TRequestStatus& aStatus,
        const TDesC8& aBuffer,
        TDes8& aResponse);
                                                                            
    // We don't give this funtionality out of library at the moment
    // returns instance of secondary display data if set.
    CAknSDData* SecondaryDisplayData();
                                                                          
private:
    IMPORT_C void CAknNotifyBase_Reserved();

private:
    TUid iUid;
    TBool iStarted;
    RNotifier2 iNotify;
    CAknSDData* iSecondaryDisplayData;
    };

#endif // __AKNNOTIFY_H__
