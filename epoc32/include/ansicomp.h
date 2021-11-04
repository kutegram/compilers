// 
// ANSIComp.h
//
//  Copyright (c) Symbian Software Ltd 1997-2007.  All rights reserved.
//

// Comments: Enforce ANSI compliance on Microsoft compilers in 'For loop' behaviour
// 


#if !defined(__ANSICOMP_H__)
#define __ANSICOMP_H__

#if defined(__VC32__) && _MSC_VER>=1100
#pragma warning(disable : 4127)		// warning C4127 : conditional expression is constant

#define for if(false);else for		// Enforce the definition of a loop variable to local scope

#endif

// __ANSICOMP_H__
#endif
