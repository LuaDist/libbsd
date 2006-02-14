#include <bsd/getopt.h>

int optreset = 0;

int
bsd_getopt (int argc, char **argv, char *shortopts)
{
  if (optreset == 1)
    {
      optreset = 0;
      optind = 0;
    }

  return getopt (argc, argv, shortopts);
}
