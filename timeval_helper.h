#ifndef __TIMEVAL_HELPER_H_
#define __TIMEVAL_HELPER_H_

#include <stdio.h>
#include <sys/time.h>

#ifndef USEC_PER_SEC 
#define USEC_PER_SEC 1000000L
#endif

struct timeval* timeval_add(struct timeval* pRet, const struct timeval* pTime1, const struct timeval* pTime2);
struct timeval* timeval_sub(struct timeval* pRet, const struct timeval* pTime1, const struct timeval* pTime2);
struct timeval* timeval_elapsed(struct timeval* result, const struct timeval* startTime);

long timeval_diff(struct timeval* pTime1, struct timeval* pTime2);
void timeval_append(struct timeval* pTime, long ms);


#endif // __TIMEVAL_HELPER_H_
