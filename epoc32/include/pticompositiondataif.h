/*
* ============================================================================
*  Name        : PtiCompositionDataIF.h
*  Part of     : PtiEngine
*  Interface   : 
*  Description : MPtiEngineCompositionDataInterface class definitions.
*  Version     : 
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef MPTIENGINECOMPOSITIONDATAINTERFACE_H
#define MPTIENGINECOMPOSITIONDATAINTERFACE_H

// INCLUDES
#include <e32base.h>
#include <badesca.h> 

// CLASS DECLARATION

/**
* MPtiEngineCompositionDataInterface class.
*  This is a class which returned by CPtiEngine::CompositionData() API.
*
*  @lib PtiEngine.lib
*  @since 2.6
*/
class MPtiEngineCompositionDataInterface
    {
    public:
        // the attribute of phrase
        enum TPtiAttributeOfPhrase
            {
            EPtiAttributeTransitoryInput,  // transitory input(before converting)
            EPtiAttributeNonTargetConvert, // non-target phrase(while converting)
            EPtiAttributeTargetConvert     // target phrase(while converting)
            };

    public:
        /**
        * Gets a cursor position on converting string
        * @since 2.6
        * @return TInt : The current cursor position
        *         If the cursor is left side, the returned value is 0.
        */
        IMPORT_C virtual TInt   CursorPosition() const = 0;

        /**
        * Gets the number of phrases on converting string
        * @since 2.6
        * @return TInt : the number of phrases
        */
        IMPORT_C virtual TInt   NumberOfPhrase() const = 0;

        /**
        * Gets the character count of each phrase
        * @since 2.6
        * @return TPtrC8 : the arrary keeping the character count
        */
        IMPORT_C virtual TPtrC8 LengthOfPhrase() const = 0;

        /**
        * Gets the attribute of each phrase
        * @since 2.6
        * @return TPtrC8 : the arrary keeping the value of TPtiAttributeOfPhrase
        */
        IMPORT_C virtual TPtrC8 AttributeOfPhrase() const = 0;

        /**
        * Gets the converting string
        * @since 2.6
        * @return TPtrC : the converting string
        */
        IMPORT_C virtual TPtrC  ConvertingString() const = 0;

        /**
        * Gets the specified string
        * @since 2.6
        * @return TPtrC : the completed string
        */
        IMPORT_C virtual TPtrC  CompletedString() const = 0;

        /**
        * Gets the reading string of the completed string
        * @since 2.6
        * @return TPtrC : the reading string
        */
        IMPORT_C virtual TPtrC  ReadingString() const = 0;

        /**
        * Checking it whether a character in a current cursor position 
        * is in modifiable character.
        * The modifiable character is diacritics and small characters.
        * There are two diacritics marks in Japanese: viced sound mark
        * and semi-voiced sound mark.
        * @since 2.6
        * @return TBool : ETrue is modifiable character.
        */
        IMPORT_C virtual TBool IsModifiableCharacter() const = 0;
    };

#endif  // MPTIENGINECOMPOSITIONDATAINTERFACE_H

// End of file
  
