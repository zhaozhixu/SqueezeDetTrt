#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <err.h>

#include "path_alloc.h"

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

/* if PATH_MAX is indeterminate, no guarantee this is adequate */
#define PATH_MAX_GUESS 1024

char *path_alloc(size_t *sizep)
{
     char *ptr;
     size_t size;

     if (posix_version == 0)
          posix_version = sysconf(_SC_VERSION);

     if (xsi_version == 0)
          xsi_version = sysconf(_SC_XOPEN_VERSION);

     if (pathmax == 0) {          /* first time through */
          errno = 0;
          if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
               if (errno == 0)
                    pathmax = PATH_MAX_GUESS;
               else
                    err(EXIT_FAILURE, "pathconf error for _PC_PATH_MAX");
          } else {
               pathmax++;
          }
     }

     /*
      * Before PASIX.1-2001, we aren't guaranteed that PATH_MAX includes
      * the terminating null byte. Same goes for XPG3.
      */
     if ((posix_version < 200112L) && (xsi_version < 4))
          size = pathmax + 1;
     else
          size = pathmax;

     if ((ptr = (char *)malloc(size)) == NULL)
          err(EXIT_FAILURE, "malloc error for pathname");

     if (sizep != NULL)
          *sizep = size;
     return ptr;
}
