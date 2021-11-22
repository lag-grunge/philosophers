#include "philo.h"

time_t	calc_time(struct timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

time_t	get_cur_time()
{
	static time_t 	first_time;
	struct timeval 	*tv;

	gettimeofday(tv, NULL);
	if (first_time)
		return (calc_time(tv) - first_time);
	first_time = calc_time(tv);
	return (0);
}
