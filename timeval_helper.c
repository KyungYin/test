#include "timeval_helper.h"

static void
_timeval_adjust(struct timeval* pTime)
{
	while(pTime->tv_usec >= USEC_PER_SEC)
	{
		pTime->tv_usec -= USEC_PER_SEC;
		pTime->tv_sec++;
	}

	while(pTime->tv_usec < 0)
	{
		pTime->tv_usec += USEC_PER_SEC;
		pTime->tv_sec--;
	}

	if(pTime->tv_sec < 0)
	{
		pTime->tv_sec = 0;
		pTime->tv_usec = 100;
	}
//  TBD. Is need to check overflow ????	
//	if(pTime->tv_sec > USEC_PER_SEC)
//		pTime->tv_sec = USEC_PER_SEC;
}

struct timeval* timeval_add(struct timeval* pRet, const struct timeval* pTime1, const struct timeval* pTime2)
{
	pRet->tv_usec = pTime1->tv_usec + pTime2->tv_usec;
	pRet->tv_sec = pTime1->tv_sec   + pTime2->tv_sec;

	_timeval_adjust(pRet);
	
	return pRet;
}

struct timeval* timeval_sub(struct timeval* pRet, const struct timeval* pTime1, const struct timeval* pTime2)
{
	pRet->tv_usec = pTime1->tv_usec - pTime2->tv_usec;
	pRet->tv_sec = pTime1->tv_sec   - pTime2->tv_sec;

	_timeval_adjust(pRet);
	
	return pRet;
}

struct timeval* timeval_elapsed(struct timeval* result, const struct timeval* startTime)
{
	gettimeofday(result, NULL);

	result->tv_sec -= startTime->tv_sec;
	result->tv_usec -= startTime->tv_usec;

	_timeval_adjust(result);

	return result;
}


long timeval_diff(struct timeval* pTime1, struct timeval* pTime2)
{
	long nSec = pTime1->tv_sec - pTime2->tv_sec;
	long nUSec = pTime1->tv_usec - pTime2->tv_usec;

	return (nSec * 1000) + (nUSec / 1000);
}

void timeval_append(struct timeval* pTime, long ms)
{
	pTime->tv_usec += (ms%1000) * 1000;
	pTime->tv_sec += ms/1000;
	
	_timeval_adjust(pTime);
}

#define TEST_MAIN
#ifdef TEST_MAIN
int main(int argc, char* argv[])
{
	struct timeval start;
	struct timeval result;

	gettimeofday(&start, NULL);

	usleep(2500 * 1000);

	timeval_elapsed(&result, &start);

	printf("After %d sec %d msec\n", result.tv_sec, result.tv_usec / 1000);
	return 0;
}
#endif
