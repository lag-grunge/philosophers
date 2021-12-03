#include "philo_bonus.h"

void eating(void *args)
{
	int timestamp;
	t_philo *philo;

	philo = args;
	timestamp = get_cur_time(philo->rules, 0);
	philo->last_eat_start = timestamp;
	display_message(timestamp, philo, eat);
	usleep(philo->rules->time_to_eat * 1000);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void sleeping(void *args)
{
	int timestamp;
	t_philo *philo;

	philo = args;
	timestamp = get_cur_time(philo->rules, 0);
	display_message(timestamp, philo, slp);
	usleep(philo->rules->time_to_sleep * 1000);
}

void trying_forks(void *args)
{
	t_philo *philo;


	philo = args;
	sem_wait(philo->forks);
	display_message(get_cur_time(philo->rules, 0), philo, frk1);
}

void thinking(void *args)
{
	t_philo *philo;
	int timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules, 0);
	display_message(timestamp, philo, thnk);
}
