/*
* ============================================================================
*  Name     : CPbkVoipAddressSelect from CPbkVoipAddressSelect.h
*  Part of  : PbkView.dll
*
*  Description:
*       Phonebook Voip number selection dialog. This dialog implements the
*       Voip number selection logic of Phonebook.
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

#ifndef __CPbkVoipAddressSelect_H__
#define __CPbkVoipAddressSelect_H__

//  INCLUDES
#include "CPbkAddressSelect.h"

// CLASS DECLARATION

/**
 * Phonebook Voip number selection dialog. This dialog implements the
 * Voip number selection logic of Phonebook.
 */
class CPbkVoipAddressSelect : public CPbkAddressSelect
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkVoipAddressSelect();

        /**
         * Parameters for ExecuteLD(TParams&).
         *
         * @see CPbkAddressSelect::TBaseParams
         * @see ExecuteLD(TParams&)
         */
        class TParams : public CPbkAddressSelect::TBaseParams
            {
            public:
                /**
                 * Constructor.
                 * @param aContact  Contact from which to select a Voip address.
                 */
                IMPORT_C TParams(const CPbkContactItem& aContact);

            private:  // Spare data
                TInt32 iSpare1;
            };

        /**
         * Runs the Voip address selection query (if necessary).
         *
         * @param aParams   Parameters and return values of the query.
         * @return  ETrue if query was accepted, EFalse if canceled.
         * @see TParams
         */
        IMPORT_C TBool ExecuteLD(TParams& aParams);

        /**
         * Destructor.
         */
        IMPORT_C ~CPbkVoipAddressSelect();

    private:  // from CPbkAddressSelect
        IMPORT_C TBool AddressField(const TPbkContactItemField& aField) const;
        IMPORT_C void NoAddressesL();
        IMPORT_C const TDesC& QueryTitleL();
        IMPORT_C TInt QuerySoftkeysResource() const;

    private: // data members
        /// Own: Title for Voip number selection list
        HBufC* iQueryTitle;
        // Spare data
        TInt32 iSpare1;
    };


#endif // __CPbkVoipAddressSelect_H__

// End of File
