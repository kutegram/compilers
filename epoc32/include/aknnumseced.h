/*
* ==============================================================================
*  Name        : Aknnumseced.h
*  Part of     : Avkon
*
*  Description : An editor for a numeric password
*  Version     :
*
*  Copyright � 2002-2004 Nokia. All rights reserved.
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

#if !defined(__AKNNUMSECED_H__)
#define __AKNNUMSECED_H__

//  INCLUDES
#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#include <eikseced.h>

// CLASS DECLARATION

/**
*  An editor for a numeric password. 
*  Implementation of Avkon numeric secret editor which expands
*  @c CEikSecretEditor to better cope with numeric passwords e.g. PINs.
*
*  @since Series 60 0.9
*/
class CAknNumericSecretEditor : public CEikSecretEditor
	{
public:
    /**
    * C++ default constructor.
    */
	IMPORT_C CAknNumericSecretEditor();
	
	/**
    * Destructor.
    */
    ~CAknNumericSecretEditor();
    
public:	// from CCoeControl

    /**
    * From @c CCoeControl. Gets the control's input capabilities.
    * Gets input capabilities that describe which forms of text input are
    * consumed by a control.
    *
    * If this function is overrided in a subclass, the subclass should
    * obtain this class' InputCapabilities' object provider through
    * TCoeInputCapabilities::ObjectProvider() and set that as a part of
    * the subclass' InputCapabilities object provider chain to ensure
    * maximum functionality.
    *
    * @return The control's input capabilities.
    */
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected:
    // methods to enable CAknNumericSecretEditor to inherit from 
    // CEikSecretEditor
    
    /**
    * Appends a character to the password.
    * @param aKeyCode A numeric character to be appended to the password.
    */
    IMPORT_C virtual void AppendCharacterL( TInt aKeyCode );
    
    /**
    * Creates a FEP state handler (@c CAknEdwinState ) with default values.
    * @return A Pointer to a FEP state handler.
    */
	IMPORT_C virtual MCoeFepAwareTextEditor_Extension1::CState* CreateFepStateL();
private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // from MCoeFepAwareTextEditor
	IMPORT_C void MCoeFepAwareTextEditor_Reserved_2();
private:  // from MCoeFepAwareTextEditor_Extension1
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_2();
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_3();
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_4();
private: // Data
	TInt iSpare;
	};

#endif	// AKNNUMSECED_H
            
// End of File
