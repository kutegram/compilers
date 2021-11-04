/*
* ==============================================================================
*  Name        : versioninfo.h
*  Part of     : Common Services / Platform Environment
*  Interface   : SDK, Version Info API
*  Description : Interface for quering system version information.
*  Version     : %version: 1 %
*
*  Copyright © 2007 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef VERSION_INFO_H
#define VERSION_INFO_H

//  INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class RFs;

// CLASS DECLARATION
/**
* Class holds system version information. Version Info API provides 
* an interface for quering system version information.
*
* Usage:
*  
* Get platform version information:
* @code
* // iFs contains open file server session
*
* VersionInfo::TPlatformVersion platformVersion;
* // Select the overload of VersionInfo::GetVersion() that suits best for 
* // the current client.
* User::LeaveIfError( VersionInfo::GetVersion( platformVersion, iFs ) );
*
* // Now platformVersion contains platform version information.
*
* @endcode
*
* @lib platformver.lib
* @since S60 3.2
*/

NONSHARABLE_CLASS(VersionInfo)
    {

public:
    /**
    * Class TVersionBase is a base class for all version information data.
    * @since S60 3.2
    */
    class TVersionBase
        {
    friend class VersionInfo;

    protected:
        /**
        * Constructor for subclasses
        * @since S60 3.2
        * @param aType Sets type of version info specified by TVersionType
        */
        inline TVersionBase( TInt aType );

    private:
        /**
        * C++ default constructor.
        */
        TVersionBase();

    private:
        /**  Contains type of version info specified by TVersionType */
        TInt iType;
        };

    /**
    * Class TPlatformVersion stores platform version information.
    * The class is used as parameter in GetVersionInfo() methods.
    * @since S60 3.2
    */
    class TPlatformVersion : public TVersionBase
        {
    public:
        /**
         * C++ default constructor.
        */
        inline TPlatformVersion();

    public:
        /**  Contains the major version. For example 3 if S60 3.2 */
        TUint16 iMajorVersion;

        /**  Contains the minor version. For example 2 if S60 3.2 */
        TUint16 iMinorVersion;
        };

    /**
    * This method gets the version information.
    *
    * @since S60 3.2
    * @param aVersion Stores the version information
    * @return System wide error code
    *
    * @see TVersionBase
    */
    IMPORT_C static TInt GetVersion( TVersionBase& aVersion );

    /**
    * This method gets the version information. Given file server 
    * session avoids the overhead of new file server connection. 
    *
    * @since S60 3.2
    * @param aVersion Stores the version information
    * @param aFs An opened file server session
    * @return System wide error code
    *
    * @see TVersionBase
    */
    IMPORT_C static TInt GetVersion( TVersionBase& aVersion, RFs& aFs );

private:
    /**
     * C++ default constructor.
     */
    VersionInfo();

    /** Used internally to detect type of version info */
    enum TVersionType
        {
        EPlatformVersion = 0
        };
    };

#include "versioninfo.inl"

#endif // VERSION_INFO_H

// End of File
