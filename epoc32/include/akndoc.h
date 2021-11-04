/*
* ============================================================================
*  Name     : AknDoc.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
#ifndef __AKNDOC_H__
#define __AKNDOC_H__

// INCLUDES

#include <eikdoc.h>

// CLASS DECLARATION

/**
*  Base class for a Series 60 application document.
*
*  @since Series 60 0.9
*/
class CAknDocument : public CEikDocument
	{
public:	// from CEikDocument
	
	/**
    * From @c CEikDocument. Opens a file.
    * @param aDoOpen Open an existing file if @c ETrue, 
    * otherwise create a new file. Not used.
    * @param aFilename The file to open or create. Not used.
    * @param aFs File server session to use. Not used.
    * @return Pointer to file store object.
    */
	IMPORT_C CFileStore* OpenFileL(TBool aDoOpen,
	                               const TDesC& aFilename,
	                               RFs& aFs);
	IMPORT_C void OpenFileL(CFileStore*& aFileStore, RFile& aFile);
protected:
	
	/**
    * C++ default constructor.
    * @param aApp The application instance with which the new document is
    * associated.
    */
	IMPORT_C CAknDocument(CEikApplication& aApp);
	};

#endif

