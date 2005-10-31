#ifndef LIBBSD_STRING_H
#define LIBBSD_STRING_H

#include <sys/types.h>
#include <stdio.h>

size_t strlcpy(char *dst, const char *src, size_t siz);
size_t strlcat(char *dst, const char *src, size_t siz);
char *fgetln(FILE *fp, size_t *lenp);

#endif
