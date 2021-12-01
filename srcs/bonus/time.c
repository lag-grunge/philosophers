#include "philo_bonus.h"

int get_cur_time(t_rules *rules, int start)
{
	struct timeval 	tv;

	gettimeofday(&tv, NULL);
	if (!start)
		return ((int)(tv.tv_sec * 1000 + tv.tv_usec / 1000 - rules->start_time));
	rules->start_time = tv.tv_usec / 1000 +  tv.tv_sec * 1000;
	return (0);
}
