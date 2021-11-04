/*
* ==============================================================================
*  Name        : MGFetch.h
*  Part of     : MediaGallery / MGFetch.lib
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Media fetch API
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

#ifndef MGFETCH_H
#define MGFETCH_H

// INCLUDES
#include <e32base.h>
#include <MediaFileTypes.hrh>
#include <badesca.h>

// FORWARD DECLARATIONS
class MMGFetchVerifier;
class MMGFetchCanceler;

// CLASS DECLARATION

/**
*  MGFetch can be used to to fetch media files from third party applications
*
*  @lib MGFetch.lib
*  @since 2.0
*/
class MGFetch
    {
    public: // New functions

        /**
        * Launch media file fetcher for single media type
        *
        * @since 2.0
        * @param aSelectedFiles Array to hold selected files
        * @param aMediaType Defines what media files to fetch
        * @param aMultiSelect Single or multiple file selection
        * @param aVerifier Optional verifier for file selection
        * @return ETrue if user selected file(s), EFalse if cancelled
        */
        IMPORT_C static TBool RunL( CDesCArray& aSelectedFiles,
                                    TMediaFileType aMediaType,
                                    TBool aMultiSelect,
                                    MMGFetchVerifier* aVerifier = NULL );

        /**
        * Launch media file fetcher for single media type
        *
        * @since 2.6
        * @param aSelectedFiles Array to hold selected files
        * @param aMediaType Defines what media files to fetch
        * @param aMultiSelect Single or multiple file selection
        * @param aSelectionSoftkey Optional text for left softkey
        *        (KNullDesC for default text)
        * @param aHeading Optional text for popup heading
        *        (KNullDesC for default text)
        * @param aVerifier Optional verifier for file selection
        * @return ETrue if user selected file(s), EFalse if cancelled
        */
        IMPORT_C static TBool RunL( CDesCArray& aSelectedFiles,
                                    TMediaFileType aMediaType,
                                    TBool aMultiSelect,
                                    const TDesC& aSelectionSoftkey,
                                    const TDesC& aHeading,
                                    MMGFetchVerifier* aVerifier = NULL );

        /**
        * Launch media file fetcher for single media type
        *
        * @since 2.6
        * @param aSelectedFiles Array to hold selected files
        * @param aMediaType Defines what media files to fetch
        * @param aMultiSelect Single or multiple file selection
        * @param aSelectionSoftkey Optional text for left softkey
        *        (KNullDesC for default text)
        * @param aHeading Optional text for popup heading
        *        (KNullDesC for default text)
        * @param aMimeTypes Optional array containing MIME types of files
        *                   which are displayed in the fetcher
        * @param aVerifier Optional verifier for file selection
        * @return ETrue if user selected file(s), EFalse if cancelled
        */
        IMPORT_C static TBool RunL( CDesCArray& aSelectedFiles,
                                    TMediaFileType aMediaType,
                                    TBool aMultiSelect,
                                    const TDesC& aSelectionSoftkey,
                                    const TDesC& aHeading,
                                    MDesCArray* aMimeTypes,
                                    MMGFetchVerifier* aVerifier = NULL );

        /**
        * Launch media file fetcher for single media type
        *
        * @since 2.6
        * @param aSelectedFiles Array to hold selected files
        * @param aMediaType Defines what media files to fetch
        * @param aMultiSelect Single or multiple file selection
        * @param aSelectionSoftkey Optional text for left softkey
        *        (KNullDesC for default text)
        * @param aHeading Optional text for popup heading
        *        (KNullDesC for default text)
        * @param aMimeTypes Optional array containing MIME types of files
        *                   which are displayed in the fetcher
        * @param aCanceler Reference to canceler interface pointer
        * @param aVerifier Optional verifier for file selection
        * @return ETrue if user selected file(s), EFalse if cancelled
        */
        IMPORT_C static TBool RunL( CDesCArray& aSelectedFiles,
                                    TMediaFileType aMediaType,
                                    TBool aMultiSelect,
                                    const TDesC& aSelectionSoftkey,
                                    const TDesC& aHeading,
                                    MDesCArray* aMimeTypes,
                                    MMGFetchCanceler*& aCanceler,
                                    MMGFetchVerifier* aVerifier = NULL
                                    );

    };
#endif // MGFETCH_H

// End of File
