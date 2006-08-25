#ifndef _LIBUTIL_H_
#define _LIBUTIL_H_

#include <features.h>
#include <sys/types.h>


__BEGIN_DECLS
int humanize_number(char *buf, size_t len, int64_t bytes,
    const char *suffix, int scale, int flags);
__END_DECLS

/* humanize_number(3) */
#define HN_DECIMAL              0x01
#define HN_NOSPACE              0x02
#define HN_B                    0x04
#define HN_DIVISOR_1000         0x08

#define HN_GETSCALE             0x10
#define HN_AUTOSCALE            0x20

#endif /* !_LIBUTIL_H_ */
