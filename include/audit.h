#ifndef AUDIT_H
#define AUDIT_H 1

#include "audit_time.h"

#define AUDIT_LOG_DIR "/tmp/log/audit/"
#define AUDIT_LOG_FILE_LIMITS 256
#define AUDIT_LOG_BUFFER_LIMITS 1024
/*1 days*/
#define AUDIT_LOG_FILE_UPDATE_TMS 86400000L 

struct audit_file {

    FILE *fp;
    unsigned long create_time;
    char fprefix[64];
};

int audit_file_init(struct audit_file *afile,const char *fprefix);

void audit(struct audit_file *afile,const char *fmt,...);

void audit_cmd(struct audit_file *afile,int argc,char **argv);

void audit_file_close(struct audit_file *afile);

#endif /*AUDIT_H*/
