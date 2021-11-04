/*
* ==============================================================================
*  Name        : MCustomCommand.h
*  Part of     :
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Definition of custom command interface
*  Version     : 1
*
*  Copyright (c) 2004 Nokia Corporation.
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

#ifndef __MCUSTOMCOMMAND_H
#define __MCUSTOMCOMMAND_H

#include <e32std.h>
#include <mmf/common/mmfcontrollerframework.h>

class MCustomCommand
	{
public:
	virtual TInt CustomCommandSync(const TMMFMessageDestinationPckg&  aDestination,
	                                     TInt                         aFunction,
	                               const TDesC8&                      aDataTo1,
	                               const TDesC8&                      aDataTo2,
	                                     TDes8&                       aDataFrom) = 0;

	virtual TInt CustomCommandSync(const TMMFMessageDestinationPckg&  aDestination,
	                                     TInt                         aFunction,
	                               const TDesC8&                      aDataTo1,
	                               const TDesC8&                      aDataTo2) = 0;

	virtual void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination,
	                                      TInt                        aFunction,
	                                const TDesC8&                     aDataTo1,
	                                const TDesC8&                     aDataTo2,
	                                      TDes8&                      aDataFrom,
	                                      TRequestStatus&             aStatus) = 0;

	virtual void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination,
	                                      TInt                        aFunction,
	                                const TDesC8&                     aDataTo1,
	                                const TDesC8&                     aDataTo2,
	                                      TRequestStatus&             aStatus) = 0;

	};

#endif
