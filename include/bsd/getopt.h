#ifndef LIBBSD_GETOPT_H
#define LIBBSD_GETOPT_H

#include <getopt.h>

extern int optreset;

int bsd_getopt (int, char **, char *);

#endif
