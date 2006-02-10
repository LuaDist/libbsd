#ifndef LIBBSD_ERR_H
#define LIBBSD_ERR_H

#include <err.h>

extern void warnc (int code, const char *format, ...);
extern void vwarnc (int code, const char *format, va_list ap);
extern void errc (int status, int code, const char *format, ...);
extern void verrc (int status, int code, const char *format, va_list ap);

#endif
