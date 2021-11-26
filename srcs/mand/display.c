#include "philo.h"

void display_message(int timestamp, t_philo *philo, int msg)
{
	pthread_mutex_lock(philo->rules->dashboard);
	if (msg == eat)
		printf("%d ms %d eating\n", timestamp, philo->id);
	else if (msg == slp)
		printf("%d ms %d sleeping\n", timestamp, philo->id);
	else if (msg == thnk)
		printf("%d ms %d thinking\n", timestamp, philo->id);
	else if (msg == die)
		printf("%d ms %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
}
