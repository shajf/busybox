
#include "collect_file.h"

int collect_file_init(struct collect_file *cfile,const char *dir,const char *fname){

    if(is_empty(dir))
        dir = "/";

    if(is_empty(fname)){

        snprintf(cfile->fname,COLLECT_FILE_NAME_LIMITS,"%s%s/%lu",COLLECT_FILES_DIR,dir,audit_time_now_ms());
    }else{
        snprintf(cfile->fname,COLLECT_FILE_NAME_LIMITS,"%s%s/%s",COLLECT_FILES_DIR,dir,fname);
    }

    dir_make_r(cfile->fname);

    cfile->fp = fopen(cfile->fname,"a+");

    return cfile->fp?0:-1;
}


void collect_file_close(struct collect_file *cfile){

    if(cfile->fp){

        fclose(cfile->fp);
        cfile->fp = NULL;
    }


}

void collect_file_append(struct collect_file *cfile,char *data,size_t dsize){

    fwrite((const void*)data,dsize,1,cfile->fp);
    fflush(cfile->fp);

}
