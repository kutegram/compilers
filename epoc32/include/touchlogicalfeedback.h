/*
* ============================================================================
*  Name        : touchlogicalfeedback.h
*  Part of     : Tactile Feedback / Tactile Feedback Client  
*  Interface   : Tactile Feedback Client API
*  Description : Logical feedback type enumeration. 
*  Version     : %version: 3 %
*
*  Copyright © 2007-2008 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.0
*/

#ifndef T_TOUCHLOGICALFEEDBACK_H
#define T_TOUCHLOGICALFEEDBACK_H



#include <e32std.h>


/**  
 *  Pointer event types, that can be used when registering
 *  areas to registry. Currently only stylus down event 
 *  is supported (this means that there will be feedback 
 *  whenever stylus down event is received on registered
 *  area, no matter what happens _after_ stylus down event).
 */
enum TTouchEventType
    {
    ETouchEventStylusDown
    };

    
/**  
 *  Logical feedback types, that can be used when producing direct
 *  feedback, or when registering areas to area registry.
 *
 *  Notice, that client application cannot decide the actual physical
 *  feedback that shall be generated. It depends on device configuration,
 *  and current settings. In current devices the user changeable settings
 *  includes vibra and sound feedbacks.
 *
 *  Instructions for using these feedback types:
 *
 *  ETouchFeedbackNone      - Use for disabling feedback for some areas of
 *                            window when using area registry.
 *
 *  ETouchFeedbackBasic     - Use as default feedback for pen down events.
 *                            For example, pressing a button or tab.
 *
 *  ETouchFeedbackSensitive - Sensitive feedback for those situations,
 *                            where the triggering action is not very 
 *                            important (e.g. change focus in list), or when
 *                            there can be a large amount of feedbacks in
 *                            a short time (e.g. text selection which gives
 *                            feedback on every new selected character).
 *                            Also used for scrolling and dragging.
 *
 */
enum TTouchLogicalFeedback
    {
    ETouchFeedbackNone,
    ETouchFeedbackBasic,   
    ETouchFeedbackSensitive
    };


#endif // T_TOUCHLOGICALFEEDBACK_H
