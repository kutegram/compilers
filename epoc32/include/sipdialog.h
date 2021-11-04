/*
* ==============================================================================
*  Name        : sipdialog.h
*  Part of     : SIP Client
*  Interface   : SDK API, SIP Client API
*  Description : 
*  Version     : 1.0
*
*  Copyright (c) 2005 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef CSIPDIALOG_H
#define CSIPDIALOG_H

// INCLUDES
#include <e32base.h>
#include <stringpool.h>
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPConnection;
class CSIPConnectionImplementation;
class MSIPRegistrationContext;
class CSIPDialogAssocBase;
class CSIPFromHeader;
class CSIPToHeader;
class CSIPCallIDHeader;
class CUri8;
class CSIPDialogImplementation;

// CLASS DECLARATION

/**
*  @publishedAll
*  
*
*  Class for managing SIP dialogs.
*  It provides services querying dialog state, obtaining the dialog related
*  SIP headers and getting all dialog associations.
*
*  The user of the class cannot instantiate this class.
*  
*/

class CSIPDialog: public CBase
	{
	public:
		/** Dialog states */
		enum TState
			{
			/** Initiliazed state */
			EInit,
			/** Early state */
			EEarly,
			/** Confirmed state */
			EConfirmed,
			/** Terminated state */
			ETerminated
			};

	public: //Constructors and destructor, for internal use
		/**
		* Two-phased constructor. 
		* This constructor should be used if the user has received
		* SIP request that creates a SIP dialog association.
        *
        * @param aConnImplementation Implementation of the used SIP connection
        * @return New object, ownership is transferred.
		*/
		static CSIPDialog*
			NewL(CSIPConnectionImplementation& aConnImplementation);

		/**
		* Two-phased constructor
		* This constructor should be used if the user has received
		* SIP request that creates a SIP dialog association.
        *
		* @param aConnImplementation Implementation of the used SIP connection
        * @return New object, ownership is transferred.
		*/
		static CSIPDialog*
			NewLC(CSIPConnectionImplementation& aConnImplementation);

		/**
		* Two-phased constructor
		* This constructor should be used if the user has received
		* SIP request that creates a SIP dialog association.
        *
        * @param aConnImplementation Implementation of the used SIP connection
		* @param aContext Registration context whose outbound proxy and other
		*        parameters are to be used.
        * @return New object, ownership is transferred.
		*/
		static CSIPDialog*
			NewL(CSIPConnectionImplementation& aConnImplementation,
                 const MSIPRegistrationContext& aContext);

		/**
		* Two-phased constructor
		* This constructor should be used if the user has received
		* SIP request that creates a SIP dialog association.
        *
        * @param aConnImplementation Implementation of the used SIP connection
		* @param aContext Registration context whose outbound proxy and other
		*        parameters are to be used.
        * @return New object, ownership is transferred.
		*/
		static CSIPDialog*
			NewLC(CSIPConnectionImplementation& aConnImplementation,
                  const MSIPRegistrationContext& aContext);

		/**
		* Destructor
		*/
		~CSIPDialog();

	public: //New functions
		/**
		* Gets dialog state		
		* @return dialog state
		*/
        IMPORT_C CSIPDialog::TState State() const;

		/**
		* Gets all dialog associations. 		
		* @return All dialog associations. Ownership of the array or the items
        *   inside it, is not transferred.
		*/
		IMPORT_C const RPointerArray<CSIPDialogAssocBase>&
					   SIPDialogAssociations() const;

        /**
        * Gets used registration context for this dialog
        * @return associated registration or 0-pointer otherwise.
        *   Ownership is not transferred.
        */
        IMPORT_C const MSIPRegistrationContext* RegistrationContext() const;
	
        /**
		* Checks if the dialog association belongs to this dialog
		* @param aDialogAssoc a dialog association
		* @return ETrue if belongs, EFalse otherwise
		*/
		IMPORT_C TBool
            IsAssociated(const CSIPDialogAssocBase& aDialogAssoc) const;

        /**
		* Gets the SIP connection used for this dialog
		* @return SIP connection used for the dialog, or 0-pointer if the
        *   connection has been deleted. Ownership isn't transferred.
		*/
        IMPORT_C CSIPConnection* Connection();

        /**
		* Gets the SIP connection used for this dialog.
		* @return SIP connection used for the dialog, or 0-pointer if the
        *   connection has been deleted. Ownership isn't transferred.
		*/
        IMPORT_C const CSIPConnection* Connection() const;

        /**
		* Gets originator's address
		* @return originator's address (From-header)
		*/
		IMPORT_C const CSIPFromHeader& FromHeader() const;

		/**
		* Gets recipient's address
		* @return recipient's address (To-header)
		*/
		IMPORT_C const CSIPToHeader& ToHeader() const;

		/**
		* Gets remote-uri used during dialog creation
		* @return Remote target uri
		*/
		IMPORT_C const CUri8& RemoteURI() const;

		/**
		* Gets Call-ID of SIP dialog
		* @pre State()==CSIPDialog::EEarly || State()==CSIPDialog::EConfirmed
		* @return Call-ID of SIP dialog
		* @leave KErrSIPInvalidDialogState if dialog doesn't yet have a Call-ID
		*/
		IMPORT_C const CSIPCallIDHeader& CallIdL() const;

        /**
		* Compares this object to another object
		* @param aDialog CSIPDialog object to compare
		* @returns ETrue if the objects are equal, otherwise EFalse
		*/
        IMPORT_C TBool operator==(const CSIPDialog& aDialog) const;

	public: // New functions, for internal use

		/**
		* Returns the CSIPDialogImplementation.
		*
 		* @return CSIPDialogImplementation
		*/
		CSIPDialogImplementation& Implementation();

    private: // Constructors

        CSIPDialog();        

        void ConstructL(CSIPConnectionImplementation& aConnImplementation);
        
        void ConstructL(CSIPConnectionImplementation& aConnImplementation,
                   		const MSIPRegistrationContext& aContext);

private: // Data

		//Implementation instance, CSIPDialog doesn't own it
		CSIPDialogImplementation* iImplementation;

private: // For testing purposes

	    UNIT_TEST(CSIP_Test)
        UNIT_TEST(CSIPInviteDialogAssoc_Test)
        UNIT_TEST(CSIPSubscribeDialogAssoc_Test)
        UNIT_TEST(CSIPReferDialogAssoc_Test)

        __DECLARE_TEST;
	};

#endif
