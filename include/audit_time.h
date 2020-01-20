#ifndef AUDIT_TIME_H
#define AUDIT_TIME_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <errno.h>

typedef int64_t audit_time_t;

struct audit_time_exp {
    /** microseconds past tm_sec */
    int tm_usec;
    /** (0-61) seconds past tm_min */
    int tm_sec;
    /** (0-59) minutes past tm_hour */
    int tm_min;
    /** (0-23) hours past midnight */
    int tm_hour;
    /** (1-31) day of the month */
    int tm_mday;
    /** (0-11) month of the year */
    int tm_mon;
    /** year since 1900 */
    int tm_year;
    /** (0-6) days since Sunday */
    int tm_wday;
    /** (0-365) days since January 1 */
    int tm_yday;
    /** daylight saving time */
    int tm_isdst;

};

/**
 * Formats the exploded time according to the format specified
 * @param s string to write to
 * @param retsize The length of the returned string
 * @param max The maximum length of the string
 * @param format The format for the time string
 * @param tm The time to convert
 */
int audit_strftime(char *s, int *retsize, int max, const char *format, struct audit_time_exp *tm);

int audit_strftime_now(char *s,int max,const char *format);

audit_time_t audit_time_now(void);

unsigned long audit_time_now_ms(void);

/**
 * Convert a time to its human readable components in the local timezone.
 * @param result the exploded time
 * @param input the time to explode
 */
int audit_time_exp_lt(struct audit_time_exp *result,audit_time_t input);


#endif 
