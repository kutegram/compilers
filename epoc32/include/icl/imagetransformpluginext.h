// ImageTransformPluginExt.h
//
// Copyright (c) Symbian Software Ltd 2004-2005.  All rights reserved.
//
// This is the extension to the plugin API for the Image Transform framework
//
#ifndef __IMAGETRANSFORMPLUGINEXT_H__
#define __IMAGETRANSFORMPLUGINEXT_H__

#include <e32base.h>

/**
This class should be derived by a plugin writer wishing to extend the client 
API defined in CImageTransform

@publishedAll

*/
class CImageTransformPluginExtension : public CBase
	{
public:
	
	/**
	Get a Uid by which a plugin extension can be identified.

	@return A Uid unique to the specific plugin extension
	*/
	IMPORT_C virtual const TUid Uid() const = 0;
private:
	// Future proofing
	IMPORT_C virtual void ReservedVirtual1();
	IMPORT_C virtual void ReservedVirtual2();
	IMPORT_C virtual void ReservedVirtual3();
	IMPORT_C virtual void ReservedVirtual4();
	};

// __IMAGETRANSFORMPLUGINEXT_H__
#endif
