/*
* ==============================================================================
*  Name        : EPos_CPosLmPartialReadParameters.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK/S60, Landmarks API
*  Description : CPosLmPartialReadParameters class
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

#ifndef CPOSLMPARTIALREADPARAMETERS_H
#define CPOSLMPARTIALREADPARAMETERS_H

#include <e32base.h>
#include <LbsFields.h>
#include "EPos_CPosLandmark.h"

/**
*  Container class for partial landmark settings.
*  Partial settings are used to define which landmark data should be returned
*  when @ref CPosLandmarkDatabase::ReadPartialLandmarkLC is called.
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*/
class CPosLmPartialReadParameters : public CBase
    {
    public:

        /**
        * Two-phased constructor.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmPartialReadParameters* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPosLmPartialReadParameters();

    public:

        /**
        * Returns a bitmap of the landmark attributes which should be included
        * in a partial landmark.
        *
        * The bitmap is a combination of the values in
        * CPosLandmark::TAttribute.
        *
        * @return The partial landmark attributes bitmap.
        */
        IMPORT_C CPosLandmark::TAttributes RequestedAttributes() const;

        /**
        * Sets a bitmap of the landmark attributes which should be included in
        * a partial landmark.
        *
        * The bitmap is constructed from the values in
        * CPosLandmark::TAttribute.
        *
        * @param[in] aAttributes A partial landmark attributes bitmap.
        */
        IMPORT_C void SetRequestedAttributes(
            CPosLandmark::TAttributes aAttributes
        );

        /**
        * Returns the position fields which should be included in a partial
        * landmark.
        *
        * @param[out] aRequestedFields Will contain the requested position fields,
        *   i.e. @p TPositionFieldId.
        * @returns @p KErrNone if successful, otherwise one of the system wide
        *   error codes.
        */
        IMPORT_C TInt GetRequestedPositionFields(
            RArray<TUint>& aRequestedFields
        ) const;

        /**
        * Sets the position fields which should be included in a partial
        * landmark.
        *
        * @param[in] aRequestedFields The requested position fields, i.e.
        *   @p TPositionFieldId.
        * @returns @p KErrNone if successful, otherwise one of the system wide
        *   error codes.
        */
        IMPORT_C TInt SetRequestedPositionFields(
            const RArray<TUint>& aRequestedFields
        );

    private:

        // C++ constructor.
        CPosLmPartialReadParameters();

        // Symbian constructor
        void ConstructL();

        // Prohibit copy constructor
        CPosLmPartialReadParameters(
            const CPosLmPartialReadParameters& );
        // Prohibit assigment operator
        CPosLmPartialReadParameters& operator= (
            const CPosLmPartialReadParameters& );

    private:

        // Requested position fields
        RArray<TUint> iRequestedFields;

        // Requested attributes
        TUint32 iAttributes;
    };

#endif      // CPOSLMPARTIALREADPARAMETERS_H


