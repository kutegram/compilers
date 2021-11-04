/*
* ==============================================================================
*  Name        : EPos_CPosLmCompositeCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK/S60, Landmarks Search API
*  Description : CPosLmCompositeCriteria class
*  Version     : %version: 2 % 
*
*  Copyright © 2005-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.0
*/

#ifndef CPOSLMCOMPOSITECRITERIA_H
#define CPOSLMCOMPOSITECRITERIA_H

#include <e32base.h>
#include "EPos_CPosLmSearchCriteria.h"

/**
*  Class used to combine multiple search criterion.
*
*  For instance, to search for all restaurants in the area, this class can be
*  used to combine a @ref CPosLmAreaCriteria and a @ref CPosLmCategoryCriteria.
*
*  If a @ref CPosLmNearestCriteria is used and no sort preference is specified,
*  the result will be sorted by distance. If more than one
*  @ref CPosLmNearestCriteria are combined using a @ref CPosLmCompositeCriteria,
*  the sort order will be undefined unless a sort preference is specified.
*
*  Nested @ref CPosLmCompositeCriteria are not allowed.
*
*  This criterion only supports searching for landmarks, e.g. if it is passed
*  to @p CPosLandmarkSearch::StartCategorySearchL, the function will fail with
*  error code @p KErrNotSupported.
*
*  @lib eposlmsearchlib.lib
*  @since S60 3.0
*/
class CPosLmCompositeCriteria : public CPosLmSearchCriteria
    {
    public:

        /**
        *  Specifies the type of the composite criterion.
        */
        enum TCompositionType
            {
            ECompositionAND = 0     /**< Search results must match all
                                    * contained criteria. */
            };

    public:

        /**
        * Two-phased constructor.
        *
        * @param[in] aType The composition type to use. Currently only
        *   @p ECompositionAND is supported.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmCompositeCriteria* NewLC(
            TCompositionType  aType
        );

        /**
        * Destructor.
        */
        virtual ~CPosLmCompositeCriteria();

    public:

        /**
        * Returns the type of this composite criterion.
        *
        * @return The composition type. Currently it is always @p ECompositionAND.
        */
        IMPORT_C TCompositionType CompositionType() const;

        /**
        * Set the type of this composite criterion.
        *
        * @param[in] The composition type to use. Currently only
        *   @p ECompositionAND is supported.
        */
        IMPORT_C void SetCompositionType( TCompositionType  aType );

        /**
        * Returns the number of criteria this object contains.
        *
        * @return The number of criteria this object contains.
        */
        IMPORT_C TUint NumOfArguments() const;

        /**
        * Returns a criterion argument contained in this object.
        *
        * This overload returns a const reference to the criterion argument.
        * There is another overload which returns a non-const reference.
        *
        * @param aIndex The argument to read. Must be in the interval
        *   [0, @ref NumOfArguments - 1], or this function will raise a
        *   USER-130 panic.
        * @return The requested argument.
        */
        IMPORT_C const CPosLmSearchCriteria& Argument( TUint aIndex ) const;

        /**
        * Returns a criterion argument contained in this object.
        *
        * This overload returns a non-const reference to the criterion
        * argument. There is another overload which returns a const reference.
        *
        * @param aIndex The argument to read. Must be in the interval
        *   [0, @ref NumOfArguments - 1], or this function will raise a
        *   USER-130 panic.
        * @return The requested argument.
        */
        IMPORT_C CPosLmSearchCriteria& Argument( TUint aIndex );

        /**
        * Adds a criterion to this composition.
        *
        * The composite criterion must contain at least one argument, otherwise
        * @ref CPosLandmarkSearch::StartLandmarkSearchL will fail with error
        * code @p KErrArgument.
        *
        * If this function returns without an error code, ownership of the
        * added criterion object is transferred to the composite object.
        *
        * Nested @ref CPosLmCompositeCriteria are not supported.
        *
        * Searching for landmark categories using @ref CPosLmCompositeCriteria 
        * is not supported.
        *
        * @param[in] aCriteria The criterion to add to the composition.
        * @returns - @p KErrNone if successful
        *          - KErrNotSupported if @ref CPosLmCompositeCriteria or 
        *            @ref CPosLmCatNameCriteria is specified.
        *          - otherwise a system wide error code.
        */
        IMPORT_C TInt AddArgument( CPosLmSearchCriteria* aCriteria );

        /**
        * Removes a criterion from this composition.
        *
        * Note: This function does not delete the criterion object. Instead,
        * the ownership of the object is passed to the caller.
        *
        * @param aIndex The argument to remove. Must be in the interval
        *   [0, @ref NumOfArguments - 1], or this function will raise a
        *   USER-130 panic.
        *
        * @returns The criterion object which was removed from the composition.
        */
        IMPORT_C CPosLmSearchCriteria* RemoveArgument( TUint  aIndex );

        /**
        * Removes and deletes all contained criterion objects.
        *
        * The composite criterion must contain at least one argument, otherwise
        * @ref CPosLandmarkSearch::StartLandmarkSearchL will fail with error
        * code @p KErrArgument.
        */
        IMPORT_C void ClearArguments();

    private:

        CPosLmCompositeCriteria( TCompositionType aType );

        void ConstructL();

        // Prohibit copy constructor
        CPosLmCompositeCriteria( const CPosLmCompositeCriteria& );
        // Prohibit assigment operator
        CPosLmCompositeCriteria& operator= ( const CPosLmCompositeCriteria& );

    private:

        TCompositionType                    iCompositionType;
        RPointerArray<CPosLmSearchCriteria> iArguments;

    };

#endif      // CPOSLMCOMPOSITECRITERIA_H


