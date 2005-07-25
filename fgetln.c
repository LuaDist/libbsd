
#include <stdio.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <string.h>

#ifdef __GLIBC__
char *
fgetln (stream, len)
	FILE *stream;
	size_t *len;
{
	char *line=NULL;
	size_t nread = 0;

	while (nread == 1) {
		nread = getline (&line, len, stream);
		if (nread == -1)
			return NULL;
	}

	(*len)--; /* get rid of the trailing \0, fgetln
		     does not have it */

	return line;
}
#endif

