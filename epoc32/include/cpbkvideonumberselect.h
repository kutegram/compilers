/*
* ============================================================================
*  Name     : CPbkVideoNumberSelect from CPbkVideoNumberSelect.h
*  Part of  : PbkView.dll
*
*  Description:
*       Phonebook video call number selection dialog. This dialog implements the 
*       video call number selection logic of Phonebook.
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

#ifndef __CPbkVideoNumberSelect_H__
#define __CPbkVideoNumberSelect_H__

//  INCLUDES
#include  "CPbkPhoneNumberSelectBase.h"

// CLASS DECLARATION

/**
 * Phonebook video call number selection dialog. This dialog implements the
 * video call number selection logic of Phonebook.
 */
class CPbkVideoNumberSelect : public CPbkPhoneNumberSelectBase
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkVideoNumberSelect();

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
                 * @param aContactItem  Contact from which to select a video call
                 * number.
                 */
                IMPORT_C TParams(const CPbkContactItem& aContact);

            private: // data
				/// Own: spare data
                TInt32 iSpare1;
            };

        /**
         * Runs the video call number selection query (if necessary).
         *
         * @param aParams   Parameters and return values of the query.
         * @return  ETrue if query was accepted, EFalse if canceled.
         * @see TParams
         */
        IMPORT_C TBool ExecuteLD(TParams& aParams);

        /**
         * Destructor.
         */
        IMPORT_C ~CPbkVideoNumberSelect();

    private:  // from CPbkAddressSelect
        IMPORT_C const TDesC& QueryTitleL();
        IMPORT_C TInt QuerySoftkeysResource() const;
        IMPORT_C TKeyResponse PbkControlKeyEventL
            (const TKeyEvent& aKeyEvent,TEventCode aType);
    
    private: // data members
        /// Own: Title for videonumber selection list
        HBufC* iQueryTitle;
        // Spare data
        TInt32 iSpare1;
    }; 

#endif // __CPbkVideoNumberSelect_H__
            
// End of File
