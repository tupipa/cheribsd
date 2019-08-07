/*-
 * SPDX-License-Identifier: BSD-4-Clause
 *
 * Copyright (c) 1995 Terrence R. Lambert
 * All rights reserved.
 *
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 *	@(#)kernel.h	8.3 (Berkeley) 1/21/94
 * $FreeBSD$
 */

#ifndef _SYS_KERNEL_H_
#define	_SYS_KERNEL_H_

#include <sys/linker_set.h>

#ifdef _KERNEL

/* for intrhook below */
#include <sys/queue.h>

/* for timestamping SYSINITs; other files may assume this is included here */
#include <sys/tslog.h>

/* Global variables for the kernel. */

/* 1.1 */
extern char kernelname[MAXPATHLEN];

extern int tick;			/* usec per tick (1000000 / hz) */
extern int hz;				/* system clock's frequency */
extern int psratio;			/* ratio: prof / stat */
extern int stathz;			/* statistics clock's frequency */
extern int profhz;			/* profiling clock's frequency */
extern int profprocs;			/* number of process's profiling */
extern volatile int ticks;

#endif /* _KERNEL */

/*
 * Enumerated types for known system startup interfaces.
 *
 * Startup occurs in ascending numeric order; the list entries are
 * sorted prior to attempting startup to guarantee order.  Items
 * of the same level are arbitrated for order based on the 'order'
 * element.
 *
 * These numbers are arbitrary and are chosen ONLY for ordering; the
 * enumeration values are explicit rather than implicit to provide
 * for binary compatibility with inserted elements.
 *
 * The SI_SUB_LAST value must have the highest lexical value.
 */
