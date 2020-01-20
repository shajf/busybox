#ifndef COLLECT_FILE_H
#define COLLECT_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "audit_time.h"

#define COLLECT_FILES_DIR "/tmp/collect"
#define COLLECT_FILE_NAME_LIMITS 256

struct collect_file {
    FILE *fp;
    char fname[COLLECT_FILE_NAME_LIMITS];
}; 


int collect_file_init(struct collect_file *cfile,const char *dir,const char *fname);

void collect_file_close(struct collect_file *cfile);

void collect_file_append(struct collect_file *cfile,char *data,size_t dsize);


#endif /*COLLECT_FILE_H*/
