//
// Copyright (c) 2001, 2007 Symbian Software Ltd.  All rights reserved.
//

/** 
 * @file 
 * Global header file for the crypto token framework.
 * 
 * Include this header file and you should have everything you'll need
 * to use the CryptoToken framework. Look inside the included header
 * files to find out details of the classes.
 *
 * @publishedAll
 * 
 */

#ifndef __CT_H__
#define __CT_H__

#include <e32std.h>
#include <e32base.h>

#include <ct/tcttokentypeattribute.h>
#include <ct/ccttokentypeinfo.h>
#include <ct/mcttokentypefilter.h>
#include <ct/tctalltokentypes.h>
#include <ct/tctfindtokentypesbyinterface.h>
#include <ct/tctfindtokentypesbyinterfaceandattribute.h>
#include <ct/ccttokentype.h>
#include <ct/mcttoken.h>
#include <ct/mcttokeninterface.h>
#include <ct/rmpointerarray.h>
#include <ct/rcpointerarray.h>
#include <securitydefs.h>

/** 
 *	Crypto Token Framework 
 */

/** 
 *	Owning pointer arrays
 *
 *	These are pointer array classes that own their contents.
 *	Close() releases the array, and also releases the contents.
 */

/** 
 *	Token Interfaces
 *
 *	These are classes defining particular interfaces which tokens
 *	might implement. Other interfaces may be defined by 3rd parties.
 */

//__CT_H__
#endif
