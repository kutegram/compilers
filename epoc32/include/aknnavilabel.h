/*
* ============================================================================
*  Name     : aknnavilabel.h
*  Part of  : AVKON
*
*  Description:
*   Label control to the status pane's navigation pane.
*
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
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

#ifndef AKNNAVILABEL_H
#define AKNNAVILABEL_H

#include <AknControl.h>

class CAknNaviLabelExtension;
class TAknLayoutText;

/**
 * Label control to the status pane's navigation pane.
 */
class CAknNaviLabel : public CAknControl
	{
public:
    enum TNaviLabelType
        {
        ENavigationLabel,
        EAdditionalInfoLabel,
        EHintText
        };

public:  // new functions

    /**
    * Constructor.
    */
    IMPORT_C CAknNaviLabel();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknNaviLabel();

    /**
     * Set type of the label.
     * @param aNaviLabelType navigation label type.
     */
    IMPORT_C void SetNaviLabelType(TNaviLabelType aNaviLabelType);

    /**
     * Returns type of the label.
     * @return navigation label type.
     */
    IMPORT_C TNaviLabelType NaviLabelType();

    /**
     * Sets navigation label text.
     * @param aText reference to the navigation text.
     */
    IMPORT_C void SetTextL(const TDesC& aText);

    /**
     * Returns the current label text.
     * @return label text. Ownership of the text is not transfered.
     */
    inline const TDesC* Text() const;

public: 

    /**
    * From CCoeControl. Handles pointer event.
    * @param aPointerEvent Pointer event to be handled.
    */
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 

protected: // from CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * From CCoeControl.  Draw a control.  
    *
    * @param aRect The region of the control to be redrawn.   
    */
    IMPORT_C void Draw(const TRect& aRect) const;
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
    /**
     * Calculates width using margins.
     * @return width.
     */
    TInt WidthInsideMargins() const;

    /**
     * Reads the text layout from Aknlayout system.
     * @return Text layout.
     */
    TAknLayoutText LayoutText() const;    

private:
	HBufC* iText;
	CAknNaviLabelExtension* iExtension;
    const CFont* iFont;
    TInt iLeftMargin;
    TInt iRightMargin;
    TInt iSpare;
    TInt iRightOffset;
    TRgb iColor; 

    TNaviLabelType iLabelType;
	};


inline const TDesC* CAknNaviLabel::Text() const
	{ return(iText); }


#endif // AKNNAVILABEL_H
