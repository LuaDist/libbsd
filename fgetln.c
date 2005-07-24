
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
	size_t leido = 0;
	
	while (leido == 1) {
	if ((leido = getline (&line, len, stream)) == -1)
		return NULL;
	}

//	if (*(line+leido) != '\n')
//	if (leido != 0)
		(*len)--; /* get rid of the trailing \0, fgetln
			     does not have it */
//	if (leido == 1)
//		leido = getline (&line, len, stream);

//	printf ("Caracter '%c' - Leido '%d'\n", *(line+leido-1), leido);
	return line;
}
#endif
