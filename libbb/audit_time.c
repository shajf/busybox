#include "audit_time.h"

#define AUDIT_TIME_USEC_PER_SEC 1000000L

/**
 * Formats the exploded time according to the format specified
 * @param s string to write to
 * @param retsize The length of the returned string
 * @param max The maximum length of the string
 * @param format The format for the time string
 * @param tm The time to convert
 */
int audit_strftime(char *s, int *retsize, int max, const char *format, struct audit_time_exp *xt){

    struct tm tm;
    memset(&tm, 0, sizeof tm);
    tm.tm_sec  = xt->tm_sec;
    tm.tm_min  = xt->tm_min;
    tm.tm_hour = xt->tm_hour;
    tm.tm_mday = xt->tm_mday;
    tm.tm_mon  = xt->tm_mon;
    tm.tm_year = xt->tm_year;
    tm.tm_wday = xt->tm_wday;
    tm.tm_yday = xt->tm_yday;
    tm.tm_isdst = xt->tm_isdst;
    (*retsize) = strftime(s, max, format, &tm);
    
    return 0;

}

int audit_strftime_now(char *s,int max,const char *format){

    struct audit_time_exp lt;

    int len;

    audit_time_exp_lt(&lt,audit_time_now());

    audit_strftime(s,&len,max,format,&lt);

    return 0;
}

audit_time_t audit_time_now(void){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * AUDIT_TIME_USEC_PER_SEC + tv.tv_usec;
}

unsigned long audit_time_now_ms(void){

    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;                
}

/**
 * Convert a time to its human readable components in the local timezone.
 * @param result the exploded time
 * @param input the time to explode
 */
int audit_time_exp_lt(struct audit_time_exp *result,audit_time_t input){

    struct tm tm;
    time_t tt = (input / AUDIT_TIME_USEC_PER_SEC);
    result->tm_usec = input % AUDIT_TIME_USEC_PER_SEC;

    tm = *localtime(&tt);

    result->tm_sec  = tm.tm_sec;
    result->tm_min  = tm.tm_min;
    result->tm_hour = tm.tm_hour;
    result->tm_mday = tm.tm_mday;
    result->tm_mon  = tm.tm_mon;
    result->tm_year = tm.tm_year;
    result->tm_wday = tm.tm_wday;
    result->tm_yday = tm.tm_yday;
    result->tm_isdst = tm.tm_isdst;

    return 0;
}


