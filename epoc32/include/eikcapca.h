// EIKCAPCA.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCAPCA_H__)
#define __EIKCAPCA_H__

#include <e32base.h>

class CEikCaptionedControl;
class CCoeControl;
class CEikCapCArrayExtension;

class CEikCapCArray : public CArrayPtrFlat<CEikCaptionedControl>
	{
public:
	/** Constructor
     *
     * Creates CEikCapCArray with a granilarity.
     *
     * @param aGranularity how many items will be allocated each time allocation happens
	 */
	IMPORT_C CEikCapCArray(TInt aGranularity);
    
    /** Destructor
     *
     * Destroys CEikCapCArray
     */
	IMPORT_C ~CEikCapCArray();

	/** MinimumSize() returns minimum size for the array
     *
     * MinimumSize calculates minimum possible size for
     * the captioned control array. 
     *
     * @return size in pixels
	 */
	IMPORT_C TSize MinimumSize();
 
    /** SetRect() sets the rectangle of the captionedcontrolarray
     *
     * SetRect layouts the captionedcontrolarray. Captioned
     * control rectangles are calculated based on provided rectangle
     * and sizes of the captioned controls.
     *
     * @param aRect Rectangle for the whole array
     */
	IMPORT_C void SetRect(const TRect& aRect);
	
	/** ResetMinimumSizes() clears size information
     *
     * ResetMinimumSizes goes through all captionedcontrols
     * and resets the minimum size information of the
     * captionedcontrols
	 */
	IMPORT_C void ResetMinimumSizes();

    /** LineIndexFromId() provides line index in array based on id number
     *
     * Every captionedcontrol has iId and based on the id,
     * LineIndexFromId goes through the captionedcontrolarray
     * and finds the captionedcontrol's position in the array
     * based on the id provided
     *
     * @param aControlId captionedcontrol's iId.
     */
	IMPORT_C TInt LineIndexFromId(TInt aControlId) const;

    /** FindLineIndex() finds line index based on control
     * 
     * Every captionedcontrol has iControl CCoeControl which
     * implements the control for the DLG_LINE. FindLineIndex
     * goes through all captionedcontrols and finds the one
     * which has aControl as it's control.
     *
     * @param aControl control to be found
     */
	IMPORT_C TInt FindLineIndex(const CCoeControl* aControl) const;

    /** DeleteLine() removes line from captionedcontrolarray
     *
     * Elements from CaptionedControlArray can be removed
     * by calling DeleteLine method.
     *
     * @param aIndex index of the line to be removed
     */
	IMPORT_C void DeleteLine(TInt aIndex);

	/** AdjustAllIds() modified iId fields of the captionedcontrols
     * 
     * @param aControlIdDelta how much to increase or decrease control id's
     */
	IMPORT_C void AdjustAllIds(TInt aControlIdDelta);

	/** SetDensePacking() sets dense packing flag
     *
     * @param aDensePacking whether dense packing flag is on
  	 */
	IMPORT_C void SetDensePacking(TBool aDensePacking);
	TBool CalcItemIndexes(TInt &aTopItemIndex, TInt &aMiddleItems, TInt &aBottomItemIndex, TSize aAreaSize);
	TInt NumberOfTextLines() const; // for scrollbar
	TInt NumberOfTextLinesBeforeLine(TInt aLine) const;
	TInt FindItemFromTextLine(TInt aTextLine) const;
	TRect Rect() const;
	void SetRect(const TRect& aRect, TInt aTop, TInt aMiddle, TInt aBottom);
	TInt YPosToLine(const TRect &aRect, TInt aTop, TInt aMiddle, TInt aBottom, TInt aYCoord);
	void CreateExtensionL();
	CEikCapCArrayExtension *ExtensionOrNull() const;
	
private:
	//TInt iCaptionWidth;
	CEikCapCArrayExtension *iExtension;
	TBool iDensePacking;
	//TRect iRect;
	};

#endif