enum sysinit_sub_id {
	SI_SUB_DUMMY		= 0x0000000,	/* not executed; for linker*/
	SI_SUB_DONE		= 0x0000001,	/* processed*/
	SI_SUB_TUNABLES		= 0x0700000,	/* establish tunable values */
	SI_SUB_COPYRIGHT	= 0x0800001,	/* first use of console*/
	SI_SUB_VM		= 0x1000000,	/* virtual memory system init*/
	SI_SUB_KMEM		= 0x1800000,	/* kernel memory*/
	SI_SUB_HYPERVISOR	= 0x1A40000,	/*
						 * Hypervisor detection and
						 * virtualization support 
						 * setup.
						 */
	SI_SUB_WITNESS		= 0x1A80000,	/* witness initialization */
	SI_SUB_MTX_POOL_DYNAMIC	= 0x1AC0000,	/* dynamic mutex pool */
	SI_SUB_LOCK		= 0x1B00000,	/* various locks */
	SI_SUB_EVENTHANDLER	= 0x1C00000,	/* eventhandler init */
	SI_SUB_VNET_PRELINK	= 0x1E00000,	/* vnet init before modules */
	SI_SUB_KLD		= 0x2000000,	/* KLD and module setup */
	SI_SUB_CPU		= 0x2100000,	/* CPU resource(s)*/
	SI_SUB_RACCT		= 0x2110000,	/* resource accounting */
	SI_SUB_KDTRACE		= 0x2140000,	/* Kernel dtrace hooks */
	SI_SUB_RANDOM		= 0x2160000,	/* random number generator */
	SI_SUB_MAC		= 0x2180000,	/* TrustedBSD MAC subsystem */
	SI_SUB_MAC_POLICY	= 0x21C0000,	/* TrustedBSD MAC policies */
	SI_SUB_MAC_LATE		= 0x21D0000,	/* TrustedBSD MAC subsystem */
	SI_SUB_VNET		= 0x21E0000,	/* vnet 0 */
	SI_SUB_INTRINSIC	= 0x2200000,	/* proc 0*/
	SI_SUB_VM_CONF		= 0x2300000,	/* config VM, set limits*/
	SI_SUB_DDB_SERVICES	= 0x2380000,	/* capture, scripting, etc. */
	SI_SUB_RUN_QUEUE	= 0x2400000,	/* set up run queue*/
	SI_SUB_KTRACE		= 0x2480000,	/* ktrace */
	SI_SUB_OPENSOLARIS	= 0x2490000,	/* OpenSolaris compatibility */
	SI_SUB_AUDIT		= 0x24C0000,	/* audit */
	SI_SUB_CREATE_INIT	= 0x2500000,	/* create init process*/
	SI_SUB_SCHED_IDLE	= 0x2600000,	/* required idle procs */
	SI_SUB_MBUF		= 0x2700000,	/* mbuf subsystem */
	SI_SUB_INTR		= 0x2800000,	/* interrupt threads */
	SI_SUB_TASKQ		= 0x2880000,	/* task queues */
#ifdef EARLY_AP_STARTUP
	SI_SUB_SMP		= 0x2900000,	/* start the APs*/
#endif
	SI_SUB_SOFTINTR		= 0x2A00000,	/* start soft interrupt thread */
	SI_SUB_DEVFS		= 0x2F00000,	/* devfs ready for devices */
	SI_SUB_INIT_IF		= 0x3000000,	/* prep for net interfaces */
	SI_SUB_NETGRAPH		= 0x3010000,	/* Let Netgraph initialize */
	SI_SUB_DTRACE		= 0x3020000,	/* DTrace subsystem */
	SI_SUB_DTRACE_PROVIDER	= 0x3048000,	/* DTrace providers */
	SI_SUB_DTRACE_ANON	= 0x308C000,	/* DTrace anon enabling */
	SI_SUB_DRIVERS		= 0x3100000,	/* Let Drivers initialize */
	SI_SUB_CONFIGURE	= 0x3800000,	/* Configure devices */
	SI_SUB_VFS		= 0x4000000,	/* virtual filesystem*/
	SI_SUB_CLOCKS		= 0x4800000,	/* real time and stat clocks*/
	SI_SUB_SYSV_SHM		= 0x6400000,	/* System V shared memory*/
	SI_SUB_SYSV_SEM		= 0x6800000,	/* System V semaphores*/
	SI_SUB_SYSV_MSG		= 0x6C00000,	/* System V message queues*/
	SI_SUB_P1003_1B		= 0x6E00000,	/* P1003.1B realtime */
	SI_SUB_PSEUDO		= 0x7000000,	/* pseudo devices*/
	SI_SUB_EXEC		= 0x7400000,	/* execve() handlers */
	SI_SUB_PROTO_BEGIN	= 0x8000000,	/* VNET initialization */
	SI_SUB_PROTO_PFIL	= 0x8100000,	/* Initialize pfil before FWs */
	SI_SUB_PROTO_IF		= 0x8400000,	/* interfaces*/
	SI_SUB_PROTO_DOMAININIT	= 0x8600000,	/* domain registration system */
	SI_SUB_PROTO_MC		= 0x8700000,	/* Multicast */
	SI_SUB_PROTO_DOMAIN	= 0x8800000,	/* domains (address families?)*/
	SI_SUB_PROTO_FIREWALL	= 0x8806000,	/* Firewalls */
	SI_SUB_PROTO_IFATTACHDOMAIN = 0x8808000,/* domain dependent data init */
	SI_SUB_PROTO_END	= 0x8ffffff,	/* VNET helper functions */
	SI_SUB_KPROF		= 0x9000000,	/* kernel profiling*/
	SI_SUB_KICK_SCHEDULER	= 0xa000000,	/* start the timeout events*/
	SI_SUB_INT_CONFIG_HOOKS	= 0xa800000,	/* Interrupts enabled config */
	SI_SUB_ROOT_CONF	= 0xb000000,	/* Find root devices */
	SI_SUB_INTRINSIC_POST	= 0xd000000,	/* proc 0 cleanup*/
	SI_SUB_SYSCALLS		= 0xd800000,	/* register system calls */
	SI_SUB_VNET_DONE	= 0xdc00000,	/* vnet registration complete */
	SI_SUB_KTHREAD_INIT	= 0xe000000,	/* init process*/
	SI_SUB_KTHREAD_PAGE	= 0xe400000,	/* pageout daemon*/
	SI_SUB_KTHREAD_VM	= 0xe800000,	/* vm daemon*/
	SI_SUB_KTHREAD_BUF	= 0xea00000,	/* buffer daemon*/
	SI_SUB_KTHREAD_UPDATE	= 0xec00000,	/* update daemon*/
	SI_SUB_KTHREAD_IDLE	= 0xee00000,	/* idle procs*/
#ifndef EARLY_AP_STARTUP
	SI_SUB_SMP		= 0xf000000,	/* start the APs*/
#endif	
	SI_SUB_RACCTD		= 0xf100000,	/* start racctd*/
	SI_SUB_LAST		= 0xfffffff	/* final initialization */
};


/*
 * Some enumerated orders; "ANY" sorts last.
 */
