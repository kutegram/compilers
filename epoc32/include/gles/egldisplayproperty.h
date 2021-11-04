// EGLDisplayProperty.h
//
// Copyright (c) Symbian Software Ltd 2005. All rights reserved.
//
// Class to encapsulate the visual presentation & geometrical properties required for a display through OpenGLES
//

#ifndef __GLES_EGLDISPLAYPROPERTY_H__
#define __GLES_EGLDISPLAYPROPERTY_H__


#include <e32base.h> 	// For CBase
#include <e32def.h>

/**
Class to encapsulate the properties required for displaying an OpenGL ES rendered scene within
a window (or equivalent surface).

@publishedPartner

*/
class CEGLDisplayProperty : public CBase
	{
public: 
	virtual ~CEGLDisplayProperty();
	
	IMPORT_C static CEGLDisplayProperty* NewL(const TRect& aDisplayRect, const TRegion& aDisplayClipRegion, TBool aVisible = ETrue);
	IMPORT_C static CEGLDisplayProperty* NewL();

	IMPORT_C void CopyL(const CEGLDisplayProperty& aEGLDisplayProperty);

	IMPORT_C void SetDisplayRect(const TRect& aDisplayRect);
	IMPORT_C const TRect& DisplayRect() const;

	IMPORT_C void SetDisplayClipRegionL(const TRegion& aDisplayClipRegion);
	IMPORT_C const TRegion&	DisplayClipRegion() const;

	IMPORT_C void SetDisplayVisible(TBool aVisible);
	IMPORT_C TBool DisplayVisible();
	
private:
	CEGLDisplayProperty();
	void ConstructL(const TRect& aDisplayRect, const TRegion& aDisplayClipRegion, TBool aVisible);
	
private: 
	TRect	 iDisplayRect;		
	RRegion  iDisplayClipRegion;
	TBool    iDisplayVisible;
	};
	
// __GLES_EGLDISPLAYPROPERTY_H__
#endif
