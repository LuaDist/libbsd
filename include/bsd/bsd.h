/*
 * Copyright (C) 2004, 2005, 2006 Guillem Jover
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
