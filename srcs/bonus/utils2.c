#include "philo_bonus.h"

int kill_em(t_dinner *dinner)
{
	int 	i;

	i = 0;
	while (i < dinner->philo_num)
	{
		kill(dinner->philos[i].pid, SIGTERM);
		i++;
	}
	return (0);
}
