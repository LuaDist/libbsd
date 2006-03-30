/* Copyright (C) 2006 Robert Millan

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.  */

/* 
  Rejected in glibc (http://sourceware.org/ml/libc-alpha/2006-03/msg00125.html)
*/

#include <bsd/stdlib.h>		/* progname, strdup */
#include <string.h>		/* free */

char *__progname = NULL;

char *
getprogname ()
{
  return __progname;
}

void
setprogname (char *new)
{
  /* For some reason, accessing the argv vector directly may cause SIGSEV.  Let's copy it to avoid trouble. */

  if (__progname != NULL)
    free (__progname);

  __progname = strdup (new);
}
