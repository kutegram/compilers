
/*
* ============================================================================
*  Name     : aknnavidecoratorobserver.h
*  Part of  : AVKON
*
*  Description:
*     Interface class for navi decorator. This observer is used
*     by observers to get right or left arrow events of navipane
*     PointerEvents for arrow decorators are handled in Navigation 
*     decorator class.
*
*
*  Version:
*
*  Copyright © 2005 Nokia Corporation.
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

#ifndef AKNNAVIDECORATOROBSERVER_H
#define AKNNAVIDECORATOROBSERVER_H

#include <e32base.h>

class MAknNaviDecoratorObserver
    {
public:
    enum TAknNaviDecoratorEvents
        {
        /** Pointer tap event id for right arrow */
        EAknNaviDecoratorEventRightTabArrow,
        /** Pointer tap event id for left arrow */
        EAknNaviDecoratorEventLeftTabArrow,
        /** Pointer tap event id for navilabel */
        EAknNaviDecoratorEventNaviLabel
        }; 
        
public:

   	/**
     * Method for handling events in observed classes. 
     * 
     * @param aEventID Id of the event.
     *
     */
    virtual void HandleNaviDecoratorEventL( TInt aEventID ) = 0; 
    };

#endif // AKNNAVIDECORATOROBSERVER_H
