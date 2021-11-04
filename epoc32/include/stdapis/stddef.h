/*-
 * � Portions copyright (c) 2005 Nokia Corporation.  All rights reserved.
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)stddef.h	8.1 (Berkeley) 6/2/93
 *
 * $FreeBSD: src/include/stddef.h,v 1.10 2003/12/07 21:10:06 marcel Exp $
 */

#ifndef _STDDEF_H_
#define _STDDEF_H_

#include <sys/cdefs.h>
#include <sys/_null.h>
#include <sys/_types.h>

typedef	__ptrdiff_t	ptrdiff_t;

#if __BSD_VISIBLE
#ifndef _RUNE_T_DECLARED
typedef	__rune_t	rune_t;
#define	_RUNE_T_DECLARED
#endif
#endif

#ifndef _SIZE_T_DECLARED
typedef	__size_t	size_t;
#define	_SIZE_T_DECLARED
#endif

#ifndef __SYMBIAN32__
#ifndef	__cplusplus
#ifndef _WCHAR_T_DECLARED
typedef	__wchar_t	wchar_t;
#define	_WCHAR_T_DECLARED
#endif //_WCHAR_T_DECLARED
#endif //__cplusplus
#else
//C++ built-in wchar data type which doesn't clash with the definition of wchar
#if !defined _WCHAR_T_DECLARED && defined __cplusplus && defined __WINSCW__
#if __option(wchar_type)
#define	_WCHAR_T_DECLARED
#endif //__option (wchar_type)
#endif //__WINSCW__

#if !defined _WCHAR_T_DECLARED && !defined __wchar_t_defined
#if defined __cplusplus
#if defined __WINSCW__
typedef unsigned short int wchar_t;
#define	_WCHAR_T_DECLARED
#endif // __WINSCW__
#else
typedef unsigned short int wchar_t;
#define	_WCHAR_T_DECLARED
#endif // __cplusplus 
#endif // __wchar_t_defined
#endif //__SYMBIAN32__

#define	offsetof(type, member)	__offsetof(type, member)

#endif /* _STDDEF_H_ */
