#include "philo.h"

void eating(t_philo *philo)
{
	int timestamp;

	timestamp = get_cur_time(philo->rules, 0);
	philo->last_eat_start = timestamp;
	display_message(timestamp, philo, eat);
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void sleeping(t_philo *philo)
{
	int timestamp;

	timestamp = get_cur_time(philo->rules, 0);
	display_message(timestamp, philo, slp);
	usleep(philo->rules->time_to_sleep * 1000);
}


void trying_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
}

void thinking(t_philo *philo)
{
	int timestamp;

	timestamp = get_cur_time(philo->rules, 0);
	display_message(timestamp, philo, thnk);
}

int is_living(t_philo *philo)
{
	if (philo->rules->someone_dead)
		return (0);
	if (philo->rules->time_to_die <= \
		get_cur_time(philo->rules, 0) - philo->last_eat_start)
	{
		philo->rules->someone_dead = 1;
		return (0);
	}
	return (1);
}
