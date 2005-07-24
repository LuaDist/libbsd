#ifndef LIBPORT_H
#define LIBPORT_H

#define setproctitle(fmt, args...)

#define __dead2
#define __printflike(x,y)
#define __FBSDID(x)

#include <sys/cdefs.h>
#include <sys/queue.h>


typedef char *                  __va_list;
#if !defined(__GNUC_VA_LIST)
#define __GNUC_VA_LIST
typedef __va_list               __gnuc_va_list; /* compatibility w/GNU headers*/
#endif


/*
 * Missing BSD sys/queue.h definitions
 */

/*
 * Singly-linked Tail queue declarations.
 */
#define	STAILQ_HEAD(name, type)						\
struct name {								\
	struct type *stqh_first;/* first element */			\
	struct type **stqh_last;/* addr of last next element */		\
}

#define	STAILQ_HEAD_INITIALIZER(head)					\
	{ NULL, &(head).stqh_first }

#define	STAILQ_ENTRY(type)						\
struct {								\
	struct type *stqe_next;	/* next element */			\
}

/*
 * Singly-linked Tail queue functions.
 */
#define	STAILQ_CONCAT(head1, head2) do {				\
	if (!STAILQ_EMPTY((head2))) {					\
		*(head1)->stqh_last = (head2)->stqh_first;		\
		(head1)->stqh_last = (head2)->stqh_last;		\
		STAILQ_INIT((head2));					\
	}								\
} while (0)

#define	STAILQ_EMPTY(head)	((head)->stqh_first == NULL)

#define	STAILQ_FIRST(head)	((head)->stqh_first)

#define	STAILQ_FOREACH(var, head, field)				\
	for((var) = STAILQ_FIRST((head));				\
	   (var);							\
	   (var) = STAILQ_NEXT((var), field))

#define	STAILQ_INIT(head) do {						\
	STAILQ_FIRST((head)) = NULL;					\
	(head)->stqh_last = &STAILQ_FIRST((head));			\
} while (0)

#define	STAILQ_INSERT_AFTER(head, tqelm, elm, field) do {		\
	if ((STAILQ_NEXT((elm), field) = STAILQ_NEXT((tqelm), field)) == NULL)\
		(head)->stqh_last = &STAILQ_NEXT((elm), field);		\
	STAILQ_NEXT((tqelm), field) = (elm);				\
} while (0)

#define	STAILQ_INSERT_HEAD(head, elm, field) do {			\
	if ((STAILQ_NEXT((elm), field) = STAILQ_FIRST((head))) == NULL)	\
		(head)->stqh_last = &STAILQ_NEXT((elm), field);		\
	STAILQ_FIRST((head)) = (elm);					\
} while (0)

#define	STAILQ_INSERT_TAIL(head, elm, field) do {			\
	STAILQ_NEXT((elm), field) = NULL;				\
	*(head)->stqh_last = (elm);					\
	(head)->stqh_last = &STAILQ_NEXT((elm), field);			\
} while (0)

#define	STAILQ_LAST(head, type, field)					\
	(STAILQ_EMPTY((head)) ?						\
		NULL :							\
	        ((struct type *)					\
		((char *)((head)->stqh_last) - __offsetof(struct type, field))))

#define	STAILQ_NEXT(elm, field)	((elm)->field.stqe_next)

#define	STAILQ_REMOVE(head, elm, type, field) do {			\
	if (STAILQ_FIRST((head)) == (elm)) {				\
		STAILQ_REMOVE_HEAD((head), field);			\
	}								\
	else {								\
		struct type *curelm = STAILQ_FIRST((head));		\
		while (STAILQ_NEXT(curelm, field) != (elm))		\
			curelm = STAILQ_NEXT(curelm, field);		\
		if ((STAILQ_NEXT(curelm, field) =			\
		     STAILQ_NEXT(STAILQ_NEXT(curelm, field), field)) == NULL)\
			(head)->stqh_last = &STAILQ_NEXT((curelm), field);\
	}								\
} while (0)

#define	STAILQ_REMOVE_HEAD(head, field) do {				\
	if ((STAILQ_FIRST((head)) =					\
	     STAILQ_NEXT(STAILQ_FIRST((head)), field)) == NULL)		\
		(head)->stqh_last = &STAILQ_FIRST((head));		\
} while (0)

#define	STAILQ_REMOVE_HEAD_UNTIL(head, elm, field) do {			\
	if ((STAILQ_FIRST((head)) = STAILQ_NEXT((elm), field)) == NULL)	\
		(head)->stqh_last = &STAILQ_FIRST((head));		\
} while (0)

/*
 * List declarations.
 */
#define	LIST_HEAD(name, type)						\
struct name {								\
	struct type *lh_first;	/* first element */			\
}

#define	LIST_HEAD_INITIALIZER(head)					\
	{ NULL }

#define	LIST_ENTRY(type)						\
struct {								\
	struct type *le_next;	/* next element */			\
	struct type **le_prev;	/* address of previous next element */	\
}

/*
 * List functions.
 */

#define	LIST_EMPTY(head)	((head)->lh_first == NULL)

#define	LIST_FIRST(head)	((head)->lh_first)

#define	LIST_FOREACH(var, head, field)					\
	for ((var) = LIST_FIRST((head));				\
	    (var);							\
	    (var) = LIST_NEXT((var), field))

