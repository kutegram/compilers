/*
* ==============================================================================
*  Name        : ?FileName.h
*  Part of     : ?Subsystem_name / ?Module_name
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

#ifndef DRMLICENSECHECKER_H
#define DRMLICENSECHECKER_H

/**
*  Check and decrypt protected data files encrypted by the license manager.
*
*  @lib DRMLicenseChecker.lib
*  @since Series 60 2.5
*/
class CDRMLicenseChecker: public CBase
    {
    public:  // Local enumerations and types

        enum
            {
            ENoRights = -100000,
            ERightsExpired = -100001,
            };

    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CDRMLicenseChecker* NewL();
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CDRMLicenseChecker();

    public: // New functions
        
        /**
        * This function performs a license check by decrypting a data file and
        * returning the decrypted contents of the data file. A license check
        * can only succeed if a rights object associated with the calling
        * application exists and sufficient rights are present. If the license
        * check fails, an error is returned.
        *
        * @since Series 60 2.6
        * @param aDataFile: the data file to be decrypted
        * @param aDataBuffer: memory buffer which will contain the decrypted
        *        contents of the data file.
        * @return ENoRights, ERightsExpired if the data file could not be opened
        *         because of insufficient rights, Symbian-wide error codes or
        *         KErrNone in case of success.
        */
        IMPORT_C TInt CheckLicense(
            const TDesC& aDataFile,
            HBufC8*& aDataBuffer);

    private:

        /**
        * C++ default constructor.
        */
        CDRMLicenseChecker();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();
        
        /**
        * Leaving version of CheckLicense
        *
        * @since Series 60 3.0
        * @param aDataFile: the data file to be decrypted
        * @param aDataBuffer: memory buffer which will contain the decrypted
        *        contents of the data file.
        * @return ENoRights, ERightsExpired if the data file could not be opened
        *         because of insufficient rights, Symbian-wide error codes or
        *         KErrNone in case of success.
        */
        void CheckLicenseL(
            const TDesC& aDataFile,
            HBufC8*& aDataBuffer);

    };

#endif      // DRMLICENSECHECKER_H   
            
// End of File