enum sysinit_elem_order {
	SI_ORDER_FIRST		= 0x0000000,	/* first*/
	SI_ORDER_SECOND		= 0x0000001,	/* second*/
	SI_ORDER_THIRD		= 0x0000002,	/* third*/
	SI_ORDER_FOURTH		= 0x0000003,	/* fourth*/
	SI_ORDER_MIDDLE		= 0x1000000,	/* somewhere in the middle */
	SI_ORDER_ANY		= 0xfffffff	/* last*/
};


/*
 * A system initialization call instance
 *
 * At the moment there is one instance of sysinit.  We probably do not
 * want two which is why this code is if'd out, but we definitely want
 * to discern SYSINIT's which take non-constant data pointers and
 * SYSINIT's which take constant data pointers,
 *
 * The C_* macros take functions expecting const void * arguments
 * while the non-C_* macros take functions expecting just void * arguments.
 *
 * With -Wcast-qual on, the compiler issues warnings:
 *	- if we pass non-const data or functions taking non-const data
 *	  to a C_* macro.
 *
 *	- if we pass const data to the normal macros
 *
 * However, no warning is issued if we pass a function taking const data
 * through a normal non-const macro.  This is ok because the function is
 * saying it won't modify the data so we don't care whether the data is
 * modifiable or not.
 */

typedef void (*sysinit_nfunc_t)(void *);
typedef void (*sysinit_cfunc_t)(const void *);

struct sysinit {
	enum sysinit_sub_id	subsystem;	/* subsystem identifier*/
	enum sysinit_elem_order	order;		/* init order within subsystem*/
	sysinit_cfunc_t func;			/* function		*/
	const void	*udata;			/* multiplexer/argument */
};

/*
 * Default: no special processing
 *
 * The C_ version of SYSINIT is for data pointers to const
 * data ( and functions taking data pointers to const data ).
 * At the moment it is no different from SYSINIT and thus
 * still results in warnings.
 *
 * The casts are necessary to have the compiler produce the
 * correct warnings when -Wcast-qual is used.
 *
 */
