#include "philo.h"

U_LLINT 	get_cur_time()
{
	static struct timeval	first_time;
	struct timeval 	tv;
	struct timeval	diff;

	gettimeofday(&tv, NULL);
	if (!first_time.tv_usec && !first_time.tv_sec)
	{
		timersub(&tv, &first_time, &diff);
		return (diff.tv_sec * 1000 + diff.tv_usec / 1000);
	}
	first_time.tv_usec = tv.tv_usec;
	first_time.tv_sec = tv.tv_sec;
	return (0);
}
