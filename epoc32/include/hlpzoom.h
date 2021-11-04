// HLPZOOM.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __HLPZOOM_H__
#define __HLPZOOM_H__

// System includes
#include <e32std.h>

// Classes referenced
class MGraphicsDeviceMap;


///////////////////////////////////////////////////////////////////////////////////////
// ----> MHlpZoomStateManager (header)
///////////////////////////////////////////////////////////////////////////////////////
class MHlpZoomStateManager
/**
@internalComponent

*/
	{
public: // Zoom state
	enum THlpZoomState
		{
		EHlpZoomStateSmall = -1,
		EHlpZoomStateNormal = 0,
		EHlpZoomStateLarge = 1
		};

public: // From MHlpZoomStateManager
	virtual void SetZoomState(THlpZoomState aState) = 0;
	virtual THlpZoomState ZoomState() const = 0;

public: // From MHlpZoomStateManager
	virtual MGraphicsDeviceMap& ZoomDeviceMap() const = 0;
	virtual TInt ZoomFactorValueForZoomState(THlpZoomState aState) const = 0;
	};



///////////////////////////////////////////////////////////////////////////////////////
// ----> MHlpZoomStateObserver (header)
///////////////////////////////////////////////////////////////////////////////////////
class MHlpZoomStateObserver
/**
@internalComponent

*/
	{
public: // From MHlpZoomStateObserver
	virtual void HandleZoomStateChangedL(MHlpZoomStateManager::THlpZoomState aZoomState) = 0;
	};



///////////////////////////////////////////////////////////////////////////////////////
// ----> MHlpZoomStateChangeNotifier (header)
///////////////////////////////////////////////////////////////////////////////////////
class MHlpZoomStateChangeNotifier : public MHlpZoomStateManager
/**
@internalComponent

*/
	{
public: // From MHlpZoomStateChangeNotifier
	virtual void RegisterForZoomStateChangeNotificationsL(MHlpZoomStateObserver& aObserver) = 0;
	virtual void RegisterForZoomStateChangeNotificationsCancel(MHlpZoomStateObserver& aObserver) = 0;
	};

#endif
