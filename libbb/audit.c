
#include "audit.h"
#include "utils.h"

#define make_fname(afile,bfile,max) \
    snprintf(bfile,max,"%s%s",AUDIT_LOG_DIR,afile->fprefix); 

static void update_audit_file(struct audit_file *afile){

    char nname[1024] = {0};
    char oname[1024] = {0};
    char tstr[256] = {0};

    unsigned long curtime = audit_time_now_ms();

    if(curtime-afile->create_time<AUDIT_LOG_FILE_UPDATE_TMS)
        return;

    make_fname(afile,oname,1024);

    audit_strftime_now(tstr,256,"%Y-%m-%d");
    snprintf(nname,1023,"%s/%s.%s",AUDIT_LOG_DIR,afile->fprefix,tstr);

    fclose(afile->fp);
    rename(oname,nname);

    afile->fp = fopen(oname,"a+");
    afile->create_time = curtime;
}

int audit_file_init(struct audit_file *afile,const char *fprefix){

    char fname[1024] = {0};

    if(is_empty(fprefix)||strlen(fprefix)>=64)
        return -1;

    snprintf(afile->fprefix,64,"%s",fprefix);

    make_fname(afile,fname,1024);

    dir_make_r(fname);

    afile->fp = fopen(fname,"a+");

    if(afile->fp == NULL){
        
        fprintf(stderr,"Cannot open file:%s to audit!\n",fname);
        fflush(stderr);

        return -1;
    }

    afile->create_time = audit_time_now_ms();

    return 0;
}

void audit(struct audit_file *afile,const char *fmt,...){

    va_list args;

    char fmt_buf[AUDIT_LOG_BUFFER_LIMITS]={0};
    char tstr[256] = {0};

    //update_audit_file(afile);
    if(afile->fp == NULL){
        return;
    }

    audit_strftime_now(tstr,256,"%Y-%m-%d %H:%M:%S");

    va_start(args,fmt);
    vsnprintf (fmt_buf,AUDIT_LOG_BUFFER_LIMITS,fmt, args);
    va_end(args);

    fprintf(afile->fp,"[%s][%d] %s\n",tstr,getpid(),fmt_buf);
    fflush(afile->fp);

}

void audit_cmd(struct audit_file *afile,int argc,char **argv){

    char argv_str[AUDIT_LOG_BUFFER_LIMITS] = {0};
    char *p = argv_str;
    char *pend = argv_str+AUDIT_LOG_BUFFER_LIMITS;
    int i;
    int len;

    if(argc ==1){
        audit(afile,"cmd:%s args:none",argv[0]);
        return;
    }

    for(i = 1;i<argc;i++){

        len = strlen(argv[i]);

        if(p+len+1>=pend)
            break;

        memcpy(p," ",1);
        p+=1;
        memcpy(p,argv[i],len);
        p+=len;
    }

    audit(afile,"cmd:%s args:%s",argv[0],argv_str);

}

void audit_file_close(struct audit_file *afile){

    if(afile->fp == NULL)
        return;
    fclose(afile->fp);
    afile->fp = NULL;
}

