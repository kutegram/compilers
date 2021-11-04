/*
* ==============================================================================
*  Name        : CEcomBrowserPluginInterface.h
*  Part of     : Webkit \ Plugin
*  Interface   : 
*  Description :
*  Version     : 3.1
*
*    Copyright (c) 2006, Nokia Corporation
*    All rights reserved.
*  
*  	Redistribution and use in source and binary forms, with or without
*  	modification, are permitted provided that the following conditions
*  	are met:
*  
*      * Redistributions of source code must retain the above copyright
*        notice, this list of conditions and the following disclaimer.
*      * Redistributions in binary form must reproduce the above copyright
*        notice, this list of conditions and the following disclaimer in
*        the documentation and/or other materials provided with the
*        distribution.
*      * Neither the name of the Nokia Corporation nor the names of its
*        contributors may be used to endorse or promote products derived
*        from this software without specific prior written permission.
*  
*  	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
*  	USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
*  	DAMAGE.
*  
*    Please see file patentlicense.txt for further grants.
* ==============================================================================
*/

#ifndef CECOMBROWSERPLUGININTERFACE_H
#define CECOMBROWSERPLUGININTERFACE_H

// System includes
#include <e32base.h>
#include <ecom/ecom.h>

// User includes
#include "npupp.h"
#include "BrowserPluginInterface.h"

typedef struct
    {
    NPNetscapeFuncs* iNetscapeFuncs;
    NPPluginFuncs* iPluginFuncs;
    }TFuncs;

//
// The ECOM interface definition for a Netscape plugin interface class.
//
class CEcomBrowserPluginInterface: public CBase
	{
	public: 

        inline static CEcomBrowserPluginInterface* CreatePluginL(
                                        TUid aImplementationUid,
                                        NPNetscapeFuncs* aNetscapeFuncs,
                                        NPPluginFuncs* aPluginFuncs);
		
		inline virtual ~CEcomBrowserPluginInterface();
		
  public:

	private:
  //	The ECom destructor key identifier
	TUid iEcomDtorID;

	// A refedrence count
	TInt iCount;

	};

//
//
inline CEcomBrowserPluginInterface* CEcomBrowserPluginInterface::CreatePluginL(
        TUid aImplementationUid,
        NPNetscapeFuncs* aNetscapeFuncs,
        NPPluginFuncs* aPluginFuncs)
	{

	TFuncs initParams;
	initParams.iNetscapeFuncs = aNetscapeFuncs;
	initParams.iPluginFuncs = aPluginFuncs;

	TAny* ptr = REComSession::CreateImplementationL(aImplementationUid, 
									_FOFF(CEcomBrowserPluginInterface, iEcomDtorID),
                                    &initParams);

	return REINTERPRET_CAST(CEcomBrowserPluginInterface*, ptr);
	}

inline CEcomBrowserPluginInterface::~CEcomBrowserPluginInterface()
	{
	REComSession::DestroyedImplementation(iEcomDtorID);
	} 	


#endif // CECOMBROWSERPLUGININTERFACE_H