#define	LIST_INSERT_BEFORE(listelm, elm, field) do {			\
	(elm)->field.le_prev = (listelm)->field.le_prev;		\
	LIST_NEXT((elm), field) = (listelm);				\
	*(listelm)->field.le_prev = (elm);				\
	(listelm)->field.le_prev = &LIST_NEXT((elm), field);		\
} while (0)

#define	LIST_NEXT(elm, field)	((elm)->field.le_next)

#define	TAILQ_FIRST(head)	((head)->tqh_first)

#define	TAILQ_FOREACH(var, head, field)					\
	for ((var) = TAILQ_FIRST((head));				\
	    (var);							\
	    (var) = TAILQ_NEXT((var), field))

#define	TAILQ_NEXT(elm, field) ((elm)->field.tqe_next)

#define	TAILQ_HEAD_INITIALIZER(head)					\
	{ NULL, &(head).tqh_first }


#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#define ICMP_TRACEROUTE         30              /* traceroute */
#define ICMP_DATACONVERR        31              /* data conversion error */
#define ICMP_MOBILE_REDIRECT    32              /* mobile host redirect */
#define ICMP_IPV6_WHEREAREYOU   33              /* IPv6 where-are-you */
#define ICMP_IPV6_IAMHERE       34              /* IPv6 i-am-here */
#define ICMP_MOBILE_REGREQUEST  35              /* mobile registration req */
#define ICMP_MOBILE_REGREPLY    36              /* mobile registration reply */
#define ICMP_SKIP               39              /* SKIP */
#define ICMP_PHOTURIS           40              /* Photuris */
#define MLD_LISTENER_QUERY              130     /* multicast listener query */
#define MLD_LISTENER_REPORT             131     /* multicast listener report */
#define MLD_LISTENER_DONE               132     /* multicast listener done */
#define ICMP6_ROUTER_RENUMBERING     138     /* router renumbering */
#define ICMP6_WRUREQUEST             139     /* who are you request */
#define ICMP6_WRUREPLY                       140     /* who are you reply */
#define ICMP6_FQDN_QUERY                139     /* FQDN query */
#define ICMP6_FQDN_REPLY                140     /* FQDN reply */
#define ICMP6_NI_QUERY                  139     /* node information request */
#define ICMP6_NI_REPLY                  140     /* node information reply */
#define MLD_MTRACE_RESP                 200     /* mtrace resp (to sender) */
#define MLD_MTRACE                      201     /* mtrace messages */
#define         ICMP_ROUTERADVERT_NORMAL                0       /* normal advertisement */
#define         ICMP_ROUTERADVERT_NOROUTE_COMMON        16      /* selective routing */
#define         ICMP_PHOTURIS_UNKNOWN_INDEX     1       /* unknown sec index */
#define         ICMP_PHOTURIS_AUTH_FAILED       2       /* auth failed */
#define         ICMP_PHOTURIS_DECRYPT_FAILED    3       /* decrypt failed */
#define ICMP6_DST_UNREACH_BEYONDSCOPE   2       /* beyond scope of source address */
#define ND_REDIRECT_ONLINK      0       /* redirect to an on-link node */
#define ND_REDIRECT_ROUTER      1       /* redirect to a better router */


#define GID_MAX         UINT_MAX        /* max value for a gid_t */
#define UID_MAX         UINT_MAX        /* max value for a uid_t */

#define SIZE_T_MAX      __SIZE_T_MAX    /* max value for a size_t */

// This depends on the arch, so this must be ported in other manner
#define       __SIZE_T_MAX    __UINT_MAX      /* max value for a size_t */
#define       __UINT_MAX      0xffffffffU     /* max value for an unsigned int */

#define    ICMP_ALTHOSTADDR        6               /* alternate host address */

#define       HTONL(x)        (x) = htonl((__uint32_t)(x))

#if _BYTE_ORDER == _LITTLE_ENDIAN

#define be64toh(x)      bswap64((x))
#else /* _BYTE_ORDER != _LITTLE_ENDIAN */

#define be64toh(x)      ((uint64_t)(x))
#endif /* _BYTE_ORDER == _LITTLE_ENDIAN */

#define bswap64(x)      __bswap64(x)

extern time_t time (time_t *__timer) __THROW;


static __inline __uint64_t
__bswap64(__uint64_t _x)
{
        return ((_x >> 56) | ((_x >> 40) & 0xff00) | ((_x >> 24) & 0xff0000) |
            ((_x >> 8) & 0xff000000) | ((_x << 8) & ((__uint64_t)0xff << 32)) |
            ((_x << 24) & ((__uint64_t)0xff << 40)) |
            ((_x << 40) & ((__uint64_t)0xff << 48)) | ((_x << 56)));
}


size_t strlcpy(char *dst, const char *src, size_t siz);
size_t strlcat(char *dst, const char *src, size_t siz);
char * fgetln(FILE *fp, size_t *lenp);

u_int32_t arc4random(void);


struct __sbuf {
        unsigned char *_base;
        int     _size;
};


// Directly from FreeBSD stdio.h

//#define    __SMOD  0x2000          /* true => fgetln modified _p text */
//#define    __SLBF  0x0001          /* line buffered */
//#define    __SWR   0x0008          /* OK to write */
//#define    __SEOF  0x0020          /* found EOF */
//#define    __SRD   0x0004          /* OK to read */
//#define    __SRW   0x0010          /* open for reading & writing */
//#define    __SERR  0x0040          /* found error */
//#define    __SNBF  0x0002          /* unbuffered */
//#define    __SIGN  0x8000          /* ignore this file in _fwalk */

#endif
