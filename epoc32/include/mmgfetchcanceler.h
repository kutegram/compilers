/*
* ==============================================================================
*  Name        : MMGFetchCanceler.h
*  Part of     : MediaGallery / MGFetch.lib
*  Interface   : ?Interface_category, ?Interface_name
*  Description : ?Description
*  Version     : ?Version
*
*  Copyright (c) 2002 Nokia Corporation.
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

#ifndef MMGFETCHCANCELER_H
#define MMGFETCHCANCELER_H

// CLASS DECLARATION

/**
*  Interface for canceling the fetch popup
*
*  @since 2.6
*/
class MMGFetchCanceler
    {
    public:  // New functions
        /**
        * Calling this method while the fetcher (MGFetch.h) popup is visible
        * (when the MMGFetchCanceler pointer is NOT NULL) causes the fetcher
        * to close.
        *
        * @since 2.6
        */
        virtual void CancelFetcherL() = 0;
    };

#endif // MMGFETCHCANCELER_H

// End of File
