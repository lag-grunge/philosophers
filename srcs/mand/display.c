#include "philo.h"

void display_message(U_LLINT timestamp, t_philo *philo, int msg)
{
	pthread_mutex_lock(philo->rules->dashboard);
	if (msg == eat)
		printf("%llu %d  eat\n", timestamp, philo->id);
	else if (msg == slp)
		printf("%llu %d  sleep\n", timestamp, philo->id);
	else if (msg == thnk)
		printf("%llu %d  thinks\n", timestamp, philo->id);
	else if (msg == die)
		printf("%llu %d  dies\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	if (msg == die)
	{
		pthread_mutex_destroy(philo->rules->dashboard);
		free(philo->rules->dashboard);
	}
}

