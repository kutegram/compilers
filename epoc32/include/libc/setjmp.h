/* SETJMP.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/** @file
@publishedAll

*/

#ifndef _SETJMP_H_
#define _SETJMP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <_ansi.h>

/** see MSVC 4.0 SETJMP.H & E32STD.H class TTrap
 */
#define _JBLEN	16		
#define _JBTYPE	unsigned long

typedef	_JBTYPE jmp_buf[_JBLEN];

IMPORT_C void longjmp(jmp_buf __jmpb, int __retval);
IMPORT_C int setjmp(jmp_buf __jmpb);

#ifdef __cplusplus
}
#endif
#endif /* _SETJMP_H_ */

