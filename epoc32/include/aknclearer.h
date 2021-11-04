/*
* ============================================================================
*  Name        : AknClearer.h
*  Part of     : S60 UI Framework / EikCoCtl
*  Description : Screen Clearer API, support for screen blanking.
*  Version     :
*
*  Copyright © 2002-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/

#ifndef AKNCLEARER_H
#define AKNCLEARER_H

#include <AknControl.h>

#include <eikenv.h>

class CAknScreenClearerBaseExtension;

/**
*  This class is base class for screen blanking.
*
*  @since Series 60 0.9
*/
class CAknScreenClearerBase : public CAknControl
	{
public:

	/**
	* Handles situation when status pane size changes.
	*/
	IMPORT_C void HandleStatusPaneSizeChangeL();
    
public: // from CCoeControl

    /**
    * From CCoeControl.
	*/
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	

protected:
    
    /**
    * Destructor.
	*/
	IMPORT_C virtual ~CAknScreenClearerBase();
	
    /**
    * Symbian 2nd phase constructor.
    *
    * @param aParent Parent window group.
    * @param aOrdinalPos Ordinal position of the blank window.
    * @param aBlankAppStatusPane A flag to decide if application status pane area is to blanked or not.
	*/
	IMPORT_C void ConstructL(RWindowGroup& aParent, TInt aOrdinalPos, TBool aBlankAppStatusPane);

private: // from CCoeControl
	
    /**
    * From CCoeControl.
	*/
	IMPORT_C void Draw(const TRect& aRect) const;

private: // from CAknControl
    /**
    * From CAknControl.
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected:
    
    /**
    * Sets shape for the cleared window.
    */
	void SetShapeL();

    /**
    * Sets skin background and shape for the cleared window.
    */
	void SetSkinShapeL();

private:
    CAknScreenClearerBaseExtension* iExtension;
	TBitFlags iFlags;
	};


// CLASS DECLARATION

/**
*  This class is for use inside applications for screen blanking.
*
*  @since Series 60 0.9
*/
class CAknLocalScreenClearer : public CAknScreenClearerBase
	{
public:

    /**
    * Two-phased constructor.
    */
	IMPORT_C static CAknLocalScreenClearer* NewLC();

    /**
    * Two-phased constructor.
    * @param aBlankAppStatusPane @c ETrue if application status pane is blank, 
    *                            @c EFalse if not.
    */
	IMPORT_C static CAknLocalScreenClearer* NewLC(TBool aBlankAppStatusPane);

    /**
    * Two-phased constructor.
    * @param aBlankAppStatusPane @c ETrue if application status pane is blank, 
    *                            @c EFalse if not.
    */
	IMPORT_C static CAknLocalScreenClearer* NewL(TBool aBlankAppStatusPane);

    /**
    * From CCoeControl
    */
	IMPORT_C void HandleResourceChange(TInt aType);

	};

#endif // AKNCLEARER_H
