/* STDDEF.H
 * 
 * Copyright (c) Symbian Software Ltd 1997-2004.  All rights reserved.
 */

/** @file
@publishedAll

*/

#ifndef _STDDEF_H_
#define _STDDEF_H_

/** 
There seems to be a lot of nonsense about _need_wchar_t etc., but for
STDLIB we have cut the Gordian knot and done the simple thing.
*/
#ifndef __wchar_t_defined
#ifndef __GCCXML__
typedef unsigned short int wchar_t;
#endif
#endif

#ifndef _PTRDIFF_T_DEFINED
#define _PTRDIFF_T_DEFINED
typedef long		ptrdiff_t;
//_PTRDIFF_T_DEFINED
#endif

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
typedef unsigned int	size_t;
//_SIZE_T_DEFINED
#endif

/** 
Offset of member MEMBER in a struct of type TYPE.  
*/
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif /* _STDDEF_H_ */
