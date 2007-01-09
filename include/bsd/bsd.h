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
#include <time.h>

/*
 * Stuff to be moved.
 */

#define __BSD_VISIBLE	1
#define __XSI_VISIBLE	1 
#include <sys/limits.h>

#include <sys/types.h>

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

#endif
