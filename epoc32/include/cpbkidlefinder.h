/*
* ============================================================================
*  Name     : CPbkIdleFinder.h
*  Part of  : PbkEng.dll
*
*  Description:
*      Abstract Phonebook entry interface.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
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

#ifndef __CPbkIdleFinder_H__
#define __CPbkIdleFinder_H__

// INCLUDES
#include <e32base.h>    // CBase

// FORWARD DECLARATIONS
class CIdleFinder;
class CContactItemFieldDef;
class CContactIdArray;

// CLASS DECLARATION

/**
 * Phonebook idle finder class. Wrapper for Contact Model's CIdleFinder.
 * @see CIdleFinder.
 */
class CPbkIdleFinder : public CBase
	{
    public:  // Constructors and destructors
        /**
         * Constructor. Not exported because objects of this class are created
         * only by CPbkContactEngine.
         *
         * @param aFinder   Contact Model idle finder object. This takes 
         *                  ownership of aFinder.
         * @param aFieldDef Field defintion passed to aFinder. This takes
         *                  ownership of aFieldDef.
         */
        CPbkIdleFinder(CIdleFinder* aFinder, CContactItemFieldDef* aFieldDef);

        /**
         * Destructor.
         */
        ~CPbkIdleFinder();
	    
    public:  // CIdleFinder interface
        /**
         * Tests whether a search is complete.
         * @return ETrue if complete, EFalse if not.
         * @see CIdleFinder::IsCompelete().
         */
	    IMPORT_C TBool IsComplete() const;

        /**
         * Gives access and ownership of the contact ids found in the search.
         * @return Contacts id's found in the search.
         * @see CIdleFinder::TakeContactIds().
         */
	    IMPORT_C CContactIdArray* TakeContactIds();

        /**
         * Check for errors when search is complete.
         * @return Error code. KErrNone if no errors occurred during the search.
         * @see CIdleFinder::Error().
         */
	    IMPORT_C TInt Error() const;

    public:  // Additional interface
        /**
         * Returns the CIdleFinder passed to constructor. Ownership not
         * transferred.
         * @return Symbian Contacts model Idle finder object. NULL if not set.
         */ 
        IMPORT_C CIdleFinder* IdleFinder() const;

        /**
         * Returns the CContactItemFieldDef passed to constructor. Ownership
         * not transferred.
         * @return Symbian Contacts model contact item field definition. NULL 
         *         if not set.
         */ 
        IMPORT_C CContactItemFieldDef* FieldDef() const;
    
    private:  // Data
		/// Own: idle finder object
        CIdleFinder* iFinder;
		/// Own: field definition (array of field types)
        CContactItemFieldDef* iFieldDef;
    };


#endif // __CPbkIdleFinder_H__

// End of File
