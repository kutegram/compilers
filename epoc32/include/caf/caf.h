// caf.h
// Copyright (C) Symbian Software Ltd 2003 - 2004.  All rights reserved.


/** 
@file

This contains all definitions required by clients accessing the 
Content Access Framework.

@publishedPartner

*/

#ifndef __CAF_H__
#define __CAF_H__

#include <e32std.h>

// Errors and Panics
#include <caf/caferr.h>
#include <caf/cafpanic.h>

// Enumerations
#include <caf/caftypes.h>

// Client side classes for use by the general public
#include <caf/agent.h>
#include <caf/content.h>
#include <caf/data.h>
#include <caf/manager.h>
#include <caf/supplier.h>
#include <caf/importfile.h>
#include <caf/rightsmanager.h>

// Utiltiy classes from CafUtils
#include <caf/supplieroutputfile.h>
#include <caf/metadata.h>
#include <caf/metadataarray.h>
#include <caf/virtualpath.h>
#include <caf/virtualpathptr.h>
#include <caf/embeddedobject.h>
#include <caf/attributeset.h>
#include <caf/rightsinfo.h>
#include <caf/attributeset.h>
#include <caf/stringattributeset.h>
#include <caf/streamableptrarray.h>
#include <caf/dirstreamable.h>

// deprecated headerfiles
#include <caf/attribute.h>
#include <caf/cafmimeheader.h>

// __CAF_H__
#endif
