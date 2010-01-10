/*
 * Copyright © 2006 Robert Millan
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

#include <bsd/err.h>
#include <errno.h>
#include <stdarg.h>

void
warnc(int code, const char *format, ...)
{
	int tmp = errno;
	va_list ap;

	va_start(ap, format);

	errno = code;
	warn(format, ap);
	errno = tmp;

	va_end(ap);
}

void
vwarnc(int code, const char *format, va_list ap)
{
	int tmp = errno;

	errno = code;
	vwarn(format, ap);
	errno = tmp;
}

void
errc(int status, int code, const char *format, ...)
{
	va_list ap;

	va_start(ap, format);

	errno = code;
	err(status, format, ap);

	va_end(ap);
}

void
verrc(int status, int code, const char *format, va_list ap)
{
	errno = code;
	verr(status, format, ap);
}
