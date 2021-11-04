// MHTTPFilterCreationCallback.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file MHTTPFilterCreationCallback.h
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __MHTTPFILTERCREATIONCALLBACK_H__
#define __MHTTPFILTERCREATIONCALLBACK_H__

// Forward declarations
class TFilterConfigurationIterator;


//##ModelId=3C4C0F450132
class MHTTPFilterCreationCallback
/**
This class serves as a pure virtual interface required as a session callback to the client
when the client requires to configure the filters that are installed. The session calls the
method in the interface when the construction of the session is complete. The callback passes
an object of CFilterConfigurationIterator that allows the client to configure the filters that
are installed.
@publishedAll

*/
	{
public: // Methods
	/**
	@fn				ConfigureSessionFiltersL(TFilterConfigurationIterator* aFilterConfigIter) = 0
	Intended Usage:	Pure virtual that is called by the session when the session construction
					is complete. This passes a CFilterConfigurationIterator back to the client
					which allows the client to install or install selected filters.
	@param			aFilterConfigIter Pointer to the filter configuration iterator. Ownership of
					CFilterConfigurationIterator remains with the session and is not transfered
	@pre 			The session has been constructed
	@post			The filters that are installed are have been configured by the client
	*/
	//##ModelId=3C4C0F450150
	virtual void ConfigureSessionFiltersL(TFilterConfigurationIterator* aFilterConfigIter) = 0;
	};

// __MHTTPFILTERCREATIONCALLBACK_H__
#endif
