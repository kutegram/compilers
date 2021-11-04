/*
* ==============================================================================
*  Name        : AknsWallpaperUtils.h
*  Part of     : Avkon Skins / Skin Library
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Defines an internal concrete class CAknsAppSkinInstance and
*                related types. This class encapsulates the concrete skin 
*                instance which is a singleton in thread scope.
*  Version     : ?Version
*
*  Copyright © 2002-2004 Nokia Corporation.
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

#ifndef AKNSWALLPAPERUTILS_H
#define AKNSWALLPAPERUTILS_H

#include <e32base.h>
#include <badesca.h>

class CCoeEnv;

/*
  Special error codes for SetIdleWallpaper.
*/
enum TAknsWpuError 
   {
   // Returned when the drm protected image has
   // only preview rights
   KAknsWpuErrorPreviewOnly = -8000
   };

/*
* An utility class for manipulating the Idle state wallpaper. This function will show
* all drm related messages and queries, if the content is drm protected.
*
* No copies of the given file, but the file is used directly where it is located.
*
* 
* @since 3.0
*/
class AknsWallpaperUtils
{
    public:
        /*
        * Sets the idle state wallpaper
        *
        * @param aFilename, the filename(incl. full path) of the image to be 
        * set as the idle state wallpaper, or KNullDesC if wallpaper is to
        * be removed. If resource id:s are given, the user must ensure that
        * the correct resource file is loaded to the given aCCoeEnv. The 
        * waitnote is type of CAknWaitNoteWrapper and is automatically launched
        * when correct resource id:s are given. 
        *
        * @param aCoeEnv a valid pointer to Control Environment, or NULL. As this function will potentially
        * show drm related messages, a valid coeenv is needed. If no messages are wanted, NULL can be given
        * as the parameter. Note that even when passing NULL, DRM related stuff will not be skipped, but
        * they are done silenty.
        *
        * @param aWaitNoteResourceTextID the resource id of the waitnote text to show
        * @param aWaitNoteResourceID the resource id of the wait note to show.
        * @return KErrNone on success or one of the system wide error codes.
        */
        IMPORT_C static TInt SetIdleWallpaper(const TDesC& aFilename, CCoeEnv* aCoeEnv, TInt aWaitNoteTextResourceID = 0, TInt aWaitNoteResourceID = 0);

        IMPORT_C static TInt SetSlidesetWallpaper(CDesCArray& aSelectedFiles, CCoeEnv* aCoeEnv, TInt aWaitNoteTextResourceID = 0, TInt aWaitNoteResourceID = 0);

};


#endif // AKNSAPPSKININSTANCE_H
            
// End of File
