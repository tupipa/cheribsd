/*-
 * Copyright 1996, 1997, 1998, 1999, 2000 John D. Polstra.
 * Copyright 2003 Alexander Kabaev <kan@FreeBSD.ORG>.
 * Copyright 2009-2012 Konstantin Belousov <kib@FreeBSD.ORG>.
 * Copyright 2012 John Marino <draco@marino.st>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef PATHS_H
#define PATHS_H

#undef _PATH_ELF_HINTS

#ifdef COMPAT_32BIT
#define	_PATH_ELF_HINTS		"/var/run/ld-elf32.so.hints"
#define	_PATH_LIBMAP_CONF	"/etc/libmap32.conf"
#define	_PATH_RTLD		"/libexec/ld-elf32.so.1"
#define	STANDARD_LIBRARY_PATH	"/lib32:/usr/lib32"
#define	LD_			"LD_32_"
#endif

#ifndef _PATH_ELF_HINTS
#define	_PATH_ELF_HINTS		"/var/run/ld-elf.so.hints"
#endif

#ifndef _PATH_LIBMAP_CONF
#define	_PATH_LIBMAP_CONF	"/etc/libmap.conf"
#endif

#ifndef _PATH_RTLD
#define	_PATH_RTLD		"/libexec/ld-elf.so.1"
#endif

#ifndef STANDARD_LIBRARY_PATH
#define	STANDARD_LIBRARY_PATH	"/lib:/usr/lib"
#endif

#ifndef LD_
#define	LD_			"LD_"
#endif

#endif /* PATHS_H */
