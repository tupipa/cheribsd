#ifndef CHERITEST_DEBUG_H
#define CHERITEST_DEBUG_H


//#define TRACK_HELLO


#ifdef TRACK_HELLO

/* define empty func for compatibility */
#define critical_enter() do{}while(0)
#define critical_exit() do{}while(0)

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


#define TRACK_HELLO_NAME "cheriabitest"
//#define TRACK_HELLO_NAME "sh"


// flag current process is not target
#define TRACK_IS_NOT_TARGET 1  
// 2 and 3 only in effective when using TRACK_HELLO_DETECT2(old, new) to detect
// flag cpu is switched from hello to another process during context switch
#define TRACK_IS_FROM_HELLO 2
// flag cpu is switched to hello from another process during context switch
#define TRACK_IS_TO_HELLO 3
// flag cpu is currently running the hello process
#define TRACK_IS_HELLO 4


// set to 0 to track all processes; 
// set to 1 to track all switches related to target
// set to 2 to track only switch from target to another one
// set to 3 to track all states when target is running.
#define CUR_TRACK_LEVEL 0  // 1 // 2 // 3

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

#define TRACK_HELLO_VAR_DEFINITION \
/* the following defined in ./usr/src/sys/kern/sched_4bsd.c */ \
char print_buf[MAX_PRINT_BUF]; \
long print_size_tmp = 0; \
long printed_total = 0; \
int print_buf_full = 0; \
/* count number of context switches */ \
int swap_counted = 0; \
/* count number of calls to PRINT_BUFFER */ \
int print_request = 0; \
/* used by TRACK_HELLO debugging, flag current hello proc*/ \
int track_detect = TRACK_IS_NOT_TARGET;	\
char track_name[] = TRACK_HELLO_NAME;


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
}while(0)


// Test target program and print
#define BUFFER_WRITE(fmt, ...) \
do{\
  critical_enter(); \
	if (track_detect > CUR_TRACK_LEVEL && !print_buf_full){ \
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
  }else if (track_detect > CUR_TRACK_LEVEL && print_buf_full){\
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
}while(0)


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
  if (track_detect > CUR_TRACK_LEVEL && \
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
  } else if (track_detect > CUR_TRACK_LEVEL) { \
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
    /* disable them since not mips arch */ \
    /* unsigned short gs__; \
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
    critical_exit(); \
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
            kgsbase_eax__, kgsbase_edx__); */ \
}while(0)

// print context 
#define PRINT_CONTEXT \
do{\
 if(track_detect > CUR_TRACK_LEVEL){ \
   DBG_PRINT_CONTEXT; \
 }\
}while(0)

#else // no TRACK_HELLO

/*************************************
 * TRACK_HELLO disabled:
 *     NO printings at all
 *************************************/

// nop for all printings
#define TRACK_HELLO_NOP


#define TRACK_HELLO_VAR_DEFINITION TRACK_HELLO_NOP

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


#endif // CHERITEST_DEBUG_H
