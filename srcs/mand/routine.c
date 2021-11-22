#include "philo.h"

void eating(t_philo *philo)
{
	time_t timestamp;

	timestamp = get_cur_time();
	philo->last_eat_start = timestamp;
	display_message(timestamp, philo, eat);
	usleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void sleeping(t_philo *philo)
{
	time_t timestamp;

	timestamp = get_cur_time();
	display_message(timestamp, philo, slp);
	usleep(philo->rules->time_to_sleep);
}

void thinking(t_philo *philo)
{
	time_t timestamp;

	timestamp = get_cur_time();
	display_message(timestamp, philo, thnk);
}
