#include "philo.h"

void display_message(int timestamp, t_philo *philo, int msg)
{
	pthread_mutex_lock(philo->rules->dashboard);
	if (philo->rules->stop)
	{
		if (msg == die)
			printf("%d %d died\n", timestamp, philo->id);
		else if (msg == lim)
			printf("%d philosophers has eaten at least %d\n", timestamp, philo->rules->limit_eats);
		pthread_mutex_unlock(philo->rules->dashboard);
		return ;
	}
	else if (msg == frk1 || msg == frk2)
		printf("%d %d has taken a fork\n", timestamp, philo->id);
	else if (msg == eat)
		printf("%d %d is eating\n", timestamp, philo->id);
	else if (msg == slp)
		printf("%d %d is sleeping\n", timestamp, philo->id);
	else if (msg == thnk)
		printf("%d %d is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
}
