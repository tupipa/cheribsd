/*
 * System call prototypes.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 */

#ifndef _CHERIABI_PROTO_H_
#define	_CHERIABI_PROTO_H_

#include <sys/signal.h>
#include <sys/acl.h>
#include <sys/cpuset.h>
#include <sys/_ffcounter.h>
#include <sys/_semaphore.h>
#include <sys/ucontext.h>
#include <sys/wait.h>

#include <bsm/audit_kevents.h>

struct proc;

struct thread;

#ifdef CPU_CHERI
#define	CHERI_PADL_(t)	(sizeof (t) > sizeof(register_t) ? \
		0 : sizeof(register_t))
#define	CHERI_PADR_(t)	(sizeof (t) > sizeof(register_t ) ? \
		0 : sizeof(__intcap_t) - (CHERI_PADL_(t) + sizeof(register_t)))
#else
#define	CHERI_PADL_(t)	0
#define	CHERI_PADR_(t)	0
#endif

#define	PAD_(t)	(sizeof(register_t) <= sizeof(t) ? \
		0 : sizeof(register_t) - sizeof(t))

#if BYTE_ORDER == LITTLE_ENDIAN
#define	PADL_(t)	0
#define	PADR_(t)	PAD_(t)
#else
#define	PADL_(t)	(CHERI_PADL_(t) + PAD_(t))
#define	PADR_(t)	CHERI_PADR_(t)
#endif

