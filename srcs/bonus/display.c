#include "philo_bonus.h"

void display_message(int timestamp, t_philo *philo, int msg)
{
	pthread_mutex_lock(philo->rules->dashboard);
	if (philo->rules->someone_dead)
	{
		if (msg == die)
			printf("%d ms %d died\n", timestamp, philo->id);
		pthread_mutex_unlock(philo->rules->dashboard);
		return ;
	}
	else if (msg == l_fork)
		printf("%d ms %d has taken left fork\n", timestamp, philo->id);
	else if (msg == r_fork)
		printf("%d ms %d has taken right fork\n", timestamp, philo->id);
	else if (msg == eat)
		printf("%d ms %d is eating\n", timestamp, philo->id);
	else if (msg == slp)
		printf("%d ms %d is sleeping\n", timestamp, philo->id);
	else if (msg == thnk)
		printf("%d ms %d is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
}
