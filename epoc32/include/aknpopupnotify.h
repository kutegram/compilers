/*
* ============================================================================
*  Name        : aknpopupnotify.h
*  Part of     : UI Framework Core / AVKON Notifiers Client
*  Description : Class definition of AVKON pop-up notifier.
*  Version     : %version: tr1s60#6 %
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
#ifndef C_AKNPOPUPNOTIFY_H
#define C_AKNPOPUPNOTIFY_H

#include <aknnotify.h>

/**
 * Class for displaying a message using a notifier pop-up.
 *
 * @deprecated
 */
NONSHARABLE_CLASS(CAknPopupNotify) : public CAknNotifyBase
    {
public:
    /**
     * @deprecated
     */
    IMPORT_C static CAknPopupNotify* NewL();
    
    /**
     * @deprecated
     */
    IMPORT_C static CAknPopupNotify* NewLC();
    
    /**
     * @deprecated
     */
    IMPORT_C ~CAknPopupNotify();

    /**
     * @deprecated
     */
    IMPORT_C void PopupMessageL(const TDesC& aMessage);

private:
    /**
     * @deprecated
     */
    CAknPopupNotify();
    
    /**
     * @deprecated
     */
    void ConstructL();
    
private:
    /**
     * @deprecated
     */
    IMPORT_C void CAknNotifyBase_Reserved();
    };

#endif // C_AKNPOPUPNOTIFY_H
