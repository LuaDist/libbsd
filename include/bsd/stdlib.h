#ifndef LIBBSD_STDLIB_H
#define LIBBSD_STDLIB_H

#include <stdlib.h>

const char *fmtcheck (const char *, const char *);

char *getprogname ();
void setprogname (char *);

int heapsort (void *, size_t, size_t, int (*)(const void *, const void *));

#endif
