#include "philo.h"

void stop_dinner(t_dinner *dinner, int started_threads)
{
	int	i;
	i = started_threads;
	while (i > 0)
	{
		pthread_join(dinner->philos[i].thread_id, NULL);
		i--;
	}
}