#ifdef TSLOG
struct sysinit_tslog {
	sysinit_cfunc_t func;
	const void * data;
	const char * name;
};
static inline void
sysinit_tslog_shim(const void * data)
{
	const struct sysinit_tslog * x = data;

	TSRAW(curthread, TS_ENTER, "SYSINIT", x->name);
	(x->func)(x->data);
	TSRAW(curthread, TS_EXIT, "SYSINIT", x->name);
}
#define	C_SYSINIT(uniquifier, subsystem, order, func, ident)	\
	static struct sysinit_tslog uniquifier ## _sys_init_tslog = {	\
		func,						\
		(ident),					\
		#uniquifier					\
	};							\
	static struct sysinit uniquifier ## _sys_init = {	\
		subsystem,					\
		order,						\
		sysinit_tslog_shim,				\
		&uniquifier ## _sys_init_tslog			\
	};							\
	DATA_WSET(sysinit_set,uniquifier ## _sys_init)
#else
#define	C_SYSINIT(uniquifier, subsystem, order, func, ident)	\
	static struct sysinit uniquifier ## _sys_init = {	\
		subsystem,					\
		order,						\
		func,						\
		(ident)						\
	};							\
	DATA_WSET(sysinit_set,uniquifier ## _sys_init)
#endif

#define	SYSINIT(uniquifier, subsystem, order, func, ident)	\
	C_SYSINIT(uniquifier, subsystem, order,			\
	(sysinit_cfunc_t)(sysinit_nfunc_t)func, (void *)(ident))

/*
 * Called on module unload: no special processing
 */
#define	C_SYSUNINIT(uniquifier, subsystem, order, func, ident)	\
	static struct sysinit uniquifier ## _sys_uninit = {	\
		subsystem,					\
		order,						\
		func,						\
		(ident)						\
	};							\
	DATA_WSET(sysuninit_set,uniquifier ## _sys_uninit)

#define	SYSUNINIT(uniquifier, subsystem, order, func, ident)	\
	C_SYSUNINIT(uniquifier, subsystem, order,		\
	(sysinit_cfunc_t)(sysinit_nfunc_t)func, (void *)(ident))

void	sysinit_add(struct sysinit **set, struct sysinit **set_end);

/*
 * Infrastructure for tunable 'constants'.  Value may be specified at compile
 * time or kernel load time.  Rules relating tunables together can be placed
 * in a SYSINIT function at SI_SUB_TUNABLES with SI_ORDER_ANY.
 *
 * WARNING: developers should never use the reserved suffixes specified in
 * loader.conf(5) for any tunables or conflicts will result.
 */

/*
 * int
 * please avoid using for new tunables!
 */
extern void tunable_int_init(void *);
struct tunable_int {
	const char *path;
	int *var;
};
#define	TUNABLE_INT(path, var)					\
	static struct tunable_int __CONCAT(__tunable_int_, __LINE__) = { \
		(path),						\
		(var),						\
	};							\
	SYSINIT(__CONCAT(__Tunable_init_, __LINE__),		\
	    SI_SUB_TUNABLES, SI_ORDER_MIDDLE, tunable_int_init,	\
	    &__CONCAT(__tunable_int_, __LINE__))

#define	TUNABLE_INT_FETCH(path, var)	getenv_int((path), (var))

/*
 * long
 */
extern void tunable_long_init(void *);
struct tunable_long {
	const char *path;
	long *var;
};
#define	TUNABLE_LONG(path, var)					\
	static struct tunable_long __CONCAT(__tunable_long_, __LINE__) = { \
		(path),						\
		(var),						\
	};							\
	SYSINIT(__CONCAT(__Tunable_init_, __LINE__),		\
	    SI_SUB_TUNABLES, SI_ORDER_MIDDLE, tunable_long_init,\
	    &__CONCAT(__tunable_long_, __LINE__))

#define	TUNABLE_LONG_FETCH(path, var)	getenv_long((path), (var))

/*
 * unsigned long
 */
extern void tunable_ulong_init(void *);
struct tunable_ulong {
	const char *path;
	unsigned long *var;
};
#define	TUNABLE_ULONG(path, var)				\
	static struct tunable_ulong __CONCAT(__tunable_ulong_, __LINE__) = { \
		(path),						\
		(var),						\
	};							\
	SYSINIT(__CONCAT(__Tunable_init_, __LINE__),		\
	    SI_SUB_TUNABLES, SI_ORDER_MIDDLE, tunable_ulong_init, \
	    &__CONCAT(__tunable_ulong_, __LINE__))

#define	TUNABLE_ULONG_FETCH(path, var)	getenv_ulong((path), (var))

/*
 * int64_t
 */
extern void tunable_int64_init(void *);
struct tunable_int64 {
	const char *path;
	int64_t *var;
};
#define	TUNABLE_INT64(path, var)				\
	static struct tunable_int64 __CONCAT(__tunable_int64_, __LINE__) = { \
		(path),						\
		(var),						\
	};							\
	SYSINIT(__CONCAT(__Tunable_init_, __LINE__),		\
	    SI_SUB_TUNABLES, SI_ORDER_MIDDLE, tunable_int64_init, \
	    &__CONCAT(__tunable_int64_, __LINE__))

#define	TUNABLE_INT64_FETCH(path, var)	getenv_int64((path), (var))

/*
 * uint64_t
 */
extern void tunable_uint64_init(void *);
struct tunable_uint64 {
	const char *path;
	uint64_t *var;
};
#define	TUNABLE_UINT64(path, var)				\
	static struct tunable_uint64 __CONCAT(__tunable_uint64_, __LINE__) = { \
		(path),						\
		(var),						\
	};							\
	SYSINIT(__CONCAT(__Tunable_init_, __LINE__),		\
	    SI_SUB_TUNABLES, SI_ORDER_MIDDLE, tunable_uint64_init, \
	    &__CONCAT(__tunable_uint64_, __LINE__))

#define	TUNABLE_UINT64_FETCH(path, var)	getenv_uint64((path), (var))

/*
 * quad
 */
extern void tunable_quad_init(void *);
struct tunable_quad {
	const char *path;
	quad_t *var;
};
#define	TUNABLE_QUAD(path, var)					\
	static struct tunable_quad __CONCAT(__tunable_quad_, __LINE__) = { \
		(path),						\
		(var),						\
	};							\
	SYSINIT(__CONCAT(__Tunable_init_, __LINE__),		\
	    SI_SUB_TUNABLES, SI_ORDER_MIDDLE, tunable_quad_init, \
	    &__CONCAT(__tunable_quad_, __LINE__))

#define	TUNABLE_QUAD_FETCH(path, var)	getenv_quad((path), (var))

extern void tunable_str_init(void *);
struct tunable_str {
	const char *path;
	char *var;
	int size;
};
#define	TUNABLE_STR(path, var, size)				\
	static struct tunable_str __CONCAT(__tunable_str_, __LINE__) = { \
		(path),						\
		(var),						\
		(size),						\
	};							\
	SYSINIT(__CONCAT(__Tunable_init_, __LINE__),		\
	    SI_SUB_TUNABLES, SI_ORDER_MIDDLE, tunable_str_init,	\
	    &__CONCAT(__tunable_str_, __LINE__))

#define	TUNABLE_STR_FETCH(path, var, size)			\
	getenv_string((path), (var), (size))

typedef void (*ich_func_t)(void *_arg);

struct intr_config_hook {
	TAILQ_ENTRY(intr_config_hook) ich_links;
	ich_func_t	ich_func;
	void		*ich_arg;
};

int	config_intrhook_establish(struct intr_config_hook *hook);
void	config_intrhook_disestablish(struct intr_config_hook *hook);
void	config_intrhook_oneshot(ich_func_t _func, void *_arg);

#include "kernel_debug.h"
// Lele: Debugging Prints
// To enable debug: define TRACK_HELLO
// To disable: undefine TRACK_HELLO here.
// * use 'hello' process means the target process to monitor
// * process is recognized by its string name, defined by TRACK_HELLO_NAME
#ifndef TRACK_HELLO
#define TRACK_HELLO
#endif


#ifdef TRACK_HELLO

#define NO_PRINT_BUFFER

// WAIT_INTERVAL : delay the printings by a number of context switches
// only used in PRINT_BUFFER
#define WAIT_INTERVAL 20
// PRINT_BUF_REQUEST: delay the printings by the number of calls to PRINT_BUFFER
// only used in PRINT_BUFFER
#define PRINT_BUF_REQUEST 20
// #define wait_interval WAIT_INTERVAL 

//#define MAX_PRINT_BUF 8186 //8192-6
//#define MAX_PRINT_BUF 16378 //16*1024-6
// #define MAX_PRINT_BUF 1048570 //1024*1024-6
#define MAX_PRINT_BUF (4*1024*1024) //1024*1024-6


#define TRACK_HELLO_NAME "hello"
//#define TRACK_HELLO_NAME "sh"

#define TRACK_IS_NOT_TARGET 1  // 0
// flag cpu is switched from hello to another process during context switch
#define TRACK_IS_FROM_HELLO 2 // 1
// flag cpu is switched to hello from another process during context switch
#define TRACK_IS_TO_HELLO 3  // 2
// flag cpu is currently running the hello process
#define TRACK_IS_HELLO 4 // 3

// the following defined in ./usr/src/sys/kern/sched_ule.c
extern char print_buf[MAX_PRINT_BUF];
extern long print_size_tmp;
extern long printed_total;
extern int print_buf_full;

/* count number of context switches */
extern int swap_counted;

/* count number of calls to PRINT_BUFFER */
extern int print_request;

/* used by TRACK_HELLO debugging, flag current hello proc*/
extern int track_detect;	
extern char track_name[];

#define TRACK_HELLO_DETECT(th) \
 if (th && th->td_proc && th->td_proc->p_comm && \
        (!strcmp(th->td_proc->p_comm, track_name))) { \
        track_detect = TRACK_IS_HELLO; \
 }else{\
   track_detect = TRACK_IS_NOT_TARGET; \
 }
 
#define TRACK_HELLO_DETECT2(old,new) \
 if (old && old->td_proc && old->td_proc->p_comm && \
        (!strcmp(old->td_proc->p_comm, track_name))) {\
        track_detect = TRACK_IS_FROM_HELLO;\
 }else if (new && new->td_proc && new->td_proc->p_comm && \
        !strcmp(new->td_proc->p_comm, track_name)) { \
        track_detect = TRACK_IS_TO_HELLO; \
 }else{\
    track_detect = TRACK_IS_NOT_TARGET; \
 }

#define TRACK_HELLO_DETECT_PROC(tdproc) \
 if (!strcmp(tdproc->p_comm, track_name)) { \
        track_detect = TRACK_IS_HELLO; \
 }else{\
   track_detect = TRACK_IS_NOT_TARGET; \
 }


// #define DBG_printf(fmt, ...) \
// 	printf(("dbg-[%s:%s:%d] " fmt), \
//        __FUNCTION__,__FILE__,__LINE__, ##__VA_ARGS__ )

// print regardless of target program
#define DBG_printf(fmt, ...) \
	do{\
  if (!print_buf_full){ \
      critical_enter(); \
      print_size_tmp = \
        snprintf(print_buf + printed_total, \
          MAX_PRINT_BUF - printed_total, \
          ("[DBG][%s:%s:%d]: " fmt), \
          __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
      if (print_size_tmp >= MAX_PRINT_BUF - printed_total ){ \
        print_buf_full = 1; \
        /*printed_total = MAX_PRINT_BUF;*/ \
        /*snprintf(print_buf + MAX_PRINT_BUF - 1, 6, "OOB!!");*/ \
        /* always keep the lastest print at the end of the buffer */ \
        snprintf(print_buf + MAX_PRINT_BUF - print_size_tmp -7, \
          print_size_tmp + 6, \
          ("[DBG][%s:%s:%d]: " fmt "OOB!!"), \
          __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
      }\
      printed_total += print_size_tmp; \
      critical_exit(); \
       \
  }else{\
      critical_enter(); \
      /* if buffer is full, then just get the size increase it to printed_total. Now printed_total is used for total size of strings requested to print, including those not printed out.*/\
      print_size_tmp = snprintf(NULL, 0,("[DBG][%s:%s:%d]: " fmt), \
         __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
      /* always keep the lastest print at the end of the buffer */ \
      snprintf(print_buf + MAX_PRINT_BUF - print_size_tmp -7, \
        print_size_tmp + 6, ("[DBG][%s:%s:%d]: " fmt "OOB!!"), \
        __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
      printed_total += print_size_tmp; \
      critical_exit(); \
  } \
}while(0);


// Test target program and print
#define BUFFER_WRITE(fmt, ...) \
do{\
  critical_enter(); \
	if (track_detect > TRACK_IS_NOT_TARGET && !print_buf_full){ \
      print_size_tmp = snprintf(print_buf + printed_total, \
        MAX_PRINT_BUF - printed_total,("[%s in %s:%d]: " fmt), \
        __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
      if (print_size_tmp >= MAX_PRINT_BUF - printed_total ){ \
        print_buf_full = 1; \
        /*printed_total = MAX_PRINT_BUF;*/ \
        /*snprintf(print_buf + MAX_PRINT_BUF - 1, 6, "OOB!!");*/ \
        /* always keep the lastest print at the end of the buffer */ \
        snprintf(print_buf + MAX_PRINT_BUF - print_size_tmp -7, \
          print_size_tmp + 6, ("[%s in %s:%d]: " fmt "OOB!!"), \
          __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
      }\
      printed_total += print_size_tmp; \
       \
  }else if (track_detect > TRACK_IS_NOT_TARGET && print_buf_full){\
      /* if buffer is full, then just get the size increase it to printed_total. Now printed_total is used for total size of strings requested to print, including those not printed out.*/\
      print_size_tmp = snprintf(NULL, 0,("[%s in %s:%d]: " fmt), \
        __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
      /* always keep the lastest print at the end of the buffer */ \
      snprintf(print_buf + MAX_PRINT_BUF - print_size_tmp -7, \
        print_size_tmp + 6, ("[DBG][%s:%s:%d]: " fmt "OOB!!"), \
        __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
      printed_total += print_size_tmp; \
  } \
  critical_exit(); \
}while(0);


// print out the buffer immediately
// regardless the target program
#define PRINT_BUFFER_IM \
  if ( printed_total > 0){ \
    long buf_used=printed_total; \
    if (printed_total >= MAX_PRINT_BUF) buf_used=MAX_PRINT_BUF; \
    printf("PRINT_BUFFER_IM@ [%s:%s:%d]\n", __FUNCTION__, __FILE__, __LINE__);\
    printf("%s\n", print_buf); \
    printf("\n--------- swap counted %d, buffer used %ld, " \
      "left %ld, print requests: %d ------\n",\
      swap_counted, buf_used, MAX_PRINT_BUF-printed_total, print_request);\
    printf("-----------------------------------\n"); \
    critical_enter(); \
    printed_total = 0; \
    print_buf_full = 0; \
    print_buf[0]= '\0'; \
    swap_counted = 0; \
    print_request = 0; \
    critical_exit(); \
  }

#ifdef NO_PRINT_BUFFER 
#define PRINT_BUFFER // empty print buffer.
#else

// print the buffer only when 
// 1. target program has been found, and
// 2. the buffer is full, or the requests/switches > max & buffer not empty.
#define PRINT_BUFFER \
  if (track_detect > TRACK_IS_NOT_TARGET && \
      (print_buf_full || swap_counted >= WAIT_INTERVAL || \
       print_request >= PRINT_BUF_REQUEST) && \
      printed_total){ \
    long buf_used=printed_total; \
    if (printed_total >= MAX_PRINT_BUF) buf_used=MAX_PRINT_BUF; \
    printf("%s\n", print_buf); \
    printf("\n--------- swap counted %d, buffer used %ld, " \
       "left %ld, print requests: %d ------\n", \
       swap_counted, buf_used, MAX_PRINT_BUF-printed_total, print_request);\
    printf("-----------------------------------\n"); \
    critical_enter(); \
    printed_total = 0; \
    print_buf_full = 0; \
    print_buf[0]= '\0'; \
    swap_counted = 0; \
    print_request = 0; \
    critical_exit(); \
  } else if (track_detect > TRACK_IS_NOT_TARGET) { \
    critical_enter(); \
    print_request ++ ; \
    critical_exit(); \
  }

#endif // NO_PRINT_BUFFER


#define QUAUX(X) #X
#define QU(X) QUAUX(X)

// Print to buffer regardless of whether the program is hello or not
#define DBG_PRINT_CONTEXT \
 do{ \
 	unsigned short gs__; \
    unsigned short fs__; \
    unsigned short es__; \
    unsigned short ds__; \
\
    unsigned long rsi__, \
                rax__, rbx__, rcx__, rdx__; \
\
    unsigned long r8__, r9__, r10__, r11__, r12__, \
                r13__, r14__, r15__; \
\
    unsigned long rbp__; \
    unsigned short cs__, ss__; \
\
    unsigned long rflags__, rsp__, retaddr__;\
\
    unsigned int fsbase_eax__, fsbase_edx__;\
    unsigned int gsbase_eax__, gsbase_edx__;\
    unsigned int kgsbase_eax__, kgsbase_edx__;\
\
    critical_enter(); \
    __asm__ __volatile__ ( \
      "pushq %%rcx\n" \
      "pushq %%rax\n" \
      "pushq %%rdx\n" \
      "movl $" QU(MSR_FSBASE) ", %%ecx\n" \
      "rdmsr \n" \
      "movl %%eax, %0\n" \
      "movl %%edx, %1\n" \
      "popq %%rdx\n" \
      "popq %%rax\n" \
      "popq %%rcx\n" \
       : "=m" (fsbase_eax__), \
       "=m" (fsbase_edx__) \
      ); \
\
    __asm__ __volatile__ ( \
      "pushq %%rcx\n" \
      "pushq %%rax\n" \
      "pushq %%rdx\n" \
      "movl $" QU(MSR_GSBASE) ", %%ecx\n" \
      "rdmsr \n" \
      "movl %%eax, %0\n" \
      "movl %%edx, %1\n" \
      "popq %%rdx\n" \
      "popq %%rax\n" \
      "popq %%rcx\n" \
       : "=m" (gsbase_eax__), \
       "=m" (gsbase_edx__) \
      ); \
\
    __asm__ __volatile__ ( \
      "pushq %%rcx\n" \
      "pushq %%rax\n" \
      "pushq %%rdx\n" \
      "movl $" QU(MSR_KGSBASE) ", %%ecx\n" \
      "rdmsr \n" \
      "movl %%eax, %0\n" \
      "movl %%edx, %1\n" \
      "popq %%rdx\n" \
      "popq %%rax\n" \
      "popq %%rcx\n" \
       : "=m" (kgsbase_eax__), \
       "=m" (kgsbase_edx__) \
      ); \
\
    __asm__ __volatile__ ("movw %%gs, %0\n" \
                            "movw %%fs, %1\n" \
                            "movw %%es, %2\n" \
                            "movw %%ds, %3\n" \
                            : "=m" (gs__),  \
                            "=m" (fs__), \
                            "=m" (es__), \
                            "=m" (ds__) \
                            ); \
\
    __asm__ __volatile__ ("movq %%rsi, %0\n" \
                            : "=m" (rsi__) \
                            ); \
\
     __asm__ __volatile__ ("movq %%rax, %0\n" \
                            "movq %%rbx, %1\n" \
                            "movq %%rcx, %2\n" \
                            "movq %%rdx, %3\n" \
                            "movq %%r8, %4\n" \
                            "movq %%r9, %5\n" \
                            "movq %%r10, %6\n" \
                            "movq %%r11, %7\n" \
                            "movq %%r12, %8\n" \
                            "movq %%r13, %9\n" \
                            "movq %%r14, %10\n" \
                            "movq %%r15, %11\n" \
                            : "=m" (rax__),  \
                            "=m" (rbx__), \
                            "=m" (rcx__), \
                            "=m" (rdx__), \
                            "=m" (r8__), \
                            "=m" (r9__), \
                            "=m" (r10__), \
                            "=m" (r11__), \
                            "=m" (r12__), \
                            "=m" (r13__), \
                            "=m" (r14__), \
                            "=m" (r15__) \
                            ); \
 \
    __asm__ __volatile__ ("movq %%rbp, %0\n" \
                            : "=m" (rbp__) \
                            ); \
\
    __asm__ __volatile__ ("movw %%cs, %0\n" \
                            "movw %%ss, %1\n"\
                            : "=m" (cs__), \
                            "=m" (ss__)\
                            );\
\
\
    __asm__ __volatile__ ("pushfq\n"\
                            "popq %0\n"\
                            : "=m" (rflags__)\
                            );\
\
    __asm__ __volatile__ ("movq %%rsp, %0\n"\
                            : "=m" (rsp__)\
                            );\
\
\
    __asm__ __volatile__ ("pushq %%rax\n"\
                        "movq (%%rsp), %%rax\n"\
                        "movq %%rax, %0\n"\
                        "popq %%rax\n"\
                        : "=m" (retaddr__)\
                       );\
\
    critical_exit();\
    DBG_printf("---[%d]----------------\n"\
            "\tgs: 0x%hx, fs: 0x%hx, es: 0x%hx, ds: 0x%hx\n"\
            "\trsi: 0x%lx, rax: 0x%lx, rbx: 0x%lx, rcx: 0x%lx, rdx: 0x%lx\n"\
            "\tr8: 0x%lx, r9: 0x%lx, r10: 0x%lx, r11: 0x%lx\n"\
            "\tr12: 0x%lx, r13: 0x%lx, r14: 0x%lx, r15: 0x%lx\n"\
            "\trbp: 0x%lx, cs: 0x%hx, ss: 0x%hx\n"\
            "\trflags: 0x%lx, rsp: 0x%lx, retaddr[rsp]: 0x%lx\n"\
            "\tfsbase_eax: 0x%x, fsbase_edx: 0x%x\n"\
            "\tgsbase_eax: 0x%x, gsbase_edx: 0x%x\n"\
            "\tkgsbase_eax: 0x%x, kgsbase_edx: 0x%x\n"\
            "\t-----------------------------\n" \
            , swap_counted, gs__, fs__, es__, ds__,\
            rsi__, rax__, rbx__, rcx__, rdx__,\
            r8__, r9__, r10__, r11__, \
            r12__,r13__, r14__, r15__,\
            rbp__, cs__, ss__,\
            rflags__, rsp__, retaddr__,\
            fsbase_eax__, fsbase_edx__,\
            gsbase_eax__, gsbase_edx__,\
            kgsbase_eax__, kgsbase_edx__);\
}while(0);

// print context 
#define PRINT_CONTEXT \
do{\
 if(track_detect > TRACK_IS_NOT_TARGET){ \
   DBG_PRINT_CONTEXT \
 }\
}while(0);

#else // no TRACK_HELLO

/*************************************
 * TRACK_HELLO disabled:
 *     NO printings at all
 *************************************/

// nop for all printings
#define TRACK_HELLO_NOP

#define TRACK_HELLO_DETECT(th) TRACK_HELLO_NOP
 
#define TRACK_HELLO_DETECT2(old,new) TRACK_HELLO_NOP

#define TRACK_HELLO_DETECT_PROC(tdproc) TRACK_HELLO_NOP

// #define DBG_printf(fmt, ...) TRACK_HELLO_NOP

#define DBG_PRINT_CONTEXT TRACK_HELLO_NOP

#define BUFFER_WRITE(fmt, ...) TRACK_HELLO_NOP

#define PRINT_BUFFER_IM TRACK_HELLO_NOP

#define PRINT_BUFFER TRACK_HELLO_NOP

#define PRINT_CONTEXT TRACK_HELLO_NOP

#endif // TRACK_HELLO

#endif /* !_SYS_KERNEL_H_*/
