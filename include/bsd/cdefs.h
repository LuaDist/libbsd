#ifndef LIBBSD_CDEFS_H
#define LIBBSD_CDEFS_H

#include <sys/cdefs.h>

#ifndef setproctitle
# define setproctitle(fmt, args...)
#endif

#ifndef __dead2
# define __dead2
#endif

/* Linux headers define a struct with a member names __unused.
 * Disable for now. */
#if 0
#ifndef __unused
# ifdef __GNUC__
#  define __unused __attribute__((unused))
# else
#  define __unused
# endif
#endif
#endif

#ifndef __printflike
# ifdef __GNUC__
#  define __printflike(x, y) __attribute((format(printf, (x), (y))))
# else
#  define __printflike(x, y)
# endif
#endif

#ifndef __FBSDID
# define __FBSDID(x)
#endif

#endif
