/*
* ============================================================================
*  Name        : eikalign.h
*  Part of     : S60 UI Framework / EikCoCtl
*  Description : Class declaration for EIKON aligned control.
*  Version     : %version: 1 %
*
*  Copyright � 2002-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/

#ifndef __EIKALIGN_H__
#define __EIKALIGN_H__

#include <coecntrl.h>
#include <gulalign.h>
#include <gulutil.h>
#include <akncontrol.h>

/**
 * Extends @c CAknControl to support control alignment and margins.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9
 */
class CEikAlignedControl : public CAknControl
	{
public:

    /**
     * C++ default constructor.
     */
	IMPORT_C CEikAlignedControl();
	
	/**
	 * Destructor
	 */
	IMPORT_C ~CEikAlignedControl();
	
	/**
	 * Sets all of the control's margins.
	 *
	 * @param aValue The number of pixels to which all margins will be set.
	 */
	IMPORT_C void SetAllMarginsTo(TInt aValue);
	
	/**
	 * Sets the control's alignment.
     *
	 * @param aAlign The alignment to be set to the control.
	 */
	IMPORT_C void SetAlignment(TGulAlignmentValue aAlign);
	
public: /** From @c CCoeControl. */

    /**
     * Handles pointer events.
     *
     * This function gets called whenever a pointer event occurs in the 
     * control, i.e. when the pointer is within the control's extent, or when 
     * the control has grabbed the pointer. The control should implement this 
     * function to handle pointer events.
     * 
     * If overriding this method, the implementation must 
     * include a base call to this method.
     *
     * From @c CCoeControl.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    	
protected:

    /**
     * Writes the internal state of the control and its components
     * to @c aWriteStream.
     *
     * Does nothing in release mode.
     * Designed to be overridden and base called from subclasses.
     *
     * From @c CCoeControl.
     *
     * @param[in,out] aWriteStream A connected write stream.
     */
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	
private: /** From @c CAknControl. */

    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
public:
    /** The control's margins. */
	TMargins8 iMargin;
	
	/** The control's alignment. */
	TGulAlignment iAlignment;

private:
    TInt iSpare[2];
	};

#endif // __EIKALIGN_H__
