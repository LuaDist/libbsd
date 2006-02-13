/*
 * util.c --- utilities for the debugfs program
 * 
 * Copyright (C) 1993, 1994 Theodore Ts'o.  This file may be
 * redistributed under the terms of the GNU Public License.
 *
 */

/* Enable getopt variables */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif

#include <unistd.h>

/* FIXME */
#ifndef __GLIBC__
# define HAVE_OPTRESET 1
#endif

/*
 * This function resets the libc getopt() function, which keeps
 * internal state.  Bad design!  Stupid libc API designers!  No
 * biscuit!
 *
 * BSD-derived getopt() functions require that optind be reset to 1 in
 * order to reset getopt() state.  This used to be generally accepted
 * way of resetting getopt().  However, glibc's getopt()
 * has additional getopt() state beyond optind, and requires that
 * optind be set zero to reset its state.  So the unfortunate state of
 * affairs is that BSD-derived versions of getopt() misbehave if
 * optind is set to 0 in order to reset getopt(), and glibc's getopt()
 * will core ump if optind is set 1 in order to reset getopt().
 * 
 * More modern versions of BSD require that optreset be set to 1 in
 * order to reset getopt().   Sigh.  Standards, anyone?
 *
 * We hide the hair here.
 */
void
reset_getopt (void)
{
#ifdef __GLIBC__
  optind = 0;
#else
  optind = 1;
#endif
#ifdef HAVE_OPTRESET
  optreset = 1;			/* Makes BSD getopt happy */
#endif
}
