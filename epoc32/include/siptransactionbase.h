/*
* ==============================================================================
*  Name        : siptransactionbase.h
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

#ifndef CSIPTRANSACTIONBASE_H
#define CSIPTRANSACTIONBASE_H

// INCLUDES
#include <e32base.h>
#include <stringpool.h>
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIPResponseElements;
class MTransactionAssociation;

// CLASS DECLARATION

/**
*  @publishedAll
*  
*
*  Base class for managing SIP transactions.
*  It provides services for querying transaction type and its state.
*
*  This class is an abstract class and cannot be instantiated.
*  
*/
class CSIPTransactionBase: public CBase
	{
	public:
		/** SIP transaction state */
		enum TState
			{
			/** Trying state */
			ETrying,
			/** Calling state */
			ECalling,
			/** Proceeding state */
			EProceeding,
			/** Completed state */
			ECompleted,
			/** Confirmed state */
			EConfirmed,
			/** Terminated state */
			ETerminated,
			/** Object is being constructed and is not yet ready for use */
			EConstructing
			};

	public: // Destructor
        /**
        * Destructor
        * @internalComponent
		*/
		virtual ~CSIPTransactionBase();

	public: // New functions
        /**
        * Gets the SIP transaction type
        * @return SIP transaction type
        */
		IMPORT_C RStringF Type() const;

		/**
		* Gets SIP transaction state
		* @return SIP transaction state
		* @leave KErrSIPResourceNotAvailable if a required SIP Client API
		*	object has been deleted
		*/
		IMPORT_C CSIPTransactionBase::TState StateL();

		/**
		* Checks the if the actual object
		* is of type CSIPClientTransaction.
		* @return ETrue if object is of type CSIPClientTransaction and
		*         EFalse otherwise
		*/
		IMPORT_C TBool IsSIPClientTransaction() const;

		/**
		* Compares this object to another object also having
		* CSIPTransactionBase base class
		* The function has to be implemented in each of the sub-classes.
		* @param aTransaction a CSIPTransactionBase object to compare
		* @return ETrue if the objects are equal otherwise EFalse
		*/
        IMPORT_C TBool
            operator==(const CSIPTransactionBase& aTransaction) const;

	public: // New functions, for internal use
        /**
		* Obtains the RequestId of the transaction.
		*
        * @return RequestId
		*/
        TUint32 RequestId() const;

        /**
		* Clears the MTransactionAssociation. After this the object can't be
        * used anymore and it is expected that user will delete it soon.
        *
        * @param aAssociation Object requesting the detach
        * @internalComponent
		*/
        virtual void Detach(const MTransactionAssociation& aAssociation);

        /**
		* Changes the transaction state.
        *
        * @param aNextState State into which transaction moves
		*/
        void ChangeState(CSIPTransactionBase::TState aNextState);

        /**
        * Determines whether this transaction has an effect on the associated
        * dialog's state.
        *
		* @return ETrue if transaction has an effect on the dialog's state,
        *   EFalse otherwise.
		*/
        TBool AffectsDialogState() const;

        /**
		* Sets this transaction to affect the dialog state.
		*/
        void SetAffectsDialogState();

        /**
		* Determines whether the transaction type is a target refresh request.
        *
        * @param aType Type of transaction
        * @return ETrue If the transaction is a target refresh request, EFalse
        *   otherwise.
		*/
        static TBool IsTargetRefresh(RStringF aType);

        /**
		* Stores response elements. Depending on the status code, transaction
        * may enter another state.
        *
        * @param aElements Response elements, ownership is transferred.
		*/
        void SetResponseElements(CSIPResponseElements* aElements);

    protected: // Constructors
        CSIPTransactionBase(TBool aIsClientTransaction,
                            TUint32 aRequestId,
                            MTransactionAssociation& aAssociation);

        void ConstructL(RStringF aType);

	protected: // New functions, for internal use
        /**
		* Checks that iAssociation is available (not NULL). If iAssociation is
        * NULL, it means user has deleted a resource needed by
        * CSIPTransactionBase, and this function leaves.
		*/
        void CheckAssociationL() const;

        /**
		* Gets response elements.
        *
		* @return Response elements. Ownership isn't transferred.
		*/
        const CSIPResponseElements* ResponseElements() const;

	protected: // Data
        
        /**
         * RequestId received from SIP client 
		 * @internalComponent
		 */       
        TUint32 iRequestId;

        /**
         * Every transaction is associated to exactly one other object:
         * CSIP, CSIPConnection, CSIPRegistrationBinding or CSIPDialogAssocBase
		 * @internalComponent
		 */
        MTransactionAssociation* iAssociation;

    private: // Data
		RStringF iType;

        //ETrue is the transaction is a client transaction, EFalse otherwise
        TBool iIsClientTransaction;

        //Current transaction state
        CSIPTransactionBase::TState iState;

        //ETrue if the transaction has an effect on the dialog state in case
        //the transaction is associated with a dialog.
        //EFalse otherwise.
        TBool iAffectsDialogState;

        //SIP response elements
        CSIPResponseElements* iResponseElements;

	private: // For testing purposes
	    UNIT_TEST(CSIP_Test)
        UNIT_TEST(CSIPServerTransaction_Test)
        UNIT_TEST(CSIPSubscribeDialogAssoc_Test)
        UNIT_TEST(CSIPInviteDialogAssoc_Test)
        UNIT_TEST(CSIPNotifyDialogAssoc_Test)
        UNIT_TEST(CSIPConnection_Test)

        __DECLARE_TEST;
    };

#endif
