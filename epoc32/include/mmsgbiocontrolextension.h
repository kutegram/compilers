/*
* ============================================================================
*  Name        : MMsgBioControlExtension.h
*  Part of     : Smart Messaging / MsgEditorUtils
*  Description : Interface to extend bio control functionality
*  Version     : %version: 1 %
*
*  Copyright © 2006-2007 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/

#ifndef MSGBIOCONTROLEXTENSION_H
#define MSGBIOCONTROLEXTENSION_H

/**
 * Bio control extension interface ids.
 *
 * @see MMsgBioControlExtension::BioControlExtension
 */
enum TMsgBioControlExtensions
    {
    // Add new enum tag for a new extension. To maintain BC always add new
    // tags only to the end of existing tags and do not touch existing tags,
    // even if extensions are deprecated. Link the enum tags to types using
    // Doxygen comments.

    /**
     * Extension interface id for MMsgBioControlScrollExtension.
     */
    KMsgBioControlScrollExtension = 1
    };

/**
 * Interface for Bio control extension.
 *
 * @since 3.2
 */
class MMsgBioControlExtension
    {
    public:

    /**
     * Extension point for future BIO control extension interfaces.
     * @since 3.2
     * @param aExtensionId The identifier for the requested extension interface.
     *                     See TMsgBioControlExtensions.
     * @return Untyped pointer to the extension interface.
     *         The pointer must be cast to appropriate type.
     */
    virtual TAny* BioControlExtension( TInt aExtensionId ) = 0;
    };

/**
 * Interface for scrolling extension
 *
 * @since 3.2
 */
class MMsgBioControlScrollExtension
    {
    public:

    /**
     * Performs the internal scrolling of control if needed.
     * @since 3.2     
     * @param aPixelsToScroll Amount of pixels to scroll.
     * @param aDirection      Scrolling direction.
     * @return Amount of pixels that were scrolled. Zero value means the component
     * cannot be scrolled to that direction anymore and view should be moved.
     */
    virtual TInt ExtScrollL( TInt aPixelsToScroll, TMsgScrollDirection aDirection ) = 0;

    /**
     * Prepares control for viewing.
     * @since 3.2     
     * @param aEvent	The event type
     * @param aParam Event related parameters
     */
    virtual void ExtNotifyViewEvent( TMsgViewEvent aEvent, TInt aParam ) = 0;
    };

#endif // MSGBIOCONTROLEXTENSION_H