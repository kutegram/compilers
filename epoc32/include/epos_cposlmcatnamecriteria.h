/*
* ==============================================================================
*  Name        : EPos_CPosLmCatNameCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK/S60, Landmarks Search API
*  Description : CPosLmCatNameCriteria class
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

#ifndef CPOSLMCATNAMECRITERIA_H
#define CPOSLMCATNAMECRITERIA_H

#include <e32base.h>
#include "EPos_CPosLmSearchCriteria.h"

/**
*  Criterion for searching landmark categories with a certain name.
*
*  Wild-card characters are supported.
*
*  The client specifies the search pattern and starts the search using
*  @ref CPosLandmarkSearch. The search returns all categories which
*  match the search pattern.
*
*  This criterion is only valid when searching for landmark categories, i.e. if
*  it is passed to @p CPosLandmarkSearch::StartLandmarkSearchL, the function
*  will fail with error code @p KErrArgument.
*
*  @lib eposlmsearchlib.lib
*  @since S60 3.0
*/
class CPosLmCatNameCriteria : public CPosLmSearchCriteria
    {
    public:

        /**
        * Two-phased constructor.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmCatNameCriteria* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPosLmCatNameCriteria();

    public:

        /**
        * Retrieves the search pattern.
        *
        * @return The category name search pattern.
        */
        IMPORT_C TPtrC SearchPattern() const;

        /**
        * Sets the search pattern.
        *
        * A non-empty search pattern must be set, otherwise
        * @ref CPosLandmarkSearch::StartCategorySearchL will leave with error
        * code @p KErrArgument.
        *
        * The search is case insensitive.
        *
        * Wild-card characters "?" and "*" are supported in the search string.
        * "?" matches a single occurrence of any character and "*" matches
        * zero or more consecutive occurrences of any characters.
        *
        * @param[in] aSearchPattern The pattern used to find categories.
        *
        * @leave KErrArgument The search pattern is longer than 
        *   @p KPosLmMaxCategoryNameLength.
        */
        IMPORT_C void SetSearchPatternL( const TDesC& aSearchPattern );

    private:

        CPosLmCatNameCriteria();

        void ConstructL();

        // Prohibit copy constructor
        CPosLmCatNameCriteria( const CPosLmCatNameCriteria& );
        // Prohibit assigment operator
        CPosLmCatNameCriteria& operator= ( const CPosLmCatNameCriteria& );

    private:

        HBufC* iSearchPattern;

    };

#endif      // CPOSLMCATNAMECRITERIA_H


