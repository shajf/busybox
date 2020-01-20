
#include "utils.h"

const char *file_basename(const char *filename) {

    const char *p;

    if (is_empty(filename)) 
        return NULL;

     p = strrchr(filename, '/');
     if (p != NULL)
        return p+1;

     return filename;
 }

void file_base_dir(char *b,int max,const char *fname){

    snprintf(b,max,"%s",fname);

    char *p = strrchr(b, '/');

    if(p!=NULL) 
        *p = 0;

}

int dir_make_r(const char *orig_path)
{
	char *s;
	char c;
	struct stat st;

    char path[1024]={0};

    char *p = strrchr(orig_path,'/');

    if(p==NULL) return 0;

    memcpy(path,orig_path,p-orig_path);

    s = path;

	while (1) {
		c = '\0';

        /* Bypass leading non-'/'s and then subsequent '/'s. */
        while (*s) {
            if (*s == '/') {
                do {
                    ++s;
                } while (*s == '/');
                c = *s; /* Save the current char */
                *s = '\0'; /* and replace it with nul. */
                break;
            }
            ++s;
        }

		if (mkdir(path, 0777) < 0) {
			/* If we failed for any other reason than the directory
			 * already exists, output a diagnostic and return -1. */
			if (errno != EEXIST
			 || ((stat(path, &st) < 0) || !S_ISDIR(st.st_mode))
			) {
				break;
			}
			/* Since the directory exists, don't attempt to change
			 * permissions if it was the full target.  Note that
			 * this is not an error condition. */
			if (!c) {
				return 0;
			}
		}

		if (!c) {
			/* Done. */
			return 0;
		}

		/* Remove any inserted nul from the path (recursive mode). */
		*s = c;
	} /* while (1) */

	return -1;
}

