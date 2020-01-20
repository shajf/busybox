#ifndef UTILS_H
#define UTILS_H 1

#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define is_empty(str) ((str)==NULL || *str==0) 

int dir_make_r(const char *orig_path);

const char *file_basename(const char *filename);

void file_base_dir(char *b,int max,const char *fname);

#endif /*UTILS_H*/
