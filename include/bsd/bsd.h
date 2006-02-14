#ifndef LIBBSD_H
#define LIBBSD_H

/*
 * Include all bsd compat headers.
 */

#include <bsd/cdefs.h>
#include <bsd/random.h>
#include <bsd/string.h>
#include <bsd/queue.h>
#include <bsd/ip_icmp.h>

/*
 * Stuff to be moved.
 */

#include <sys/types.h>

typedef char *                  __va_list;
#if !defined(__GNUC_VA_LIST)
#define __GNUC_VA_LIST
typedef __va_list               __gnuc_va_list; /* compatibility w/ GNU headers */
#endif

extern time_t time (time_t *__timer) __THROW;

struct __sbuf {
        unsigned char *_base;
        int     _size;
};

#define MLD_LISTENER_QUERY              130     /* multicast listener query */
#define MLD_LISTENER_REPORT             131     /* multicast listener report */
#define MLD_LISTENER_DONE               132     /* multicast listener done */
#define ICMP6_ROUTER_RENUMBERING        138     /* router renumbering */
#define ICMP6_WRUREQUEST                139     /* who are you request */
#define ICMP6_WRUREPLY                  140     /* who are you reply */
#define ICMP6_FQDN_QUERY                139     /* FQDN query */
#define ICMP6_FQDN_REPLY                140     /* FQDN reply */
#define ICMP6_NI_QUERY                  139     /* node information request */
#define ICMP6_NI_REPLY                  140     /* node information reply */
#define MLD_MTRACE_RESP                 200     /* mtrace resp (to sender) */
#define MLD_MTRACE                      201     /* mtrace messages */
#define ICMP6_DST_UNREACH_BEYONDSCOPE   2       /* beyond scope of source address */
#define ND_REDIRECT_ONLINK      0       /* redirect to an on-link node */
#define ND_REDIRECT_ROUTER      1       /* redirect to a better router */

/*
 * Limits.
 */

#define GID_MAX         UINT_MAX        /* max value for a gid_t */
#define UID_MAX         UINT_MAX        /* max value for a uid_t */

#define SIZE_T_MAX      __SIZE_T_MAX    /* max value for a size_t */

// This depends on the arch, so this must be ported in other manner
#define       __SIZE_T_MAX    __UINT_MAX      /* max value for a size_t */
#define       __UINT_MAX      0xffffffffU     /* max value for an unsigned int */

/*
 * Endianness.
 */

#define       HTONL(x)        (x) = htonl((__uint32_t)(x))

#if _BYTE_ORDER == _LITTLE_ENDIAN
#define be64toh(x)      bswap64((x))
#else /* _BYTE_ORDER != _LITTLE_ENDIAN */
#define be64toh(x)      ((uint64_t)(x))
#endif /* _BYTE_ORDER == _LITTLE_ENDIAN */

#define bswap64(x)      __bswap64(x)

static __inline __uint64_t
__bswap64(__uint64_t _x)
{
        return ((_x >> 56) | ((_x >> 40) & 0xff00) | ((_x >> 24) & 0xff0000) |
            ((_x >> 8) & 0xff000000) | ((_x << 8) & ((__uint64_t)0xff << 32)) |
            ((_x << 24) & ((__uint64_t)0xff << 40)) |
            ((_x << 40) & ((__uint64_t)0xff << 48)) | ((_x << 56)));
}

#endif
