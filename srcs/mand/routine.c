#include "philo.h"

void eating(t_philo *philo)
{
	U_LLINT timestamp;

	timestamp = get_cur_time();
	philo->last_eat_start = timestamp;
	display_message(timestamp, philo, eat);
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void sleeping(t_philo *philo)
{
	U_LLINT timestamp;

	timestamp = get_cur_time();
	display_message(timestamp, philo, slp);
	usleep(philo->rules->time_to_sleep * 1000);
}

void thinking(t_philo *philo)
{
	U_LLINT timestamp;

	timestamp = get_cur_time();
	display_message(timestamp, philo, thnk);
}

int dying(t_philo *philo)
{
	return (philo->rules->time_to_die <= \
			(int) (get_cur_time() - philo->last_eat_start));
}