#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif
struct cheriabi_syscall_args {
	char number_l_[PADL_(int)]; int number; char number_r_[PADR_(int)];
};
struct cheriabi_open_args {
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
	char mode_l_[PADL_(mode_t)]; mode_t mode; char mode_r_[PADR_(mode_t)];
};
struct cheriabi_link_args {
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
	char to_l_[PADL_(const char *__capability)]; const char *__capability to; char to_r_[PADR_(const char *__capability)];
};
struct cheriabi_unlink_args {
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
};
struct cheriabi_chdir_args {
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
};
struct cheriabi_mount_args {
	char type_l_[PADL_(const char *__capability)]; const char *__capability type; char type_r_[PADR_(const char *__capability)];
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
	char data_l_[PADL_(void *__capability)]; void *__capability data; char data_r_[PADR_(void *__capability)];
};
struct cheriabi_recvmsg_args {
	char s_l_[PADL_(int)]; int s; char s_r_[PADR_(int)];
	char msg_l_[PADL_(struct msghdr_c *)]; struct msghdr_c * msg; char msg_r_[PADR_(struct msghdr_c *)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct cheriabi_sendmsg_args {
	char s_l_[PADL_(int)]; int s; char s_r_[PADR_(int)];
	char msg_l_[PADL_(const struct msghdr_c *)]; const struct msghdr_c * msg; char msg_r_[PADR_(const struct msghdr_c *)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct cheriabi_setlogin_args {
	char namebuf_l_[PADL_(const char *__capability)]; const char *__capability namebuf; char namebuf_r_[PADR_(const char *__capability)];
};
struct cheriabi_sigaltstack_args {
	char ss_l_[PADL_(const cheriabi_stack_t *)]; const cheriabi_stack_t * ss; char ss_r_[PADR_(const cheriabi_stack_t *)];
	char oss_l_[PADL_(cheriabi_stack_t *)]; cheriabi_stack_t * oss; char oss_r_[PADR_(cheriabi_stack_t *)];
};
struct cheriabi_ioctl_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char com_l_[PADL_(u_long)]; u_long com; char com_r_[PADR_(u_long)];
	char data_l_[PADL_(void *)]; void * data; char data_r_[PADR_(void *)];
};
struct cheriabi_execve_args {
	char fname_l_[PADL_(const char *)]; const char * fname; char fname_r_[PADR_(const char *)];
	char argv_l_[PADL_(void *__capability *)]; void *__capability * argv; char argv_r_[PADR_(void *__capability *)];
	char envv_l_[PADL_(void *__capability *)]; void *__capability * envv; char envv_r_[PADR_(void *__capability *)];
};
struct cheriabi_mprotect_args {
	char addr_l_[PADL_(const void *)]; const void * addr; char addr_r_[PADR_(const void *)];
	char len_l_[PADL_(size_t)]; size_t len; char len_r_[PADR_(size_t)];
	char prot_l_[PADL_(int)]; int prot; char prot_r_[PADR_(int)];
};
struct cheriabi_madvise_args {
	char addr_l_[PADL_(void *)]; void * addr; char addr_r_[PADR_(void *)];
	char len_l_[PADL_(size_t)]; size_t len; char len_r_[PADR_(size_t)];
	char behav_l_[PADL_(int)]; int behav; char behav_r_[PADR_(int)];
};
struct cheriabi_readv_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char iovp_l_[PADL_(struct iovec_c *)]; struct iovec_c * iovp; char iovp_r_[PADR_(struct iovec_c *)];
	char iovcnt_l_[PADL_(u_int)]; u_int iovcnt; char iovcnt_r_[PADR_(u_int)];
};
struct cheriabi_writev_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char iovp_l_[PADL_(struct iovec_c *)]; struct iovec_c * iovp; char iovp_r_[PADR_(struct iovec_c *)];
	char iovcnt_l_[PADL_(u_int)]; u_int iovcnt; char iovcnt_r_[PADR_(u_int)];
};
struct cheriabi_rmdir_args {
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
};
struct cheriabi_quotactl_args {
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char uid_l_[PADL_(int)]; int uid; char uid_r_[PADR_(int)];
	char arg_l_[PADL_(void *__capability)]; void *__capability arg; char arg_r_[PADR_(void *__capability)];
};
struct cheriabi_nlm_syscall_args {
	char debug_level_l_[PADL_(int)]; int debug_level; char debug_level_r_[PADR_(int)];
	char grace_period_l_[PADL_(int)]; int grace_period; char grace_period_r_[PADR_(int)];
	char addr_count_l_[PADL_(int)]; int addr_count; char addr_count_r_[PADR_(int)];
	char addrs_l_[PADL_(void *__capability *)]; void *__capability * addrs; char addrs_r_[PADR_(void *__capability *)];
};
struct cheriabi_nfssvc_args {
	char flag_l_[PADL_(int)]; int flag; char flag_r_[PADR_(int)];
	char argp_l_[PADL_(void *__capability)]; void *__capability argp; char argp_r_[PADR_(void *__capability)];
};
struct cheriabi_sysarch_args {
	char op_l_[PADL_(int)]; int op; char op_r_[PADR_(int)];
	char parms_l_[PADL_(char *)]; char * parms; char parms_r_[PADR_(char *)];
};
struct cheriabi_ktimer_create_args {
	char clock_id_l_[PADL_(clockid_t)]; clockid_t clock_id; char clock_id_r_[PADR_(clockid_t)];
	char evp_l_[PADL_(struct sigevent_c *)]; struct sigevent_c * evp; char evp_r_[PADR_(struct sigevent_c *)];
	char timerid_l_[PADL_(int *)]; int * timerid; char timerid_r_[PADR_(int *)];
};
struct cheriabi_aio_read_args {
	char aiocbp_l_[PADL_(struct aiocb_c *__capability)]; struct aiocb_c *__capability aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *__capability)];
};
struct cheriabi_aio_write_args {
	char aiocbp_l_[PADL_(struct aiocb_c *__capability)]; struct aiocb_c *__capability aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *__capability)];
};
struct cheriabi_lio_listio_args {
	char mode_l_[PADL_(int)]; int mode; char mode_r_[PADR_(int)];
	char acb_list_l_[PADL_(struct aiocb_c *const __capability *)]; struct aiocb_c *const __capability * acb_list; char acb_list_r_[PADR_(struct aiocb_c *const __capability *)];
	char nent_l_[PADL_(int)]; int nent; char nent_r_[PADR_(int)];
	char sig_l_[PADL_(struct sigevent_c *)]; struct sigevent_c * sig; char sig_r_[PADR_(struct sigevent_c *)];
};
struct cheriabi_kbounce_args {
	char src_l_[PADL_(const void *__capability)]; const void *__capability src; char src_r_[PADR_(const void *__capability)];
	char dst_l_[PADL_(void *__capability)]; void *__capability dst; char dst_r_[PADR_(void *__capability)];
	char len_l_[PADL_(size_t)]; size_t len; char len_r_[PADR_(size_t)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct cheriabi_preadv_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char iovp_l_[PADL_(struct iovec_c *)]; struct iovec_c * iovp; char iovp_r_[PADR_(struct iovec_c *)];
	char iovcnt_l_[PADL_(u_int)]; u_int iovcnt; char iovcnt_r_[PADR_(u_int)];
	char offset_l_[PADL_(off_t)]; off_t offset; char offset_r_[PADR_(off_t)];
};
struct cheriabi_pwritev_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char iovp_l_[PADL_(struct iovec_c *)]; struct iovec_c * iovp; char iovp_r_[PADR_(struct iovec_c *)];
	char iovcnt_l_[PADL_(u_int)]; u_int iovcnt; char iovcnt_r_[PADR_(u_int)];
	char offset_l_[PADL_(off_t)]; off_t offset; char offset_r_[PADR_(off_t)];
};
struct cheriabi_kldstat_args {
	char fileid_l_[PADL_(int)]; int fileid; char fileid_r_[PADR_(int)];
	char stat_l_[PADL_(struct kld_file_stat_c *)]; struct kld_file_stat_c * stat; char stat_r_[PADR_(struct kld_file_stat_c *)];
};
struct cheriabi_aio_return_args {
	char aiocbp_l_[PADL_(struct aiocb_c *__capability)]; struct aiocb_c *__capability aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *__capability)];
};
struct cheriabi_aio_suspend_args {
	char aiocbp_l_[PADL_(struct aiocb_c *const __capability *)]; struct aiocb_c *const __capability * aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *const __capability *)];
	char nent_l_[PADL_(int)]; int nent; char nent_r_[PADR_(int)];
	char timeout_l_[PADL_(const struct timespec *)]; const struct timespec * timeout; char timeout_r_[PADR_(const struct timespec *)];
};
struct cheriabi_aio_cancel_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char aiocbp_l_[PADL_(struct aiocb_c *)]; struct aiocb_c * aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *)];
};
struct cheriabi_aio_error_args {
	char aiocbp_l_[PADL_(struct aiocb_c *)]; struct aiocb_c * aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *)];
};
struct cheriabi_kldsym_args {
	char fileid_l_[PADL_(int)]; int fileid; char fileid_r_[PADR_(int)];
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char data_l_[PADL_(struct kld_sym_lookup_c *)]; struct kld_sym_lookup_c * data; char data_r_[PADR_(struct kld_sym_lookup_c *)];
};
struct cheriabi_jail_args {
	char jailp_l_[PADL_(struct jail_c *)]; struct jail_c * jailp; char jailp_r_[PADR_(struct jail_c *)];
};
struct cheriabi_sigtimedwait_args {
	char set_l_[PADL_(const sigset_t *)]; const sigset_t * set; char set_r_[PADR_(const sigset_t *)];
	char info_l_[PADL_(struct siginfo_c *)]; struct siginfo_c * info; char info_r_[PADR_(struct siginfo_c *)];
	char timeout_l_[PADL_(const struct timespec *)]; const struct timespec * timeout; char timeout_r_[PADR_(const struct timespec *)];
};
struct cheriabi_sigwaitinfo_args {
	char set_l_[PADL_(const sigset_t *)]; const sigset_t * set; char set_r_[PADR_(const sigset_t *)];
	char info_l_[PADL_(struct siginfo_c *)]; struct siginfo_c * info; char info_r_[PADR_(struct siginfo_c *)];
};
struct cheriabi_aio_waitcomplete_args {
	char aiocbp_l_[PADL_(struct aiocb_c *__capability *)]; struct aiocb_c *__capability * aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *__capability *)];
	char timeout_l_[PADL_(struct timespec *)]; struct timespec * timeout; char timeout_r_[PADR_(struct timespec *)];
};
struct cheriabi_nmount_args {
	char iovp_l_[PADL_(struct iovec_c *)]; struct iovec_c * iovp; char iovp_r_[PADR_(struct iovec_c *)];
	char iovcnt_l_[PADL_(unsigned int)]; unsigned int iovcnt; char iovcnt_r_[PADR_(unsigned int)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct cheriabi___mac_get_proc_args {
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi___mac_set_proc_args {
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi___mac_get_fd_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi___mac_get_file_args {
	char path_p_l_[PADL_(const char *)]; const char * path_p; char path_p_r_[PADR_(const char *)];
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi___mac_set_fd_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi___mac_set_file_args {
	char path_p_l_[PADL_(const char *)]; const char * path_p; char path_p_r_[PADR_(const char *)];
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi_kenv_args {
	char what_l_[PADL_(int)]; int what; char what_r_[PADR_(int)];
	char name_l_[PADL_(const char *__capability)]; const char *__capability name; char name_r_[PADR_(const char *__capability)];
	char value_l_[PADL_(char *__capability)]; char *__capability value; char value_r_[PADR_(char *__capability)];
	char len_l_[PADL_(int)]; int len; char len_r_[PADR_(int)];
};
struct cheriabi_sendfile_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char s_l_[PADL_(int)]; int s; char s_r_[PADR_(int)];
	char offset_l_[PADL_(off_t)]; off_t offset; char offset_r_[PADR_(off_t)];
	char nbytes_l_[PADL_(size_t)]; size_t nbytes; char nbytes_r_[PADR_(size_t)];
	char hdtr_l_[PADL_(struct sf_hdtr_c *)]; struct sf_hdtr_c * hdtr; char hdtr_r_[PADR_(struct sf_hdtr_c *)];
	char sbytes_l_[PADL_(off_t *)]; off_t * sbytes; char sbytes_r_[PADR_(off_t *)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct cheriabi_mac_syscall_args {
	char policy_l_[PADL_(const char *__capability)]; const char *__capability policy; char policy_r_[PADR_(const char *__capability)];
	char call_l_[PADL_(int)]; int call; char call_r_[PADR_(int)];
	char arg_l_[PADL_(void *__capability)]; void *__capability arg; char arg_r_[PADR_(void *__capability)];
};
struct cheriabi___mac_get_pid_args {
	char pid_l_[PADL_(pid_t)]; pid_t pid; char pid_r_[PADR_(pid_t)];
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi___mac_get_link_args {
	char path_p_l_[PADL_(const char *)]; const char * path_p; char path_p_r_[PADR_(const char *)];
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi___mac_set_link_args {
	char path_p_l_[PADL_(const char *)]; const char * path_p; char path_p_r_[PADR_(const char *)];
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi___mac_execve_args {
	char fname_l_[PADL_(char *)]; char * fname; char fname_r_[PADR_(char *)];
	char argv_l_[PADL_(void *__capability *)]; void *__capability * argv; char argv_r_[PADR_(void *__capability *)];
	char envv_l_[PADL_(void *__capability *)]; void *__capability * envv; char envv_r_[PADR_(void *__capability *)];
	char mac_p_l_[PADL_(struct mac_c *)]; struct mac_c * mac_p; char mac_p_r_[PADR_(struct mac_c *)];
};
struct cheriabi_sigaction_args {
	char sig_l_[PADL_(int)]; int sig; char sig_r_[PADR_(int)];
	char act_l_[PADL_(struct sigaction_c *)]; struct sigaction_c * act; char act_r_[PADR_(struct sigaction_c *)];
	char oact_l_[PADL_(struct sigaction_c *)]; struct sigaction_c * oact; char oact_r_[PADR_(struct sigaction_c *)];
};
struct cheriabi_sigreturn_args {
	char sigcntxp_l_[PADL_(const ucontext_c_t *)]; const ucontext_c_t * sigcntxp; char sigcntxp_r_[PADR_(const ucontext_c_t *)];
};
struct cheriabi_getcontext_args {
	char ucp_l_[PADL_(ucontext_c_t *)]; ucontext_c_t * ucp; char ucp_r_[PADR_(ucontext_c_t *)];
};
struct cheriabi_setcontext_args {
	char ucp_l_[PADL_(const ucontext_c_t *)]; const ucontext_c_t * ucp; char ucp_r_[PADR_(const ucontext_c_t *)];
};
struct cheriabi_swapcontext_args {
	char oucp_l_[PADL_(ucontext_c_t *)]; ucontext_c_t * oucp; char oucp_r_[PADR_(ucontext_c_t *)];
	char ucp_l_[PADL_(const ucontext_c_t *)]; const ucontext_c_t * ucp; char ucp_r_[PADR_(const ucontext_c_t *)];
};
struct cheriabi_thr_create_args {
	char ctx_l_[PADL_(ucontext_c_t *)]; ucontext_c_t * ctx; char ctx_r_[PADR_(ucontext_c_t *)];
	char id_l_[PADL_(long *)]; long * id; char id_r_[PADR_(long *)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct cheriabi_auditon_args {
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char data_l_[PADL_(void *__capability)]; void *__capability data; char data_r_[PADR_(void *__capability)];
	char length_l_[PADL_(u_int)]; u_int length; char length_r_[PADR_(u_int)];
};
struct cheriabi_thr_new_args {
	char param_l_[PADL_(struct thr_param_c *)]; struct thr_param_c * param; char param_r_[PADR_(struct thr_param_c *)];
	char param_size_l_[PADL_(int)]; int param_size; char param_size_r_[PADR_(int)];
};
struct cheriabi_sigqueue_args {
	char pid_l_[PADL_(pid_t)]; pid_t pid; char pid_r_[PADR_(pid_t)];
	char signum_l_[PADL_(int)]; int signum; char signum_r_[PADR_(int)];
	char value_l_[PADL_(void *)]; void * value; char value_r_[PADR_(void *)];
};
struct cheriabi_kmq_notify_args {
	char mqd_l_[PADL_(int)]; int mqd; char mqd_r_[PADR_(int)];
	char sigev_l_[PADL_(const struct sigevent_c *)]; const struct sigevent_c * sigev; char sigev_r_[PADR_(const struct sigevent_c *)];
};
struct cheriabi_abort2_args {
	char why_l_[PADL_(const char *)]; const char * why; char why_r_[PADR_(const char *)];
	char nargs_l_[PADL_(int)]; int nargs; char nargs_r_[PADR_(int)];
	char args_l_[PADL_(void *__capability *)]; void *__capability * args; char args_r_[PADR_(void *__capability *)];
};
struct cheriabi_aio_fsync_args {
	char op_l_[PADL_(int)]; int op; char op_r_[PADR_(int)];
	char aiocbp_l_[PADL_(struct aiocb_c *__capability)]; struct aiocb_c *__capability aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *__capability)];
};
struct cheriabi_mmap_args {
	char addr_l_[PADL_(void *)]; void * addr; char addr_r_[PADR_(void *)];
	char len_l_[PADL_(size_t)]; size_t len; char len_r_[PADR_(size_t)];
	char prot_l_[PADL_(int)]; int prot; char prot_r_[PADR_(int)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char pos_l_[PADL_(off_t)]; off_t pos; char pos_r_[PADR_(off_t)];
};
struct cheriabi_fexecve_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char argv_l_[PADL_(void *__capability *)]; void *__capability * argv; char argv_r_[PADR_(void *__capability *)];
	char envv_l_[PADL_(void *__capability *)]; void *__capability * envv; char envv_r_[PADR_(void *__capability *)];
};
struct cheriabi_linkat_args {
	char fd1_l_[PADL_(int)]; int fd1; char fd1_r_[PADR_(int)];
	char path1_l_[PADL_(const char *__capability)]; const char *__capability path1; char path1_r_[PADR_(const char *__capability)];
	char fd2_l_[PADL_(int)]; int fd2; char fd2_r_[PADR_(int)];
	char path2_l_[PADL_(const char *__capability)]; const char *__capability path2; char path2_r_[PADR_(const char *__capability)];
	char flag_l_[PADL_(int)]; int flag; char flag_r_[PADR_(int)];
};
struct cheriabi_openat_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
	char flag_l_[PADL_(int)]; int flag; char flag_r_[PADR_(int)];
	char mode_l_[PADL_(mode_t)]; mode_t mode; char mode_r_[PADR_(mode_t)];
};
struct cheriabi_unlinkat_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char path_l_[PADL_(const char *__capability)]; const char *__capability path; char path_r_[PADR_(const char *__capability)];
	char flag_l_[PADL_(int)]; int flag; char flag_r_[PADR_(int)];
};
struct cheriabi_jail_get_args {
	char iovp_l_[PADL_(struct iovec_c *)]; struct iovec_c * iovp; char iovp_r_[PADR_(struct iovec_c *)];
	char iovcnt_l_[PADL_(unsigned int)]; unsigned int iovcnt; char iovcnt_r_[PADR_(unsigned int)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct cheriabi_jail_set_args {
	char iovp_l_[PADL_(struct iovec_c *)]; struct iovec_c * iovp; char iovp_r_[PADR_(struct iovec_c *)];
	char iovcnt_l_[PADL_(unsigned int)]; unsigned int iovcnt; char iovcnt_r_[PADR_(unsigned int)];
	char flags_l_[PADL_(int)]; int flags; char flags_r_[PADR_(int)];
};
struct cheriabi___semctl_args {
	char semid_l_[PADL_(int)]; int semid; char semid_r_[PADR_(int)];
	char semnum_l_[PADL_(int)]; int semnum; char semnum_r_[PADR_(int)];
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char arg_l_[PADL_(union semun_c *)]; union semun_c * arg; char arg_r_[PADR_(union semun_c *)];
};
struct cheriabi_msgctl_args {
	char msqid_l_[PADL_(int)]; int msqid; char msqid_r_[PADR_(int)];
	char cmd_l_[PADL_(int)]; int cmd; char cmd_r_[PADR_(int)];
	char buf_l_[PADL_(struct msqid_ds_c *)]; struct msqid_ds_c * buf; char buf_r_[PADR_(struct msqid_ds_c *)];
};
struct cheriabi_wait6_args {
	char idtype_l_[PADL_(int)]; int idtype; char idtype_r_[PADR_(int)];
	char id_l_[PADL_(id_t)]; id_t id; char id_r_[PADR_(id_t)];
	char status_l_[PADL_(int *)]; int * status; char status_r_[PADR_(int *)];
	char options_l_[PADL_(int)]; int options; char options_r_[PADR_(int)];
	char wrusage_l_[PADL_(struct __wrusage *)]; struct __wrusage * wrusage; char wrusage_r_[PADR_(struct __wrusage *)];
	char info_l_[PADL_(struct siginfo_c *)]; struct siginfo_c * info; char info_r_[PADR_(struct siginfo_c *)];
};
struct cheriabi_aio_mlock_args {
	char aiocbp_l_[PADL_(struct aiocb_c *__capability)]; struct aiocb_c *__capability aiocbp; char aiocbp_r_[PADR_(struct aiocb_c *__capability)];
};
struct cheriabi_procctl_args {
	char idtype_l_[PADL_(int)]; int idtype; char idtype_r_[PADR_(int)];
	char id_l_[PADL_(id_t)]; id_t id; char id_r_[PADR_(id_t)];
	char com_l_[PADL_(int)]; int com; char com_r_[PADR_(int)];
	char data_l_[PADL_(void *)]; void * data; char data_r_[PADR_(void *)];
};
struct cheriabi_kevent_args {
	char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
	char changelist_l_[PADL_(const struct kevent_c *)]; const struct kevent_c * changelist; char changelist_r_[PADR_(const struct kevent_c *)];
	char nchanges_l_[PADL_(int)]; int nchanges; char nchanges_r_[PADR_(int)];
	char eventlist_l_[PADL_(struct kevent_c *)]; struct kevent_c * eventlist; char eventlist_r_[PADR_(struct kevent_c *)];
	char nevents_l_[PADL_(int)]; int nevents; char nevents_r_[PADR_(int)];
	char timeout_l_[PADL_(const struct timespec *)]; const struct timespec * timeout; char timeout_r_[PADR_(const struct timespec *)];
};
struct cheriabi_coexecve_args {
	char pid_l_[PADL_(pid_t)]; pid_t pid; char pid_r_[PADR_(pid_t)];
	char fname_l_[PADL_(const char *)]; const char * fname; char fname_r_[PADR_(const char *)];
	char argv_l_[PADL_(void *__capability *)]; void *__capability * argv; char argv_r_[PADR_(void *__capability *)];
	char envv_l_[PADL_(void *__capability *)]; void *__capability * envv; char envv_r_[PADR_(void *__capability *)];
};
#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif
int	cheriabi_syscall(struct thread *, struct cheriabi_syscall_args *);
int	cheriabi_open(struct thread *, struct cheriabi_open_args *);
int	cheriabi_link(struct thread *, struct cheriabi_link_args *);
int	cheriabi_unlink(struct thread *, struct cheriabi_unlink_args *);
int	cheriabi_chdir(struct thread *, struct cheriabi_chdir_args *);
int	cheriabi_mount(struct thread *, struct cheriabi_mount_args *);
int	cheriabi_recvmsg(struct thread *, struct cheriabi_recvmsg_args *);
int	cheriabi_sendmsg(struct thread *, struct cheriabi_sendmsg_args *);
int	cheriabi_setlogin(struct thread *, struct cheriabi_setlogin_args *);
int	cheriabi_sigaltstack(struct thread *, struct cheriabi_sigaltstack_args *);
int	cheriabi_ioctl(struct thread *, struct cheriabi_ioctl_args *);
int	cheriabi_execve(struct thread *, struct cheriabi_execve_args *);
int	cheriabi_mprotect(struct thread *, struct cheriabi_mprotect_args *);
int	cheriabi_madvise(struct thread *, struct cheriabi_madvise_args *);
int	cheriabi_readv(struct thread *, struct cheriabi_readv_args *);
int	cheriabi_writev(struct thread *, struct cheriabi_writev_args *);
int	cheriabi_rmdir(struct thread *, struct cheriabi_rmdir_args *);
int	cheriabi_quotactl(struct thread *, struct cheriabi_quotactl_args *);
int	cheriabi_nlm_syscall(struct thread *, struct cheriabi_nlm_syscall_args *);
int	cheriabi_nfssvc(struct thread *, struct cheriabi_nfssvc_args *);
int	cheriabi_sysarch(struct thread *, struct cheriabi_sysarch_args *);
int	cheriabi_ktimer_create(struct thread *, struct cheriabi_ktimer_create_args *);
int	cheriabi_aio_read(struct thread *, struct cheriabi_aio_read_args *);
int	cheriabi_aio_write(struct thread *, struct cheriabi_aio_write_args *);
int	cheriabi_lio_listio(struct thread *, struct cheriabi_lio_listio_args *);
int	cheriabi_kbounce(struct thread *, struct cheriabi_kbounce_args *);
int	cheriabi_preadv(struct thread *, struct cheriabi_preadv_args *);
int	cheriabi_pwritev(struct thread *, struct cheriabi_pwritev_args *);
int	cheriabi_kldstat(struct thread *, struct cheriabi_kldstat_args *);
int	cheriabi_aio_return(struct thread *, struct cheriabi_aio_return_args *);
int	cheriabi_aio_suspend(struct thread *, struct cheriabi_aio_suspend_args *);
int	cheriabi_aio_cancel(struct thread *, struct cheriabi_aio_cancel_args *);
int	cheriabi_aio_error(struct thread *, struct cheriabi_aio_error_args *);
int	cheriabi_kldsym(struct thread *, struct cheriabi_kldsym_args *);
int	cheriabi_jail(struct thread *, struct cheriabi_jail_args *);
int	cheriabi_sigtimedwait(struct thread *, struct cheriabi_sigtimedwait_args *);
int	cheriabi_sigwaitinfo(struct thread *, struct cheriabi_sigwaitinfo_args *);
int	cheriabi_aio_waitcomplete(struct thread *, struct cheriabi_aio_waitcomplete_args *);
int	cheriabi_nmount(struct thread *, struct cheriabi_nmount_args *);
int	cheriabi___mac_get_proc(struct thread *, struct cheriabi___mac_get_proc_args *);
int	cheriabi___mac_set_proc(struct thread *, struct cheriabi___mac_set_proc_args *);
int	cheriabi___mac_get_fd(struct thread *, struct cheriabi___mac_get_fd_args *);
int	cheriabi___mac_get_file(struct thread *, struct cheriabi___mac_get_file_args *);
int	cheriabi___mac_set_fd(struct thread *, struct cheriabi___mac_set_fd_args *);
int	cheriabi___mac_set_file(struct thread *, struct cheriabi___mac_set_file_args *);
int	cheriabi_kenv(struct thread *, struct cheriabi_kenv_args *);
int	cheriabi_sendfile(struct thread *, struct cheriabi_sendfile_args *);
int	cheriabi_mac_syscall(struct thread *, struct cheriabi_mac_syscall_args *);
int	cheriabi___mac_get_pid(struct thread *, struct cheriabi___mac_get_pid_args *);
int	cheriabi___mac_get_link(struct thread *, struct cheriabi___mac_get_link_args *);
int	cheriabi___mac_set_link(struct thread *, struct cheriabi___mac_set_link_args *);
int	cheriabi___mac_execve(struct thread *, struct cheriabi___mac_execve_args *);
int	cheriabi_sigaction(struct thread *, struct cheriabi_sigaction_args *);
int	cheriabi_sigreturn(struct thread *, struct cheriabi_sigreturn_args *);
int	cheriabi_getcontext(struct thread *, struct cheriabi_getcontext_args *);
int	cheriabi_setcontext(struct thread *, struct cheriabi_setcontext_args *);
int	cheriabi_swapcontext(struct thread *, struct cheriabi_swapcontext_args *);
int	cheriabi_thr_create(struct thread *, struct cheriabi_thr_create_args *);
int	cheriabi_auditon(struct thread *, struct cheriabi_auditon_args *);
int	cheriabi_thr_new(struct thread *, struct cheriabi_thr_new_args *);
int	cheriabi_sigqueue(struct thread *, struct cheriabi_sigqueue_args *);
int	cheriabi_kmq_notify(struct thread *, struct cheriabi_kmq_notify_args *);
int	cheriabi_abort2(struct thread *, struct cheriabi_abort2_args *);
int	cheriabi_aio_fsync(struct thread *, struct cheriabi_aio_fsync_args *);
int	cheriabi_mmap(struct thread *, struct cheriabi_mmap_args *);
int	cheriabi_fexecve(struct thread *, struct cheriabi_fexecve_args *);
int	cheriabi_linkat(struct thread *, struct cheriabi_linkat_args *);
int	cheriabi_openat(struct thread *, struct cheriabi_openat_args *);
int	cheriabi_unlinkat(struct thread *, struct cheriabi_unlinkat_args *);
int	cheriabi_jail_get(struct thread *, struct cheriabi_jail_get_args *);
int	cheriabi_jail_set(struct thread *, struct cheriabi_jail_set_args *);
int	cheriabi___semctl(struct thread *, struct cheriabi___semctl_args *);
int	cheriabi_msgctl(struct thread *, struct cheriabi_msgctl_args *);
int	cheriabi_wait6(struct thread *, struct cheriabi_wait6_args *);
int	cheriabi_aio_mlock(struct thread *, struct cheriabi_aio_mlock_args *);
int	cheriabi_procctl(struct thread *, struct cheriabi_procctl_args *);
int	cheriabi_kevent(struct thread *, struct cheriabi_kevent_args *);
int	cheriabi_coexecve(struct thread *, struct cheriabi_coexecve_args *);

#ifdef COMPAT_43

#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif

#endif /* COMPAT_43 */


#ifdef COMPAT_FREEBSD4

#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif

#endif /* COMPAT_FREEBSD4 */


#ifdef COMPAT_FREEBSD6

#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif

#endif /* COMPAT_FREEBSD6 */


#ifdef COMPAT_FREEBSD7

#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif

#endif /* COMPAT_FREEBSD7 */


#ifdef COMPAT_FREEBSD10

#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif

#endif /* COMPAT_FREEBSD10 */


#ifdef COMPAT_FREEBSD11

#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif

#endif /* COMPAT_FREEBSD11 */

#define	CHERIABI_SYS_AUE_cheriabi_syscall	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_open	AUE_OPEN_RWTC
#define	CHERIABI_SYS_AUE_cheriabi_link	AUE_LINK
#define	CHERIABI_SYS_AUE_cheriabi_unlink	AUE_UNLINK
#define	CHERIABI_SYS_AUE_cheriabi_chdir	AUE_CHDIR
#define	CHERIABI_SYS_AUE_cheriabi_mount	AUE_MOUNT
#define	CHERIABI_SYS_AUE_cheriabi_recvmsg	AUE_RECVMSG
#define	CHERIABI_SYS_AUE_cheriabi_sendmsg	AUE_SENDMSG
#define	CHERIABI_SYS_AUE_cheriabi_setlogin	AUE_SETLOGIN
#define	CHERIABI_SYS_AUE_cheriabi_sigaltstack	AUE_SIGALTSTACK
#define	CHERIABI_SYS_AUE_cheriabi_ioctl	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_execve	AUE_EXECVE
#define	CHERIABI_SYS_AUE_cheriabi_mprotect	AUE_MPROTECT
#define	CHERIABI_SYS_AUE_cheriabi_madvise	AUE_MADVISE
#define	CHERIABI_SYS_AUE_cheriabi_readv	AUE_READV
#define	CHERIABI_SYS_AUE_cheriabi_writev	AUE_WRITEV
#define	CHERIABI_SYS_AUE_cheriabi_rmdir	AUE_RMDIR
#define	CHERIABI_SYS_AUE_cheriabi_quotactl	AUE_QUOTACTL
#define	CHERIABI_SYS_AUE_cheriabi_nlm_syscall	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_nfssvc	AUE_NFS_SVC
#define	CHERIABI_SYS_AUE_cheriabi_sysarch	AUE_SYSARCH
#define	CHERIABI_SYS_AUE_cheriabi_ktimer_create	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_aio_read	AUE_AIO_READ
#define	CHERIABI_SYS_AUE_cheriabi_aio_write	AUE_AIO_WRITE
#define	CHERIABI_SYS_AUE_cheriabi_lio_listio	AUE_LIO_LISTIO
#define	CHERIABI_SYS_AUE_cheriabi_kbounce	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_preadv	AUE_PREADV
#define	CHERIABI_SYS_AUE_cheriabi_pwritev	AUE_PWRITEV
#define	CHERIABI_SYS_AUE_cheriabi_kldstat	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_aio_return	AUE_AIO_RETURN
#define	CHERIABI_SYS_AUE_cheriabi_aio_suspend	AUE_AIO_SUSPEND
#define	CHERIABI_SYS_AUE_cheriabi_aio_cancel	AUE_AIO_CANCEL
#define	CHERIABI_SYS_AUE_cheriabi_aio_error	AUE_AIO_ERROR
#define	CHERIABI_SYS_AUE_cheriabi_kldsym	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_jail	AUE_JAIL
#define	CHERIABI_SYS_AUE_cheriabi_sigtimedwait	AUE_SIGWAIT
#define	CHERIABI_SYS_AUE_cheriabi_sigwaitinfo	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_aio_waitcomplete	AUE_AIO_WAITCOMPLETE
#define	CHERIABI_SYS_AUE_cheriabi_nmount	AUE_NMOUNT
#define	CHERIABI_SYS_AUE_cheriabi___mac_get_proc	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_set_proc	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_get_fd	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_get_file	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_set_fd	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_set_file	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_kenv	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_sendfile	AUE_SENDFILE
#define	CHERIABI_SYS_AUE_cheriabi_mac_syscall	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_get_pid	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_get_link	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_set_link	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi___mac_execve	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_sigaction	AUE_SIGACTION
#define	CHERIABI_SYS_AUE_cheriabi_sigreturn	AUE_SIGRETURN
#define	CHERIABI_SYS_AUE_cheriabi_getcontext	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_setcontext	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_swapcontext	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_thr_create	AUE_THR_CREATE
#define	CHERIABI_SYS_AUE_cheriabi_auditon	AUE_AUDITON
#define	CHERIABI_SYS_AUE_cheriabi_thr_new	AUE_THR_NEW
#define	CHERIABI_SYS_AUE_cheriabi_sigqueue	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_kmq_notify	AUE_MQ_NOTIFY
#define	CHERIABI_SYS_AUE_cheriabi_abort2	AUE_NULL
#define	CHERIABI_SYS_AUE_cheriabi_aio_fsync	AUE_AIO_FSYNC
#define	CHERIABI_SYS_AUE_cheriabi_mmap	AUE_MMAP
#define	CHERIABI_SYS_AUE_cheriabi_fexecve	AUE_FEXECVE
#define	CHERIABI_SYS_AUE_cheriabi_linkat	AUE_LINKAT
#define	CHERIABI_SYS_AUE_cheriabi_openat	AUE_OPENAT_RWTC
#define	CHERIABI_SYS_AUE_cheriabi_unlinkat	AUE_UNLINKAT
#define	CHERIABI_SYS_AUE_cheriabi_jail_get	AUE_JAIL_GET
#define	CHERIABI_SYS_AUE_cheriabi_jail_set	AUE_JAIL_SET
#define	CHERIABI_SYS_AUE_cheriabi___semctl	AUE_SEMCTL
#define	CHERIABI_SYS_AUE_cheriabi_msgctl	AUE_MSGCTL
#define	CHERIABI_SYS_AUE_cheriabi_wait6	AUE_WAIT6
#define	CHERIABI_SYS_AUE_cheriabi_aio_mlock	AUE_AIO_MLOCK
#define	CHERIABI_SYS_AUE_cheriabi_procctl	AUE_PROCCTL
#define	CHERIABI_SYS_AUE_cheriabi_kevent	AUE_KEVENT
#define	CHERIABI_SYS_AUE_cheriabi_coexecve	AUE_NULL

#undef PAD_
#undef PADL_
#undef PADR_

#endif /* !_CHERIABI_PROTO_H_ */
