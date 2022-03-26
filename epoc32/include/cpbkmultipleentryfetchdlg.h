/*
* ============================================================================
*  Name     : CPbkMultipleEntryFetchDlg from CPbkMultipleEntryFetchDlg.h
*  Part of  : PbkView.dll
*
*  Description:
*      Phonebook Multiple Entry Fetch API.
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

#ifndef __CPbkMultipleEntryFetchDlg_H__
#define __CPbkMultipleEntryFetchDlg_H__

//  INCLUDES
#include <e32base.h>    // CBase

//  FORWARD DECLARATIONS
class CPbkContactEngine;
class CContactViewBase;
class CContactIdArray;
class CPbkFetchDlg;
class MObjectProvider;
class MPbkFetchDlgSelection;


// CLASS DECLARATION

/**
 * Phonebook Multiple Entry Fetch API. This class is used to construct 
 * a Phonebook UI dialog where the user is able to select multiple
 * contact entries from a list. The selection is then returned to the 
 * client.
 */
class CPbkMultipleEntryFetchDlg : public CBase
    {
    public:  // Types
        /**
         * Multiple entry fetch parameter class. 
         */
        class TParams
            {
            public:  // Input parameters
                /**
                 * Contact view to display. If NULL loads the default
                 * contact view containing all names in the contact
                 * database.
                 */
                CContactViewBase* iContactView;

            public:  // Output parameters
                /**
                 * Returns an array of ids of the selected entries,
                 * undefined if the dialog is canceled.
                 * Caller must delete iMarkedEntries when no longer needed.
                 */
                CContactIdArray* iMarkedEntries;

            public: // Additional input parameters
                /**
                 * OPTIONAL: Fetch softkey resource ID. 
                 * If 0, default softkeys are used.
                 */
                TInt iCbaId;
                
                /**
                 * OPTIONAL: Fetch selection accepter. 
                 * If NULL, not applicable.                 
                 */
                MPbkFetchDlgSelection* iFetchSelection;

            public:  // Interface
                /**
                 * C++ constructor.
                 */
                IMPORT_C TParams();

                // Compiler-generated destructor is ok for this class

                /**
                 * Returns a cleanup item which will handle cleanup of this
                 * object in case of a leave.
                 */
                IMPORT_C operator TCleanupItem();

            private:  // Implementation
                static void Cleanup(TAny* aPtr);

            private:  // Unimplemented functions
                /// Unimplemented copy constructor
                TParams(const TParams&);
                /// Unimplemented assignment operator
                TParams& operator=(const TParams&);
            };

    public:  // Interface
        /**
         * Creates a new multiple entry fetch dialog.
         *
         * @param aParams   Fetch parameters, see TParams.
         * @param aEngine   Phonebook engine.
         * @return A new instance of this class.
         */
        IMPORT_C static CPbkMultipleEntryFetchDlg* NewL
            (TParams& aParams, CPbkContactEngine& aEngine);

        /**
         * See CCoeControl::SetMopParent(MObjectProvider* aParent)
         */
        IMPORT_C void SetMopParent(MObjectProvider* aParent);

        /**
         * Executes this dialog.
         * NOTE: this object is deleted when ExecuteLD returns or leaves!
         * NOTE: current status pane layout is replaced with the Phonebook
         * one. Restoring the original pane is left to be the responsibility
         * of the caller.
         *
         * @return A non-zero value if accepted, zero if canceled.
         */
        IMPORT_C TInt ExecuteLD();

        /**
         * Destructor. Also cancels this dialog and makes ExecuteLD return.
         */
        ~CPbkMultipleEntryFetchDlg();

    private:  // Implementation
        CPbkMultipleEntryFetchDlg(TParams& aParams, CPbkContactEngine& aEngine);
        void ConstructL();
        static void Panic(TInt aReason);

    private:  // Data
        /// Own: parameters
        TParams& iParams;
        /// Own: fetch dialog
        CPbkFetchDlg* iFetchDlg;
        /// Ref: Phonebook engine
        CPbkContactEngine& iPbkEngine;
        /// Ref: set to ETrue in destructor
        TBool* iDestroyedPtr;
        /// Own: Object Provider
        MObjectProvider* iObjectProvider;
    };

#endif // __CPbkMultipleEntryFetchDlg_H__

// End of File
