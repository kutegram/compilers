/*
* ============================================================================
*  Name     : CPbkSmsAddressSelect from CPbkSmsAddressSelect.h
*  Part of  : PbkView.dll
*
*  Description:
*     Phonebook SMS address selection dialog.
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

#ifndef __CPbkSmsAddressSelect_H__
#define __CPbkSmsAddressSelect_H__

//  INCLUDES
#include "CPbkPhoneNumberSelectBase.h"

// CLASS DECLARATION

/**
 * Phonebook SMS address selection dialog.
 */
class CPbkSmsAddressSelect : public CPbkPhoneNumberSelectBase
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkSmsAddressSelect();

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
                 * @param aContact  Contact from which to select a phone number.
                 */
                IMPORT_C TParams(const CPbkContactItem& aContact);
            };

        /**
         * Runs the SMS address selection query (if necessary).
         *
         * @param aParams   Parameters and return values of the query.
         * @return  ETrue if query was accepted, EFalse if canceled.
         * @see TParams
         */
        inline TBool ExecuteLD(TParams& aParams);

        /**
         * Destructor.
         */
        IMPORT_C ~CPbkSmsAddressSelect();

    private:  // from CPbkAddressSelect
        IMPORT_C const TDesC& QueryTitleL();
        IMPORT_C TInt QuerySoftkeysResource() const;

    private: // Data
        /// Own: Title for phonenumber selection list
        HBufC* iQueryTitle;
    }; 


// INLINE FUNCTIONS
inline TBool CPbkSmsAddressSelect::ExecuteLD(TParams& aParams)
    {
    return CPbkAddressSelect::ExecuteLD(aParams);
    }

#endif // __CPbkSmsAddressSelect_H__
            
// End of File
