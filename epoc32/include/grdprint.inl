// GRDPRINT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline void CGridPrinter::SetRealPrintingDeviceMap(const MGraphicsDeviceMap* aGraphicsDeviceMap)
/** Supplies the object that deals with the mapping between twips and device-specific 
units for a specific printer.

@param aGraphicsDeviceMap The interface object for mapping between twips and 
device-specific units. */
	{
	iGraphicsDeviceMap=aGraphicsDeviceMap;
	}

inline CGridLay& CGridPrinter::GridLay()
/** Gets the grid layout used by this printing object.

Note that this is not the same object passed to CGridPrinter::NewL(). Internally, 
the class creates its own CGridLay object from the information supplied in the 
CGridLay object passed to CGridPrinter::NewL().

@return The grid layout object. */
	{
	return *iGridLay;
	}
