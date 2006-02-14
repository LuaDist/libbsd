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

#include <bsd/err.h>
#include <errno.h>
#include <stdarg.h>

void
warnc (int code, const char *format, ...)
{
  int tmp = errno;
  va_list ap;
  va_start (ap, format);

  errno = code;
  warn (format, ap);
  errno = tmp;

  va_end (ap);
}

void
vwarnc (int code, const char *format, va_list ap)
{
  int tmp = errno;

  errno = code;
  vwarn (format, ap);
  errno = tmp;
}

void
errc (int status, int code, const char *format, ...)
{
  va_list ap;
  va_start (ap, format);

  errno = code;
  err (status, format, ap);

  va_end (ap);
}

void
verrc (int status, int code, const char *format, va_list ap)
{
  errno = code;
  verr (status, format, ap);
}
