/*
* ==============================================================================
*  Name        : EPos_CPosLmSearchCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK/S60, Landmarks Search API
*  Description : CPosLmSearchCriteria class
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

#ifndef CPOSLMSEARCHCRITERIA_H
#define CPOSLMSEARCHCRITERIA_H

#include <e32base.h>

/**
*  Abstract base class for landmark search criterion classes.
*
*  Criterion classes are used in @ref CPosLandmarkSearch to specify what to
*  search for. It specifies what criteria the landmark must fulfill to be
*  considered a search match.
*
*  @lib eposlmsearchlib.lib
*  @since S60 3.0
*/
class CPosLmSearchCriteria : public CBase
    {
    public:

        /**
        *  Specifies the subclass of the criterion object.
        */
        enum TCriteriaType
            {
            ECriteriaArea = 0     /**< subclass CPosLmAreaCriteria */,
            ECriteriaText         /**< subclass CPosLmTextCriteria */,
            ECriteriaComposite    /**< subclass CPosLmCompositeCriteria */,
            ECriteriaCategory     /**< subclass CPosLmCategoryCriteria */,
            ECriteriaFindNearest  /**< subclass CPosLmNearestCriteria */,
            ECriteriaIdList       /**< subclass CPosLmIdListCriteria */,

            ECriteriaCategoryByName = 100 /**< subclass CPosLmCatNameCriteria */
            };

    public:

        /**
        * Destructor.
        */
        virtual ~CPosLmSearchCriteria();

    public:

        /**
        * Returns the criterion type.
        *
        * @returns The criterion type.
        */
        IMPORT_C TCriteriaType CriteriaType() const;

    protected:

        // C++ constructor.
        CPosLmSearchCriteria( TCriteriaType aCriteriaType );

    private:

        // Prohibit copy constructor
        CPosLmSearchCriteria( const CPosLmSearchCriteria& );
        // Prohibit assigment operator
        CPosLmSearchCriteria& operator= ( const CPosLmSearchCriteria& );

    private:

        TCriteriaType iCriteriaType;

    };

#endif      // CPOSLMSEARCHCRITERIA_H


