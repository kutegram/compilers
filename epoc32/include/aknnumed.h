/*
* ==============================================================================
*  Name        : AknNumed.h
*  Part of     : EikCtl
*  
*  Description : Intermediate class for defining data shared between numeric 
*                edwins  
*  Version     :
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/
#if !defined(__AKNNUMED_H_)
#define __AKNNUMED_H_

//  INCLUDES
#include <eikedwin.h>


// CLASS DECLARATION

/**
* Intermediate class for defining data shared between numeric edwins
*
* @since Series 60 0.9
*/
class CAknNumericEdwin : public CEikEdwin
	{
public:
	/**
    * Destructor.
    */
	IMPORT_C virtual ~CAknNumericEdwin();
	
	/** 
    * 
    * Indicates a validiton status for values read from the control.
    * 
    */
	enum TValidationStatus
		{
		EValueValid = KErrNone,/**< Read value is valid. */
		EValueTooSmall,   /**< Read value is smaller than the minimum value. */
		EValueTooLarge,   /**< Read value is larger than the maximum value. */
		EValueNotParsed,  /**< Read value can not be parsed. */
		EEmpty            /**< The control is empty. */
		};

    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected:
	/**
    * Maps a key event so that any numeric character is mapped to the correct 
    * digit type that this editor is using.
    * @since Series 60 2.0
    * @param aKeyEvent The key event to modify.
    * @param aType The type to modify.
    * @param aDigitType The digit type to map all numeric characters to.
    */
	IMPORT_C void MapKeyEvent(
		TKeyEvent& aKeyEvent,
		TEventCode& /*aType*/, 
		TDigitType aDigitType) const;


private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: // from CEikEdwin
		IMPORT_C virtual void Reserved_3();
private:		
		TInt iSpare; // Needs at least some data
	};


#endif
