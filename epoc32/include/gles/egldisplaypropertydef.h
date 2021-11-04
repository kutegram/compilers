// EGLDisplayPropertyDef.h
//
// Copyright (c) Symbian Software Ltd 2005. All rights reserved.
//
//

#ifndef __GLES_EGLDISPLAYPROPERTYDEF_H__
#define __GLES_EGLDISPLAYPROPERTYDEF_H__

#include <egl.h>		// For EGL types
	
// Name string of function in GetProcAddress lookup
#define Symbian_EGL_Set_Display_Property_Name "EGL_SET_DISPLAY_PROPERTY_SYMBIAN"

// Function declaration of that returned by GetProcAddress for function named above
typedef void* Symbian_EGLDisplayPropertyType;
typedef EGLBoolean (*Symbian_EGLSetDisplayProperty)(EGLDisplay aDisplay, EGLSurface aSurface, Symbian_EGLDisplayPropertyType aDisplayProperty);

// __GLES_EGLDISPLAYPROPERTYDEF_H__
#endif
